#
#This file can be used with gnuplot. Simply type at the command line:
#gnuplot daySZRD.gnu
#
plot "data/daySZRD.dat" u 1:2 w lines title "S", "data/daySZRD.dat" u 1:3 w lines title "Z", "data/daySZRD.dat" u 1:4 w lines title "R", "data/daySZRD.dat" u 1:5 w lines title "D"
pause -1 "hit return to continue"
