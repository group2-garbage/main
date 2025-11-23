#include "node.h"
typedef node* nodePtr;

class LL{
  private:        
      nodePtr hol;// node * hol;
         //head of linked list
      int size;
  public:
      LL();
      void insert_node(int,string);
      void displaySummary();
     ~LL();

};

LL::LL(){
  hol=NULL;
  size=0;
}

void LL::insert_node(int t,string w){
  nodePtr t=hol; 
  if(hol==NULL) hol=new node(t,w,b); //create the first node or use if(hol=NULL)
  else{    	
    //search for location(last node)
   	while(t->get_next()!= NULL) t=t->get_next();
    //t->next --> private
   	t->set_next(new node(t,w,b));
    //t->next=
  }
  cout << "→ This waste goes into the **" << bin << " Bin**\n";
}

LL::~LL(){
  cout << "LinkedList Deconstruction Started"<<endl;
    nodePtr t = hol;
        while (t != NULL) {
            hol = hol->get_next();
            delete t;  // destructor prints message
            t=hol;
        }
        size=0
} 

void LL::displaySummary() {
        int countRecycling = 0, countCompost = 0, countEWaste = 0,
            countHazardous = 0, countGeneral = 0;

        double weightRecycling = 0, weightCompost = 0, weightEWaste = 0,
               weightHazardous = 0, weightGeneral = 0;

        Node* t = hol;

        while (t != NULL) {
            if (t->binType == "Recycling") {
                countRecycling++;
                weightRecycling += t->weight;
            }
            else if (t->binType == "Compost") {
                countCompost++;
                weightCompost += t->weight;
            }
            else if (t->binType == "E-Waste") {
                countEWaste++;
                weightEWaste += t->weight;
            }
            else if (t->binType == "Hazardous") {
                countHazardous++;
                weightHazardous += t->weight;
            }
            else {
                countGeneral++;
                weightGeneral += t->weight;
            }

            t = t->get_next();
        }

        cout << "========== TOTAL WASTE SUMMARY =========="<<endl;
        cout << "Recycling Bin : " << countRecycling << " items, " << weightRecycling << " kg"<<<endl;
        cout << "Compost Bin   : " << countCompost   << " items, " << weightCompost   << " kg"<<<endl;
        cout << "E-Waste Bin   : " << countEWaste    << " items, " << weightEWaste    << " kg"<<<endl;
        cout << "Hazardous Bin : " << countHazardous << " items, " << weightHazardous << " kg"<<<endl;
        cout << "General Bin   : " << countGeneral   << " items, " << weightGeneral   << " kg"<<<endl;
        cout << "=========================================="<<endl;
}
