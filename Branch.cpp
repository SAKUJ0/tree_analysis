#include "Branch.h"

Branch::Branch(TTree *tree, const char* varname) {

   name = const_cast<char*>(varname);
   TBranch *branch = tree->GetBranch(varname);
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
   return tree->GetMinimum(name);
}

Int_t Branch::getMax() const{
   TTree *tree = this->getTTree();
   return tree->GetMaximum(name);
}

TTree *Branch::getTTree() const{
   return tbranch->GetTree();
}

char *Branch::getName() const{
   return name;
}
