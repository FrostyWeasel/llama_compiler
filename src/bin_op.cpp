#include "bin_op.hpp"
#include "type_variable.hpp"
#include "error_handler.hpp"
#include "symbol_table.hpp"
#include "semantic_analyzer.hpp"
#include "type_entry.hpp"
#include <iostream>
#include <memory>

BinOp::BinOp(Expr* lval, Expr* rval, OpType op): lval(lval), rval(rval), op(op) {}

BinOp::~BinOp() {
    delete lval;
    delete rval;
}
    
void BinOp::print(std::ostream &out) const {
    if(lval != nullptr)
        lval->print(out);
    else
        out << " null";

    switch(op){
        case OpType::And:
            out << " &&";
            break;
        case OpType::Assign:
            out << " :=";
            break;
        case OpType::Concat:
            out << " ;";
            break;
        case OpType::Divide:
            out << " /";
            break;
        case OpType::Equals:
            out << " =";
            break;
        case OpType::GreaterOrEqualThan:
            out << " >=";
            break;
        case OpType::GreaterThan:
            out << " >";
            break;
        case OpType::LessOrEqualThan:
            out << " <=";
            break;
        case OpType::LessThan:
            out << " <";
            break;
        case OpType::Minus:
            out << " -";
            break;
        case OpType::Modulo:
            out << " %";
            break;
        case OpType::NatEquals:
            out << " ==";
            break;
        case OpType::NatNotEquals:
            out << " !=";
            break;
        case OpType::NotEquals:
            out << " <>";
            break;
        case OpType::Or:
            out << " ||";
            break;
        case OpType::Plus:
            out << " +";
            break;
        case OpType::Times:
            out << " *";
            break;
        case OpType::PlusFloat:
            out << " +.";
            break;
        case OpType::MinusFloat:
            out << " -.";
            break;
        case OpType::TimesFloat:
            out << " *.";
            break;
        case OpType::DivideFloat:
            out << " /.";
            break;
        case OpType::ExponentiateFloat:
            out << " **";
            break;
        default:
            error_handler->print_error("Unknown binary operator type\n", ErrorType::Internal, this->lineno);

            break;
    }
    if(rval != nullptr)
        rval->print(out);
    else
        out << "null ";
}

std::shared_ptr<TypeVariable> BinOp::infer() {
    std::shared_ptr<TypeVariable> lval_type = nullptr;
    std::shared_ptr<TypeVariable> rval_type = nullptr;

    switch(op) {
        case OpType::And:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type, this->lineno);
            this->st->add_constraint(lval_type, std::make_shared<TypeVariable>(TypeTag::Bool), this->lineno);
            break;
        case OpType::Assign:
            lval_type = this->lval->infer(); //Type must be t ref
            rval_type = this->rval->infer(); //Type must be t
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Unit);

            this->st->add_constraint(lval_type, std::make_shared<TypeVariable>(TypeTag::Reference, rval_type), this->lineno);
            break;
        case OpType::Concat:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Unknown);

            this->st->add_constraint(rval_type, this->type_variable, this->lineno);

            break;
        case OpType::Divide:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

            this->st->add_constraint(lval_type, this->type_variable, this->lineno);
            this->st->add_constraint(rval_type, this->type_variable, this->lineno);
            break;
        case OpType::Equals:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type, this->lineno);
            break;
        case OpType::GreaterOrEqualThan:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type, this->lineno);
            break;
        case OpType::GreaterThan:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type, this->lineno);
            break;
        case OpType::LessOrEqualThan:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type, this->lineno);
            break;
        case OpType::LessThan:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type, this->lineno);
            break;
        case OpType::Minus:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

            this->st->add_constraint(lval_type, this->type_variable, this->lineno);
            this->st->add_constraint(rval_type, this->type_variable, this->lineno);
            break;
        case OpType::Modulo:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

            this->st->add_constraint(lval_type, this->type_variable, this->lineno);
            this->st->add_constraint(rval_type, this->type_variable, this->lineno);
            break;
        case OpType::NatEquals:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type, this->lineno);
            break;
        case OpType::NatNotEquals:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type, this->lineno);
            break;
        case OpType::NotEquals:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type, this->lineno);
            break;
        case OpType::Or:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type, this->lineno);
            this->st->add_constraint(lval_type, std::make_shared<TypeVariable>(TypeTag::Bool), this->lineno);
            break;
        case OpType::Plus:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

            this->st->add_constraint(lval_type, this->type_variable, this->lineno);
            this->st->add_constraint(rval_type, this->type_variable, this->lineno);  
            break;
        case OpType::Times:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

            this->st->add_constraint(lval_type, this->type_variable, this->lineno);
            this->st->add_constraint(rval_type, this->type_variable, this->lineno); 
            break;
        case OpType::PlusFloat:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Float);

            this->st->add_constraint(lval_type, this->type_variable, this->lineno);
            this->st->add_constraint(rval_type, this->type_variable, this->lineno);  
            break;
        case OpType::MinusFloat:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Float);

            this->st->add_constraint(lval_type, this->type_variable, this->lineno);
            this->st->add_constraint(rval_type, this->type_variable, this->lineno);  
            break;
        case OpType::TimesFloat:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Float);

            this->st->add_constraint(lval_type, this->type_variable, this->lineno);
            this->st->add_constraint(rval_type, this->type_variable, this->lineno);  
            break;
        case OpType::DivideFloat:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Float);

            this->st->add_constraint(lval_type, this->type_variable, this->lineno);
            this->st->add_constraint(rval_type, this->type_variable, this->lineno);  
            break;
        case OpType::ExponentiateFloat:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Float);

            this->st->add_constraint(lval_type, this->type_variable, this->lineno);
            this->st->add_constraint(rval_type, this->type_variable, this->lineno);
            break;
        default:
            error_handler->print_error("Unknown binary operator type\n", ErrorType::Internal, this->lineno);
            break;
    }

    return this->type_variable;
}

