#include "match.hpp"
#include "expr.hpp"
#include "clause.hpp"
#include "type_variable.hpp"
#include "block.hpp"
#include "error_handler.hpp"
#include "constructor_pattern.hpp"
#include "pattern.hpp"
#include <sstream>
#include <iostream>
#include <memory>
    
Match::Match(Expr* expr, Block<Clause>* clause_list) : expr(expr), clause_list(clause_list), Expr(new TypeVariable(TypeTag::Unknown)) {

}

Match::~Match() {
    delete expr;
    delete clause_list;
}


void Match::print(std::ostream &out) const {
    out << "Match(";
    out << "Type: ";
    if(type_variable != nullptr)
        type_variable->print(out);
    else
        out << "null ";
    out << " Clause_list: ";
    if(clause_list != nullptr)
        clause_list->print(out);
    else
        out << "null ";
    out << ") ";
}

std::shared_ptr<TypeVariable> Match::infer() {
    auto expr_type = this->expr->infer();

    auto clauses =  this->clause_list->get_list();

    //At the start of each clause a new scope is opened and ids defined in the clauses pattern are in scope only in the clauses expression
    st->scope_open();

    //All patterns must be of same type t which matches the expr type
    auto clause_pattern_type = clauses[0]->infer_pattern();
    st->add_constraint(expr_type, clause_pattern_type, this->lineno);

    //All expressions must have the same type which is the same as the type of the match statement
    auto clause_expr_type = clauses[0]->infer_expression();
    st->add_constraint(this->type_variable, clause_expr_type, this->lineno);

    st->scope_close();

    for(auto clause_it = ++clauses.begin(); clause_it != clauses.end(); clause_it++) {
        st->scope_open();

        auto other_clause_pattern_type = (*clause_it)->infer_pattern();
        st->add_constraint(clause_pattern_type, other_clause_pattern_type, this->lineno);

        auto other_clause_expr_type = (*clause_it)->infer_expression();
        st->add_constraint(clause_expr_type, other_clause_expr_type, this->lineno);

        st->scope_close();
    }

    return this->type_variable;
}

void Match::sem() {
    this->expr->sem();

    auto clauses =  this->clause_list->get_list();

    for(auto clause_it = clauses.begin(); clause_it != clauses.end(); clause_it++) {
        st->scope_open();

        (*clause_it)->sem();

        st->scope_close();
    }

    //The expr type (and thus all pattern types) must be user_types
    if(sa->is_not_same_tag(this->expr->get_type(), TypeTag::UserType)) {
        error_handler->non_allowed_type(this->expr->get_type(), this->lineno, ErrorType::User, NodeType::Expr);
    }
}

