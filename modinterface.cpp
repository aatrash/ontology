#include "modinterface.h"

ModInterface::ModInterface(){
}

/************************************************************
 * Add a modality to the interface
 *************************************************************/
void ModInterface::addModality(Node modality){

  cout << "modinterface.cpp:\tAdding modality: " << modality.getName() << "\n";

  // Add the modality
  currentModalities.insert(modality.getID());

  // Add it's requirements
  set <int> requirements = modality.getRequirements();
  vector <int> temp_required; 


  set <int> newRequirementsAll;

  // Creating NewRequirementsAll   ***********************
  // Need to make the union between the old requirements set on the new requirements added
  // Update the requirementsLeft 
  if (requirementsLeft.empty()){
    newRequirementsAll = requirements;
  } else if (requirements.empty())
  {
    // no change to Requirements
    newRequirementsAll = requirementsLeft;

  } else {
  //  set_union(requirements.begin(), requirements.end(),
  //      requirementsLeft.begin(), requirementsLeft.end(), temp_required.begin());
    set_union(requirements.begin(), requirements.end(),
        requirementsLeft.begin(), requirementsLeft.end(), inserter(temp_required, temp_required.end()));
    newRequirementsAll = set <int> (temp_required.begin(), temp_required.end());
  }

  // Creating requirementsMet   ***********************
  // newRequirementsAll now has ALL the old requirements plus the new
  // requirements added by the new modality.  This may include requirements
  // already met, as well as the requirements for which this modality was
  // added.

  // Next we add the requirements met by the new modality to the old set of requirements met.  
  // This gives us ALL the requirements met by the new interface.


  vector <int> temp_provided;
  set <int> provided = modality.getResourcesProvided();
  if (requirementsMet.empty()){
    // if the current requirements list is empty, just make it the requirements
    // provided by the modality we just added.
    requirementsMet = provided;
  } else {
    // otherwise, combine it with the previous requirementsMet list
  /*  set_union(provided.begin(), provided.end(),
        requirementsMet.begin(), requirementsMet.end(), temp_provided.begin());*/
    set_union(provided.begin(), provided.end(),
        requirementsMet.begin(), requirementsMet.end(), inserter(temp_provided, temp_provided.end()));
    set <int> newRequirementsMet(temp_provided.begin(), temp_provided.end());
    requirementsMet = newRequirementsMet;
  }


  // Creating requirementsLeft   ***********************
  // We have now updated all the requirements met by the current interface,
  // including the most recently added modality.   We need to filter out stuff
  // from the requirements.  We'll find the elements in newRequirementsAll but
  // NOT in requirementsMet.  This will then become requirementsLeft.
  vector <int> diffRequirements;
  // if newRequirementsAll is empty, it means there are currently no unmet requirements
  // if requirementsMet is empty, it means the current interface provides no resources
  if (newRequirementsAll.empty())
  {
    requirementsLeft = newRequirementsAll;

  } else if (requirementsMet.empty())
  {
    requirementsLeft = newRequirementsAll;

  } else
  {
    set_difference(newRequirementsAll.begin(), newRequirementsAll.end(),
        requirementsMet.begin(), requirementsMet.end(), inserter(diffRequirements, diffRequirements.end())); 
    requirementsLeft = set <int> (diffRequirements.begin(), diffRequirements.end());

  }

  // Time to add the attributes.  
  // Need to account for valued links as well.
  // This will be tricky.  If the attribute is valued, and already is listed, then increment by the value.
  // Otherwise, initialize

  // We'll be using a map for this.  Hash table style.
  // key on the attribute ID.  

  // 1) Get the list of attributes of the current modality

  map <int,int> attr = modality.getAttributes();

  // Iterate over the attributes.

  if (attr.empty()){ 
    cout << "modinterface.cpp: Node has no attributes\n";
  } else {
    cout << "modinterface.cpp: Attributes not empty\n";
    for (map<int,int>::iterator it=attr.begin(); it!=attr.end(); ++it){

      int a = it->first;
      int v = it->second;
      // 2) Check of that attribute has already been added to the list

      cout << "Attributes: "  << it->first << " " << it->second << "\n";
      if ( attributes.find(it->first) == attributes.end() ) {
        cout << "modinterface.cpp: Attribute already exists in interface. \n";
        // if it's not valued, then don't worry.  Already there.
        if (v >= 0){
          attributes[a] = attributes[a]+v;
        }

        // not found
      } else {
        cout << "modinterface.cpp: Attribute new to interface. \n";

        attributes[a] = v;

      }

      // 3) If not, then


    }

  }

  //set <int> diffRequirementsTemp(diffRequirements.begin(), diffRequirements.end());
  // requirementsLeft = diffRequirementsTemp;

  // Logic:  Add all of it's requirements to requirementsLeft, then update
  // RequirementsMet, then remove requirementsMet from requirementsLeft

  // Add the resources it provides

  // update the requirements based on the resources it provides


  // also update the requirementsMet;

}