void BinOp::sem() { 
    switch(op) {
        case OpType::And:
            this->lval->sem();
            this->rval->sem();
                            
            break;
        case OpType::Assign:
            this->lval->sem(); //Type must be t ref
            this->rval->sem(); //Type must be t
            
            break;
        case OpType::Concat:
            this->lval->sem();
            this->rval->sem();

            break;
        case OpType::Divide:
            this->lval->sem();
            this->rval->sem();
            
            break;
        case OpType::Equals:
            this->lval->sem();
            this->rval->sem();
            
            if((sa->is_same_tag(this->lval->get_type(),
                TypeTag::Function))) {
                
                error_handler->non_allowed_type(this->lval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_same_tag(this->lval->get_type(),
                TypeTag::Array))) {
                
                error_handler->non_allowed_type(this->lval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Function))) {
                
            error_handler->non_allowed_type(this->rval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Array))) {
                
                error_handler->non_allowed_type(this->rval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
        break;
        case OpType::GreaterOrEqualThan:
            this->lval->sem();
            this->rval->sem();

            this->lval->get_type()->set_default_type(TypeTag::Int);
            this->rval->get_type()->set_default_type(TypeTag::Int);

            if((sa->is_not_same_tag(this->lval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char, TypeTag::Float, TypeTag::Unknown}))) {
                
                error_handler->non_allowed_type(this->lval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_not_same_tag(this->rval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char, TypeTag::Float, TypeTag::Unknown}))) {
                
                error_handler->non_allowed_type(this->rval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            break;
        case OpType::GreaterThan:
            this->lval->sem();
            this->rval->sem();

            this->lval->get_type()->set_default_type(TypeTag::Int);
            this->rval->get_type()->set_default_type(TypeTag::Int);

            if((sa->is_not_same_tag(this->lval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char, TypeTag::Float, TypeTag::Unknown}))) {
                
                error_handler->non_allowed_type(this->lval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_not_same_tag(this->rval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char, TypeTag::Float, TypeTag::Unknown}))) {
                
                error_handler->non_allowed_type(this->rval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            break;
        case OpType::LessOrEqualThan:
            this->lval->sem();
            this->rval->sem();

            this->lval->get_type()->set_default_type(TypeTag::Int);
            this->rval->get_type()->set_default_type(TypeTag::Int);

            if((sa->is_not_same_tag(this->lval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char, TypeTag::Float, TypeTag::Unknown}))) {
                
                error_handler->non_allowed_type(this->lval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_not_same_tag(this->rval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char, TypeTag::Float, TypeTag::Unknown}))) {
                
                error_handler->non_allowed_type(this->rval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            break;
        case OpType::LessThan:
            this->lval->sem();
            this->rval->sem();

            this->lval->get_type()->set_default_type(TypeTag::Int);
            this->rval->get_type()->set_default_type(TypeTag::Int);

            if((sa->is_not_same_tag(this->lval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char, TypeTag::Float, TypeTag::Unknown}))) {
                
                error_handler->non_allowed_type(this->lval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_not_same_tag(this->rval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char, TypeTag::Float, TypeTag::Unknown}))) {
                
                error_handler->non_allowed_type(this->rval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }             
            break;
        case OpType::Minus:
            this->lval->sem();
            this->rval->sem();
            
            break;
        case OpType::Modulo:
            this->lval->sem();
            this->rval->sem();    
            
            break;
        case OpType::NatEquals:
            this->lval->sem();
            this->rval->sem();
            if((sa->is_same_tag(this->lval->get_type(),
                TypeTag::Function))) {
                
                error_handler->non_allowed_type(this->lval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_same_tag(this->lval->get_type(),
                TypeTag::Array))) {
                
                error_handler->non_allowed_type(this->lval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Function))) {
                
            error_handler->non_allowed_type(this->rval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Array))) {
                
                error_handler->non_allowed_type(this->rval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            } 

            
            break;
        case OpType::NatNotEquals:
            this->lval->sem();
            this->rval->sem();
            if((sa->is_same_tag(this->lval->get_type(),
                TypeTag::Function))) {
                
                error_handler->non_allowed_type(this->lval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_same_tag(this->lval->get_type(),
                TypeTag::Array))) {
                
                error_handler->non_allowed_type(this->lval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Function))) {
                
            error_handler->non_allowed_type(this->rval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Array))) {
                
                error_handler->non_allowed_type(this->rval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }

            break;
        case OpType::NotEquals:
            this->lval->sem();
            this->rval->sem();
            if((sa->is_same_tag(this->lval->get_type(),
                TypeTag::Function))) {
                
                error_handler->non_allowed_type(this->lval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_same_tag(this->lval->get_type(),
                TypeTag::Array))) {
                
                error_handler->non_allowed_type(this->lval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Function))) {
                
            error_handler->non_allowed_type(this->rval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Array))) {
                
                error_handler->non_allowed_type(this->rval->get_type(), this->lineno, ErrorType::User, NodeType::BinOp);
            }

            
            break;
        case OpType::Or:
            this->lval->sem();
            this->rval->sem();

            
            break;
        case OpType::Plus:
            this->lval->sem();
            this->rval->sem();

            
            break;
        case OpType::Times:
            this->lval->sem();
            this->rval->sem(); 
            
            break;
        case OpType::PlusFloat:
            this->lval->sem();
            this->rval->sem(); 

            break;
        case OpType::MinusFloat:
            this->lval->sem();
            this->rval->sem(); 

            break;
        case OpType::TimesFloat:
            this->lval->sem();
            this->rval->sem(); 

            break;
        case OpType::DivideFloat:
            this->lval->sem();
            this->rval->sem(); 

            break;
        case OpType::ExponentiateFloat:
            this->lval->sem();
            this->rval->sem(); 

            break;
        default:
            error_handler->print_error("Unknown binary operator type\n", ErrorType::Internal, this->lineno);
            break;
    }  
}

