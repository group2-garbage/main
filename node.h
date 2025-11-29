#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

class node{ 
  private:
    string wasteType; //type of the waste
    double weight; //weight of the waste
    string binType; //type of bin
    node *next; //private (LL.h can't access directly)

  public:
   node(string,double,string);
   void print();
   ~node();
    void set_next(node* x){next=x;}
    node * get_next(){return next;}
    string getBin(){return binType;}
    double get_weight(){return weight;}
};
typedef node* nodePtr;

const string recyclable[] = {"plastic","bottle","paper", "metal", "glass"};
const string composition[] = {"organic","food", "fruit", "vegetable"};
const string e_waste[] = {"battery","electronics","ewaste","e-waste"};
const string hazardous[] = {"chemical","paint", "toxic", "oil","medical"};

node::node(string t,double w,string b){
  wasteType=t;
  weight=w;
  binType=b;
  next=NULL;
}

void node::print(){
    cout<<wasteType <<"weight : "<<weight<< " kg, Bin: " <<binType<<endl;
}

node::~node(){
     cout<<"Deleting "<<wasteType<<setw(2)<<setfill(' ')<<"("<<weight<<")"<<endl; 
}

string getBin(string type) {
    for (char &c : type) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    
    for(int i = 0; i < 5; i++){
        if (type == recyclable[i])
            return "Recycling";
    }
    for(int i = 0; i < 4; i++){
        if (type == composition[i])
            return "Compost";
    }
    for(int i = 0; i < 4; i++){
        if (type == e_waste[i])
            return "E-Waste";
    }
    for(int i = 0; i < 5; i++){
        if (type == hazardous[i])
            return "Hazardous";
    }
    return "General";
}


#endif