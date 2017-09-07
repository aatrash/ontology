#include <iostream>
#include <set>
#include <queue>
#include "node.h"
#include "ontology.h"

using namespace std;

int main(){
  Ontology oComplete("new_ontology.ont");
  oComplete.printOntology();
  oComplete.printDotFile("new_ontology.dot");
}

