
/********************************************************************************
 * Find a configure of interfaces which meets the requirements
 *  To begin with, we will implement a simple randomized approach
 * Old version.  Re-writing from scratch
 ********************************************************************************/
void Ontology::selectInterfacesSample_Old(){

  /* Summary:
   * Start with the requirements node
   * Maintain a list of requirements to be met.  Maintain as a stack (or queue?)
   * Add all of the initial requirements to the stack.
   * For each element in the stack
   * 1) Pop the element
   * 2) Follow the 'provides' backlinks to the requirement
   * 3) For the nodes which provide, add their requirements (if any)
   */

  queue<int> reqs;    // list of requirements
  queue<int> reqs_met; // of requirements that are already met
  queue<int> mods;    // list of suitable modalities

  set <int> result; // the list of modalities

  set <string> Relationships;  // the list of relationships to follow through the ontology
  Relationships.insert("provides");

  srand(time(NULL));

  cout << "\n\n\t+++++++++++++++++++++++++++++++\n\n\tBeginning Ontology Analysis\n\n";
  cout << "\t++++++++++++++++++++++++++++++++\n\n";

  // Get the links leading out of 'requirements'.  This should lead to the requirements (obviously)
  vector <Olink> links = Nodes[requirements_node_id].getLinks();

  // Iterate over the links
  for (int i=0; i<links.size(); i++){
    int j = links[i].getEnd();    // get the requirement
    cout << "Adding requirement " << Nodes[j].getName() << "\n";
    reqs.push(j);  // add it to the stack of requiremens
  }

  // Now we have initialized 'reqs'.  A stack with all the requirements
  // for each of the requirements, find the modalities which can provide it

  while (!reqs.empty()){ 

    // get the first in the list.
    int current_req = reqs.front();
    // reqs.pop();

    // Follow it's 'provides' backlinks
    vector <Olink> b_links = Nodes[current_req].getBackLinks(Relationships);

    cout << "*********************************************\n";
    Nodes[current_req].printNode();
    cout << "*********************************************\n";

    // Follow it's 'requires' links (of current_req, the current requirement we are investigating)

    // 1) Check to see if this is hardware on the robot.
    if (isRobotEquipment(Nodes[current_req])){
      cout << "Requirement is device on robot\n";
      result.insert(current_req);


    } else{
      // 2) Otherwise, let's find nodes which can provide that requirements
      cout << "Nodes which provide " << current_req << "\n";

      // Right now, b_links is the set of nodes which provide the requirement.
      // For now, we select one of them randomly.
      int r = rand() % b_links.size();

      // print out all the nodes which provide the requirement
      for (int i=0; i<b_links.size(); i++){
        cout << " Req Supplier\t" << b_links[i].getEnd() << "\n";
      }

      // We've now selected one at random
      cout << "Selecting r: " << r << "(" << b_links[r].getEnd() << ")\n";

      // Is the modality already in the list?  
      // result is a set of integers.  Check to see if 'r' is in the set.
      if (result.find(r) != result.end()){
        cout << "Already added.  Keep moving...\n";
      } else {
        // Add that to the list
        //result.insert(current_req);
        result.insert(r);
        // Also add it to the requirements
        //   reqs.push(current_req);
        cout << "Adding new requirement: " << Nodes[current_req].getName() << "\n";

      }

    }

  }

  // reqs.pop();

}



/********************************************************************************
 * Find a configure of interfaces which meets the requirements
 *  To begin with, we will implement a simple randomized approach
 ********************************************************************************/

