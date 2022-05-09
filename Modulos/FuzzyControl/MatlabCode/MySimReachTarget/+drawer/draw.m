classdef draw
    %DRAW Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        radius          % radio del robot, target, y el obstaculo.
        x_ambiente      % dimensiones x e y del ambiente de simulacion
        y_ambiente      %
  
    end
    
    methods
        
        function obj = draw(radius, x_ambiente, y_ambiente)
            % Crea un nuevo objeto Draw
            obj.radius = radius;
            obj.x_ambiente = x_ambiente;
            obj.y_ambiente = y_ambiente;
        end
       
        function polyList = showOTR(obj,obstacle,target,robot,polyList)
            % Muestra la posicion inicial del robot, obstaculo y target
           
            obj.radius = 1;        % radio del robot, target, y el obstaculo.
            axis([0 obj.x_ambiente 0 obj.y_ambiente]);    % ambiente de simulacion.
            pbaspect([1 1 1]);     % Grafico cuadrado (sale con la misma relacion de aspecto al graficar)

            % Dibujo de obstaculos
            for i = 1 : size(obstacle,2)/2
                %drawer.funciones.dibujar_obstaculo(obstacle, obj.radius, i);
                polyList = drawer.funciones.new_dibujar_obstaculo(obstacle, obj.radius, obj.radius, i, polyList);
            end
            
            % Dibujo target
            drawer.funciones.dibujar_target(target, obj.radius);

            % Dibujo robot
            drawer.funciones.dibujar_robot(robot, obj.radius);
        end
    end
end

