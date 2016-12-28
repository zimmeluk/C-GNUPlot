//  demo-plot.cpp
//  plots data using gnuplot

#include <iostream>
#include <string>
#include "gnuplot_i.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)
 #include <conio.h>
 #include <windows.h>
 void sleep(int i) { Sleep(i*1000); }
#endif


#define SLEEP_LGTH 2     // sleep time in seconds
#define NPOINTS    50    // length of array

void wait_for_key();     // Program halts until keypress

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    cout << "*** example of gnuplot control through C++ ***" << endl << endl;

    try
    {
      Gnuplot tornado;

      const std::string filename = "tornado_data.dat";
      const std::string title = "Tornado Data";
      const unsigned int column_x = 1;
      const unsigned int column_y = 2;

      tornado.reset_plot();
      tornado.set_style("lines");
      tornado.set_grid().set_samples(600).set_xrange(1950, 2010);
      tornado.set_pointsize(1.0).set_style("points");
      tornado.plotfile_xy(filename, 1, 2, title);
	
      tornado.set_xautoscale().replot();
	
      wait_for_key();

    }
    catch (GnuplotException ge)
    {
        cout << ge.what() << endl;
    }

    cout << endl << "*** end of gnuplot example" << endl;

    return 0;
}



void wait_for_key ()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
    cout << endl << "Press any key to continue..." << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    cout << endl << "Press ENTER to continue..." << endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
    return;
}