llvm::Value* Match::codegen() {
    auto current_function = Builder.GetInsertBlock()->getParent();
    auto match_start = llvm::BasicBlock::Create(TheContext, "match_start", current_function);
    auto match_end = llvm::BasicBlock::Create(TheContext, "match_end");
    auto match_all_failed = llvm::BasicBlock::Create(TheContext, "match_all_failed");

    //match return value type
    auto match_return_type = map_to_llvm_type(this->type_variable);

    Builder.CreateBr(match_start);
    Builder.SetInsertPoint(match_start);

    //Get the value of the expression
    auto expr_value = this->expr->codegen();

    auto clauses =  this->clause_list->get_list();

    /*The patterns that can match constructors are of 2 types:
        1.Ids here we just store the pointer to the constructor in the id
        2.Constructors coming from the same user type. Since it is checked during inference
          that the constructor is correct then its type will match the type of a constructor of user type.
          
            2.1 if it is the same contructor that was used for the expr then there tag will be the same and we know
                the type of the constructor struct from the constructor pattern.
          
            2.2 if the tag is different the we have a type missmatch and nothing else needs to be checked. 
    */

    /*
        If one pattern fails just move on to the next pattern
        If all patterns fail then we reach end of pattern checks and branch to match_all_failed
        if one pattern succeeds then we branch to the expression for that pattern and execute it
    */

    std::vector<llvm::Value*> clause_expr_values;
    std::vector<llvm::BasicBlock*> clause_expr_BB;

    //Compare expression against every pattern
    for(auto clause_it = clauses.begin(); clause_it != clauses.end(); clause_it++) {
        st->scope_open();

        auto match_success = llvm::BasicBlock::Create(TheContext, "match_success");
        auto match_fail = llvm::BasicBlock::Create(TheContext, "match_fail"); 

        //Compare the expr_value with each pattern and find the first that matches
        auto pattern_value = (*clause_it)->codegen_pattern();

        match_expr_to_pattern(expr_value, pattern_value, match_success, match_fail, (*clause_it)->get_pattern(), (*clause_it)->get_clause_pattern_type());

        current_function->getBasicBlockList().push_back(match_success);
        Builder.SetInsertPoint(match_success);

        auto clause_expr_result = (*clause_it)->codegen_expression();
        clause_expr_values.push_back(clause_expr_result);
        clause_expr_BB.push_back(Builder.GetInsertBlock());

        Builder.CreateBr(match_end);

        //If this pattern failed then check the next pattern
        current_function->getBasicBlockList().push_back(match_fail);
        Builder.SetInsertPoint(match_fail);

        st->scope_close();
    }

    //If we reach this point all pattern checks have failed
    Builder.CreateBr(match_all_failed);

    //Throw runtime error if pattern was matched 
    current_function->getBasicBlockList().push_back(match_all_failed);
    Builder.SetInsertPoint(match_all_failed);

    std::stringstream msg;
    msg << "No match found in match expression at line " << this->lineno << ".\n";

    auto string_ptr = Builder.CreateGlobalStringPtr(msg.str());

    Builder.CreateCall(AST::runtime_error_function, { string_ptr });

    //Dummy value in case no pattern matched
    auto dummy_value_alloca = Builder.CreateAlloca(match_return_type, nullptr, "dummy_value_alloca");
    auto dummy_value = Builder.CreateLoad(dummy_value_alloca, "dummy_value"); 

    //Control flow will never reach this branch.
    Builder.CreateBr(match_end);

    //Rest of the code continuous from match_end
    current_function->getBasicBlockList().push_back(match_end);
    Builder.SetInsertPoint(match_end);

    auto phi_node = Builder.CreatePHI(match_return_type, clauses.size(), "match_expr_value");
    phi_node->addIncoming(dummy_value, match_all_failed);

    //Match result may come from any clause's expression value
    unsigned int i = 0;
    for(auto clause_expr_value: clause_expr_values) {
        phi_node->addIncoming(clause_expr_value, clause_expr_BB[i++]);
    }

    return phi_node;
}