llvm::Value* BinOp::codegen() {
    llvm::Value* lhs = nullptr;
    llvm::Value* rhs = nullptr;

    switch (op) {
        case OpType::And: {
            lhs = this->lval->codegen();

            auto top_BB = Builder.GetInsertBlock();

            //If the lhs is false then we know that the whole expr is false and we do not execute the rhs
            auto current_function = Builder.GetInsertBlock()->getParent();

            auto execute_and_rhs_BB = llvm::BasicBlock::Create(TheContext, "execute_and_rhs", current_function);
            auto and_expr_end_BB = llvm::BasicBlock::Create(TheContext, "and_expr_end");

            auto short_circuit_result = Builder.CreateICmp(llvm::CmpInst::Predicate::ICMP_EQ, lhs, c1(0), "short_circuit_result");
            Builder.CreateCondBr(short_circuit_result, and_expr_end_BB, execute_and_rhs_BB);

            Builder.SetInsertPoint(execute_and_rhs_BB);
            rhs = this->rval->codegen();

            execute_and_rhs_BB = Builder.GetInsertBlock();

            auto and_result = Builder.CreateAnd(lhs, rhs, "and");
            Builder.CreateBr(and_expr_end_BB);

            current_function->getBasicBlockList().push_back(and_expr_end_BB);
            Builder.SetInsertPoint(and_expr_end_BB);

            auto phi_result = Builder.CreatePHI(i1, 2, "andtmp");
            phi_result->addIncoming(lhs, top_BB);
            phi_result->addIncoming(and_result, execute_and_rhs_BB);

            return phi_result;
            break;
        }
        case OpType::Assign: {
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            Builder.CreateStore(rhs, lhs);
            return llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { });
            break;
        }
        case OpType::Concat:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();
            
            return rhs;
            break;
        case OpType::Divide:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateSDiv(lhs, rhs, "divtmp");
            break;
        case OpType::Equals:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            //for references the pointer to the reference is compared if compairing the type is desired the user can dereference first
            if(this->lval->get_type()->get_tag() == TypeTag::Float)
                return Builder.CreateFCmp(llvm::CmpInst::FCMP_OEQ, lhs, rhs, "equ");
            else if(this->lval->get_type()->get_tag() == TypeTag::UserType) {
                auto user_type = this->lval->get_type();
                auto user_type_id = user_type->get_user_type_id();
                auto type_entry = dynamic_cast<TypeEntry*>(st->lookup_entry_of_type(user_type_id, EntryType::ENTRY_TYPE));
                auto cmp_function_def = type_entry->get_constructor_cmp_function();
                return Builder.CreateCall(cmp_function_def, { lhs, rhs }, "equ");
            }
            else
                return Builder.CreateICmp(llvm::CmpInst::ICMP_EQ, lhs, rhs, "equ");
            break;
        case OpType::GreaterOrEqualThan:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();
            if(this->lval->get_type()->get_tag() == TypeTag::Float)
                return Builder.CreateFCmp(llvm::CmpInst::FCMP_OGE, lhs, rhs, "greater_or_equal");
            else
                return Builder.CreateICmp(llvm::CmpInst::ICMP_SGE, lhs, rhs, "greater_or_equal");
            break;
        case OpType::GreaterThan:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();
            if(this->lval->get_type()->get_tag() == TypeTag::Float)
                return Builder.CreateFCmp(llvm::CmpInst::FCMP_OGT, lhs, rhs, "greater_than");
            else
                return Builder.CreateICmp(llvm::CmpInst::ICMP_SGT, lhs, rhs, "greater_than");
            break;
        case OpType::LessOrEqualThan:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();
            if(this->lval->get_type()->get_tag() == TypeTag::Float)
                return Builder.CreateFCmp(llvm::CmpInst::FCMP_OLE, lhs, rhs, "less_or_equal");
            else
                return Builder.CreateICmp(llvm::CmpInst::ICMP_SLE, lhs, rhs, "less_or_equal");
            break;
        case OpType::LessThan:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();
            if(this->lval->get_type()->get_tag() == TypeTag::Float)
                return Builder.CreateFCmp(llvm::CmpInst::FCMP_OLT, lhs, rhs, "less_than");
            else
                return Builder.CreateICmp(llvm::CmpInst::ICMP_SLT, lhs, rhs, "less_than");
            break;
        case OpType::Minus:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateSub(lhs, rhs, "subtmp");
            break;
        case OpType::Modulo:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateSRem(lhs, rhs, "modtmp");
            break;
        case OpType::NatEquals:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();
            if(this->lval->get_type()->get_tag() == TypeTag::Float)
                return Builder.CreateFCmp(llvm::CmpInst::FCMP_OEQ, lhs, rhs, "nat_equ");
            else
                return Builder.CreateICmp(llvm::CmpInst::ICMP_EQ, lhs, rhs, "nat_equ");

            break;
        case OpType::NatNotEquals:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();
            if(this->lval->get_type()->get_tag() == TypeTag::Float) {
                return Builder.CreateFCmp(llvm::CmpInst::FCMP_ONE, lhs, rhs, "nat_not_equ");
            }

            return Builder.CreateICmp(llvm::CmpInst::ICMP_NE, lhs, rhs, "nat_not_equ");

            break;
        case OpType::NotEquals:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            if(this->lval->get_type()->get_tag() == TypeTag::Float)
                return Builder.CreateFCmp(llvm::CmpInst::FCMP_ONE, lhs, rhs, "not_equ");
            else if(this->lval->get_type()->get_tag() == TypeTag::UserType) {
                auto user_type = this->lval->get_type();
                auto user_type_id = user_type->get_user_type_id();
                auto type_entry = dynamic_cast<TypeEntry*>(st->lookup_entry_of_type(user_type_id, EntryType::ENTRY_TYPE));
                auto cmp_function_def = type_entry->get_constructor_cmp_function();

                return Builder.CreateNot(Builder.CreateCall(cmp_function_def, { lhs, rhs }, "equ"), "not_equ");
            }
            else
                return Builder.CreateICmp(llvm::CmpInst::ICMP_NE, lhs, rhs, "not_equ");
                
            break;
        case OpType::Or: {
            lhs = this->lval->codegen();

            auto top_BB = Builder.GetInsertBlock();

            //If the lhs is true then we know that the whole expr is true and we do not execute the rhs
            auto current_function = Builder.GetInsertBlock()->getParent();

            auto execute_or_rhs_BB = llvm::BasicBlock::Create(TheContext, "execute_or_rhs", current_function);
            auto or_expr_end_BB = llvm::BasicBlock::Create(TheContext, "or_expr_end");

            auto short_circuit_result = Builder.CreateICmp(llvm::CmpInst::Predicate::ICMP_EQ, lhs, c1(1), "short_circuit_result");
            Builder.CreateCondBr(short_circuit_result, or_expr_end_BB, execute_or_rhs_BB);

            Builder.SetInsertPoint(execute_or_rhs_BB);
            rhs = this->rval->codegen();

            //rhs codegen may change BB so get current BB (the one in which the assignment to the rhs happened) for the phi node
            execute_or_rhs_BB = Builder.GetInsertBlock();

            auto or_result = Builder.CreateOr(lhs, rhs, "or");
            Builder.CreateBr(or_expr_end_BB);

            current_function->getBasicBlockList().push_back(or_expr_end_BB);
            Builder.SetInsertPoint(or_expr_end_BB);

            auto phi_result = Builder.CreatePHI(i1, 2, "andtmp");
            phi_result->addIncoming(lhs, top_BB);
            phi_result->addIncoming(or_result, execute_or_rhs_BB);

            return phi_result;

            return Builder.CreateOr(lhs, rhs, "ortmp");
            break;
        }
        case OpType::Plus:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateAdd(lhs, rhs, "addtmp");
            break;
        case OpType::Times:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateMul(lhs, rhs, "multtmp");
            break;
        case OpType::PlusFloat:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateFAdd(lhs, rhs, "float_addtmp");
            
            break;
        case OpType::MinusFloat:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateFSub(lhs, rhs, "float_subtmp");

            break;
        case OpType::TimesFloat:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateFMul(lhs, rhs, "float_multtmp");

            break;
        case OpType::DivideFloat:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateFDiv(lhs, rhs, "float_divtmp");

            break;
        case OpType::ExponentiateFloat:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateIntrinsic(llvm::Intrinsic::pow, { f64 }, { lhs, rhs }, nullptr, "float_exptmp");

            break;
        default:
            error_handler->print_error("Unknown binary operator type\n", ErrorType::Internal, this->lineno);
            break;
    }

    return nullptr;
}