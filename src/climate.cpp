//  demo-ui.cpp
//  demonstration of the proposed UI for final SD Project

#include <iostream>
using namespace std;

#include <string.h>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cassert>
#include <string>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)
#include <conio.h>
#include <windows.h>
void sleep(int i) { Sleep(i*1000); }
#endif
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "texture.h"
#include "Data_Array.h"
#include "Data_Point.h"
#include "Data_Array.cpp"
#include "MenuItem.h"
#include "Menu.h"
#include "gnuplot_i.hpp"

#define SLEEP_LGTH 2               // sleep time in seconds
#define NPOINTS    50              // length of array

void wait_for_key();               // Program halts until keypress

int WIDTH = 600;                   // width of the user window
int HEIGHT = 350;                  // height of the user window
char programName[] = "Demo UI";
int Tornado1, Tornado2, Tornado3;
int Carbon1, Carbon2, Carbon3;
int Upload1, Upload2, Upload3;
int Checkbox1, Checkbox2, Graph1, Graph2;
int Intensity1, Intensity2, Intensity3;

// button info
bool buttonIsPressed = false, overButton = false;
double buttonPos[] = { 20, 75,   180, 60 };    // upper left

// button2 info
bool button2IsPressed = false, overButton2 = false;
double button2Pos[] = { 205, 75, 180, 60 };    // upper right

// button3 info
bool button3IsPressed = false, overButton3 = false;
double button3Pos[] = { 20, 140,   180, 60 };  // middle left

// button4 info
bool button4IsPressed = false, overButton4 = false;
double button4Pos[] = { 205, 140, 180, 60 };   // middle right

// button5 info
bool button5IsPressed = false, overButton5 = false;
double button5Pos[] = { 425, 285, 125, 45 };   // middle right

// checkbox info
bool checkPressed = false, overCheck = false;
double checkPos[] = { 425, 200, 13, 13 };

// checkbox info
bool check2Pressed = false, overCheck2 = false;
double check2Pos[] = { 425, 230, 13, 13 };

//textbox info
double textPos[]= { 20, 205, 365, 125 };

// Slider information
bool sliderIsPressed = false, overSlider = false;
bool sliderIsPressed2 = false;
double sliderBox1[] =   { 425, 58,   128, 4 };    // background of slider
double sliderBoxMin[] = { 420, 50,   10, 20 };    // foregroundMin of slider
double sliderBoxMax[] = { 420, 50,   10, 20 };    // foregroundMax of slider
double sliderPos  = 0;      // where the slider currently is located
double sliderPos2 = 128;    // where slider2 is currently located
double sliderStartPos;      // where the mouse first clicked on the slider
double sliderStartPos2;     // where the mouse first clicked on slider2
double sliderMax = 128;     // upper limit to the sliderPos
char minVal [] = "Minimum value";
char maxVal [] = "Maximum value";
char mapGraph [] = "XY Axis Graph";
char axisGraph [] = "3D Graph";
char selectYear []  = "YEAR";
char selectData []  = "DATASET";
char selectGraph [] = "GRAPH";
char sliderPosStr [5];
char sliderPosStr2 [5];
int yr;
double value;
Data_Array tornado(65);
Data_Array carbon(52);
Data_Array upload(135);                // this needs to be sized based on the input data
Data_Array intensity(65);
Menu data(2);
Menu graph(2);
MenuItem tornado_sel(1, "tornado.txt");
MenuItem carbon_sel(2, "carbon.txt");
MenuItem us_map(1, "United States Map");
MenuItem xy_axis(2, "XY Axis Graph");
char upload_data[50];
char temp;


// the following function draws a rectangle, given
//   the upper left vertex and the width and height
void drawBox(double x, double y, double width, double height)
{
  glBegin(GL_POLYGON);
    glVertex2f(x, y);                   // upper left
    glVertex2f(x, y + height);          // lower left
    glVertex2f(x + width, y + height);  // lower right
    glVertex2f(x + width, y);           // upper right
  glEnd();
}

void drawBox(double *pos)
{
  drawBox(pos[0], pos[1], pos[2], pos[3]);
}

// the drawText function draws some text at location x, y
//   note:  the text to be drawn is a C-style string!
void drawText(double x, double y, const char *text, int font)
{
  glRasterPos2f( x, y );
  int length = strlen(text);
  if (font > 0) {
    for (int i = 0; i < length; i++) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
  }
  else if (font <= 0) {
    for (int i = 0; i < length; i++) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
  }
}

