#include <iostream>
using namespace std;
#include "MenuItem.h"
#include "MenuItem.cpp"
#include "Menu.h"
#include <cassert>

unsigned int Menu::DEFAULT_SIZE=2;

Menu::Menu(int sz){
  vec=new MenuItem*[sz];
  size=sz;
  count=0;
  not_found=-1;
}

Menu::Menu(){
  vec=new MenuItem*[DEFAULT_SIZE];
  size=DEFAULT_SIZE;
  count=0;
  not_found=-1;
}

Menu::Menu(const Menu& m){
  size=m.size;
  copyVec(m);
  count=m.count;
  not_found=m.not_found;
}

Menu::~Menu(){
  deleteVec();
}

Menu& Menu::operator =(const Menu& m){
  deleteVec();
  size=m.size;
  count=m.count;
  not_found=m.not_found;
  copyVec(m);
  return *this;
}

int Menu::add_item(int vl,char* lbl){
  if (count<size){
    MenuItem* temp=new MenuItem(vl,lbl);
    count+=1;
    vec[count-1]=temp;
    if ((*temp).val<not_found)
      not_found=(*temp).val-1;
    return 1;
  }
  else{
    return 0;
  }
}

int Menu::add_item(MenuItem& item){
  if (count<size){
    MenuItem* temp=new MenuItem(item);
    count+=1;
    vec[count-1]=temp;
    if ((*temp).val<not_found)
      not_found=(*temp).val-1;
    return 1;
  }
  else{
    return 0;
  }
}

void Menu::display(ostream& ostr){
  ostr<<"size="<<size<<" count="<<count<<" not_found="<<not_found<<endl;
  for (int i=0;i<count;i++){
    ostr<<i<<". ";
    vec[i]->display(ostr);}
}

MenuItem& Menu:: operator [](unsigned int index){
  assert(0<=index<count);
  return *vec[index];
}

int Menu::get_value(ostream& ostr,istream& istr){
  for (int i=0;i<count;i++){
    ostr<<(i+1)<<". ";
    for (int a=0;(*vec[i]).label[a]!='\0';a++){
      ostr<<(*vec[i]).label[a];}
    ostr<<"\n";}
  ostr<<"Your choice (1-"<<count<<"):";
  int choice;
  istr>>choice;
  if (choice<=0|choice>=count){
    return not_found;}
  else
    return (*vec[choice-1]).val;
}
