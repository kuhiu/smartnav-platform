function showOTR(obstacle,target,robot,navigationResults)

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
%display(celda{2})
for i= 1 : size(vldObstacle_per_graph,1)
    rectangle('Position',[obstacle{i}-0.5*radius obstacle(2)+0.5*radius ancho_obstaculo largo_obstaculo], ...
        'Curvature',[0 0],'FaceColor','b','EdgeColor','b')

% Dibujo target
rectangle('Position',[target(1)-0.5*radius target(2)+0.5*radius radius radius], ...
    'Curvature',[1 1],'FaceColor','r','EdgeColor','r')

% Dibujo robot
rectangle('Position',[robot(1)-0.5*radius robot(2)+0.5*radius radius radius], ...
    'Curvature',[1 1],'FaceColor','g','EdgeColor','g')

% Grafica la trayectoria del robot
if nargin == 4  % si a la funcion le pasamos como cuarto argumento el modelo fis
    x = navigationResults.x;
    y = navigationResults.y;
    for i = 1:numel(x)  % numel devuelve el numero de argumentos en el arrays
        rectangle('Position',[x(i)-0.5*radius y(i)+0.5*radius radius radius], 'Curvature',[1 1],'FaceColor','g','EdgeColor','g')
    end
end

end
