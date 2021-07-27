// #include "block.hpp"

// template <class T>
// void Block<T>::print(std::ostream &out) const {
//     int i = 0;

//     switch (this->block_type) {
//         case BlockType::Par:
//         for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
//             (*element_it)->print(out);
//             // if(i < list.size() - 1)
//             //   out << "";
//             i++;
//         }
//         break;
//         case BlockType::Expr:
//         for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
//             (*element_it)->print(out);
//             if(i < list.size() - 1)
//             out << " ";
//             i++;
//         }
//         break;
//         case BlockType::ExprComma:
//         for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
//             (*element_it)->print(out);
//             if(i < list.size() - 1)
//             out << ", ";
//             i++;
//         }
//         break;
//         case BlockType::Def:
//         for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
//             (*element_it)->print(out);
//         }
//         break;
//         case BlockType::LetDef:
//         for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
//             (*element_it)->print(out);
//             out << "\n";
//         }
//         break;
//         default:
//         std::cerr << "Uknown block type\n";
//         exit(1); //TODO: Error handling.
//         break;
//     }
// }

// template <class T>
// void Block<T>::append(T* element) { list.push_back(element); }

// template <class T>
// void Block<T>::insert(typename std::vector<T*>::const_iterator it, T* element) { list.insert(it, element); }

// template <class T>
// const typename std::vector<T*>::const_iterator Block<T>::begin() const { return list.cbegin(); }

// template <class T>
// unsigned int Block<T>::block_size() { return list.size(); }

// template <class T>
// void Block<T>::add_to_symbol_table() {
//     switch (this->block_type) {
//             case BlockType::Def:
//             for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
//                 if(*element_it != nullptr){
//                 (*element_it)->add_to_symbol_table();
//                 }
//                 else {
//                 std::cerr << "Nullptr in block list.\n";
//                 exit(1); //TODO: Error handling
//                 }
//             }
//             break;

//         default:
//             std::cerr << "Attempting to add non definitions to symbol table.\n";
//             exit(1); //TODO: Error handling
//         break;
//     }
// }

// template <class T>
// void Block<T>::allocate() {
//     switch (this->block_type) {
//             case BlockType::Def:
//             for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
//                 if(*element_it != nullptr){
//                     (*element_it)->allocate();
//                 }
//                 else {
//                     std::cerr << "Nullptr in block list.\n";
//                     exit(1); //TODO: Error handling
//                 }
//             }
//             break;

//         default:
//             std::cerr << "Attempting to allocate non definitions.\n";
//             exit(1); //TODO: Error handling
//         break;
//     }
// }

// template <class T>
// std::shared_ptr<TypeVariable> Block<T>::infer() {
//     std::shared_ptr<TypeVariable> block_type = nullptr;

//     switch (this->block_type) {
//         case BlockType::Par:
//         if(this->list.size() == 0) {
//             std::cerr << "Parameter list is empty.\n";
//             exit(1); //TODO: Error handling
//         }
//         else {
//             block_type = list[0]->infer();
//             for(auto element_it = ++this->list.begin(); element_it != this->list.end(); element_it++) {
//                 if(*element_it != nullptr){
//                 std::shared_ptr<TypeVariable> new_type = (*element_it)->infer();
//                 block_type = std::make_shared<TypeVariable>(TypeTag::Function, block_type, new_type, FunctionTypeTag::Curry);
//                 }
//                 else {
//                 std::cerr << "Nullptr in block list.\n";
//                 exit(1); //TODO: Error handling
//                 }
//             }
//         }
//         break;

//         case BlockType::Expr:
//         if(this->list.size() == 0) {
//             std::cerr << "Expression list is empty.\n";
//             exit(1); //TODO: Error handling
//         }
//         else {
//             block_type = list[0]->infer();
//             for(auto element_it = ++this->list.begin(); element_it != this->list.end(); element_it++) {
//                 if(*element_it != nullptr){
//                 std::shared_ptr<TypeVariable> new_type = (*element_it)->infer();
//                 block_type = std::make_shared<TypeVariable>(TypeTag::Function, block_type, new_type, FunctionTypeTag::Curry);
//                 }
//                 else {
//                 std::cerr << "Nullptr in block list.\n";
//                 exit(1); //TODO: Error handling
//                 }
//             }
//         }
//         break;

//         case BlockType::ExprComma:
//             for(auto element_it = this->list.begin(); element_it != this->list.end(); element_it++) {
//             if(*element_it != nullptr){
//                 std::shared_ptr<TypeVariable> new_type = (*element_it)->infer();
//                 st->add_constraint(new_type, std::make_shared<TypeVariable>(TypeTag::Int));
//             }
//             else {
//                 std::cerr << "Nullptr in block list.\n";
//                 exit(1); //TODO: Error handling
//             }
//         }
//         break;
//         default:
//             for(T* element: list) {
//             if(element != nullptr)
//                 element->infer();
//             }
//         break;
//     }

//     return block_type;
// }

// template <class T>
// void Block<T>::sem() {
//     for(T* element: list) {
//         if(element != nullptr)
//         element->sem();
//     }
// }

// template <class T>
// llvm::Value* Block<T>::codegen()  {
//     llvm::Value* block_value = nullptr;

//     for(T* element: list) {
//         if(element != nullptr)
//             element->codegen();
//     }

//     return block_value;
// }

// template <class T>
// void Block<T>::make_non_local_variable_stack() {
//     for(T* element: list) {
//         if(element != nullptr)
//             element->make_non_local_variable_stack();
//     }
// }

// template <class T>
// std::vector<T*>& Block<T>::get_list() {
//     return this->list();
// }