#include "Histogram.h"

Histogram::Histogram(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), Int_t nbins) {
   thistogram = new TH1F("name","title", nbins, 0, 2);
   this->check = check;
   this->transform = transform;
   this->nbins = nbins;

   mean = 0.0;
   rms = 0.0;
   nentries = 0;
}

TH1F *Histogram::getHistogram() const {
   return thistogram;
}

Float_t Histogram::getMean() const {
   return mean;
}

Float_t Histogram::getRMS() const {
   return rms;
}
