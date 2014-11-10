cortex-data
===========
PURPOSE: Storing data files on VEX Cortex; analyzing collected data using Python and Matlab


FILES/FOLDERS:

jpearman-lib - library for writing flash data to cortex (needed to run makefile.c)

makefile.c - robotc program that generates sensor data, can be customized to fit specific robot

debug013.dat - binary encoder data collected during a makefile.c run

plot_matlab - loads debu013.dat, converts data to integers, plots. can be customized for further data analysis

plot_python - same purpose as plot_matlab, but written in python using scipy, numpy, and matplotlib

Encoder Values Python.png - python plot of debug013.dat data
