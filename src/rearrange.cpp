#include<iostream>
using namespace std;
#include<fstream>

// take horizontal data and make it verticle for easier use

int main() {
  ifstream in("carbon.txt");

  int Year[55];
  int temp;
  for(int i = 0; i < 56; i++){
    in >> temp;
    Year[i] = temp;
  }

  
  double Data[55];
  double datatemp;
  for(int i =0; i < 56; i++){
    in >> datatemp;
    Data[i] = datatemp;
  }


  ofstream out("US_Carbon_Emissions.txt");

  for(int i = 0; i < 56; i++)
    out << Year[i] << '\t' << Data[i] << endl;
}
  
