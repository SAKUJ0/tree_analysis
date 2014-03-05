#include <iostream>
#include <string>
#include <vector>
using std::vector;
#include <math.h>

#include <TFile.h>
#include <TTree.h>

#include "Branch.h"
#include "Histogram.h"

class Tree {
      TTree *ttree;
      vector<Branch*> branches;
      vector<Histogram*> histograms;

      void traverse(void (Tree::*process)(const vector<Float_t>& var, const Int_t& j) const) const;
      void processFillHistograms(const vector<Float_t>& var, const Int_t& j) const;
      void processCalculateMean(const vector<Float_t>& var, const Int_t& j) const;
      void processCalculateRMS(const vector<Float_t>& var, const Int_t& j) const;

   public:
      Tree(TFile *file, const std::string& name);

      void setBranch(const std::string& name);
      Histogram *setHistogram(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), const std::string& name, Int_t nbins, Float_t min, Float_t max, std::string title = "");
      Histogram *setHistogramLog(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), const std::string& name, Int_t nbins, Float_t min, Float_t max, std::string title = "");

      void fillHistograms() const;
      void calculateMean() const;
      void calculateRMS() const;
};
