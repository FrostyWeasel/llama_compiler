#include "bin_op.hpp"
    
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
        default:
            out << "ERROR: No known type "; //TODO: Error: Replace by error handling
            exit(1);
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

            this->st->add_constraint(lval_type, rval_type);
            this->st->add_constraint(lval_type, std::make_shared<TypeVariable>(TypeTag::Bool));
            break;
        case OpType::Assign:
            lval_type = this->lval->infer(); //Type must be t ref
            rval_type = this->rval->infer(); //Type must be t
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Unit);

            this->st->add_constraint(lval_type, std::make_shared<TypeVariable>(TypeTag::Reference, rval_type));
            break;
        case OpType::Concat:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Unknown);

            this->st->add_constraint(rval_type, this->type_variable);

            break;
        case OpType::Divide:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

            this->st->add_constraint(lval_type, this->type_variable);
            this->st->add_constraint(rval_type, this->type_variable);
            break;
        case OpType::Equals:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type);
            break;
        case OpType::GreaterOrEqualThan:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type);
            break;
        case OpType::GreaterThan:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type);
            break;
        case OpType::LessOrEqualThan:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type);
            break;
        case OpType::LessThan:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type);
            break;
        case OpType::Minus:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

            this->st->add_constraint(lval_type, this->type_variable);
            this->st->add_constraint(rval_type, this->type_variable);
            break;
        case OpType::Modulo:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

            this->st->add_constraint(lval_type, this->type_variable);
            this->st->add_constraint(rval_type, this->type_variable);
            break;
        case OpType::NatEquals:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type);
            break;
        case OpType::NatNotEquals:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type);
            break;
        case OpType::NotEquals:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type);
            break;
        case OpType::Or:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Bool);

            this->st->add_constraint(lval_type, rval_type);
            this->st->add_constraint(lval_type, std::make_shared<TypeVariable>(TypeTag::Bool));
            break;
        case OpType::Plus:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

            this->st->add_constraint(lval_type, this->type_variable);
            this->st->add_constraint(rval_type, this->type_variable);  
            break;
        case OpType::Times:
            lval_type = this->lval->infer();
            rval_type = this->rval->infer();
            this->type_variable = std::make_shared<TypeVariable>(TypeTag::Int);

            this->st->add_constraint(lval_type, this->type_variable);
            this->st->add_constraint(rval_type, this->type_variable); 
            break;
        default:
            std::cerr << "Unknown binary operator type\n";
            exit(1); //TODO:Error handling
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
                
                std::cerr << "Argument can not be of type function\n" << "offending type is: " << *this->lval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_same_tag(this->lval->get_type(),
                TypeTag::Array))) {
                
                std::cerr << "Argument can not be of type array\n" << "offending type is: " << *this->lval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Function))) {
                
            std::cerr << "Argument can not be of type function\n" << "offending type is: " << *this->rval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Array))) {
                
                std::cerr << "Argument can not be of type array\n" << "offending type is: " << *this->rval->get_type();
                exit(1); //TODO: Error handling.
            }
        break;
        case OpType::GreaterOrEqualThan:
            //TODO: Sem float same for other comp
            this->lval->sem();
            this->rval->sem();

            if((sa->is_not_same_tag(this->lval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char}))) {
                
                std::cerr << "Argument must be of type int or float or char\n" << "offending type is: " << *this->lval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_not_same_tag(this->rval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char}))) {
                
                std::cerr << "Argument must be of type int or float or char\n" << "offending type is: " << *this->rval->get_type();
                exit(1); //TODO: Error handling.
            }
            break;
        case OpType::GreaterThan:
            this->lval->sem();
            this->rval->sem();

            if((sa->is_not_same_tag(this->lval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char}))) {
                
                std::cerr << "Argument must be of type int or float or char\n" << "offending type is: " << *this->lval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_not_same_tag(this->rval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char}))) {
                
                std::cerr << "Argument must be of type int or float or char\n" << "offending type is: " << *this->rval->get_type();
                exit(1); //TODO: Error handling.
            }
            break;
        case OpType::LessOrEqualThan:
            this->lval->sem();
            this->rval->sem();

            if((sa->is_not_same_tag(this->lval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char}))) {
                
                std::cerr << "Argument must be of type int or float or char\n" << "offending type is: " << *this->lval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_not_same_tag(this->rval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char}))) {
                
                std::cerr << "Argument must be of type int or float or char\n" << "offending type is: " << *this->rval->get_type();
                exit(1); //TODO: Error handling.
            }
            break;
        case OpType::LessThan:
            this->lval->sem();
            this->rval->sem();

            if((sa->is_not_same_tag(this->lval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char}))) {
                
                std::cerr << "Argument must be of type int or float or char\n" << "offending type is: " << *this->lval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_not_same_tag(this->rval->get_type(),
                std::vector<TypeTag>{TypeTag::Int, TypeTag::Char}))) {
                
                std::cerr << "Argument must be of type int or float or char\n" << "offending type is: " << *this->rval->get_type();
                exit(1); //TODO: Error handling.
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
                
                std::cerr << "Argument can not be of type function\n" << "offending type is: " << *this->lval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_same_tag(this->lval->get_type(),
                TypeTag::Array))) {
                
                std::cerr << "Argument can not be of type array\n" << "offending type is: " << *this->lval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Function))) {
                
            std::cerr << "Argument can not be of type function\n" << "offending type is: " << *this->rval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Array))) {
                
                std::cerr << "Argument can not be of type array\n" << "offending type is: " << *this->rval->get_type();
                exit(1); //TODO: Error handling.
            } 

            
            break;
        case OpType::NatNotEquals:
            this->lval->sem();
            this->rval->sem();
            if((sa->is_same_tag(this->lval->get_type(),
                TypeTag::Function))) {
                
                std::cerr << "Argument can not be of type function\n" << "offending type is: " << *this->lval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_same_tag(this->lval->get_type(),
                TypeTag::Array))) {
                
                std::cerr << "Argument can not be of type array\n" << "offending type is: " << *this->lval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Function))) {
                
            std::cerr << "Argument can not be of type function\n" << "offending type is: " << *this->rval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Array))) {
                
                std::cerr << "Argument can not be of type array\n" << "offending type is: " << *this->rval->get_type();
                exit(1); //TODO: Error handling.
            }

            break;
        case OpType::NotEquals:
            this->lval->sem();
            this->rval->sem();
            if((sa->is_same_tag(this->lval->get_type(),
                TypeTag::Function))) {
                
                std::cerr << "Argument can not be of type function\n" << "offending type is: " << *this->lval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_same_tag(this->lval->get_type(),
                TypeTag::Array))) {
                
                std::cerr << "Argument can not be of type array\n" << "offending type is: " << *this->lval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Function))) {
                
            std::cerr << "Argument can not be of type function\n" << "offending type is: " << *this->rval->get_type();
                exit(1); //TODO: Error handling.
            }
            if((sa->is_same_tag(this->rval->get_type(),
                TypeTag::Array))) {
                
                std::cerr << "Argument can not be of type array\n" << "offending type is: " << *this->rval->get_type();
                exit(1); //TODO: Error handling.
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
        default:
            std::cerr << "Unknown binary operator type\n";
            exit(1); //TODO:Error handling
            break;
    }  
}

