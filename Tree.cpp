#include "Tree.h"

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

TH1F *Tree::getHistogram(const char* varname, Int_t nbins) const {

   TTree *tree = this->getTTree();
   TBranch *branch = tree->GetBranch(varname);

   Double_t min = tree->GetMinimum(varname);
   Double_t max = tree->GetMaximum(varname);

   TH1F *hist = new TH1F("name","title", nbins, min, max);

   TClass *tclass = new TClass();
   EDataType type;
   branch->GetExpectedType(*&tclass, type);

   if(type == 5) { //5: Float_t
      Float_t var;
      BranchToHist(branch, hist, var);
   }
   else if(type == 13) { //13: UInt_t
      UInt_t var;
      BranchToHist(branch, hist, var);
   }
   else
      std::cerr << "Branch type not float/int. Type ID: " << type << std::endl;

   return hist;
}
