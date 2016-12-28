//  demo-ui.cpp
//  demonstration of the proposed UI for final SD Project

#include <iostream>
using namespace std;

#include <string.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "texture.h"
#include "Data_Array.h"
#include "Data_Point.h"
#include "Data_Array.cpp"

int WIDTH = 600;                   // width of the user window
int HEIGHT = 350;                  // height of the user window
char programName[] = "Demo UI";
int Tornado1;

// button info
bool buttonIsPressed = false, overButton = false;
double buttonPos[] = { 20, 70,   140, 50 };    // upper left

// button2 info
bool button2IsPressed = false, overButton2 = false;
double button2Pos[] = { 170, 70, 180, 50 };    // upper right

// button3 info
bool button3IsPressed = false, overButton3 = false;
double button3Pos[] = { 20, 130,   180, 50 };  // middle left

// button4 info
bool button4IsPressed = false, overButton4 = false;
double button4Pos[] = { 210, 130, 140, 50 };   // middle right

// button5 info
bool button5IsPressed = false, overButton5 = false;
double button5Pos[] = { 420, 275, 120, 40 };   // middle right

// checkbox info
bool checkPressed = false, overCheck = false;
double checkPos[] = { 425, 200, 10, 10 };

// checkbox info
bool check2Pressed = false, overCheck2 = false;
double check2Pos[] = { 425, 230, 10, 10 };

//textbox info
double textPos[]= { 20 , 190 , 330 , 140 };

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
char mapGraph [] = "United States Map";
char axisGraph [] = "XY Axis Graph";
char selectYear []  = "YEAR";
char selectData []  = "DATASET";
char selectGraph [] = "GRAPH";
char sliderPosStr [5];
char sliderPosStr2 [5];
int yr;
double value;
Data_Array tornado(65);
Data_Array carbon(55);


/*
//input our data
ifstream g("tornado_data.txt");
int year;
float value;
g>>year>>value;
*/
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
  oss << num; oss.flush();
  drawText(x, y, oss.str().c_str(), 0);
}

void drawCheckBox(double x1, double y1, double width, double height)
{
  // Draw black boundary.
  glColor3f(0.0, 0.0, 0.0);
  drawBox(x1 - 3, y1 - 3, width + 6, width + 6);

  glColor3f(1., 1., 1.);
  //placement of the check box
  drawBox(x1, y1, width, height);
}

void drawCheckBox(double *pos)
{
  drawCheckBox(pos[0], pos[1], pos[2], pos[3]);
}

