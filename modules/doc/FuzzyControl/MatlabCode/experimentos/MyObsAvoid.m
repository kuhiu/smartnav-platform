close all
clear 
clc

fis = readfis('mamfis');

vldObstacle_per_graph = {[11 10] [9 8] [3 4] [-1 -1] [-1 -1]};
vldObstacle_per_graph2 = {[11 11] [8 8] [5 5] [2 2] [12 17]};

obstacle = [vldObstacle_per_graph ; vldObstacle_per_graph ; vldObstacle_per_graph2];

%celda = obstacle(1,:);
%display(celda{2}(1,2))

robot = [12 20 -pi/2;5 20 -pi/2;5 20 -pi/2];
target = [12 4;12 4;12 4];


% Expand figure horizontally to tile the simulation environments.
h = figure;
%h.Position = [h.Position(1:2) 3*h.Position(3) h.Position(4)];
numTasks = size(target,1);  % Numero de planos a dibujar

fid = [];
fid1 = fopen('MyTextFile1.txt','wt');
fid2 = fopen('MyTextFile2.txt','wt');
fid3 = fopen('MyTextFile3.txt','wt');
fid = [fid1 fid2 fid3];

for i = 1:numTasks
    o = obstacle(i,:);  % Obstaculo de cada plot
    t = target(i,:);    % Target de cada plot
    r = robot(i,:);     % Robot de cada plot
    subplot(1,numTasks,i);
    %results = MyNavigationResult(o,t,r, fis, fid(i));
    display('One task finished');
    showOTR2(o,t,r)
end





