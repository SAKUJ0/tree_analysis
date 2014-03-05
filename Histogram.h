#include <vector>
using std::vector;
#include <string>

#include <TH1F.h>

class Histogram {
   friend class Tree;
      TH1F *thistogram;
      bool (*check)(const vector<Float_t>&);
      Float_t (*transform)(const vector<Float_t>&);
      Int_t nbins;

      Float_t mean;
      Float_t rms;
      Float_t min;
      Float_t max;
      Int_t nentries;

   public:
      Histogram(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&)); 
      Histogram(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), const std::string& name, Int_t nbins, Float_t min, Float_t max, std::string title = std::string());
      Histogram(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), const std::string& name, Int_t nbins, Float_t* edges, std::string title = std::string()); 

      TH1F *getHistogram() const; 
      Float_t getMean() const; 
      Float_t getRMS() const; 
      Float_t getMin() const; 
      Float_t getMax() const; 
};
