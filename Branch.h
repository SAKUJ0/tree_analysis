#include <iostream>

#include <TROOT.h>
#include <TTree.h>
#include <TDataType.h>
#include <TClass.h>

class Branch {
      TBranch *tbranch;
      char* name;

   public:
      Branch(TTree *file, const char* name);

      Int_t getSize() const;
      Int_t getType() const;
      Int_t getMin() const;
      Int_t getMax() const;
      TTree *getTTree() const;

      char *getName() const;
      TBranch *getTBranch() const;
      void setTBranch(TBranch *branch);
};
