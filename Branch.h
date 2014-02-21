#include <iostream>
#include <string>

#include <TROOT.h>
#include <TTree.h>
#include <TDataType.h>
#include <TClass.h>

class Branch {
      TBranch *tbranch;
      std::string name;

   public:
      Branch(TTree *file, std::string name);

      Int_t getSize() const;
      Int_t getType() const;
      Int_t getMin() const;
      Int_t getMax() const;
      TTree *getTTree() const;

      std::string getName() const;
      TBranch *getTBranch() const;
      void setTBranch(TBranch *branch);
};
