#ifndef _MENU_
#define _MENU_

class Menu{
  MenuItem** vec;
  unsigned int size;
  unsigned int count;
  int not_found;

  void copyVec(const Menu& m){
    int i;
    vec=new MenuItem*[m.size];
    for (int i=0;i<m.count;i++){
      vec[i]=new MenuItem;
      (*vec[i]).val=(*m.vec[i]).val;
      int len;
      for (len=0;(*m.vec[i]).label[len]!='\0';len++);
      (*vec[i]).label=new char[len+1];
      for (int a=0;(*m.vec[i]).label[a]!='\0';a++){
	(*vec[i]).label[a]=(*m.vec[i]).label[a];}
    }
    for (int i;i<m.size;i++){
      vec[i]=m.vec[i];
    }
  }

  void deleteVec(){
    for (int i=0;i<count;i++)
      delete vec[i];
    delete[] vec;
    vec=new MenuItem*[0];
  }
public:
  static unsigned int DEFAULT_SIZE;
  Menu(int sz);
  Menu();
  Menu(const Menu& m);
  ~Menu();
  Menu& operator =(const Menu& m);
  int get_size(){return size;}
  int get_count(){return count;}
  int get_not_found(){return not_found;}
  int add_item(int vl,char* lbl);
  int add_item(MenuItem& item);
  void display(ostream& ostr);
  MenuItem& operator [](unsigned int index);
  int get_value(ostream& ostr,istream& istr);
};

#endif //_MENU_
