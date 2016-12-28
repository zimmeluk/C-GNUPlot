reset

# color definitions
set border linewidth 1.5
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5 # --- blue

# graph information
set title "Tornado Data"
set xlabel "Year"
set ylabel "Number of Tornadoes"
set autoscale

plot 'tornado_data.dat' with linespoints ls 1