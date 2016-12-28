#ifndef _DATAARRAY_
#define _DATAARRAY_
#include <iostream>
#include "Data_Point.h"
using namespace std;

class Data_Array {
public:
  int size;
  Data_Point ** elt;
  static const int DEFAULT_SIZE = 1;

  Data_Array (int sz);
  Data_Array ();
  Data_Array (Data_Array &g);
  ~Data_Array ();

  int getSize();
  void display();

  Data_Point* & operator[] (int i);
  Data_Array * operator= (Data_Array & da);
  double max();
  double min();
  void read_data(char * filename);
};

#endif
