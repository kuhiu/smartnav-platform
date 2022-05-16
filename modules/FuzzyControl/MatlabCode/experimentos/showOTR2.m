function showOTR2(obstacle,target,robot)

% Show the robot trajectory in the simulation environment.

% radio, anchos y altos del robot, target, y el obstaculo.
radius = 1; % 1m
largo_obstaculo = 1;
ancho_obstaculo = 1;

% 30x30 ambiente de simulacion.
axis([0 25 0 25]);

% Grafico cuadrado (sale con la misma relacion de aspecto al graficar)
pbaspect([1 1 1])

% Dibujo de obstaculos
%celda = vldObstacle(1,:);
display(obstacle)
display(size(obstacle,2))
%celda{2}(1,2)
display(obstacle{1})
display(obstacle{1}(1,1))

for i= 1 : size(obstacle,2)
    rectangle('Position',[obstacle{i}(1,1)-0.5*radius obstacle{i}(1,2)+0.5*radius ancho_obstaculo largo_obstaculo], ...
        'Curvature',[0 0],'FaceColor','b','EdgeColor','b')

% Dibujo target
rectangle('Position',[target(1)-0.5*radius target(2)+0.5*radius radius radius], ...
    'Curvature',[1 1],'FaceColor','r','EdgeColor','r')

% Dibujo robot
rectangle('Position',[robot(1)-0.5*radius robot(2)+0.5*radius radius radius], ...
    'Curvature',[1 1],'FaceColor','g','EdgeColor','g')

end