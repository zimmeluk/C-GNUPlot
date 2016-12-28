#include<iostream>
#include<fstream>
using namespace std;
#ifdef MACOSX
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<sstream>

int WIDTH = 800;  // width of the user window
int HEIGHT = 600;  // height of the user window
char programName[] = "Big Data Sample UI";

// button info
bool buttonIsPressed = false, overButton = false;
double buttonPos[] = { 50, 350,   80, 40 };  // upper left, width, height
bool button2IsPressed = false, overButton2 = false;
double button2Pos[] = { 150, 350, 80, 40 };  // ul, w, h
bool button3IsPressed = false, overButton3 = false;
double button3Pos[] = { 250, 350, 80, 40 };  // ul, w, h
bool button4IsPressed = false, overButton4 = false;
double button4Pos[] = { 350, 350, 80, 40 };  // ul, w, h
bool buttongoIsPressed = false, overButtongo = false;
double buttongoPos[] = { 350, 500, 110, 60 };  // ul, w, h

// slider info
bool slider1IsPressed = false, overSlider1 = false;
bool slider2IsPressed = false, overSlider2 = false;
double slider1Box1[] = { 105, 208,   128, 4 };  // background of slider
double slider2Box1[] = { 405, 208,   128, 4 };  // background of slider
double slider1Box2[] = { 100, 200,   10, 20 };  // foreground 1 of slider
double slider1Pos = 0;  // where the slider currently is located
double slider1StartPos;  // where the mouse first clicked on the slider
double slider2Box2[] = { 400, 200,   10, 20 };  // foreground 2 of slider
double slider2Pos = 128;  // where the slider currently is located
double slider2StartPos;  // where the mouse first clicked on the slider
double sliderMax = 128;  // upper limit to the sliderPos

// textbox info
bool overTextBox = false;
string textInBox = "Or, enter filename";
double textBox1[] = { 450, 350,   200, 40 };  // outer box for text
double textBox2[] = { 455, 355,   190, 30 };  // inner box for text
const unsigned int MAX_NUM_CHARS_IN_TEXTBOX = 20;

// labels info
char instyear [] = "Please choose a range of years from 1950 to 2014.";
char instdata [] = "Please choose which dataset you would like to display.";
char instdoit [] = "Press 'view graph' to see your completed graph.";
int year = 2014;

// the following function draws a rectangle, given
//   the upper left vertex and the width and height
void drawBox(double x, double y, double width, double height)
{
  glBegin(GL_POLYGON);
    glVertex2f(x, y);  // upper left
    glVertex2f(x, y + height);  // lower left
    glVertex2f(x + width, y + height);  // lower right
    glVertex2f(x + width, y);  // upper right
  glEnd();
}
void drawBox(double *pos)
{
  drawBox(pos[0], pos[1], pos[2], pos[3]);
}

