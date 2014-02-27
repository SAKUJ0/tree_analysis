#include <iostream>
#include <string>
#include <vector>
using std::vector;

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>

#include "Branch.h"
#include "Histogram.h"

class Tree {
      TTree *ttree;
      vector<Branch*> branches;
      vector<Histogram*> histograms;

   public:
      Tree(TFile *file, const std::string& name);

      void setBranch(const std::string& name);
      Histogram *setHistogram(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), Int_t nbins = 200);

      void process() const;
};
