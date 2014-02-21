#include <iostream>
#include <string>
#include <vector>
using std::vector; using std::string;

#include <TApplication.h>

#include "Tree.h"
#include "Branch.h"

bool check(const vector<Float_t>& x) {
   return x[1] != 0.0;
}

Float_t transform(const vector<Float_t>& x) {
   if(x[1] != 0.0)
      return x[0] / x[1];
   else
      std::cerr << "Division by zero. Implement proper check function" << std::endl;
      return 0.0;
}

int main(int argc, char **argv) {
   TApplication theApp("App", &argc, argv);

   TFile *file = new TFile("tree.root", "READ");
   Tree *tree = new Tree(file);

   vector<string> varnames;
   varnames.push_back("EcalEnergy");
   varnames.push_back("TrackerRigidity");

   tree->getHistogram(varnames, check, transform, 200)->Draw();

   theApp.Run();
   return 0;
}
