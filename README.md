                                  BIG DATA
README

  Big Data is a graphical user interface for Gnuplot that focuses specifially
  on the analysis of climate data. Using WebMapReduce, we have produced some
  data samples that come pre-packaged with the program.  Find out how to use
  Big Data by reading the User Manual.


CONTACT

  If you have any questions or concerns, please contact any of the Big Data
  team members:
  Rachel Frantsen '16......frantsen@stolaf.edu
  Maria Handzel '16........handzel@stolaf.edu
  Diyang Yu '17............yu@stolaf.edu
  Luke Zimmerman '18.......zimmer2@stolaf.edu


INSTALLATION

  To unpack or extract the tar.gz file, type:

     $ tar -xzvf BigData.tar.gz
 
  To run Big Data, you must first have Gnuplot installed on your computer.
  Gnuplot is a command line graphing utility that is available at:

     www.gnuplot.info

  Move the gnuplot-x.x.x folder to the place where you would like Gnuplot
  to be installed. Change into the gnuplot-x.x.x folder and install Gnuplot
  by running the follwing commands at the command line (Unix):

     $ ./configure
     $ make
     $ make install

  After Gnuplot has been installed, change into the BigData directory. Type
  the following at the command line:

     $ make

  To run Big Data, type:

     $ ./climate

  We hope you enjoy using Big Data!


WIKI

     www.cs.stolaf.edu/wiki/index.php/BigData


NOTICE

  We could not have complete this project without Gnuplot or the C++
  iostream interface written by Dan Stahlke. Dan's code can be found at:

     www.stahlke.org/dan/gnuplot-iostream/
     http://code.google.com/p/gnuplot-cpp/


