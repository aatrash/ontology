#include "searchtree.h"

/************************************************************
 * Constructor.  Uses an existing ontology
 ************************************************************/
SearchTree::SearchTree(){

}

/************************************************************
 * Constructor.  Uses an existing ontology
 ************************************************************/
SearchTree::SearchTree(Ontology database){
  cout << "searchtree.cpp: Creating Search Tree.  Using a queue representation (BFS).\n";
  cout << "searchtree.cpp: Copying ontology\n";
  myOntology = database;
}


/************************************************************
 * Add a node to the tree.  Will need to check if it is a repeat or not.  Add
 * to either the stack, queue, or priority queue based on sorting method.
 ************************************************************/
void SearchTree::addNode(ModInterface newNode){

  // need to check for loops.  ie. maintain a set of visited nodes.
  // Check if the new node has already been examined

  set <ModInterface>::iterator iter;

  for (iter = ExaminedNodes.begin(); iter != ExaminedNodes.end(); ++iter){
    if (newNode.compare(*iter)){ 
      return; 
    }
  }
  // if not, then add it to the queue.

  SearchQueue.push(newNode);

}

/************************************************************
 * Add a vector of nodes to the tree.
 ************************************************************/
void SearchTree::addNode(vector <ModInterface> nodeList){

  // Iterate over nodeList and call addNode for each
  for (int i=0; i<nodeList.size(); i++){
    addNode(nodeList[i]);
  }

}


/*************************************************************
 *
 * return if the tree is empty or not
 *
 *************************************************************/
bool SearchTree::isEmpty(){

  if (SearchQueue.empty()){
    cout << "Search is empty\n";
  } else { cout << "SearchQueue is not empty\n";
  }
  return(SearchQueue.empty());

}

/************************************************************
 * Return the next node in the tree.
 ************************************************************/
ModInterface SearchTree::returnNext(){

  ModInterface newInterface = SearchQueue.front();
  SearchQueue.pop();

  return newInterface;

}



/************************************************************
  Search to find a potential interface which meets the requirements using the
  ontology as the database.
 ************************************************************/

void SearchTree::selectInterfacesSample(){

  // Create list of requirements
  //  Initalized from ontology
  // Create list of currently selected modalities
  // Create list of met requirements
  // for each item in requirements list
  // check if requirement has already been met
  // If not met yet
  //   Follow the "provides" backlinks --> Provides a list of potential modalities
  //   Select one modality from the list randomly
  //   Version 1) Add Modality.  Add requirements of modality. Add requirements it provides
  //     Assume requirement is met, add it to list of completed requirements
  // Repeat until requirements list empty
  // Need to check if all requirements can be met.  If not, then start over.
  //   Version 2) Iterate on modality.  Make sure requirements can be met before adding



  // Add the initial set of requirements by adding the requirements node
  ModInterface currentInterface;

  vector <ModInterface> potentialInterfaces;

  currentInterface.addModality(myOntology.getReqNode());
  currentInterface.print();


  // push the initial modality onto the search "tree" (ie. queue)
  addNode(currentInterface);

  // Now repeat until
  // 1) we have an interface with remaining requirements
  // or 2) until search tree is empty.  If empty, then fail.

  // while ((!isEmpty()) && currentInterface.hasRequirements())
  while (!isEmpty())
  {

    cout << "******************************************\n";
    cout << "Examining node\n";
    currentInterface.print();

    // Be careful about data structures here, we have Nodes, Interfaces, and a SearchTree

    if (!currentInterface.hasRequirements()){
      // add it to the list
      potentialInterfaces.push_back(currentInterface);
    } else {

    // 1) Generate the children of the current interface
    //vector <ModInterface> children = myOntology.makeChildren(currentInterface);
    vector <ModInterface> children = currentInterface.makeChildren(myOntology);

    // 2) Add those children to the tree
    addNode(children);

    // 3) Get the next interface to examine from the tree
   }

   currentInterface = returnNext();


  }

  cout << "\n\n********************************************************************************\n";
  cout << "********************************************************************************\n";

  for (int i=0; i<potentialInterfaces.size(); i++){ 
    potentialInterfaces[i].print(myOntology);
  cout << "********************************************************************************\n";
  }


}

