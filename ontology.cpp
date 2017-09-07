#include "ontology.h"	

Ontology::Ontology(){


}

/********************************************************************************
 * Constructor function.  Reads the nodes and links from a file 
 * specified by 'filename'. 
 ********************************************************************************/
Ontology::Ontology(std::string const & filename){

  cout << "Reading Ontology from file:" << filename << "\n";

  ifstream ontFile;
  string line;
  string token;

  ontFile.open(filename.c_str());

  if (ontFile.is_open()){

    // Get the line from the file
    while (getline (ontFile, line) ){

      // each line is a node
      Node n;
      //    cout << line  << "\n";
      istringstream ss(line);

      // We have the line in 'line'.  Time to parse. 
      // First split on the semicolons.  ';'
      while (getline(ss, token, ';')){
        // Each token is potentially a new link (anything except 'name' and 'id'

        // Create the link
        Olink l;

        // Now need to split 'token' on ':'
        // token should be 'relationship:target' 
        string relationship;
        string target;
        istringstream ss2(token);
        getline(ss2, relationship, ':');
        getline(ss2, target);

        // If the relationship is 'name' then set the node name 
        if (relationship.compare("name") == 0){
          n.setName(target);
        } // If the relationship is 'id' then set the node name 
        else if (relationship.compare("id") == 0){
          n.setID(std::atoi(target.c_str()));
        }
        else {

          // Need to check if the liink has a parameter
          // Check the "relationship" variable to see if something is in () A
          // First, see if anything exists before a opening paren
          size_t opening_p = relationship.find("("); //)
          if (opening_p != string::npos){ //)
            cout << "Parameter found!!!!!" << opening_p << " " << opening_p + 1 << "\n"; 
            //(
            size_t closing_p = relationship.find(")"); //
            cout << "Closing found at " << closing_p << "\n";
            string val = relationship.substr(opening_p + 1, closing_p - opening_p-1);
            string name = relationship.substr(0, opening_p);
            cout << "Parameter value: " << name << " " << val << "\n";
            // Update the link info
            l.setInfo2(name, std::atoi(target.c_str()));
            l.setValue(atoi(val.c_str()));
            // Add the link to the node
            n.addLink(l);
          } else {
            // Otherwise, just update as usual
            // Update the link info
            l.setInfo2(relationship, std::atoi(target.c_str()));
            // Add the link to the node
            n.addLink(l);
          }
        }


      } // while (getline(ss, token, ';'))

      // Add the node to the ontology
      n.fixLinks();
      AddNode(n);

    }
    ontFile.close();

    // Now need to iterate over the ontology and add the backlinks
    // Iterate over all the nodes
    if (Nodes.size() == 0){
      cout << "There are no nodes in the ontology.\n";
    } else {
      for (int i=0; i<Nodes.size(); i++){
        // for each node, get the set of links
        vector <Olink> links = Nodes[i].getLinks();
        // For each link, look at the start_id, and end_id.  Reverse them, make a link, and add it to the
        // backlink of the end_id node
        for (int j=0; j<links.size(); j++){
          int start_id = links[j].getStart();
          int end_id = links[j].getEnd();
          Olink blink(links[j].getName(), end_id, start_id);
          Nodes[end_id].addBackLink(blink);
        }

      }
    }

  }

}

/********************************************************************************
 * Traverse through the now-read in ontology to add all the backlinks to the nodes
 ********************************************************************************/
void Ontology::addBackLinks(){

}

/********************************************************************************
 * Add a node to the ontology with name n_name and id n_id.  This function *might*
 * have been made obsolete after recent changes.
 ********************************************************************************/
void Ontology::AddNode(string n_name, int n_id){

  // if this node is larger than the current vector length, 
  // then resize the vector to accomodate
  if (Nodes.capacity() <= n_id){
    Nodes.resize(n_id+1);
  }

  Nodes[n_id] = Node(n_name, n_id);


}


/********************************************************************************
 * Add a new node to the ontology.  This node has already been created and only 
 * needs to be inserted
 ********************************************************************************/
void Ontology::AddNode(Node new_node){

  int n_id;

  n_id = new_node.getID();
  // if this node is larger than the current vector length, 
  // then resize the vector to accomodate
  if (Nodes.size() <= n_id+1){
    Nodes.resize(n_id+1);
  }

  //Nodes.push_back(new_node);
  Nodes[n_id] = new_node;

  // Check this node.  If it is 'requirements', 'operator', 'robot', or 'enviornment'
  // we need to store that info

  if (new_node.getName().compare("requirements") == 0){
    cout << "Found the requirements node\n";
    requirements_node_id = new_node.getID();
  }
  if (new_node.getName().compare("operator") == 0){
    cout << "Found the operator node\n";
    operator_node_id = new_node.getID();
  }
  if (new_node.getName().compare("robot") == 0){
    cout << "Found the robot node\n";
    robot_node_id = new_node.getID();
  }
  if (new_node.getName().compare("environment") == 0){
    cout << "Found the environment node\n";
    environment_node_id = new_node.getID();
  }

}