void Match::match_expr_to_pattern(llvm::Value* expr_value, llvm::Value* pattern_value, llvm::BasicBlock* match_success, llvm::BasicBlock* match_fail, Pattern* current_pattern, PatternType pattern_type) {
    /*
        if this or a nested pattern match (for constructors) failed then the hole pattern match failed and we should jump to pattern match_failed BB
        
        if this branch succeeded then we branch to match_success
            if this is a full pattern then match_success == matched_full_pattern_success

            if this is a nested pattern called by a constructor then match_success == constructor_pattern_match_success 
            and we then check the next pattern argument of the constructor 
    */

    switch(pattern_type) {
        case PatternType::Int: {
            auto cmp_result = Builder.CreateICmp(llvm::CmpInst::Predicate::ICMP_EQ, expr_value, pattern_value);
            Builder.CreateCondBr(cmp_result, match_success, match_fail);
            break;
        }
        case PatternType::Float: {
            auto cmp_result = Builder.CreateFCmp(llvm::CmpInst::Predicate::FCMP_OEQ, expr_value, pattern_value);
            Builder.CreateCondBr(cmp_result, match_success, match_fail);
            break;
        }
        case PatternType::Bool: {
            auto cmp_result = Builder.CreateICmp(llvm::CmpInst::Predicate::ICMP_EQ, expr_value, pattern_value);
            Builder.CreateCondBr(cmp_result, match_success, match_fail);
            break;
        }
        case PatternType::Char: {
            auto cmp_result = Builder.CreateICmp(llvm::CmpInst::Predicate::ICMP_EQ, expr_value, pattern_value);
            Builder.CreateCondBr(cmp_result, match_success, match_fail);
            break;
        }
        case PatternType::Id: {
            Builder.CreateStore(expr_value, pattern_value);
            Builder.CreateBr(match_success);
            break;
        }
        case PatternType::Constructor: {
            auto constructor_pattern = dynamic_cast<ConstructorPattern*>(current_pattern);

            //Load tag of both constructors
            auto expr_tag_ptr = Builder.CreateBitCast(expr_value, llvm::PointerType::get(i32, 0), "expr_tag_ptr");
            auto expr_tag = Builder.CreateLoad(expr_tag_ptr, "expr_constr_tag");

            auto pattern_tag_ptr = Builder.CreateBitCast(pattern_value, llvm::PointerType::get(i32, 0), "pattern_tag_ptr");
            auto pattern_tag = Builder.CreateLoad(pattern_tag_ptr, "pattern_constr_tag");

            //Compare tags
            auto current_function = Builder.GetInsertBlock()->getParent();
            auto match_compare_constr_args_start = llvm::BasicBlock::Create(TheContext, "match_compare_constr_args_start");

            auto cmp_tags_result = Builder.CreateICmp(llvm::CmpInst::Predicate::ICMP_EQ, expr_tag, pattern_tag);
            Builder.CreateCondBr(cmp_tags_result, match_compare_constr_args_start, match_fail);

            //Create match_compare_constr_args BB
            current_function->getBasicBlockList().push_back(match_compare_constr_args_start);
            Builder.SetInsertPoint(match_compare_constr_args_start);

            //Cast the user type pointer to the actual struct type of the constructors
            auto expr_struct_ptr = Builder.CreateBitCast(expr_value, llvm::PointerType::get(constructor_pattern->get_matching_constructor_llvm_type(), 0), "expr_struct_ptr");
            auto pattern_struct_ptr = Builder.CreateBitCast(pattern_value, llvm::PointerType::get(constructor_pattern->get_pattern_constructor_llvm_type(), 0), "pattern_struct_ptr");

            auto pattern_list = constructor_pattern->get_pattern_list();

            unsigned int i = 1;
            for(auto constr_pattern_arg: pattern_list) {
                auto match_compare_constr_args = llvm::BasicBlock::Create(TheContext, "match_compare_constr_args", current_function);
                auto match_compare_constr_args_success = llvm::BasicBlock::Create(TheContext, "match_compare_constr_args_success");
                
                Builder.CreateBr(match_compare_constr_args);
                Builder.SetInsertPoint(match_compare_constr_args);

                auto expr_value_ptr = Builder.CreateStructGEP(expr_struct_ptr, i, "expr_value_ptr");
                auto pattern_value_ptr = Builder.CreateStructGEP(pattern_struct_ptr, i, "pattern_value_ptr");

                auto expr_value = Builder.CreateLoad(expr_value_ptr, "expr_value");
                auto pattern_value = Builder.CreateLoad(pattern_value_ptr, "pattern_value");

                match_expr_to_pattern(expr_value, pattern_value, match_compare_constr_args_success, match_fail, constr_pattern_arg, constr_pattern_arg->get_pattern_type());
                
                current_function->getBasicBlockList().push_back(match_compare_constr_args_success);
                Builder.SetInsertPoint(match_compare_constr_args_success);

                i++;
            }

            //If by this point we haven't failed a match then constructor match was successfull
            Builder.CreateBr(match_success);

            break;    
        }
        default: {
            error_handler->print_error("Uknown pattern\n", ErrorType::Internal, this->lineno);
            break;
        }
    }
}