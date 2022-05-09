function [distL, distC, distR] = SensoresDeDistancia(obstacle,robot)    
    % De vuelve la distancia de 3 sensores, izquierda, derecha y central, en
    % caso de encontrar un obstaculo en alguno de ellos, sino devuelve la
    % max distancia posible de medir (40 cm)
    acumC = [];
    acumL = [];
    acumR = [];
    
    for i = 1 : size(obstacle,2)
        dx = obstacle{i}(1,1) - robot(1);
        dy = obstacle{i}(1,2) - robot(2);
        acumC(i) = sqrt(dx^2+dy^2);
        acumL(i) = sqrt(dx^2+dy^2);
        acumR(i) = sqrt(dx^2+dy^2);
        ang = atan2(dy,dx);
        
        if (ang >= (pi/9+robot(3)) || ang <= (-pi/9+robot(3)))          % Simulo que los sensores solo tienen (aprox HC-SR04)
            acumC(i) = 40;        % un rango de vision de 20 grados
        end
        if (ang >= (-pi/9+robot(3)) || ang <= (2*pi/9+robot(3)))        % Sensor izquierda
            acumL(i) = 40;       % un rango de vision de 20 grados
        end
        if (ang <= (pi/9+robot(3)) || ang >= (2*pi/9+robot(3)))         % Sensor derecha
            acumR(i) = 40;        % un rango de vision de 20 grados
        end
    end
   %display(acumC)
   distC = min(acumC);
   distL = min(acumL);
   distR = min(acumR);
end
