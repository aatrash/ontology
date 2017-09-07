#include <iostream>
#include <set>
#include <queue>
#include "node.h"
#include "ontology.h"
#include "searchtree.h"

using namespace std;

int main(){
  //Ontology oComplete("interface.ont");
  Ontology oComplete("new_ontology.ont");
  oComplete.printOntology();
//  oComplete.printDotFile("graph2.dot");

  queue <int> mod;

  // For quick testing, add some nodes to be examined
  //mod.push(1);
  //mod.push(0);
  //mod.push(14);
  //oComplete.listInterfaceAttributes(mod);
  cout << "==================================================\n";

  SearchTree InterfaceTree(oComplete);
  InterfaceTree.selectInterfacesSample();

//  oComplete.selectInterfacesSample();


  

}

