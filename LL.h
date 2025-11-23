#include "node.h"
typedef node* nodePtr;

class LL{
  private:        
      nodePtr hol;// node * hol;
         //head of linked list
      int size;
  public:
      LL();
      void add_waste(string,double);
      void displaySummary();
     ~LL();

};

LL::LL(){
  hol=NULL;
  size=0;
}

void LL::add_waste(string t,double w){
  nodePtr temp;
  temp = hol; 
  string b = getBin(t);
  if(hol==NULL) hol=new node(t,w,b); //create the first node or use if(hol=NULL)
  else{    	
    //search for location(last node)
   	while(temp->get_next()!= NULL) temp=temp->get_next();
    //t->next --> private
   	temp->set_next(new node(t,w,b));
    //t->next=
  }
  cout<<t<<" ("<<fixed<<setprecision(2)<<w<<" kg)"<<endl;
  cout << "→ This waste goes into the " << b << " Bin"<<endl;
}

LL::~LL(){
  cout << "Deconstruction Started"<<endl;
    nodePtr t = hol;
        while (t != NULL) {
            hol = hol->get_next();
            delete t;  // destructor prints message
            t=hol;
        }
        size=0;
} 

void LL::displaySummary() {
        int countRecycling = 0, countCompost = 0, countEWaste = 0,
            countHazardous = 0, countGeneral = 0;

        double weightRecycling = 0, weightCompost = 0, weightEWaste = 0,
               weightHazardous = 0, weightGeneral = 0;

        nodePtr temp = hol;

        while (temp != NULL) {
            if (temp->getBin() == "Recycling") {
                countRecycling++;
                weightRecycling += temp->get_weight();
            }
            else if (temp->getBin() == "Compost") {
                countCompost++;
                weightCompost += temp->get_weight();
            }
            else if (temp->getBin() == "E-Waste") {
                countEWaste++;
                weightEWaste += temp->get_weight();
            }
            else if (temp->getBin() == "Hazardous") {
                countHazardous++;
                weightHazardous += temp->get_weight();
            }
            else {
                countGeneral++;
                weightGeneral += temp->get_weight();
            }

            temp = temp->get_next();
        }

        cout <<endl<< "========== TOTAL WASTE SUMMARY =========="<<endl;
        cout << "Recycling Bin : " << countRecycling << " items, " <<fixed<<setprecision(2)<< weightRecycling << " kg"<<endl;
        cout << "Compost Bin   : " << countCompost   << " items, " <<fixed<<setprecision(2)<< weightCompost   << " kg"<<endl;
        cout << "E-Waste Bin   : " << countEWaste    << " items, " <<fixed<<setprecision(2)<< weightEWaste    << " kg"<<endl;
        cout << "Hazardous Bin : " << countHazardous << " items, " <<fixed<<setprecision(2)<< weightHazardous << " kg"<<endl;
        cout << "General Bin   : " << countGeneral   << " items, " <<fixed<<setprecision(2)<< weightGeneral   << " kg"<<endl;
        cout << "=========================================="<<endl<<endl;
}
