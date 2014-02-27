#include <vector>
using std::vector;

#include <TH1F.h>

class Histogram {
   friend class Tree;
      TH1F *thistogram;
      bool (*check)(const vector<Float_t>&);
      Float_t (*transform)(const vector<Float_t>&);
      Int_t nbins;

   public:
      Histogram(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), Int_t nbins);

      TH1F *getHistogram() const; 
};
