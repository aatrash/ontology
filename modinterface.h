#ifndef MODINTERFACE_H
#define MODINTERFACE_H

#include <iostream>
#include <algorithm>
#include "node.h"
#include <map>
#include "ontology.h"

using namespace std;

/* The interface object will include information about the current interface,
   including the current modalities selected, the current requirements met, and
   the remaining requirements to be met. */

class ModInterface
{
  protected:

    set <int> currentModalities;   // Modalities in the current interface
    set <int> requirementsMet;  // The requirements met by the current interface
    set <int> requirementsLeft;  // the requirements required by the current interface which have not currently been met

    map <int,int> attributes;

  public:
    ModInterface();

    // Add a modality to the current interface.
    void addModality(Node modality);    

    // Get the requirements of the current interface
    set <int> getRequirements();   

    // Check if the current interface has any requirements
    bool hasRequirements();

    // Print otu the current interface
    void print();
    void print(Ontology O);

    // Print otu the current interface
    bool compare(const ModInterface &b);

    bool operator == (ModInterface& d) {
      return compare(d);
    }

    vector <ModInterface> makeChildren(Ontology myOntology);

};
#endif
