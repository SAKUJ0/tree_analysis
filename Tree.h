#include <iostream>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TDataType.h>
#include <TClass.h>

class Tree {
      TTree *ttree;
   public:
      Tree(TFile *file);

      Int_t getSize() const;
      TTree *getTTree() const;
      void setTTree(TTree *tree);

      TH1F *getHistogram(const char* varname, Int_t nbins = 100) const;
};
