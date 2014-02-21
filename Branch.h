#include <iostream>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TDataType.h>
#include <TClass.h>

class Branch {
      TBranch *tbranch;
      char* name;

   public:
      Branch(TTree *file, char* name);

      Int_t getSize() const;
      Int_t getType() const;
      Int_t getMin() const;
      Int_t getMax() const;
      Int_t getTTree() const;

      Int_t getName() const;
      TBranch *getTBranch() const;
      void setTBranch(TBranch *tree);
};
