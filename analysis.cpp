#include <iostream>

#include <TApplication.h>

#include "Tree.h"

int main(int argc, char **argv) {

   TApplication theApp("App", &argc, argv);

   TFile *file = new TFile("tree.root", "READ");
   Tree *tree = new Tree(file);

   tree->getHistogram("EcalEnergy")->Draw();
   //tree->getTTree()->StartViewer();

   theApp.Run();

   //init data_file tree.root

   //create_hist tree.root, x, y

   //set style options
   
   //draw hist

   return 0;
}
