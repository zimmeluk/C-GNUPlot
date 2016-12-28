########################
##                    ##
##      MAKEFILE      ##
##                    ##
########################

##
##  THE FOLLOWING LINES SET UP THE COMPILER OPTIONS AND LIBRARIES
##

OPTS = -g -Wall -std=c++11 -Iinclude/
LIBS = -lGL -lglut -lm
ARCH := $(shell uname)
TARBALL_FILES = README.md Makefile $(wildcard *.cpp *.h *.hpp *.xml *.csv *.dat *.txt Graphics/*.pam)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif

##
##  RULES
##

climate: climate.o texture.o Menu.o Data_Array.o
	g++ -w $(OPTS) -o climate -ggdb texture.o Menu.o climate.o $(LIBS)

climate.o: src/climate.cpp include/Menu.h include/MenuItem.h include/texture.h src/Data_Array.cpp
	g++ -w -ggdb -DDEBUGGA $(OPTS) $(MACOSX_DEFINE) -c src/climate.cpp

demo1-ui: demo1-ui.o texture.o
	g++ -w $(OPTS) -o demo1-ui demo1-ui.o texture.o $(LIBS)

demo1-ui.o: src/demo1-ui.cpp
	g++ -w $(OPTS) $(MACOSX_DEFINE) -c src/demo1-ui.cpp

MenuDriver: Menu.o  MenuDriver.o
	g++ $(OPTS) -o MenuDriver Menu.o MenuDriver.o

MenuItemDriver: MenuItemDriver.o MenuItem.o
	g++ $(OPTS) -o MenuItemDriver MenuItem.o MenuItemDriver.o

MenuItemDriver.o: src/MenuItemDriver.cpp include/Menu.h include/MenuItem.h
	g++ $(OPTS) -c src/MenuItemDriver.cpp

MenuDriver.o: src/MenuDriver.cpp include/Menu.h include/MenuItem.h
	g++ $(OPTS) -c src/MenuDriver.cpp

Menu.o:
	g++ $(OPTS) -c src/Menu.cpp

MenuItem.o: src/MenuItem.cpp include/MenuItem.h
	g++ $(OPTS) -c src/MenuItem.cpp

Data_Array.o: src/Data_Array.cpp include/Data_Array.h
	g++ $(OPTS) -c src/Data_Array.cpp

commandline: src/commandline.cpp
	g++ -o commandline src/commandline.cpp

demo-plot: demo-plot.o
	g++ -o $@ -ggdb demo-plot.o -lstdc++

demo-plot.o: src/demo-plot.cpp
	g++ -ggdb -DDEBUGGA -c $<

texture.o: src/texture.cpp include/texture.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c src/texture.cpp

tarball: $(TARBALL_FILES)
	tar cfz bigdata.tar.gz $(TARBALL_FILES)

clean:
	rm *.o climate