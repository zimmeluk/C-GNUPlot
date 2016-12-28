#include <iostream>
using namespace std;
#include "MenuItem.h"


MenuItem::MenuItem(int init_val,char* init_label){
  val=init_val;
  label=makeString(init_label);
}

MenuItem::MenuItem(){
  val=0;
  label=new char[1];
  label[0]='\0';
}

MenuItem::MenuItem(const MenuItem& mi){
  val=mi.val;
  label=makeString(mi.label);
}

MenuItem::~MenuItem(){
  delete []label;
}

MenuItem& MenuItem:: operator = (const MenuItem &mi){
  val=mi.val;
  delete []label;
  label=makeString(mi.label);
  return *this;
}


void MenuItem:: set_label(char* new_label){
  delete []label;
  label=makeString(new_label);
}

void MenuItem::display(ostream &ostr){
  ostr<<"["<<val<<"] ";
  for (int i=0;label[i]!='\0';i++)
    ostr<<label[i];
  ostr<<"\n";
}

  
