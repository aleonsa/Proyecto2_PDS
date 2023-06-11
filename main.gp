# GRAFICACION EN GNUPLOT

#set term corel


set autoscale
set multiplot layout 2,1 rowsfirst
set grid
set style data lines

#------------- Graf 1 ----------------
set title "Voltage Controlled Oscilator"
#unset label
set xlabel   "n"
set ylabel   "VCO(n)"
plot  "vco.dat"
unset xlabel
unset ylabel
unset title

#------------- Graf 2 ----------------
set title "Spectrum magnitude of the VCO"
# unset label
set xlabel   "w"
set ylabel   "|VCO(w)|"
plot  "spec.dat"
unset xlabel
unset ylabel
unset title

unset xlabel
unset ylabel
unset title

#pause(3)
#unset multiplot

#