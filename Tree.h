#include <iostream>
#include <string>
#include <vector>
using std::vector;

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>

#include "Branch.h"

class Tree {
      TTree *ttree;
      vector<Branch*> branches;
      //vector<TH1F> *histograms;

   public:
      Tree(TFile *file);

      Int_t getSize() const;

      TH1F *BranchToHist(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), Int_t nbins) const;
      TH1F *getHistogram(const vector<std::string>& varname, bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), Int_t nbins = 200);
};
