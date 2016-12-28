#include <iostream>
using namespace std;
#include <fstream>
#include "Data_Array.h"
#include "Data_Point.h"

Data_Array::Data_Array (int sz) {
  size = sz;
  elt = new Data_Point * [size];
  for (int i = 0; i < size; i++)
    elt[i] = 0;
}

Data_Array::Data_Array () {
  size = DEFAULT_SIZE;
  elt = new Data_Point* [size];
  elt[DEFAULT_SIZE-1] = 0;
}

Data_Array::Data_Array (Data_Array & g) {
  elt = new Data_Point* [g.size];
  for (int i = 0; i < g.size; i++)
    elt[i] = g.elt[i];
  size = g.size;
}

Data_Array::~Data_Array () {
  for (int i = 0; i < size; i++)
    delete elt[i];
  delete [] elt; 
  elt = NULL;
}

int Data_Array::getSize() {
  return size;
}

void Data_Array::display () {
  for (int i = 0; i < size; i++) {
    if (elt[i] != 0)
      cout << i << ":  [" << elt[i]->year << ".  "<<elt[i]->data_value<< "]" << endl;
  }
}

Data_Point* & Data_Array::operator[] (int i) {
  if (i < 0) {
    cout << "Error! Please enter a valid" << endl;
    return elt[0];
  } else if (i >= size) {
    cout << "Error! Please enter a valid index!" << endl;
    return elt[size-1];
  } else
    return elt[i];
}

Data_Array * Data_Array::operator= (Data_Array &da) {
  size = da.size;
  Data_Point ** newelt = new Data_Point * [size];
  for (int i = 0; i < size; i++)
    newelt[i] = da.elt[i];
  delete elt;
  elt = newelt;
  return this;
}

double Data_Array::max(){
  double max=0;
  int number=0;
  for (int i=0;i<size;i++){
    if (max < (elt[i]->data_value)){
      max=elt[i]->data_value;number=elt[i]->year;}
  }
  return number;
}

double Data_Array::min(){
  double min=200000000;
  int number2=0;
  for (int i=0;i<size;i++){
    if (min > (elt[i]->data_value)){
      min=elt[i]->data_value;number2=elt[i]->year;}
  }
  return number2;
}

void Data_Array::read_data(char * filename){
  ifstream in(filename);

  int y;
  double d;

  for(int i = 0; i < size; i++){
    in >> y;
    in >> d;
    elt[i] = new Data_Point(y,d);
  }
}