void drawNumber(double x, double y, double num) {
  stringstream oss;
    oss << fixed << setprecision(0) << num; oss.flush();
  drawText(x, y, oss.str().c_str(), 0);
}

void drawWindow()
{
  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  
  //draw the text box
  glColor3f(0.90, 0.90, 0.90);
  drawBox(textPos);
  glColor3f(0., 0., 0.);
  drawText(150, 230, "Statistic Information" , 0);

  // draw the button TORNADO
  if ( buttonIsPressed ) {
    glColor3f(0.,.4, 0.7);    // dark blue
    drawText(100,260,"Year: ",0);
    drawNumber(150,260,tornado[0]->year);
    drawNumber(190,260,tornado[64]->year);
    drawText(180,260,"-",0);
    drawText(100,280,"Max: ",0);
    drawNumber(140,280,tornado[tornado.max()-1950]->data_value);
    drawText(175,280,"in year ",0);
    drawNumber(220,280,tornado.max());
    drawText(100,300,"Min: ",0);
    drawNumber(140,300,tornado[tornado.min()-1950]->data_value);
    drawText(175,300,"in year ",0);
    drawNumber(220,300,tornado.min());
  }
  if (buttonIsPressed) drawTexture(Tornado3, buttonPos);
  else if (overButton) drawTexture(Tornado2, buttonPos);
  else drawTexture(Tornado1, buttonPos);
  

  // draw the second button CARBON
  if ( button2IsPressed ){
    glColor3f(0., .4, 0.7);  // dark blue
    drawText(100,260, "Year: ",0);
    drawNumber(150,260,carbon[0]->year);
    drawNumber(190,260,carbon[51]->year);
    drawText(180, 260, "-",0);
    drawText(100,280,"Max: ",0);
    drawNumber(140,280,carbon[carbon.max()-1960]->data_value);
    drawText(210,280,"in year ",0);
    drawNumber(260,280,carbon.max());
    drawText(100,300,"Min: ",0);
    drawNumber(140,300,carbon[carbon.min()-1960]->data_value);
    drawText(210,300,"in year ",0);
    drawNumber(260,300,carbon.min());  
  }
  if (button2IsPressed) drawTexture(Carbon3, button2Pos);
  else if (overButton2) drawTexture(Carbon2, button2Pos);
  else drawTexture(Carbon1, button2Pos);

  // draw the third button 
  if (button3IsPressed) {
    drawTexture(Intensity3, button3Pos);
    glColor3f(0., .4, 0.7);  // dark blue
    drawText(100,260, "Year: ",0);
    drawNumber(150,260,intensity[0]->year);
    drawNumber(190,260,intensity[64]->year);
    drawText(180, 260, "-",0);
    drawText(100,280,"Max: ",0);
    drawNumber(140,280,intensity[intensity.max()-1950]->data_value);
    drawText(210,280,"in year ",0);
    drawNumber(260,280,intensity.max());
    drawText(100,300,"Min: ",0);
    drawNumber(140,300,intensity[intensity.min()-1950]->data_value);
    drawText(210,300,"in year ",0);
    drawNumber(260,300,intensity.min());}
  else if (overButton3) drawTexture(Intensity2, button3Pos);
  else drawTexture(Intensity1, button3Pos);

  // draw the fourth button  UPLOAD

  if (button4IsPressed) {
    glColor3f(0.,0.4,0.7);
    drawText(50, 260, "Please refer to the commandline for upload instructions.",0);
  }
  
  if (button4IsPressed) drawTexture(Upload3, button4Pos);
  else if (overButton4) drawTexture(Upload2, button4Pos);
  else drawTexture(Upload1, button4Pos);


  // draw the fifth button
  if (button5IsPressed) drawTexture(Graph2, button5Pos);
  else drawTexture(Graph1, button5Pos);

  // draw checkbox
  if (checkPressed) drawTexture(Checkbox2, checkPos);
  else drawTexture(Checkbox1, checkPos);

  // draw checkbox2
  if (check2Pressed) drawTexture(Checkbox2, check2Pos);
  else drawTexture(Checkbox1, check2Pos);

  // draw checkbox values
  glColor3f(0., 0., 0.);
  drawText(455, 210, mapGraph, 0);
  drawText(455, 240, axisGraph, 0);

  // draw selection label
  glColor3f(0., .70, .90);
  drawText(160, 55, selectData, 1);
  // glColor3f(.75, .30, .30);
  drawText(470, 35, selectYear, 1);
  // glColor3f(0., .90, .40);
  drawText(460, 175, selectGraph, 1);

  // draw the minimum and maximum value labels
  glColor3f(0., 0., 0.);
  drawText(430, 95, minVal, 0);
  drawText(430, 125, maxVal, 0);

  // draw the values
  sprintf(sliderPosStr, "%3.0lf", sliderPos);
  sprintf(sliderPosStr2, "%3.0lf", sliderPos2);

  glColor3f(.5, .5, .5);
  drawNumber(520, 95, (int)(sliderPos/2) + 1950);
  drawNumber(520, 125, (int)(sliderPos2/2) + 1950);

  // draw the slider background
  glColor3f(0., 0., 0.);                                          // dark gray
  drawBox(sliderBox1);
  // draw the slider foreground-max
  if ( overSlider ) glColor3f(.0, .70, .90);// (.75, .30, .30);
  else glColor3f(.75, .75, .75);                                  // light gray
  drawBox(sliderBoxMin[0] + sliderPos, sliderBoxMin[1], 
          sliderBoxMin[2],  sliderBoxMin[3]);
  // draw the slider foreground-max
  if ( overSlider ) glColor3f(.0, .70, .90);// (.75, .30, .30);
  else glColor3f(.75, .75, .75);                                  // light gray
  drawBox(sliderBoxMax[0] + sliderPos2, sliderBoxMax[1], 
          sliderBoxMax[2],  sliderBoxMax[3]);
  
  // tell the graphics card that we're done-- go ahead and draw!
  //   (technically, we are switching between two color buffers...)
  glutSwapBuffers();
}

