#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "olink.h"
#include <vector>
#include <set>
#include <map>
using namespace std;

/*********************
 * This class represents a node in the ontology.  It will be one modality,
 * requirement, resource, etc...  The nodes will be connected via olinks to
 * create a network.
 */

class Node
{
  private:
    int id;
    string name;
    vector<Olink> Links;
    vector<Olink> BackLinks;

  public:
    Node();
    Node(string name, int id);
    // Get the ID of the node
    int getID(); 

    // Print the contents of this node
    void printNode();

    // Set the ID of the node
    void setID(int n_id);

    // Set the name of the node
    void setName(string n_name);

    // Add a link to the node.
    void addLink(string l_name, int end_node);
    void addLink(Olink l);

    // Add a backlink to this node (a link *in* from another node
    void addBackLink(Olink l);

    // Iterate over the links and change the start node to be the current node.
    void fixLinks();

    // Get the links out from this node
    vector<Olink> getLinks();

    // Get the links out from this node which have a name found in "Relationships"
    vector<Olink> getLinks(set <string> Relationships);

    // Get the requirements of this node 
    set <int> getRequirements();

    // Get the resources this node provides
    set <int> getResourcesProvided();

    // Get the list of nodes which provide this resource
    set <int> getSuppliers();

    // Get the list attributes associated with this node
    map <int,int> getAttributes();

    // Get the list of BackLInks into this node, ie.  links from other nodes into this one
    vector<Olink> getBackLinks();
    vector<Olink> getBackLinks(set <string> Relationships);

    // Get the name of this node
    string getName();

};

#endif

