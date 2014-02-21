#include "Branch.h"

Branch::Branch(TTree *tree, std::string varname) {

   name = varname;
   TBranch *branch = tree->GetBranch(varname.c_str());
   this->setTBranch(branch);
}

void Branch::setTBranch(TBranch* branch) {
   tbranch = branch;
}

TBranch *Branch::getTBranch() const {
   return tbranch;
}

Int_t Branch::getSize() const{
   return tbranch->GetEntries();
}

Int_t Branch::getType() const{
   TClass *tclass = new TClass();
   EDataType type;
   tbranch->GetExpectedType(*&tclass, type);

   return type;
}

Int_t Branch::getMin() const{
   TTree *tree = this->getTTree();
   return tree->GetMinimum(name.c_str());
}

Int_t Branch::getMax() const{
   TTree *tree = this->getTTree();
   return tree->GetMaximum(name.c_str());
}

TTree *Branch::getTTree() const{
   return tbranch->GetTree();
}

std::string Branch::getName() const{
   return name;
}
