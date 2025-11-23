#ifndef NODE_H
#define NODE_H

class node
{ private:
    int id_G;
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

node::node(int id_G ,string type,int num_G){
  id_G=x;
  type=t;
  num_G=n;
  next=NULL;
}
void node::print(){
    cout<<id<<" "<<id_G<<endl;
}

node::~node(){
     cout<<"Deleting "<<id_G<<endl;
}


#endif