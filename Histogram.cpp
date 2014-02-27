#include "Histogram.h"

Histogram::Histogram(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), Int_t nbins) {
   thistogram = new TH1F("name","title", nbins, 0, 2);
   this->check = check;
   this->transform = transform;
   this->nbins = nbins;
}

TH1F *Histogram::getHistogram() const {
   return thistogram;
}
