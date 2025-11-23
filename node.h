#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class node{ 
  private:
    string wasteType;
    double weight;
    string binType;
    node *next; //private (LL.h can't access directly)

  public:
   node(string,double,string);
   void print();
   ~node();
    string get_binType();
    double get_weight();
     void set_next(node* x){next=x;}
    node * get_next(){return next;}
   
};
typedef node* nodePtr;

node::node(string t,double w,string b){
  wasteType=t;
  weight=w;
  binType=b;
  next=NULL;
}

void node::print(){
    cout<<wasteType <<"weight : "<<weight<< " kg, Bin: " <<binType<<endl;
}

string node::get_binType(){
    return binType;
}

double node::get_weight(){
    return weight;
}


node::~node(){
     cout<<"Deleting "<<wasteType<<" ( "<<weight<<" )"<<endl; 
}

string getBin(string type) {
    for (char &c : type) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));

    if (type == "plastic" || type == "paper" || type == "metal" || type == "glass")
        return "Recycling";

    if (type == "organic" || type == "food" || type == "fruit" || type == "vegetable")
        return "Compost";

    if (type == "battery" || type == "electronics" || type == "ewaste" || type == "e-waste")
        return "E-Waste";

    if (type == "chemical" || type == "paint" || type == "toxic"|| type=="medical equipment")
        return "Hazardous";

    return "General";
}

#endif