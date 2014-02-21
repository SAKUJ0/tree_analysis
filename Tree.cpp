#include "Tree.h"
#include "Branch.h"

Tree::Tree(TFile *file) {
   TTree *tree;
   tree = (TTree*)file->Get("LeptonAnalysis");

   this->setTTree(tree);
}

Int_t Tree::getSize() const {
   return ttree->GetEntries();
}

void Tree::setTTree(TTree* tree) {
   ttree = tree;
}

TTree *Tree::getTTree() const {
   return ttree;
}

template <typename Number>
void BranchToHist(TBranch *branch, TH1F *hist, Number &var) {
   Int_t treesize = branch->GetEntries();
   branch->SetAddress(&var);
   for(Int_t i=0; i<treesize; i++) {
      branch->GetEntry(i);
      hist->Fill(var);
   }
}

TH1F *Tree::getHistogram(std::string varname, Int_t nbins) const {

   TH1F *hist = new TH1F("name","title", nbins, 0, 10000000000);

   Branch *branch = new Branch(ttree, varname);

   if(branch->getType() == 5) { //5: Float_t
      Float_t var;
      BranchToHist(branch->getTBranch(), hist, var);
   }
   else if(branch->getType() == 13) { //13: UInt_t
      UInt_t var;
      BranchToHist(branch->getTBranch(), hist, var);
   }
   else
      std::cerr << "Branch type not float/int. Type ID: " << branch->getType() << std::endl;

   return hist;
}
