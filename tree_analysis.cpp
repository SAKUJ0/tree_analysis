#include <iostream>
#include <vector>
using std::vector;

#include <TApplication.h>

#include "Tree.h"

bool check(const vector<Float_t>& x) {
   return x[1] != 0.0 && x[0] / x[1] > 0.0 && x[0] / x[1] < 2.0;
}

Float_t transform(const vector<Float_t>& x) {
   if(x[1] != 0.0)
      return x[0] / x[1];
   else {
      std::cerr << "Division by zero. Implement proper check function" << std::endl;
      return 0.0;
   }
}

int main(int argc, char **argv) {
   TApplication theApp("App", &argc, argv);

   TFile *file = new TFile("tree.root", "READ");
   Tree *tree = new Tree(file, "LeptonAnalysis");

   tree->setBranch("EcalEnergy");
   tree->setBranch("TrackerRigidity");

   Histogram *hist = tree->setHistogram(check, transform, 200);
//   tree->calculateMean();
//   tree->calculateRMS();
//   std::cerr << hist->getMean() << " +/- " << hist->getRMS() << std::endl;
   
   tree->fillHistograms();
   hist->getHistogram()->Draw();

   theApp.Run();
   return 0;
}
