#ifndef LL_H
#define LL_H

#include "node.h"
#define MAX 15 // max capacity of each bin (kg)
#define MIN 3  // min kg for throwing waste out of the bin
typedef node* nodePtr;

class LL{
  private:        
      nodePtr hol;   // head of linked list
      int size;

      // total weights in each bin (kg)
      double totalWeightRecycling = 0; 
      double totalWeightCompost = 0; 
      double totalWeightEWaste = 0; 
      double totalWeightHazardous = 0; 
      double totalWeightGeneral = 0; 

      // track auto-throw count for each bin
      int countThrowRecycling = 0;
      int countThrowCompost = 0;
      int countThrowEWaste = 0;
      int countThrowHazardous = 0;
      int countThrowGeneral = 0;

      // track number of items in each bin
      int totalRecycling = 0;
      int totalCompost = 0;
      int totalEWaste = 0;
      int totalHazardous = 0;
      int totalGeneral = 0;

  public:
      LL();
      void add_waste(string t, double w);       // now inserts into a *sorted* linked list
      void displaySummary();
      void throwBin(const string& binName);
      ~LL();
};

LL::LL(){
    hol = NULL;
    size = 0;

    totalRecycling  = 0;
    totalCompost    = 0;
    totalEWaste     = 0;
    totalHazardous  = 0;
    totalGeneral    = 0;

    totalWeightRecycling  = 0;
    totalWeightCompost    = 0;
    totalWeightEWaste     = 0;
    totalWeightHazardous  = 0;
    totalWeightGeneral    = 0;

    countThrowRecycling = 0;
    countThrowCompost   = 0;
    countThrowEWaste    = 0;
    countThrowHazardous = 0;
    countThrowGeneral   = 0;
}

void LL::add_waste(string t, double w) {
     // Validate weight input: reject non-positive weights
    if (w <= 0) {
        cout <<endl<< "NO!!❌ Invalid weight: " << fixed << setprecision(2) << w
             << " kg. Weight must be > 0."<<endl<<endl;
        return;
    }
    string b = getBin(t);   // decide bin: Recycling, Compost, etc.

    // 1) Choose which totalWeight & item count belong to this bin
    double* currentWeight = nullptr; // pointer to the correct total weight

    if (b == "Recycling") {
        totalRecycling++;
        currentWeight = &totalWeightRecycling;
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
        totalGeneral++;
        currentWeight = &totalWeightGeneral; 
    }

    // 2) PREDICT → will adding w exceed the bin limit?
    if (*currentWeight + w > MAX) {
        cout <<endl<< " Adding " << fixed << setprecision(2) << w
             << " kg to the " << b << " Bin will exceed the "
             << MAX << " kg limit."<<endl;
        cout << "Auto-throwing waste activate..."<<endl;

        // auto-throw this bin (clear items + reset weight)
        throwBin(b);

        cout << "Adding new trash is now available for the " << b << " Bin."<<endl<<endl;
        // after throwBin, *currentWeight is now 0
    }

    // 3) Now safely add the new trash weight
    *currentWeight += w;

    // 4) INSERT NODE IN SORTED ORDER BY WEIGHT
    nodePtr newNode = new node(t, w, b);

    // CASE 1: list is empty OR new node should be first
    if (hol == NULL || w < hol->get_weight()) {
        newNode->set_next(hol);
        hol = newNode;
    } 
    else {
        // CASE 2: find correct position to keep list sorted (ascending by weight)
        nodePtr cur = hol;
        while (cur->get_next() != NULL &&
               cur->get_next()->get_weight() <= w) 
        {
            cur = cur->get_next();
        }

        newNode->set_next(cur->get_next());
        cur->set_next(newNode);
    }

    size++;

    // 5) PRINT INFO FOR THIS ITEM
    cout << "Item : " << t << " (" << fixed << setprecision(2) << w << " kg)"<<endl;
    cout << "→ This waste goes into the " << b << " Bin"<<endl<<endl;
}

LL::~LL(){
    cout << "\nDeconstruction Started: Clear all leftover waste" << endl;
    nodePtr t = hol;
    while (t != NULL) {
        hol = hol->get_next();
        delete t;   // node destructor prints message
        t = hol;
    }
    size = 0;
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
    cout << "Recycling Bin   threw : " << countThrowRecycling  << " times"<<endl;
    cout << "Compost Bin     threw : " << countThrowCompost    << " times"<<endl;
    cout << "E-Waste Bin     threw : " << countThrowEWaste     << " times"<<endl;
    cout << "Hazardous Bin   threw : " << countThrowHazardous  << " times"<<endl;
    cout << "General Bin     threw : " << countThrowGeneral    << " times"<<endl;
    cout << "==========================================" << endl << endl;
}

// Function to throw out all waste in a specified bin
void LL::throwBin(const string& binName) {
    // 1) Check if current weight in that bin >= MIN (3 kg)
    double currentWeight = 0.0;

    if (binName == "Recycling")        currentWeight = totalWeightRecycling;
    else if (binName == "Compost")     currentWeight = totalWeightCompost;
    else if (binName == "E-Waste")     currentWeight = totalWeightEWaste;
    else if (binName == "Hazardous")   currentWeight = totalWeightHazardous;
    else if (binName == "General")     currentWeight = totalWeightGeneral;

    if (currentWeight < MIN) {
        cout <<endl<< "❌ Cannot throw " << binName << " Bin."<<endl;
        cout << "   It has only " << fixed << setprecision(2) << currentWeight 
             << " kg,"<<endl<< "below the minimum " << MIN << " kg required."<<endl;
        cout << "   Please add more waste before throwing this bin."<<endl;
        return; // stop here, no deletion
    }

    // 2) Delete all nodes whose bin matches binName
    nodePtr curr = hol;
    nodePtr prev = NULL;

    while (curr != NULL) {
        if (curr->getBin() == binName) {
            nodePtr toDelete = curr;

            if (prev == NULL) {
                hol = curr->get_next();          // deleting head
            } else {
                prev->set_next(curr->get_next()); // bypass current node
            }

            curr = curr->get_next();  // move forward
            delete toDelete;          // node destructor prints message
            size--;
        } else {
            prev = curr;
            curr = curr->get_next();
        }
    }

    // 3) Reset weight + item count + increase throw counter
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

    cout << "✅ All waste in " << binName << " Bin has been thrown out."<<endl;
    cout << "Now the " << binName << " bin is empty (0 kg)."<<endl<<endl;
}

#endif