// close the window and finish the program
void exitAll()
{
  int win = glutGetWindow();
  glutDestroyWindow(win);
  exit(0);
}

// process keyboard events
void keyboard( unsigned char c, int x, int y )
{
    switch(c) {
      case 'q':
      case 'Q':
      case 27:
        exitAll();
        break;
      default:
        break;
    }
  glutPostRedisplay();
}

// the reshape function handles the case where the user changes the size
//   of the window.  We need to fix the coordinate
//   system, so that the drawing area is still the unit square.
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   WIDTH = w;  HEIGHT = h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);
}

// the following function tests whether a point at position x,y is inside
//   the rectangle on the screen corresponding to the button
bool onButton(int x, int y, double * barray);
bool onSliderForeground(int x, int y);
bool onSlider2Foreground(int x, int y);
bool onSliderBackground(int x, int y);
bool onCheck(int x, int y);
bool onCheck2(int x, int y);
  
void onButton(int x, int y, double * barray, bool &bflag)
{
  if (x >= barray[0]  && y >= barray[1] &&
      x <= barray[0] + barray[2] &&
      y <= barray[1] + barray[3])
    bflag = true;
  else if (onButton(x,y,button5Pos) ||
	   onSliderForeground(x, y) ||
	   onSlider2Foreground(x,y) ||
	   onSliderBackground(x, y) ||
	   onCheck(x, y)            ||
	   onCheck2(x, y))
    if (bflag == true)
      bflag = true;
    else bflag = false;
  else bflag = false;
}


bool onButton(int x, int y, double * barray)
{
  return (x >= barray[0]  && y >= barray[1] &&
          x <= barray[0] + barray[2] &&
	  y <= barray[1] + barray[3]);

}

bool onCheck(int x, int y)
{
  return x >= checkPos[0]  && y >= checkPos[1] &&
         x <= checkPos[0] + checkPos[2] &&
         y <= checkPos[1] + checkPos[3];
}

bool onCheck2(int x, int y)
{
  return x >= check2Pos[0]  && y >= check2Pos[1] &&
         x <= check2Pos[0] + check2Pos[2] &&
         y <= check2Pos[1] + check2Pos[3];
}

bool onSliderForeground(int x, int y)
{
  return x >= sliderBoxMin[0]+sliderPos  && y >= sliderBoxMin[1] &&
         x <= sliderBoxMin[0]+sliderBoxMin[2]+sliderPos &&
         y <= sliderBoxMin[1]+sliderBoxMin[3];
}

bool onSlider2Foreground(int x, int y)
{
  return x >= sliderBoxMax[0]+sliderPos2  && y >= sliderBoxMax[1] &&
         x <= sliderBoxMax[0]+sliderBoxMax[2]+sliderPos2 &&
         y <= sliderBoxMax[1]+sliderBoxMax[3];
}

