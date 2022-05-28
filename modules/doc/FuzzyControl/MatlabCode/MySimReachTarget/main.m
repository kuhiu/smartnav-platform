close all
clear 
clc

% Creo navegador (AQUI SE INICIALIZA EL SISTEMA)
nav = simulador.navegador();

% Creo graficador
d = drawer.draw(1,nav.X_LIM_AREA,nav.Y_LIM_AREA);

% Plot
subplot(1,1,1);

% Simulacion
nav = nav.GoToTarget(d);








