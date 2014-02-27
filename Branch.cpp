#include "Branch.h"

Branch::Branch(TTree *tree, std::string varname) {

   name = varname;
   TBranch *branch = tree->GetBranch(varname.c_str());
   tbranch = branch;
}

TBranch *Branch::getTBranch() const {
   return tbranch;
}

Int_t Branch::getType() const{
   TClass *tclass = new TClass();
   EDataType type;
   tbranch->GetExpectedType(*&tclass, type);

   return type;
}