void drawWindow()
{
  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  
  //draw the text box
  glColor3f(0.9, 0.9, 0.9);                              // dark gray
  drawBox(textPos);
  glColor3f(0., 0., 0.);
  drawText(120,205,"Statistic Information",0);

  // draw the button TORNADO
  if ( buttonIsPressed ) {
    glColor3f(0.,.4, 0.7);    // dark blue
    drawText(100,230,"Year: ",0);
    drawNumber(140,230,tornado[0]->year);
    drawNumber(180,230,tornado[64]->year);
    drawText(170,230,"-",0);
    drawText(90,250,"Max: ",0);
    drawNumber(130,250,tornado[tornado.max()-1950]->data_value);
    drawText(165,250,"in year ",0);
    drawNumber(210,250,tornado.max());
    drawText(90,270,"Min: ",0);
    drawNumber(130,270,tornado[tornado.min()-1950]->data_value);
    drawText(165,270,"in year ",0);
    drawNumber(210,270,tornado.min());
  }
  else if ( overButton ) glColor3f(.75,.75,.75);   // light gray
  else glColor3f(0., .70, .90);                    // light blue
  drawBox(buttonPos);
  
  // if (buttonIsPressed) drawTexture(Tornado1, buttonPos);
  // else if (overButton) drawTexture(Tornado1, buttonPos);
  // else drawTexture(Tornado1, buttonPos);
  

  // draw the second button CARBON
  if ( button2IsPressed ){
    glColor3f(0., .4, 0.7);  // dark blue
    drawText(100,230, "Year: ",0);
    drawNumber(140,230,carbon[0]->year);
    drawNumber(180,230,carbon[54]->year);
    drawText(170, 230, "-",0);
    drawText(90,250,"Max: ",0);
    drawNumber(130,250,carbon[carbon.max()-1960]->data_value);
    drawText(165,250,"in year ",0);
    drawNumber(210,250,carbon.max());
    drawText(90,270,"Min: ",0);
    drawNumber(130,270,carbon[carbon.min()-1960]->data_value);
    drawText(165,270,"in year ",0);
    drawNumber(210,270,carbon.min());
   
  }
  
  else if ( overButton2 ) glColor3f(.75,.75,.75);  // light gray
  else glColor3f(0., .70, .90);                    // light blue
  drawBox(button2Pos);

  // draw the third button
  if ( button3IsPressed ) glColor3f(0.,.4, 0.7);   // dark blue
  else if ( overButton3 ) glColor3f(.75,.75,.75);  // light gray
  else glColor3f(0., .70, .90);                    // light blue
  drawBox(button3Pos);

  // draw the fourth button
  if ( button4IsPressed ) glColor3f(0.,.4, 0.7);   // dark blue
  else if ( overButton4 ) glColor3f(.75,.75,.75);  // light gray
  else glColor3f(0., .70, .90);                    // light blue
  drawBox(button4Pos);

  // draw the fifth button
  if ( button5IsPressed ) glColor3f(0.,.75, 1.);   // light blue
  else if ( overButton5 ) glColor3f(.75,.75,.75);  // light gray
  else glColor3f(.75, .75, .75);                   // light gray
  drawBox(button5Pos);

  //draw the button value
  glColor3f(0., 0., 0.);
  drawText(60,100,"Tornado",0);
  drawText(230,100,"Carbon Emissions",0);
  drawText(75,160,"Tornado",0);
  drawText(220,160,"Upload your own",0);
  drawText(450,300,"view graph",0);

  // draw checkbox
  drawCheckBox(checkPos);
  if (checkPressed) glColor3f(0, .90, .40);
  else glColor3f(1., 1., 1.);
  drawBox(checkPos);

  // draw checkbox2
  drawCheckBox(check2Pos);
  if (check2Pressed) glColor3f(0, .90, .40);
  else glColor3f(1., 1., 1.);
  drawBox(check2Pos);

  // draw checkbox values
  glColor3f(0., 0., 0.);
  drawText(455, 210, mapGraph, 0);
  drawText(455, 240, axisGraph, 0);

  // draw selection label
  glColor3f(0., .70, .90);
  drawText(150, 55, selectData, 1);
  glColor3f(.75, .30, .30);
  drawText(470, 35, selectYear, 1);
  glColor3f(0., .90, .40);
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
  if ( overSlider ) glColor3f(.75, .30, .30);                     // red
  else glColor3f(.75, .75, .75);                                  // light gray
  drawBox(sliderBoxMin[0] + sliderPos, sliderBoxMin[1], 
          sliderBoxMin[2],  sliderBoxMin[3]);
  // draw the slider foreground-max
  if ( overSlider ) glColor3f(.75, .30, .30);                     // red
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
/*
bool onEverything(int x, int y,double * barray, bool &bflag){
  return (onButton(x,y, barray,bflag)||
	  onCheck(x,y)
	  );
}
*/

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
      /*
      if (onEverything(x,y,buttonPos, buttonIsPressed)) buttonIsPressed=true;
      else buttonIsPressed=false;
      if (onEverything(x,y,button2Pos, button2IsPressed)) button2IsPressed=true;
      else button2IsPressed=false;
      if (onEverything(x,y,button3Pos, button3IsPressed)) button3IsPressed=true;
      else button3IsPressed=false;
      if (onEverything(x,y,button4Pos, button4IsPressed)) button4IsPressed=true;
      else button4IsPressed=false;
      */
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
      // the user just let go the mouse-- do something
      if (overButton && buttonIsPressed) {//buttonIsPressed = false;
        cout << "Button press." << endl;}
      if (overButton2 && button2IsPressed) {//button2IsPressed = false;
        cout << "Button2 press." << endl;}
      if (overButton3 && button3IsPressed) {//button3IsPressed = false;
	cout << "Button3 press." << endl;}
      if (overButton4 && button4IsPressed) {//button4IsPressed = false;
	cout << "Button4 press." << endl;}
      if (overButton5 && button5IsPressed) {button5IsPressed = false;
	cout << "Button5 press." << endl;}
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
  cout << "This is Big Data's proposed UI design." << endl;
  cout << "Textures coming soon!" << endl;
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

  // Tornado1 = loadTexture("Tornado1.pam");
  
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
  int i=0;
  while(g>>yr>>value){
    Data_Point a(yr,value);
    tornado[i]=new Data_Point;
    tornado[i]->year=a.year;
    tornado[i]->data_value=a.data_value;
    i++;
  }
  
}

void input2(const char*b){
  ifstream in(b);
  int i = 0;
  while(in>>yr>>value){
    Data_Point b(yr,value);
    carbon[i]= new Data_Point;
    carbon[i]->year = b.year;
    carbon[i]->data_value = b.data_value;
    i++;
  }
}
  
int main()
{
  input("tornado_data.txt");  //input our data
  input2("US_Carbon_Emissions.txt");
  cout << carbon[54]->year << " " << carbon[54]->data_value << endl;
  // tornado.read_data("tornado_data.txt");
  // carbon.read_data("US_Carbon_Emissions.txt");
  init_gl_window();
}
