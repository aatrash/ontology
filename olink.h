#ifndef OLINK_H
#define OLINK_H

#include <iostream>
#include <string>

using namespace std;

/* Olinks connect the nodes in the ontology.  These describe the relationships
 * between the start node and end node.
*/

class Olink
{

  private:
    int start_node;
    int end_node;
    string name;
    int value;
    bool valued;


  public:
    Olink();
    Olink(string n_name, int node1, int node2);

    // Print the information about this link
    void printLink();

    // Set the name of this link
    void setName(string n_name);

    // Set the starting node of this link
    void setStart(int node_id);

    // Set the terminating node of this link
    void setEnd(int node_id);

    // Set all the info about this link at once
    void setInfo(string n_name, int node1, int node2);
    void setInfo2(string n_name, int node2);
    void setValue(int v);

    // Return the starting point of this link
    int getStart();

    // Return the end point of this link
    int getEnd();

    // Return the name of this link
    string getName();

    // is the link a valued link? (has a numeric value associated with it)
    bool isValued();
    int getValue();  // return that value

};


#endif 
