#include <iostream>
#include <set>
#include <queue>
#include "node.h"
#include "ontology.h"

using namespace std;

int main()
{
  Ontology oComplete("interface.ont");
 
  ModInterface currentInterface; 
  ModInterface testInterface;
 
  int ReqID = oComplete.getReqID();
  Node ReqNode = oComplete.getNode(ReqID);
  
  currentInterface.addModality(ReqNode);
  currentInterface.print(); 
  currentInterface.addModality(oComplete.getNode(18));
  currentInterface.print(); 
  currentInterface.addModality(oComplete.getNode(9));
  currentInterface.print(); 
  currentInterface.addModality(oComplete.getNode(0));
  currentInterface.print(); 

  testInterface.addModality(ReqNode);
  testInterface.print(); 
  testInterface.addModality(oComplete.getNode(18));
  testInterface.print(); 
  testInterface.addModality(oComplete.getNode(9));
  testInterface.print(); 
  testInterface.addModality(oComplete.getNode(0));
  testInterface.print(); 

  if (currentInterface.compare(testInterface)) cout << "True!!!\n";
  else cout << "False!!!\n";

  if (currentInterface == testInterface) cout << "True!!!\n";
  else cout << "False!!!\n";
}