bool onSliderBackground(int x, int y)
{
  return x >= sliderBoxMin[0]  && y >= sliderBoxMin[1] &&
         x <= sliderBoxMin[0]+sliderMax+sliderBoxMin[2] &&
         y <= sliderBoxMin[1]+sliderBoxMin[3];
}

// the mouse function is called when a mouse button is pressed down or released
void mouse(int mouseButton, int state, int x, int y)
{
  if ( GLUT_LEFT_BUTTON == mouseButton ) {
    if ( GLUT_DOWN == state ) {
      // the user just pressed down on the mouse-- do something
      
      onButton(x,y,buttonPos, buttonIsPressed);
      onButton(x,y,button2Pos,button2IsPressed);
      onButton(x,y,button3Pos,button3IsPressed);
      onButton(x,y,button4Pos,button4IsPressed);
      onButton(x,y,button5Pos,button5IsPressed);

      if ( onCheck(x,y) ) checkPressed = true;
      else if (onButton(x,y,buttonPos)  ||
	       onButton(x,y,button2Pos) ||
	       onButton(x,y,button3Pos) ||
	       onButton(x,y,button4Pos) ||
	       onButton(x,y,button5Pos) ||
	       onSliderForeground(x, y) ||
	       onSlider2Foreground(x,y) ||
	       onSliderBackground(x, y))
	if (checkPressed == true)
	  checkPressed = true;
        else checkPressed = false;
      else checkPressed = false;
      if ( onCheck2(x,y) ) check2Pressed = true;
      else if (onButton(x,y,buttonPos)  ||
         onButton(x,y,button2Pos) ||
	       onButton(x,y,button3Pos) ||
	       onButton(x,y,button4Pos) ||
	       onButton(x,y,button5Pos) ||
	       onSliderForeground(x, y) ||
	       onSlider2Foreground(x,y) ||
	       onSliderBackground(x, y))
	if (check2Pressed == true)
	  check2Pressed = true;
        else check2Pressed = false;
      else check2Pressed = false;
      if ( onSliderForeground(x,y) ) {
        sliderIsPressed = true;
        sliderStartPos = x - sliderPos;
      } else if ( onSlider2Foreground(x,y) ) {
        sliderIsPressed2 = true;
        sliderStartPos2 = x - sliderPos2;
      } else sliderIsPressed = false;
    } else {
      // the user just let go the mouse -- do something
      if (overButton && buttonIsPressed)   { }
      if (overButton2 && button2IsPressed) { }
      if (overButton3 && button3IsPressed) { }
      if (overButton4 && button4IsPressed) {
	       cout << "You have selected to upload your own file." << endl;
	       cout << "Please reffer to the user manual and verify that your data is in the same format as the example data." << endl;
	       cout << "File name:" << endl;
               cin.getline(upload_data, 50);                                   // gets stuck with this
	       cout << "Thank you.  You may return to the user interface.";
      }
      if (overButton5 && button5IsPressed) {
	button5IsPressed = false;

	if (buttonIsPressed) {
	  cout << "Plotting Tornado Data..." << endl;
	  try
	    {
	      Gnuplot tornado;

	      const std::string filename = "data/tornado_data.dat";
	      const std::string title = "Tornado Data";
	      const unsigned int column_x = 1;
	      const unsigned int column_y = 2;

	      tornado.reset_plot();
	      tornado.set_xlabel("Year");
	      tornado.set_ylabel("Number of Tornadoes");
	      tornado.set_xrange((sliderPos / 2) + 1950, (sliderPos2 / 2) + 1950);
	      tornado.set_pointsize(0.5).set_style("linespoints");
	      tornado.set_style("linespoints");
	      tornado.plotfile_xy(filename, 1, 2, title);
	    
	      wait_for_key();
	      button5IsPressed = false;
	    }
	  catch (GnuplotException ge)
	    {
	      cout << ge.what() << endl;
	    }
	}
	else if (button2IsPressed) {
	  cout << "Plotting Carbon Data..." << endl;
	  try
	    {
	      Gnuplot carbon;

	      const std::string filename = "data/US_Carbon_Emissions.dat";
	      const std::string title = "Carbon Data";
	      const unsigned int column_x = 1;
	      const unsigned int column_y = 2;

	      carbon.reset_plot();
	      carbon.set_xlabel("Year");
	      carbon.set_ylabel("Carbon Emissions");
	      carbon.set_xrange((sliderPos / 2) + 1950, (sliderPos2 / 2) + 1950);
	      carbon.set_pointsize(0.5).set_style("linespoints");
	      carbon.set_style("linespoints");
	      carbon.plotfile_xy(filename, 1, 2, title);
	    
	      wait_for_key();
	      button5IsPressed = false;
	    }
	  catch (GnuplotException ge)
	    {
	      cout << ge.what() << endl;
	    }
	}
	else if (button3IsPressed && checkPressed) {
	  cout << "Plotting Tornado Intensity Data..." << endl;
	  try
	    {
	      Gnuplot intensity;

	      const std::string filename = "data/tornado_intensity.dat";
	      const std::string title = "Tornado Intensity Data";
	      const unsigned int column_x = 1;
	      const unsigned int column_y = 2;

	      intensity.reset_plot();
	      intensity.set_xlabel("Year");
	      intensity.set_ylabel("Intensity");
	      intensity.set_xrange((sliderPos / 2) + 1950, (sliderPos2 / 2) + 1950);
	      intensity.set_yautoscale();
	      intensity.set_pointsize(0.5).set_style("linespoints");
	      intensity.set_style("linespoints");
	      intensity.plotfile_xy(filename, 1, 2, title);
	    
	      wait_for_key();
	      button5IsPressed = false;
	    }
	  catch (GnuplotException ge)
	    {
	      cout << ge.what() << endl;
	    }
	}
	else if (button3IsPressed && check2Pressed) {
	  cout << "Plotting Tornado Intensity Data 3D..." << endl;
	  try
	    {
	      Gnuplot plot3D;

	      const std::string filename = "data/tornado_data_3D.dat";
	      const std::string title = "Tornado Intensity Data";
	      const unsigned int column_x = 1;
	      const unsigned int column_y = 2;
	      const unsigned int column_dy = 3;

	      plot3D.reset_plot();
	      plot3D.set_xlabel("Year");
	      plot3D.set_ylabel("Number of Tornadoes");
	      plot3D.set_zlabel("Tornado Intensity");
	      plot3D.set_xrange((sliderPos / 2) + 1950, (sliderPos2 / 2) + 1950);
	      plot3D.set_yautoscale();
	      plot3D.set_pointsize(0.5).set_style("linespoints");
	      plot3D.set_style("linespoints");
	      plot3D.plotfile_xyz(filename, 1, 2, 3, title);
	    
	      wait_for_key();
	      button5IsPressed = false;
	    }
	  catch (GnuplotException ge)
	    {
	      cout << ge.what() << endl;
	    }
	}
	else if (button4IsPressed) {
	  cout << "Plotting User-Uploaded Data..." << endl;
	  try
	    {
	      Gnuplot uploaded;

	      const std::string filename = "data/ocean_temp.dat";
	      const std::string title = "Ocean Temperature";
	      const unsigned int column_x = 1;
	      const unsigned int column_y = 2;

	      uploaded.reset_plot();
	      uploaded.set_xlabel("Year");
	      uploaded.set_ylabel("Average Temperature");
	      uploaded.set_xrange(1880, 2014);
	      uploaded.set_yautoscale();
	      uploaded.set_pointsize(0.5).set_style("linespoints");
	      uploaded.set_style("linespoints");
	      uploaded.plotfile_xy(filename, 1, 2, title);
	    
	      wait_for_key();
	      button5IsPressed = false;
	    }
	  catch (GnuplotException ge)
	    {
	      cout << ge.what() << endl;
	    }
	}
      }
      if ( sliderIsPressed ) {
          cout << "Minimum: " << (sliderPos/2) + 1950 << endl;
      }
      sliderIsPressed = false;
      if ( sliderIsPressed2 ) {
        cout << "Maximum: " << (sliderPos2/2) + 1950 << endl;
      }
      sliderIsPressed2 = false;
    }
  } else if ( GLUT_RIGHT_BUTTON == mouseButton ) {
  }
  glutPostRedisplay();
}

