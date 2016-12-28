#ifndef _DATAPOINT_
#define _DATAPOINT_

#include<iostream>
#include <fstream>

class Data_Point{
 public:
  int year;
  double data_value;
  Data_Point(int a,double b):year(a),data_value(b){}
  Data_Point(){year=0;data_value=0;}
  void display(){cout <<"["<<year<<" "<<data_value<< "]";}

};


#endif // _DATAPOINT_