// the drawText function draws some text at location x, y
//   note:  the text to be drawn is a C-style string!
void drawText(double x, double y, const char *text)
{
  glRasterPos2f( x, y );
  int length = strlen(text);
  for (int i = 0; i < length; i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
}

// the drawNumber function draws a number at location x, y
void drawNumber(double x, double y, double num)
{
  stringstream oss;
  oss << num; oss.flush();
  drawText(x, y, oss.str().c_str());
}


void drawWindow()
{
  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);
  
  // draw the button
  if ( buttonIsPressed ) glColor3f(0.3, 0.3, 0.3);  // make it dark gray
  else if ( overButton ) glColor3f(1.,1.,1.);  // light gray
  else glColor3f(.75, .75, .75);  // gray
  drawBox(buttonPos);
  glColor3f(0.,0.,0.);  drawText(58,374,"Tornado");
  
  // draw the second button
  if ( button2IsPressed ) glColor3f(0.3, 0.3, 0.3);  // make it dark gray
  else if ( overButton2 ) glColor3f(1.,1.,1.);  // white
  else glColor3f(.75, .75, .75);  // light gray
  drawBox(button2Pos);
  glColor3f(0.,0.,0.);  drawText(158,374,"Tornado");
  
  // draw the third button
  if ( button3IsPressed ) glColor3f(0.3, 0.3, 0.3);  // make it dark gray
  else if ( overButton3 ) glColor3f(1.,1.,1.);  // white
  else glColor3f(.75, .75, .75);  // light gray
  drawBox(button3Pos);
  glColor3f(0.,0.,0.);  drawText(258,374,"Tornado");
  
  // draw the fourth button
  if ( button4IsPressed ) glColor3f(0.3, 0.3, 0.3);  // make it dark gray
  else if ( overButton4 ) glColor3f(1.,1.,1.);  // white
  else glColor3f(.75, .75, .75);  // light gray
  drawBox(button4Pos);
  glColor3f(0.,0.,0.);  drawText(360,374,"Tornado");
  
  // draw the go button
  if ( buttongoIsPressed ) glColor3f(0.3, 0.3, 0.3);  // make it dark gray
  else if ( overButtongo ) glColor3f(1.,1.,1.);  // white
  else glColor3f(.75, .75, .75);  // light gray
  drawBox(buttongoPos);
  glColor3f(0.,0.,0.);  drawText(360,530,"View graph");
  
  // draw the slider 1 background
  if ( slider1IsPressed || overSlider1 ) glColor3f(.5, .5, .5);  // gray
  else glColor3f(.25, .25, .25);  // dark gray
  drawBox(slider1Box1);
    // draw the slider 2 background
  if ( slider2IsPressed || overSlider2 ) glColor3f(.5, .5, .5);  // gray
  else glColor3f(.25, .25, .25);  // dark gray
  drawBox(slider2Box1);
  // draw the slider 1 foreground
  if ( overSlider1 ) glColor3f(.95, .95, .95);  // very light gray
  else glColor3f(.75, .75, .75);  // light gray
  drawBox(slider1Box2[0] + slider1Pos, slider1Box2[1], 
          slider1Box2[2],  slider1Box2[3]);
  // draw the slider 2 foreground
  if ( overSlider2 ) glColor3f(.95, .95, .95);  // very light gray
  else glColor3f(.75, .75, .75);  // light gray
  drawBox(slider2Box2[0] + slider2Pos, slider2Box2[1], 
          slider2Box2[2],  slider2Box2[3]);
  
  // draw the textbox
  glColor3f(.25, .25, .25);  // dark gray
  drawBox(textBox1);
  if ( overTextBox ) glColor3f(1,1,1);  // white
  else glColor3f(.75, .75, .75);  // light gray
  drawBox(textBox2);
  glColor3f(0, 0, 0);  // black
  if ( overTextBox ) { // draw with a cursor
    string withCursor(textInBox);
    withCursor += '|';
    drawText( textBox2[0]+5, textBox2[1]+textBox2[3]-10, withCursor.c_str() );
  } else drawText( textBox2[0]+5, textBox2[1]+textBox2[3]-10, textInBox.c_str() );

  // Draw the instructions
  glColor3f(1,1,1);
  drawText(320, 50, programName);
  drawText(50, 150, instyear);
  drawText(50, 300, instdata);
  drawText(50, 450, instdoit);
  drawNumber(280, 212, (int)(slider1Pos/2)+1950);
  drawText(320, 212, "-");
  drawNumber(330, 212, (int)(slider2Pos/2)+1950);

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
  if ( overTextBox ) { // intercept keyboard press, to place in text box
    if ( 27==c ) exitAll();  // escape terminates the program, even in textbox
    if ( 13==c ) {
      cout << "textBox content was: " << textInBox << endl;
      textInBox = "";
    } else if ( '\b'==c || 127==c ) { // handle backspace
      if ( textInBox.length() > 0 ) textInBox.erase(textInBox.end()-1);
    } else if ( c >= 32 && c <= 126 ) { // check for printable character
      // check that we don't overflow the box
      if ( textInBox.length() < MAX_NUM_CHARS_IN_TEXTBOX ) textInBox += c;
    }
  } else {
    switch(c) {
      case 'q':
      case 'Q':
      case 27:
        exitAll();
        break;
      default:
        break;
    }
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
bool onButton(int x, int y)
{
  return x >= buttonPos[0]  && y >= buttonPos[1] &&
         x <= buttonPos[0] + buttonPos[2] &&
         y <= buttonPos[1] + buttonPos[3];
}
// Same as above for button2
bool onButton2(int x, int y)
{
  return x >= button2Pos[0]  && y >= button2Pos[1] &&
         x <= button2Pos[0] + button2Pos[2] &&
         y <= button2Pos[1] + button2Pos[3];
}// Same as above for button3
bool onButton3(int x, int y)
{
  return x >= button3Pos[0]  && y >= button3Pos[1] &&
         x <= button3Pos[0] + button3Pos[2] &&
         y <= button3Pos[1] + button3Pos[3];
}// Same as above for button4
bool onButton4(int x, int y)
{
  return x >= button4Pos[0]  && y >= button4Pos[1] &&
         x <= button4Pos[0] + button4Pos[2] &&
         y <= button4Pos[1] + button4Pos[3];
}// Same as above for buttongo
bool onButtongo(int x, int y)
{
  return x >= buttongoPos[0]  && y >= buttongoPos[1] &&
         x <= buttongoPos[0] + buttongoPos[2] &&
         y <= buttongoPos[1] + buttongoPos[3];
}

// the following function tests whether a point at position x,y is inside
//   the rectangle on the screen corresponding to the slider
bool onSlider1Foreground(int x, int y)
{
  return x >= slider1Box2[0]+slider1Pos  && y >= slider1Box2[1] &&
         x <= slider1Box2[0]+slider1Box2[2]+slider1Pos &&
         y <= slider1Box2[1]+slider1Box2[3];
}
bool onSlider2Foreground(int x, int y)
{
  return x >= slider2Box2[0]+slider2Pos  && y >= slider2Box2[1] &&
         x <= slider2Box2[0]+slider2Box2[2]+slider2Pos &&
         y <= slider2Box2[1]+slider2Box2[3];
}
bool onSlider1Background(int x, int y)
{
  return x >= slider1Box2[0]  && y >= slider1Box2[1] &&
         x <= slider1Box2[0]+sliderMax+slider1Box2[2] &&
         y <= slider1Box2[1]+slider1Box2[3];
}
bool onSlider2Background(int x, int y)
{
  return x >= slider2Box2[0]  && y >= slider2Box2[1] &&
         x <= slider2Box2[0]+sliderMax+slider2Box2[2] &&
         y <= slider2Box2[1]+slider2Box2[3];
}

// the following function tests whether a point at position x,y is inside
//   the rectangle on the screen corresponding to the textBox background
bool onTextBox(int x, int y)
{
  return x >= textBox1[0] && y >= textBox1[1] &&
         x <= textBox1[0]+textBox1[2] &&
         y <= textBox1[1]+textBox1[3];
}

// the mouse function is called when a mouse button is pressed down or released
void mouse(int mouseButton, int state, int x, int y)
{
  if ( GLUT_LEFT_BUTTON == mouseButton ) {
    if ( GLUT_DOWN == state ) {
      // the user just pressed down on the mouse-- do something
      if ( onButton(x,y) ) buttonIsPressed = true;
      else buttonIsPressed = false;
      if ( onButton2(x,y) ) button2IsPressed = true;
      else button2IsPressed = false;
      if ( onButton3(x,y) ) button3IsPressed = true;
      else button3IsPressed = false;
      if ( onButton4(x,y) ) button4IsPressed = true;
      else button4IsPressed = false;
      if ( onButtongo(x,y) ) buttongoIsPressed = true;
      else buttongoIsPressed = false;
      
      if ( onSlider1Foreground(x,y) ) {
        slider1IsPressed = true;
        slider1StartPos = x - slider1Pos;
      } else if ( onSlider1Background(x,y) ) {
        slider1IsPressed = true;
        slider1Pos = x - slider1Box1[0];
        slider1StartPos = x-slider1Pos;
      } else slider1IsPressed = false;

      if ( onSlider2Foreground(x,y) ) {
        slider2IsPressed = true;
        slider2StartPos = x - slider2Pos;
      } else if ( onSlider2Background(x,y) ) {
        slider2IsPressed = true;
        slider2Pos = x - slider2Box1[0];
        slider2StartPos = x-slider2Pos;
      } else slider2IsPressed = false;
    } else {
      // the user just let go the mouse-- do something
      if ( onButton(x,y) && buttonIsPressed )
        cout << "Button 1 press." << endl;
      buttonIsPressed = false;
      if ( onButton2(x,y) && button2IsPressed )
	cout << "Button 2 press." << endl;
      button2IsPressed = false;
      if ( onButton3(x,y) && button3IsPressed )
	cout << "Button 3 press." << endl;
      button3IsPressed = false;
      if ( onButton4(x,y) && button4IsPressed )
	cout << "Button 4 press." << endl;
      button4IsPressed = false;
      if ( onButtongo(x,y) && buttongoIsPressed )
	cout << "Button go press." << endl;
      buttongoIsPressed = false;
      if ( slider1IsPressed )
        cout << "New slider position: " << slider1Pos << endl;
      slider1IsPressed = false;
      if ( slider2IsPressed )
        cout << "New slider position: " << slider2Pos << endl;
      slider2IsPressed = false;
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
  if ( buttonIsPressed ) {
    // do nothing
  } else if ( slider1IsPressed ) {
    double newSlider1Pos = x - slider1StartPos;
    // check that the new slider pos does not go off the end of the slider
    if ( newSlider1Pos < 0 ) slider1Pos = 0;
    else if ( newSlider1Pos > sliderMax ) slider1Pos = sliderMax;
    else slider1Pos = newSlider1Pos;
  } else {
    if ( onButton(x,y) ) overButton = true;
    else overButton = false;
    if ( onButton2(x,y) ) overButton2 = true;
    else overButton2 = false;
    if ( onButton3(x,y) ) overButton3 = true;
    else overButton3 = false;
    if ( onButton4(x,y) ) overButton4 = true;
    else overButton4 = false;
    if ( onButtongo(x,y) ) overButtongo = true;
    else overButtongo = false;
    if ( onSlider1Background(x,y) ) overSlider1 = true;
    else overSlider1 = false;
    if ( onTextBox(x,y) ) overTextBox = true;
    else overTextBox = false;
  }; if ( slider2IsPressed ) {
    double newSlider2Pos = x - slider2StartPos;
    // check that the new slider pos does not go off the end of the slider
    if ( newSlider2Pos < 0 ) slider2Pos = 0;
    else if ( newSlider2Pos > sliderMax ) slider2Pos = sliderMax;
    else slider2Pos = newSlider2Pos;
  } else {
    if ( onButton(x,y) ) overButton = true;
    else overButton = false;
    if ( onButton2(x,y) ) overButton2 = true;
    else overButton2 = false;
    if ( onButton3(x,y) ) overButton3 = true;
    else overButton3 = false;
    if ( onButton4(x,y) ) overButton4 = true;
    else overButton4 = false;
    if ( onButtongo(x,y) ) overButtongo = true;
    else overButtongo = false;
    if ( onSlider2Background(x,y) ) overSlider2 = true;
    else overSlider2 = false;
    if ( onTextBox(x,y) ) overTextBox = true;
    else overTextBox = false;
  }
  glutPostRedisplay();
}

// the init function sets up the graphics card to draw properly
void init(void)
{
  // clear the window to black
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // set up the coordinate system:  number of pixels along x and y
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);

  // welcome message
  cout << "Welcome to " << programName << ".  Try pressing the button, moving the slider," << endl;
  cout << " or typing in the text box." << endl;
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

  glutDisplayFunc(drawWindow);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_motion);
  glutPassiveMotionFunc(mouse_motion);
  glutMainLoop();
}

int main()
{
  init_gl_window();
}
