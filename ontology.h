#ifndef ONTOLOGY_H
#define ONTOLOGY_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <cstdlib>
#include <set>
#include <queue>
#include "node.h"
#include <time.h>

using namespace std;

/*! The ontology is a network of nodes connected by links that captures the
 * information about all the potential modalities, resources, and information
 * available.  The ontology contains all possible available information, which
 * is then searched to find a subset (or interface) which meets the
 * requirements.
 */

class Ontology
{

  protected:
    /// The list of nodes in the ontology
    vector<Node> Nodes;
    /// The total number of nodes
    int num_nodes;
    ///  Add the back links from a node, going back from the child to the parents
    void addBackLinks();
    /// ID of the requirements node
    int requirements_node_id;
    /// ID of the operator node
    int operator_node_id;
    /// ID of the robot node
    int robot_node_id; 
    /// ID of the environment node
    int environment_node_id;


  public:
    /// Default constructor function
    Ontology();

    /// Constructor function.  Reads ontology from a file
    /*!  
      @param filename the name of the file to be loaded
     */
    Ontology(std::string const & filename);

    /// Print out everything in the ontology
    void printOntology();

    /// Add a node to the ontology with name and id.  Creates the node from the information
    /*! 
      \param n_name the name of the node to add
      \param n_id the id of the node to add
     */
    void AddNode(string n_name, int n_id);

    /// Add a node to the ontology.
    /*! 
      \param new_node the node to be added
     */
    void AddNode(Node new_node);

    /// print the ontology as a dot graphic file format 
    /*! 
      \param filename The name of dot file to output
     */
    void printDotFile(string filename);

    /// Search through the ontology starting at 'start_id' and list out the attributes
    /*! 
      \param modalities The list of modalities in the currently selected interface
     */
    void listInterfaceAttributes(queue<int> modalities);

    /// Is this current node a piece of robot equipment.  Originally for older algorithm which was removed
    bool isRobotEquipment(Node node);

    /// Return the node in the ontology with id == nodeID
    Node getNode(int nodeID);

    /// Get the ID of the requirements node
    int getReqID();

    ///  Get the requirements node
    Node getReqNode();

    //  Make the children of a current interface
    //    vector <ModInterface> makeChildren(ModInterface I);

};

#endif

