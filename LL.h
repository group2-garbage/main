#ifndef LL_H
#define LL_H

#include "node.h"
#define MAX 15 //max capacity of each bin (kg)
#define MIN 3 //min kg for throwing waste out of the bin
typedef node* nodePtr;

class LL{
  private:        
      nodePtr hol;// node * hol; head of linked list
      int size;
    // total weights in each bin (kg)
      double totalWeightRecycling = 0; 
      double totalWeightCompost = 0; 
      double totalWeightEWaste = 0; 
      double totalWeightHazardous = 0; 
      double totalWeightGeneral = 0; 

      //track auto-throw count for each bin
      int countThrowRecycling = 0;
      int countThrowCompost = 0;
      int countThrowEWaste = 0;
      int countThrowHazardous = 0;
      int countThrowGeneral = 0;

      //track item in each bin
      int totalRecycling = 0;
      int totalCompost = 0;
      int totalEWaste = 0;
      int totalHazardous = 0;
      int totalGeneral = 0;
  public:
      LL();
      void add_waste(string,double);
      void displaySummary();
      void throwBin(const string& binName);
     ~LL();


};

LL::LL(){
  hol=NULL;
  size=0;
    totalRecycling=0;
    totalCompost=0;
    totalEWaste=0;
    totalHazardous=0;
    totalGeneral=0;

    totalWeightRecycling=0;
    totalWeightCompost=0;
    totalWeightEWaste=0;
    totalWeightHazardous=0;
    totalWeightGeneral=0;

    totalRecycling        = 0;
    totalCompost          = 0;
    totalEWaste           = 0;
    totalHazardous        = 0;
    totalGeneral          = 0;

   countThrowRecycling = 0;
    countThrowCompost = 0;
    countThrowEWaste = 0;
    countThrowHazardous = 0;
    countThrowGeneral = 0;

}

void LL::add_waste(string t, double w) {
    string b = getBin(t);   // decide bin: Recycling, Compost, etc.

    // 1) Choose which totalWeight & throwCounter belong to this bin
    double* currentWeight = nullptr; // pointer to the correct total weight (*currentWeight = current kg in that bin)

    // Update item count for the bin
    if (b == "Recycling"){
        totalRecycling++;// increase item count
        currentWeight = &totalWeightRecycling; // pointer to totalWeightRecycling
    } else if (b == "Compost")  {
        totalCompost++;
        currentWeight = &totalWeightCompost;
    } else if (b == "E-Waste")  {
        totalEWaste++;
        currentWeight = &totalWeightEWaste;
    } else if (b == "Hazardous") {
        totalHazardous++;
        currentWeight = &totalWeightHazardous;
    } else {
        totalGeneral++;  // General bin
        currentWeight = &totalWeightGeneral; 
    }

    // 2) PREDICT → will adding w exceed the bin limit?
    if (*currentWeight + w > MAX) {
        cout << "\n⚠️ Adding " << fixed << setprecision(2) << w
             << " kg to the " << b << " Bin will exceed the "
             << MAX << " kg limit.\n";
        cout << "Auto-throwing waste activate...\n";

        // auto-throw this bin (clear items + reset weight)
        throwBin(b);

        cout << "Adding new trash is now available for the " << b << " Bin.\n\n";

        // after throwBin, *currentWeight is now 0
    } else{
        
    }

    // 3) Now safely add the new trash weight
    *currentWeight += w;

    // 4) INSERT NODE AT END OF LINKED LIST
    if (hol == NULL) {
        hol = new node(t, w, b);     // first node
    } else {
        nodePtr temp = hol;
        while (temp->get_next() != NULL)
            temp = temp->get_next();
        temp->set_next(new node(t, w, b));
    }
    size++;

    // 5) PRINT INFO FOR THIS ITEM
    cout << "Item : " << t << " (" << fixed << setprecision(2) << w << " kg)\n";
    cout << "→ This waste goes into the " << b << " Bin\n\n";
}