// the mouse_motion function is called when the mouse is being dragged,
//   and gives the current location of the mouse
void mouse_motion(int x,int y)
{
  // the mouse button is pressed, and the mouse is moving....
  if ( sliderIsPressed ) {
    double newSliderPos = x - sliderStartPos;
    // check that the new slider pos does not go off the end of the slider
    if ( newSliderPos < 0 ) sliderPos = 0;
    // check that the new slider pos is not greater than the maximum
    else if (newSliderPos >= sliderPos2 - 1) sliderPos = sliderPos2 - 1;
    else sliderPos = newSliderPos;
  } else if ( sliderIsPressed2 ) {
    double newSliderPos2 = x - sliderStartPos2;
    // check that the new slider pos does not go off the end of the slider
    if ( newSliderPos2 > sliderMax ) sliderPos2 = sliderMax;
    // check that the new slider pos is not less than the minimum
    else if (newSliderPos2 <= sliderPos - 1) sliderPos2 = sliderPos + 1;
    else sliderPos2 = newSliderPos2;
  } else {

    onButton(x,y,buttonPos, overButton);
    onButton(x,y,button2Pos,overButton2); 
    onButton(x,y,button3Pos,overButton3);
    onButton(x,y,button4Pos,overButton4);
    onButton(x,y,button5Pos,overButton5);
    if ( onSliderBackground(x,y) ) overSlider = true;
    else overSlider = false;
  }
  glutPostRedisplay();
}

