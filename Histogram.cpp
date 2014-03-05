#include "Histogram.h"

Histogram::Histogram(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&))
{ 
   this->check = check;
   this->transform = transform;
   this->min = 0.0;
   this->max = 0.0;
   mean = 0.0;
   rms = 0.0;
   nentries = 0;
}

Histogram::Histogram(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), const std::string& name, Int_t nbins, Float_t min, Float_t max, std::string title) : Histogram(check, transform)
{
   if (title == "")
      title = name;
   thistogram = new TH1F(name.c_str(), title.c_str(), nbins, min, max);
   this->nbins = nbins;
}

Histogram::Histogram(bool (*check)(const vector<Float_t>&), Float_t (*transform)(const vector<Float_t>&), const std::string& name, Int_t nbins, Float_t* edges, std::string title) : Histogram(check, transform) 
{
   if (title == "")
      title = name;
   thistogram = new TH1F(name.c_str(), title.c_str(), nbins, edges);
   this->nbins = nbins;
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

Float_t Histogram::getMin() const {
   return min;
}

Float_t Histogram::getMax() const {
   return max;
}
