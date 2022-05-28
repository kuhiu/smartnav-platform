close all
clear 
clc

fisin = readfis('mamfis2');

vldObstacle = [13 5;10 10;8 21];
vldRobot = [15 20 0;5 20 -pi/2;19 19 -pi];
vldTarget = [16 1;12 4;2 15];

showNavigationTrajectories(fisin,vldObstacle,vldTarget,vldRobot);

