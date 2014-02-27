#include "Tree.h"

Tree::Tree(TFile *file) {
   TTree *tree;
   tree = (TTree*)file->Get("LeptonAnalysis");

   ttree = tree;
}

Int_t Tree::getSize() const {
   return ttree->GetEntries();
}

TH1F *Tree::BranchToHist(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), Int_t nbins) const{

   Int_t treesize = getSize();
   Int_t number_of_branches = branches.size();
   vector<Int_t> type(number_of_branches);
   vector<Float_t> var(number_of_branches);
   vector<UInt_t> var_int(number_of_branches);
   vector<TBranch*> tbranch(number_of_branches);

   ttree->SetBranchStatus("*", 0);

   for(Int_t i=0; i<number_of_branches; i++) {
      type[i] = branches[i]->getType();
      tbranch[i] = branches[i]->getTBranch();
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
      ttree->GetEntry(i);
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

TH1F *Tree::getHistogram(const vector<std::string>& varname, bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), Int_t nbins) {

   Int_t number_of_branches = varname.size();
   branches.resize(number_of_branches);
   for(Int_t i=0; i<number_of_branches; i++)
      branches[i] = new Branch(ttree, varname[i]);

   return this->BranchToHist(check, transform, nbins);
}
