#include <iostream>
using namespace std;
#include "Data_Array.h"
#include "Data_Point.h"
#include <fstream>

int main() {
  int yr;
  double value;
  ifstream g("tornado_data.txt");
  Data_Array tornado(65);
  int i=0;
  while(g>>yr>>value){
    Data_Point a(yr,value);
    
    tornado[i]=new Data_Point;
    tornado[i]->year=a.year;
    tornado[i]->data_value=a.data_value;
    i++;
  }

    tornado.display();
    cout<<tornado.max();
    cout<<tornado.min();

}
  
