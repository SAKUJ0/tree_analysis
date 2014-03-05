#include <iostream>
#include <vector>
using std::vector;
#include <cmath> //abs()
using std::abs;

#include <TApplication.h>
#include <TPad.h>

#include "Tree.h"

bool cut_true(const vector<Float_t>& x) {
   return true;
}

bool cut_cutbased_ep_selection(const vector<Float_t>& x) {
   return     abs(x[1]) > 0         // Rigidity > 0
           && 0.5 < x[0]/abs(x[1])  // EcalEnergy ~ Rigidity
           && x[0]/abs(x[1]) < 10   //   (factor 0.5 - 10)
           && x[2] > -0.8;          // EcalBDT > -0.8
}

bool cut_cutbased_ep_selection_no_ER(const vector<Float_t>& x) {
   return     abs(x[1]) > 0         // Rigidity > 0
           //&& 0.5 < x[0]/abs(x[1])  // EcalEnergy ~ Rigidity
           //&& x[0]/abs(x[1]) < 10   //   (factor 0.5 - 10)
           && x[2] > -0.8;          // EcalBDT > -0.8
}

bool cut_low_energy(const vector<Float_t>& x) {
   return     x[0] > 8.0
           && x[0] < 12.0;
}

Float_t log_E_R(const vector<Float_t>& x) {
   if(x[1] != 0.0)
      return log(x[0] / abs(x[1]));
   else {
      std::cerr << "Division by zero. Implement proper check function" << std::endl;
      return 0.0;
   }
}

Float_t EcalBDT(const vector<Float_t>& x) {
   return x[2];
}

Float_t Run(const vector<Float_t>& x) {
   return x[3];
}

Float_t Event(const vector<Float_t>& x) {
   return x[4];
}

Float_t EcalEnergy(const vector<Float_t>& x) {
   return x[0];
}

int main(int argc, char **argv) {
   TApplication theApp("App", &argc, argv);

   TFile *file = new TFile("tree.root", "READ");
   Tree *tree = new Tree(file, "LeptonAnalysis");

   tree->setBranch("EcalEnergy");
   tree->setBranch("TrackerRigidity");
   tree->setBranch("EcalBDT");
   tree->setBranch("Run");
   tree->setBranch("Event");

//   tree->setBranch("EventFlags");
//   tree->setBranch("TriggerFlags");
//   tree->setBranch("McParticleId");
//   tree->setBranch("McGeneratedMomentum");
//   tree->setBranch("McEventWeight");
//   tree->setBranch("TofBeta");
//   tree->setBranch("TofLowerCharge");
//   tree->setBranch("TofUpperCharge");
//   tree->setBranch("TrackerNumberOfTracks");
//   tree->setBranch("TrackerCharge");
//   tree->setBranch("TrackerChiSquareX");
//   tree->setBranch("TrackerChiSquareY");
//   tree->setBranch("TrackerPattern");
//   tree->setBranch("TrackerChargeConfusionBDT");
//   tree->setBranch("TrackerTrackEcalCogDeltaX");
//   tree->setBranch("TrackerTrackEcalCogDeltaY");
//   tree->setBranch("EcalRearLeakage");
//   tree->setBranch("EcalChiSquare");
//   tree->setBranch("EcalShowerDirectionZ");
//   tree->setBranch("TrdActiveLayers");
//   tree->setBranch("TrdNumberOfVertices");
//   tree->setBranch("TrdRElecProt");
//   tree->setBranch("TrdRHeliElec");
//   tree->calculateRMS();
//   std::cerr << hist->getMean() << " +/- " << hist->getRMS() << std::endl;

//   Histogram *hist0 = tree->setHistogram(cut_cutbased_ep_selection, log_E_R, "log ( E / R )", 500, -3.0, 3.0);
//   Histogram *hist1 = tree->setHistogram(cut_cutbased_ep_selection_no_ER, log_E_R, "log ( E / R ) no ER cut", 500, -3.0, 3.0);
//   Histogram *hist2 = tree->setHistogram(cut_cutbased_ep_selection, EcalBDT, "EcalBDT", 500, -1.0, 1.0);
//   Histogram *run = tree->setHistogram(cut_low_energy, Run, "Run", 200, 1.3073e+09, 1.31992e+09);
   Histogram *ecalE = tree->setHistogramLog(cut_true, EcalEnergy, "double log EcalEnergy", 1000, 0.1, 5000);

   tree->fillHistograms();
//   tree->calculateMean();
//   std::cerr << "Min = " << run->getMin()
//             << "Max = " << run->getMax() << std::endl;

//   hist0->getHistogram()->Draw();
//   hist1->getHistogram()->Draw("same");
//   hist2->getHistogram()->Draw();

   //gPad->SetLogy();

   ecalE->getHistogram()->Draw();

   theApp.Run();
   return 0;
}
