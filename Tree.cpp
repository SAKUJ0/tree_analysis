#include "Tree.h"

Tree::Tree(TFile *file, const std::string& name) {
   TTree *tree;
   tree = (TTree*)file->Get(name.c_str());

   ttree = tree;
}

void Tree::setBranch(const std::string& name) {
   branches.push_back(new Branch(ttree, name));
}

Histogram *Tree::setHistogram(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), Int_t nbins) {
   Histogram *hist = new Histogram(check, transform, nbins);
   histograms.push_back(hist);
   return hist;
}

void Tree::traverse(void (Tree::*process)(const vector<Float_t>& var, const Int_t& j) const) const {

   Int_t treesize = ttree->GetEntriesFast();
   Int_t number_of_branches = branches.size();
   Int_t number_of_histograms = histograms.size();

   vector<Int_t>     type(number_of_branches);
   vector<Float_t>   var(number_of_branches);
   vector<UInt_t>    var_int(number_of_branches);
   vector<TBranch*>  tbranch(number_of_branches);

   ttree->SetBranchStatus("*", 0);

   for(Int_t i=0; i<number_of_branches; i++) {
      type[i] = branches[i]->getType();
      tbranch[i] = branches[i]->tbranch;
      tbranch[i]->SetStatus(1);      
      if(type[i] == 5) //5: Float_t
         tbranch[i]->SetAddress(&var[i]);
      else if(type[i] == 13) //13: UInt_t
         tbranch[i]->SetAddress(&var_int[i]);
      else
         std::cerr << "Branch type not float/int. Type ID: " << type[i] << std::endl;
   }

   for(Int_t i=0; i<treesize; i++) {
      ttree->GetEntry(i);

      for(Int_t j=0; j<number_of_branches; j++)
         if(type[j] == 13)  //13: UInt_t
            var[j] = static_cast<Float_t>(var_int[j]);

      for(Int_t j=0; j<number_of_histograms; j++) {
         if(histograms[j]->check(var) == false)
            continue;
         (*this.*process)(var, j); 
      }
   }
}

void Tree::processFillHistograms(const vector<Float_t>& var, const Int_t& j) const {
   histograms[j]->thistogram->Fill(histograms[j]->transform(var));
}

void Tree::fillHistograms() const {
   traverse(&Tree::processFillHistograms);
}

void Tree::processCalculateMean(const vector<Float_t>& var, const Int_t& j) const {
   histograms[j]->mean += histograms[j]->transform(var);
   histograms[j]->nentries++;
}

void Tree::calculateMean() const {
   Int_t number_of_histograms = histograms.size();
   Int_t number_of_entries = 0;

   traverse(&Tree::processCalculateMean);

   for (Int_t i = 0; i < number_of_histograms; i++ ){
      number_of_entries = histograms[i]->nentries;
      if(number_of_entries != 0)
         histograms[i]->mean /= number_of_entries;
   }
}

void Tree::processCalculateRMS(const vector<Float_t>& var, const Int_t& j) const {
   histograms[j]->rms += pow(histograms[j]->transform(var) - histograms[j]->mean, 2);
}

void Tree::calculateRMS() const {
   Int_t number_of_histograms = histograms.size();
   Int_t number_of_entries = 0;

   bool mean_is_calculated = true;
   for (Int_t i = 0; i < number_of_histograms; i++ )
      mean_is_calculated = histograms[i]->nentries > 0;
   if(!mean_is_calculated)
      calculateMean();

   traverse(&Tree::processCalculateRMS);

   for (Int_t i = 0; i < number_of_histograms; i++ ){
      number_of_entries = histograms[i]->nentries;
      if(number_of_entries != 0)
         histograms[i]->rms = sqrt(histograms[i]->rms / number_of_entries);
   }
}
