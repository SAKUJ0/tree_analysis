#include <string>

#include <TTree.h>
#include <TDataType.h>
#include <TClass.h>

class Branch {
   friend class Tree;
      TBranch *tbranch;
      std::string name;

   public:
      Branch(TTree *tree, std::string name);
      Int_t getType() const;
};
