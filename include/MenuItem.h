#ifndef _MENUITEM_
#define _MENUITEM_

class MenuItem{
 public:
  int val;
  char* label;
  char* makeString(char* str){
    int len;
    for (len=0;str[len]!='\0';len++);
    char* temp;
    temp=new char[len+1];
    for (int i=0;i<len+1;i++)
      temp[i]=str[i];
    return temp;
  }

  MenuItem(int init_val,char* init_label);
  MenuItem();
  MenuItem(const MenuItem &mi);
  ~MenuItem();
  MenuItem& operator = (const MenuItem &mi);
  int get_val(){return val;}
  void set_val(int new_val){val=new_val;}
  char* get_label(){return label;}
  void set_label(char* new_label);
  void display(ostream& ostr);
};

#endif // _MENUITEM_
