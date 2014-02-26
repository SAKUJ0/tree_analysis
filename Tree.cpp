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

TH1F *BranchToHist(const vector<Branch*> branch, bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), Int_t nbins) {

   Int_t treesize = branch[0]->getSize();
   Int_t number_of_branches = branch.size();
   vector<Int_t> type(number_of_branches);
   vector<Float_t> var(number_of_branches);
   vector<UInt_t> var_int(number_of_branches);
   vector<TBranch*> tbranch(number_of_branches);

   branch[0]->getTTree()->SetBranchStatus("*", 0);

   for(Int_t i=0; i<number_of_branches; i++) {
      type[i] = branch[i]->getType();
      tbranch[i] = branch[i]->getTBranch();
      tbranch[i]->SetStatus(1);      
      if(type[i] == 5) //5: Float_t
         tbranch[i]->SetAddress(&var[i]);
      else if(type[i] == 13) //13: UInt_t
         tbranch[i]->SetAddress(&var_int[i]);
      else
         std::cerr << "Branch type not float/int. Type ID: " << type[i] << std::endl;
   }

   TH1F *hist = new TH1F("name","title", nbins, 0, 2);

   for(Int_t i=0; i<treesize; i++) {
      branch[0]->getTTree()->GetEntry(i);
      for(Int_t j=0; j<number_of_branches; j++) {
         if(type[j] == 13)  //13: UInt_t
            var[j] = static_cast<Float_t>(var_int[j]);
      }
      if(check(var) == false)
         continue;

      hist->Fill(transform(var));
   }

   return hist;
}

TH1F *Tree::getHistogram(const vector<std::string>& varname, bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), Int_t nbins) const {

   Int_t number_of_branches = varname.size();
   vector<Branch*> branches(number_of_branches);
   for(Int_t i=0; i<number_of_branches; i++)
      branches[i] = new Branch(ttree, varname[i]);

   return BranchToHist(branches, check, transform, nbins);
}
