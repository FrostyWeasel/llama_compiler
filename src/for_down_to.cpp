#include "for_down_to.hpp"

void ForDownTo::print(std::ostream &out) const {
    out << "for " << id << " =";

    if(first_condition != nullptr)
        first_condition->print(out);
    else
        out << " null";

    out << " downto";

    if(second_condition != nullptr)
        second_condition->print(out);
    else
        out << " null";

    out << " do";

    if(expr != nullptr)
        expr->print(out);
    else
        out << " null";

    out << " done";
}

llvm::Value* ForDownTo::codegen() { 
    this->second_condition->sem();

    //Get initial value of iterator variable
    auto start_value = this->first_condition->codegen();

    auto current_function = Builder.GetInsertBlock()->getParent();

    //Current previous BB
    auto header_BB = Builder.GetInsertBlock();

    //Create BB for the loop
    auto loop_start_BB = llvm::BasicBlock::Create(TheContext, "loop_start", current_function);
    auto loop_body_BB = llvm::BasicBlock::Create(TheContext, "loop_body");
    auto loop_end_BB = llvm::BasicBlock::Create(TheContext, "loop_end");

    //Enter the loop
    Builder.CreateBr(loop_start_BB);
    Builder.SetInsertPoint(loop_start_BB);

    auto phi_node = Builder.CreatePHI(i32, 2, this->id);
    phi_node->addIncoming(start_value, header_BB);

    auto end_condition = this->second_condition->codegen();
    auto condition_result = Builder.CreateICmp(llvm::CmpInst::ICMP_SGT, end_condition, phi_node, "end_condition");
    Builder.CreateCondBr(condition_result, loop_end_BB, loop_body_BB);

    //Start loop body BB
    current_function->getBasicBlockList().push_back(loop_body_BB);
    Builder.SetInsertPoint(loop_body_BB);
    //Only expression is in scope of iterator
    //Output expression code, ignore result
    st->scope_open();

    ConstantEntry* entry = new ConstantEntry(id, EntryType::ENTRY_CONSTANT, std::make_shared<TypeVariable>(TypeTag::Int));
    st->insert_entry(entry);

    this->expr->codegen();        

    st->scope_close();

    auto next_value = Builder.CreateSub(phi_node, c32(1), "increment_iterator");
    loop_body_BB = Builder.GetInsertBlock();
    phi_node->addIncoming(next_value, loop_body_BB);
    Builder.CreateBr(loop_start_BB);

    //end of loop
    current_function->getBasicBlockList().push_back(loop_end_BB);
    Builder.SetInsertPoint(loop_end_BB);

    return llvm::ConstantStruct::get(llvm::StructType::get(TheContext), { });
}