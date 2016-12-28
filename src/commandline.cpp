#include <iostream>
using namespace std;
#include <fstream>

void menu_text(){
  cout << "Select the type of data you would like to display" << endl;
  cout << "Enter the number that corresponds with the item" << endl;
  cout << '\t' << "1. Tornados" << endl;
  cout << '\t' << "2. Ocean Temperatures" << endl;
  cout << '\t' << "3. Carbon Emissions" << endl;
  cout << '\t' << "4. Upload your own" << endl;
}

int main(){
  cout << endl;
  cout << "Welcome to the BigData Weather analyzer!" << endl;
  menu_text();

  int x;
  cin >> x;
  
  while ( x > 4 ){
    cout << "That number does not correspond with an item. Please try again." << endl;
    cin >> x;
  }
  
  ////// Tornado stuff
  
  if ( x == 1 ){
    cout << "Tornado data ranges from 1950-2014" << endl;
    cout << "Please enter a start year, followed by the enter key, and then an end year." << endl;
    cout << endl;

    int start, end;
    cin >> start;
    while (start < 1950){
      cout << "Number not in range.  Please enter again." << endl;
      cin >> start;
    }
    cin >> end;
    while (end > 2014){
      cout << "Number not in range. Please enter again." << endl;
      cin >> end;
    }
    cout << "Will return a GNU plot of that data. GNU plot has yet to be linked in." << endl;
    cout << "Tornado returns this data:" << endl;
    cout << "Year" << '\t' << "Number of Tornados" << endl;

    ifstream g("tornado_data.txt");
    int y,n;
    int period = end - start + 1;
    for(int i = 0; i < period; i++){
      g >> y;
      g >> n;
      cout << y << '\t' << n << endl;
    }   
  }


  
  if ( x == 2 ){
    cout << "Oops.  We haven't written the ocean temperatures code yet.  Please stick to Tornados." << endl;
  }
  if (x == 3 ) {
    cout << "Oops. We haven't written the CO2 emissions code yet.  Please stick to Tornados." << endl;
  }
  if ( x == 4 ) {
    cout << "Oops. We havne't written the code for that yet. Please stick to Tornadoes." << endl;
  }
}
