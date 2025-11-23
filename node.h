#ifndef NODE_H
#define NODE_H

class node
{ private:
    string name;
    int num_G;
    string type;
    node *next; //private (LL.h can't access directly)

  public:
   node(int,string,int);
   void print();
   ~node();
     void set_next(node* x){next=x;}
    node * get_next(){return next;}
   
};
typedef node* nodePtr;

node::node(string x,string t,int n){
  name=x;
  type=t;
  num_G=n;
  next=NULL;
}
void node::print(){
    cout<<name<<" "<<type<<endl;
}

node::~node(){
     cout<<"Deleting "<<name<<endl; 
}


#endif