/************************************************************
 * Return the list of unmet requirements of the interface.
 *************************************************************/

set <int> ModInterface::getRequirements(){

  return(requirementsLeft);

}


/************************************************************
 * Does this interface still have requirements to fulfill?
 *************************************************************/

bool ModInterface::hasRequirements(){

  if (requirementsLeft.empty()){
    return false;
  } else{ 
    return true;
  }

}


/************************************************************
 * Print out this interface
 *************************************************************/

void ModInterface::print(){

  set <int>::iterator iter;

  cout << "Modalities:\n";
  
  for (iter=currentModalities.begin(); iter != currentModalities.end(); ++iter){
    cout << "\t" << *iter << "\n";
  }

  cout << "requirementsMet:\n";
  
  for (iter=requirementsMet.begin(); iter != requirementsMet.end(); ++iter){
    cout << "\t" << *iter << "\n";
  }

  cout << "requirementsLeft:\n";
  
  for (iter=requirementsLeft.begin(); iter != requirementsLeft.end(); ++iter){
    cout << "\t" << *iter << "\n";
  }

  cout << "attributes:\n";

  map <int,int>::iterator it;


  for (map<int,int>::iterator it=attributes.begin(); it!=attributes.end(); ++it){

    // 2) Check of that attribute has already been added to the list

    // 3) If not, then

    cout << "\t"  << it->first << " " << it->second << "\n";
  }

}

/************************************************************
 * Print out this interface.  Ontology input for better output
 *************************************************************/

void ModInterface::print(Ontology O){

  set <int>::iterator iter;

  cout << "Modalities:\n";
  
  for (iter=currentModalities.begin(); iter != currentModalities.end(); ++iter){
    cout << "\t" << O.getNode(*iter).getName() << " " << *iter << "\n";
  }

  cout << "requirementsMet:\n";
  
  for (iter=requirementsMet.begin(); iter != requirementsMet.end(); ++iter){
    cout << "\t" << O.getNode(*iter).getName() << " " << *iter << "\n";
  }

  cout << "requirementsLeft:\n";
  
  for (iter=requirementsLeft.begin(); iter != requirementsLeft.end(); ++iter){
    cout << "\t" << O.getNode(*iter).getName() << " " << *iter << "\n";
  }

  cout << "attributes:\n";

  map <int,int>::iterator it;


  for (map<int,int>::iterator it=attributes.begin(); it!=attributes.end(); ++it){

    // 2) Check of that attribute has already been added to the list

    // 3) If not, then
    cout << "\tAttribute: "  << O.getNode(it->first).getName() << " value: " << it->second << "\n";
  }

}

/************************************************************
 * Compare two interfaces
 *************************************************************/

bool ModInterface::compare(const ModInterface &b){

  if (currentModalities != b.currentModalities) return false;
  if (requirementsMet != b.requirementsMet) return false;
  if (requirementsLeft != b.requirementsLeft) return false;

  return true;

}


/********************************************************************************
 * Given an interface, make all the children of that interface
 *  ********************************************************************************/

vector <ModInterface> ModInterface::makeChildren(Ontology myOntology){

  vector <ModInterface> children;
  // get all of it's requirements
  //requirementsLeft = getRequirements();


  for (set <int>::iterator i = requirementsLeft.begin(); i != requirementsLeft.end(); i++){
    int currentRequirement = *i;
    // For each requirement

    cout << "\tChecking requirement " << currentRequirement << "\n";
    // Get the list of modalities which meet those requirements
    set <int> Suppliers = myOntology.getNode(currentRequirement).getSuppliers();
    cout << "\t\tHas " << Suppliers.size() << " suppliers\n";

    // For each of those modalities
    for (set <int>::iterator j = Suppliers.begin(); j != Suppliers.end(); j++){
      int currentMod = *j;

      cout << "modinterface.cpp: Returning requirements node\n";
      // Create a new interface with that modality added
      ModInterface newInterface = *this;
      newInterface.addModality(myOntology.getNode(currentMod));

      // is that modality new?  If so, cram it into the queue
      children.push_back(newInterface);
    }

    // otherwise, just ignore
  }

  return(children);

}