LL::~LL(){
  cout << "\nDeconstruction Started: Clear all leftover waste"<<endl;
    nodePtr t = hol;
        while (t != NULL) {
            hol = hol->get_next();
            delete t;  // destructor prints message
            t=hol;
        }
        size=0;
} 

void LL::displaySummary() {
    cout << endl << "========== TOTAL WASTE SUMMARY ===========" << endl;
        cout << "Recycling Bin : " << totalRecycling 
            << " items, " << totalWeightRecycling << " kg" << endl;
        cout << "Compost Bin   : " << totalCompost   
            << " items, " << totalWeightCompost   << " kg" << endl;
        cout << "E-Waste Bin   : " << totalEWaste    
            << " items, " << totalWeightEWaste    << " kg" << endl;
        cout << "Hazardous Bin : " << totalHazardous 
            << " items, " << totalWeightHazardous << " kg" << endl;
        cout << "General Bin   : " << totalGeneral   
            << " items, " << totalWeightGeneral   << " kg" << endl;
        cout << "==========================================" << endl;

        cout << endl << "============ BIN THROW REPORT ============" << endl;
        cout << "Recycling Bin   threw : " << countThrowRecycling  << " times\n";
        cout << "Compost Bin     threw : " << countThrowCompost    << " times\n";
        cout << "E-Waste Bin     threw : " << countThrowEWaste     << " times\n";
        cout << "Hazardous Bin   threw : " << countThrowHazardous  << " times\n";
        cout << "General Bin     threw : " << countThrowGeneral    << " times\n";
        cout << "==========================================" << endl << endl;
}
// Function to throw out all waste in a specified bin
void LL::throwBin(const string& binName) {
    //1) Check if current weight in that bin >= MIN (3 kg)
    double currentWeight = 0.0;

    if (binName == "Recycling")        currentWeight = totalWeightRecycling;
    else if (binName == "Compost")     currentWeight = totalWeightCompost;
    else if (binName == "E-Waste")     currentWeight = totalWeightEWaste;
    else if (binName == "Hazardous")   currentWeight = totalWeightHazardous;
    else if (binName == "General")     currentWeight = totalWeightGeneral;

    if (currentWeight < MIN) {
        cout << "\n❌ Cannot throw " << binName << " Bin.\n";
        cout << "   It has only " << fixed << setprecision(2) << currentWeight 
            << " kg,\n Below the minimum available " << MIN << " kg required.\n";
        cout << "   Please add more waste before throwing this bin.\n\n";
        return; // stop here, no deletion
    }

  // 1) Delete all nodes whose bin matches binName
  nodePtr curr = hol;
  nodePtr prev = NULL;

  while (curr != NULL) {
    // Check if current node's bin matches binName
    if (curr->getBin() == binName) {
        // Delete current node
      nodePtr toDelete = curr; // Node to be deleted

      if (prev == NULL) {
        hol = curr->get_next();        // deleting head
      } else {
        prev->set_next(curr->get_next()); // bypass the current node
      }

      curr = curr->get_next(); // Move to next node
      delete toDelete;  // destructor prints message
      size--; // decrease size
    } else {
      prev = curr; // move prev to current
      curr = curr->get_next(); // move to next node
    }
  }

  // 2) Reset weight + item count + increase throw counter
  if (binName == "Recycling") {
    totalWeightRecycling = 0;
    totalRecycling = 0;
    countThrowRecycling++;
  }
  else if (binName == "Compost") {
    totalWeightCompost = 0;
    totalCompost = 0;
    countThrowCompost++;
  }
  else if (binName == "E-Waste") {
    totalWeightEWaste = 0;
    totalEWaste = 0;
    countThrowEWaste++;
  }
  else if (binName == "Hazardous") {
    totalWeightHazardous = 0;
    totalHazardous = 0;
    countThrowHazardous++;
  }
  else if (binName == "General") {
    totalWeightGeneral = 0;
    totalGeneral = 0;
    countThrowGeneral++;
  }

  cout << "✅ All waste in " << binName << " Bin has been thrown out.\n";
  cout << "Now the " << binName << " bin is empty (0 kg).\n\n";

}
#endif