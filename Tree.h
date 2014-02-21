#include <iostream>
#include <string>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>

class Tree {
      TTree *ttree;
   public:
      Tree(TFile *file);

      Int_t getSize() const;
      TTree *getTTree() const;
      void setTTree(TTree *tree);

      TH1F *getHistogram(std::string varname, Int_t nbins = 100) const;
};