void wait_for_key ()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
    cout << "Press any key to continue..." << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    cout << "Press ENTER to continue..." << endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
    return;
}

// the init function sets up the graphics card to draw properly
void init(void)
{
  // clear the window to black
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // set up the coordinate system:  number of pixels along x and y
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);

  // allow blending (for transparent textures)
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  // welcome message
  cout << "Welcome to " << programName << ". ";
  cout << "This is Big Data's UI design." << endl;
}


// init_gl_window is the function that starts the ball rolling, in
//  terms of getting everything set up and passing control over to the
//  glut library for event handling.  It needs to tell the glut library
//  about all the essential functions:  what function to call if the
//  window changes shape, what to do to redraw, handle the keyboard,
//  etc.
void init_gl_window()
{
  char *argv[] = { programName };
  int argc = sizeof(argv) / sizeof(argv[0]);
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(100,100);
  glutCreateWindow(programName);
  init();

  Tornado1  = loadTexture("graphics/Tornado1.pam");
  Tornado2  = loadTexture("graphics/Tornado2.pam");
  Tornado3  = loadTexture("graphics/Tornado3.pam");
  Carbon1   = loadTexture("graphics/Carbon1.pam");
  Carbon2   = loadTexture("graphics/Carbon2.pam");
  Carbon3   = loadTexture("graphics/Carbon3.pam");
  Upload1   = loadTexture("graphics/Upload1.pam");
  Upload2   = loadTexture("graphics/Upload2.pam");
  Upload3   = loadTexture("graphics/Upload3.pam");
  Checkbox1 = loadTexture("graphics/Checkbox1.pam");
  Checkbox2 = loadTexture("graphics/Checkbox2.pam");
  Graph1    = loadTexture("graphics/Graph1.pam");
  Graph2    = loadTexture("graphics/Graph2.pam");
  Intensity1= loadTexture("graphics/Intensity1.pam");
  Intensity2= loadTexture("graphics/Intensity2.pam");
  Intensity3= loadTexture("graphics/Intensity3.pam");
  
  glutDisplayFunc(drawWindow);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_motion);
  glutPassiveMotionFunc(mouse_motion);
  glutMainLoop();
}

void input(const char* a){
  ifstream g(a);
  int i = 0;
  while(g>>yr>>value){
    Data_Point a(yr,value);
    tornado[i] = new Data_Point;
    tornado[i]->year = a.year;
    tornado[i]->data_value=a.data_value;
    i++;
  }
  
}

void input2(const char* b){
  ifstream in(b);
  int i = 0;
  while(in >>yr>>value){
    Data_Point b(yr,value);
    carbon[i] = new Data_Point;
    carbon[i]->year = b.year;
    carbon[i]->data_value = b.data_value;
    i++;
  }
}

void input3(const char* c){
  ifstream in(c);
  int i = 0;
  while(in>>yr>>value){
    Data_Point c(yr,value);
    upload[i] = new Data_Point;
    upload[i]->year = c.year;
    upload[i]->data_value = c.data_value;
    i++;
  }
}


void input4(const char* c){
  ifstream in(c);
  int i = 0;
  while(in>>yr>>value){
    Data_Point c(yr,value);
    intensity[i] = new Data_Point;
    intensity[i]->year = c.year;
    intensity[i]->data_value = c.data_value;
    i++;
  }
}
  
int main()
{
  input("data/tornado_data.txt");  //input our data
  input2("data/US_Carbon_Emissions.txt");
  input4("data/tornado_intensity.txt");
  init_gl_window();
}
