#include <iostream>
#include <string>
#include <vector>
using std::vector;

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

      TH1F *getHistogram(const vector<std::string>& varname, bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), Int_t nbins = 200) const;
};