void Ontology::selectInterfacesSample(){

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

  queue<int> requirements;  // the current list of requirements
  set<int> RequirementsMet; // current list of requirements met with the current interface
  set<int> current_interface; // the current interface.  Being constructed


  // The list of links to follow back from the requirement.  Right now, it's
  // only "provides" but can be expanded in the future.

  set <string> Relationships;
  Relationships.insert("provides");

  set <string> RequirementsNames;
  RequirementsNames.insert("requires");

  srand(time(NULL));  // Initialize the random seed.  Useful later

  cout << "\n\n*******************************************************************\n";
  cout << "********************** Beginning Ontology Analysis ****************\n";
  cout << "*******************************************************************\n";

  // First, get the list of requirements pointed to by the "requirements" node.
  // These will be the links leading out of the node.  Useful info:
  // requirements_node_id is the id of the main requirements node in the
  // ontology
  vector <Olink> requirements_links = Nodes[requirements_node_id].getLinks();

  // Follow these links to create the initial set of requirements
  for (int i=0; i<requirements_links.size(); i++){
    int j = requirements_links[i].getEnd();  // follow the link to the requirement node
    cout << "\tAdding requirement: " << Nodes[j].getName() << "\n";
    requirements.push(j);  // add j to the requirements list
  }

  // Iterate over the requirements list, examining each, removing it, until empty

  while (!requirements.empty()){
    // get the first requirement from the list
    int current_requirement = requirements.front();
    cout << "\tChecking requirement: " << current_requirement << "\n";

    // First, check if a requirement is equipment on the robot.  If so, SUCCESS
    if (isRobotEquipment(Nodes[current_requirement])){
      cout << "Requirement is device on robot!  Success!\n";
      current_interface.insert(current_requirement);
      RequirementsMet.insert(current_requirement);

      // Otherwise, let's do some work
    } else{

      cout << "Here!!\n";
      // For the current requirement, let's find all the modalities which can provide it.
      vector <Olink> providing_modalities = Nodes[current_requirement].getBackLinks(Relationships);
     
      cout << "\tNumber of providing modalities for " << current_requirement << " : " << providing_modalities.size();

      // Select one of the modalities at random
      int r = rand() % providing_modalities.size();
      // The rth modality from the list is....
      int TempModality = providing_modalities[r].getStart();

      // Add this modality to the interface
      if (current_interface.find(r) != current_interface.end()){
        cout << "Interface already added.  Moving along...\n";
      } else{

        current_interface.insert(r);
        // Now need to add teh requirements of that modality     
        // Get the requirements of modality r
        vector <Olink> RequirementsList = Nodes[r].getLinks(RequirementsNames);

        // Add only requirements not in the RequirementsMet set
        for (int i=0; i<RequirementsList.size(); i++){
          // Follow the link to get the requirement at the end

          // Add any requirements that haven't already been met
          int r2 = RequirementsList[i].getEnd();
          // Is r2 in RequirementsMet?  If not, add it
          if (RequirementsMet.find(r2) == RequirementsMet.end()){
            cout << "About to push..." << r2 << "\n";
            requirements.push(r2);
            cout << "Adding requirement " << r2 << "\n";
          }

          // Go ahead and add everything it provides

        }

      }


    }

    // Remove this requirement from the list
    requirements.pop();
  }

}


/********************************************************************************/
/********************************************************************************
 * Find a configure of interfaces which meets the requirements
 *  To begin with, we will implement a simple randomized approach
 ********************************************************************************/

void Ontology::selectInterfacesSample(){

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


  // make a queue of potential interfaces.  This will help with searching 
  SearchTree InterfaceTree;

  // Add the initial set of requirements by adding the requirements node
  ModInterface currentInterface;

  currentInterface.addModality(Nodes[requirements_node_id]);
  currentInterface.print();

  // push the initial modality onto the search "tree" (ie. queue)
  InterfaceTree.addNode(currentInterface);

  // Now repeat until 
  // 1) we have an interface with remaining requirements
  // or 2) until search tree is empty.  If empty, then fail.

  // while (!InterfaceTree.isEmpty())
  while ((!InterfaceTree.isEmpty()) && currentInterface.hasRequirements())
  {
    cout << "******************************************\n";
    cout << "Examining node\n";
    currentInterface.print();
    // Be careful about data structures here, we have Nodes, Interfaces, and a SearchTree

    // 1) Generate the children of the current interface
    vector <ModInterface> children = makeChildren(currentInterface);

    // 2) Add those children to the tree
    InterfaceTree.addNode(children);

    // 3) Get the next interface to examine from the tree
    currentInterface = InterfaceTree.returnNext();

  }


  cout << "\n\nDone! Found:\n";
  currentInterface.print();

  // Maintain a list of interfaces

  // From the most recent interface, get a requirement
  // need interface function to require missing requirement
  // Find a node which meets that requirement
  // nned node function which returns links to it
  // Add that node to the interface
  // need to add node to interface, must also take in ontology and requirements


}