llvm::Value* BinOp::codegen() {
    llvm::Value* lhs = nullptr;
    llvm::Value* rhs = nullptr;

    switch (op) {
        case OpType::And:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateAnd(lhs, rhs, "andtmp");
            break;
        case OpType::Assign: {
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            Builder.CreateStore(rhs, lhs);
            return nullptr;
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

            return Builder.CreateICmp(llvm::CmpInst::ICMP_EQ, lhs, rhs, "equ");
            break;
        case OpType::GreaterOrEqualThan:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateICmp(llvm::CmpInst::ICMP_SGE, lhs, rhs, "greater_or_equal");
            break;
        case OpType::GreaterThan:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateICmp(llvm::CmpInst::ICMP_SGT, lhs, rhs, "greater_than");
            break;
        case OpType::LessOrEqualThan:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateICmp(llvm::CmpInst::ICMP_SLE, lhs, rhs, "less_or_equal");
            break;
        case OpType::LessThan:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

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

            return Builder.CreateICmp(llvm::CmpInst::ICMP_EQ, lhs, rhs, "nat_equ");

            break;
        case OpType::NatNotEquals:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateICmp(llvm::CmpInst::ICMP_NE, lhs, rhs, "nat_not_equ");

            break;
        case OpType::NotEquals:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateICmp(llvm::CmpInst::ICMP_NE, lhs, rhs, "not_equ");

            break;
        case OpType::Or:
            lhs = this->lval->codegen();
            rhs = this->rval->codegen();

            return Builder.CreateOr(lhs, rhs, "ortmp");
            break;
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
        default:
            std::cerr << "Unknown binary operator type\n";
            exit(1); //TODO:Error handling
            break;
    }

    return nullptr;
}