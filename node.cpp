#include "node.h"


/********************************************************************************
 * Get the ID of the node
 ********************************************************************************/
int Node::getID(){

  return id;
}

/********************************************************************************
 * Default Node Constructor
 ********************************************************************************/
Node::Node(){
}


/********************************************************************************
// Node constructor given the name and id of the node
 ********************************************************************************/
Node::Node(string c_name, int c_id){

  name = c_name;
  id = c_id;

}

/********************************************************************************
// Print the information in the node
 ********************************************************************************/
void Node::printNode(){
  cout << "ID: " << id << " Name: " << name << "\n";
  cout << "\tLinks:\n";
  for (int i=0; i<Links.size(); i++){
    Links[i].printLink();
  }
  cout << "\tBackLinks:\n";
  for (int i=0; i<BackLinks.size(); i++){
    BackLinks[i].printLink();
  }
}

/********************************************************************************
// Set the ID number of the node
 ********************************************************************************/
void Node::setID(int n_id){
  id = n_id;
}

/********************************************************************************
 * Set the name of the node
 ********************************************************************************/
void Node::setName(string n_name){
  name = n_name;
}

/********************************************************************************
 * Add a link to the node.
 ********************************************************************************/
void Node::addLink(Olink l){

  Links.push_back(l);

}

/********************************************************************************
 * Add a back link to the node.
 ********************************************************************************/
void Node::addBackLink(Olink l){

  BackLinks.push_back(l);

}

/********************************************************************************
 * Iterate over the links and change the start node to be the current node.
 ********************************************************************************/
void Node::fixLinks(){

  for (int i=0; i<Links.size(); i++){
    Links[i].setStart(id);
  }
}

/********************************************************************************
 * Return a list of the links in a node
 ********************************************************************************/
vector<Olink> Node::getLinks(){

  return Links;

}
/********************************************************************************
 * Return a list of the links to the node
 * ONLY return the links with names in 'relationships'
 ********************************************************************************/
vector<Olink> Node::getLinks(set <string> Relationships){

  vector <Olink> LinkSubset;

  // Iterate over the Backlinks
  for (int i=0; i < Links.size(); i++){
    if (Relationships.find(Links[i].getName()) != Relationships.end()){
     // Add that node to the subset
     LinkSubset.push_back(Links[i]);
    }
  }

  return LinkSubset;

}

/********************************************************************************
 * Return a list of REQUIREMENTS of the node
 ********************************************************************************/
set <int> Node::getRequirements(){

  set <string> RequirementsNames;
  RequirementsNames.insert("requires");

  set <int> Requirements;

  vector <Olink> RequirementsList = getLinks(RequirementsNames);
  // construct the in version of this 

  for (int i=0; i<RequirementsList.size(); i++){
    Requirements.insert(RequirementsList[i].getEnd());
   
  }

  return (Requirements);

}

/********************************************************************************
 * Return a list of reources provided by the node
 ********************************************************************************/
set <int> Node::getResourcesProvided(){

  set <string> RequirementsNames;
  RequirementsNames.insert("provides");
  RequirementsNames.insert("has");

  set <int> Requirements;

  vector <Olink> RequirementsList = getLinks(RequirementsNames);
  // construct the in version of this 

  for (int i=0; i<RequirementsList.size(); i++){
    Requirements.insert(RequirementsList[i].getEnd());
   
  }

  return (Requirements);


}
/********************************************************************************
 * Return a list of nodes which provide this resource
 ********************************************************************************/

set <int> Node::getSuppliers(){

  set <string> SupplyLinkName;
  SupplyLinkName.insert("provides");
  SupplyLinkName.insert("has");

  set <int> Suppliers;

  vector <Olink> SuppliersList = getBackLinks(SupplyLinkName);
  // construct the in version of this 

  for (int i=0; i<SuppliersList.size(); i++){
    Suppliers.insert(SuppliersList[i].getEnd());
   
  }

  return (Suppliers);


}

// Get the list attributes associated with this node
map <int,int> Node::getAttributes(){

  set <string> AttributeLinkName;
  AttributeLinkName.insert("attribute");
  map <int, int> attributeSet;

  // Iterate over the links
  for (int i=0; i < Links.size(); i++){
    // if the link is labelled "attribute", then we want to keep it
    if (AttributeLinkName.find(Links[i].getName()) != AttributeLinkName.end()){
      cout << "node.cpp : attribute found\n";
      // check if that node is valued
      int nodeID = Links[i].getEnd();
      if (Links[i].isValued()){
        attributeSet[nodeID] = Links[i].getValue();
      } else {
        attributeSet[nodeID] = -1;
      }
    }
  }
  
  return attributeSet;

}


/********************************************************************************
 * Return a list of the back links to the node
 ********************************************************************************/
vector<Olink> Node::getBackLinks(){

  return BackLinks;

}


/********************************************************************************
 * Return a list of the back links to the node
 * ONLY return the links with names in 'relationships'
 ********************************************************************************/
vector<Olink> Node::getBackLinks(set <string> Relationships){

  vector <Olink> BackLinkSubset;

  // Iterate over the Backlinks
  for (int i=0; i < BackLinks.size(); i++){
    if (Relationships.find(BackLinks[i].getName()) != Relationships.end()){
     // Add that node to the subset
     BackLinkSubset.push_back(BackLinks[i]);
    }
  }

  return BackLinkSubset;

}
/********************************************************************************
 * Return a list of the links in a node
 ********************************************************************************/
string Node::getName(){

  return name;

}