/********************************************************************************
 * Print out the Ontology
 ********************************************************************************/

void Ontology::printOntology(){
  cout << "=============================================\n";
  cout << "Print Ontology...\n";
  cout << "Number of nodes: " << Nodes.size() << "\n";
  cout << "Requirements Node ID: " << requirements_node_id << "\n";
  cout << "Operator Node ID: " << operator_node_id << "\n";
  cout << "Robot Node ID: " << robot_node_id << "\n";
  cout << "Environment Node ID: " << environment_node_id << "\n";

  if (Nodes.size() == 0){
    cout << "There are no nodes in the ontology.\n";
  } else {
    for (int i=0; i<Nodes.size(); i++){
      Nodes[i].printNode();
    }
  }

  cout << "=============================================\n";


}

/********************************************************************************
 * Print out dot file.  Visualize using vimdot
 ********************************************************************************/

void Ontology::printDotFile(string filename){

  ofstream dotfile;

  dotfile.open(filename.c_str());

  dotfile << "digraph Ontology {\n";

  // Iterate over all the nodes in the ontology.  
  if (Nodes.size() == 0){
    cout << "There are no nodes in the ontology.\n";
  } else {
    // first print the main nodes;
    dotfile << "\t\toperator [ color=\"red\"];\n";
    dotfile << "\t\trobot [ color=\"blue\"];\n";
    dotfile << "\t\trequirements [ color=\"green\"];\n";
    dotfile << "\t\tenvironment [ color=\"orange\"];\n";

    for (int i=0; i<Nodes.size(); i++){
      vector<Olink> l;
      l = Nodes[i].getLinks();
      for (int j=0; j<l.size(); j++){
        // For each link, get the start and end
        int start_id = l[j].getStart();
        int end_id = l[j].getEnd();
        string label = l[j].getName();
        string start_name = Nodes[start_id].getName();
        string end_name = Nodes[end_id].getName();
        dotfile << "\t\t" << start_name << " -> " << end_name;
        if (l[j].isValued()){
          dotfile <<  " [ label =\"" << label << "(" << l[j].getValue() <<  ")\"];\n";
        } else {
          dotfile <<  " [ label =\"" << label << "\"];\n";

        }
      }
    }
  }


  // For each node, iterate over each link and add that to the graph


  dotfile << "}0\n";
  dotfile.close();
}



/********************************************************************************
 * Search through the ontology starting at 'start_id' and list out the attributes
 ********************************************************************************/
void Ontology::listInterfaceAttributes(queue<int> modalities){

  int start_id;

  set<string> Relationships;
  Relationships.insert("represents");
  Relationships.insert("displays");

  cout << "Analyzing ontology\n";
  // iterate over the list of modalities
  //  using only start_id for now, but this should become a vector or array

  while (!modalities.empty()){

    start_id = modalities.front();
    modalities.pop();
    vector <Olink> links = Nodes[start_id].getLinks();
    cout << "\t" << Nodes[start_id].getName() << "\n";
    // Iterate over the set of links
    for (int i=0; i<links.size();i++){
      cout << "\t\t" << links[i].getName() << " : ";
      int j = links[i].getEnd();
      cout << Nodes[j].getName() << "\n";
      // Need to follow specific link names
      if (Relationships.find(links[i].getName()) != Relationships.end()){
        modalities.push(j);
      }
    }

  }


}

/********************************************************************************
 * Check if a node is equipment on the robot (or potentially on the robot)
 ********************************************************************************/
bool Ontology::isRobotEquipment(Node node)
{
  // check if one of the Backlinks into the node is an 'is' from 'robot
  // if so, return True, otherwise, return False
  set <string> Relationships;
  Relationships.insert("has");

  vector <Olink> b_links = node.getBackLinks(Relationships);

  if (b_links.size() == 0){
    return false;
  }

  for (int i=0; i<b_links.size(); i++){
    int original_node = b_links[i].getEnd();
    if (Nodes[original_node].getName().compare("robot") == 0){
      return true;
    }
  }

  return false;

}


/********************************************************************************
 * Return the node with nodeID
 ********************************************************************************/
Node Ontology::getNode(int nodeID)
{

  return(Nodes[nodeID]);

}

/********************************************************************************
 * Get the requirements node ID
 ********************************************************************************/
int Ontology::getReqID()
{

  return(requirements_node_id);

}

/********************************************************************************
 * Get the requirements node ID
 ********************************************************************************/
Node Ontology::getReqNode()
{

  cout << "ontology.cpp: Returning requirements node\n";
  return(getNode(getReqID()));

}
