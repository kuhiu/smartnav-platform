close all
clear 
clc

% Creo navegador (AQUI SE INICIALIZA EL SISTEMA)
nav = simulador.navegador();

% Creo graficador
d = drawer.draw(1,25,25);

% Plot
subplot(1,1,1);

% Simulacion
nav = nav.GoToTarget(d);








