function results = MyNavigationResult(obstacle,target,robot,fis,fid)
    %
    % Va a devolver los resultados para una posicion especifica del robot,
    % target y del obstaculo. (incluye, la trayectoria (x,y) y un flag que 
    % indica si no colisiono)
   

    % Inicializacion de variables.
    persistent options
    if isempty(options)
        options = evalfisOptions;
        options.EmptyOutputFuzzySetMessage = 'none';
        options.NoRuleFiredMessage = 'none';
        options.OutOfRangeInputValueMessage = 'none';
    end
    reachedTarget = false;
    notSafe = false;
    travelledDistance = 0;
    X = [];
    Y = [];
    samplePeriod = 1;
    speed = 0.5;

    % Determine initial distances and angles of the target and obstacle.
    [distL_T distC_T distR_T] = SensoresDeDistancia(target,robot,fid);
    [distL_O distC_O distR_O] = SensoresDeDistancia(obstacle,robot,fid);

    % Simulacion
    for i = 1:100/samplePeriod

        % Evalua el FIS para conseguir theta
        Theta = evalfis(fis,[distL_O distC_O distR_O],options); % Theta orientado a cero
        
        fprintf(fid,"Las distancias: %d, %d, %d , el angulo: %d \n", distL_O,distC_O,distR_O, Theta);
        
        dx = target(1)-robot(1);
        dy = target(2)-robot(2);
        %dist = sqrt(dx^2+dy^2);
        ang = atan2(dy,dx); % ang al target
        Theta = ang+Theta;  % Ahora theta esta orientado al target
        robot(3) = correctTheta(Theta);    % Evita que theta sea mayor que un permitido

        % Save previous robot position to calculate travelled distance.
        prx = robot(1);
        pry = robot(2);

        % Update robot position.
        robot(1) = robot(1) + samplePeriod*speed*cos(robot(3));
        robot(2) = robot(2) + samplePeriod*speed*sin(robot(3));

        % Update trajectory vectors.
        X = [X robot(1)]; %#ok<AGROW>
        Y = [Y robot(2)]; %#ok<AGROW>

        % Calculate travelled distance.
        travelledDistance = travelledDistance + sqrt((robot(1)-prx)^2+(robot(2)-pry)^2);

        % Update distance and angle to the target.
        %display(distC_O)
        [distL_T distC_T distR_T] = SensoresDeDistancia(target,robot,fid);

        % End simulation if target is reached.
        if (distL_T <= 1 || distC_T <= 1 || distR_T <= 1)
            reachedTarget = true;
            break
        end

        % Update distance and angle to the obstacle.
        [distL_O,distC_O,distR_O] = SensoresDeDistancia(obstacle,robot,fid);

        % End simulation if the robto collides with the obstacle.
        if (distL_O <= 1 || distC_O <= 1 || distR_O <= 1)
            notSafe = true;
            break
        end

        % End simulation if the robto goes outside of the simulation
        % environment. This condition is also treated as an unsafe condition as
        % a collision.
        if (robot(1)<0 || robot(1)>25) || (robot(2)<0 || robot(2)>25)
            notSafe = true;
            break
        end

    end

    % Update navigation results.
    results.x = X;
    results.y = Y;
    results.reachedTarget = reachedTarget;
    results.notSafe = notSafe;
    results.travelledDistance = travelledDistance;

    fclose(fid);

end

function [distL distC distR] = SensoresDeDistancia(loc,robot, fid)    
% De vuelve la distancia de 3 sensores, izquierda, derecha y central, en
% caso de encontrar un obstaculo en alguno de ellos

    % Calculate distance of LOC from ROBOT and determine orientation of LOC
    % with respect to ROBOT's heading direction.
    dx = loc(1)-robot(1);
    dy = loc(2)-robot(2);
    distC = sqrt(dx^2+dy^2);
    distL = sqrt(dx^2+dy^2);
    distR = sqrt(dx^2+dy^2);
    ang = atan2(dy,dx);

    %fprintf(fid,"Las distancias: %d, %d, %d , el angulo: %d \n", distL,distC,distR, ang);
    %fprintf(fid,"ang es: %d , robot(3) es :%d ,(pi/9+robot(3)) || ang <= (-pi/9+robot(3)) son: %d %d\n", ang, robot(3), (pi/9+robot(3)), (-pi/9+robot(3)) );
    
    if (ang >= (pi/9+robot(3)) || ang <= (-pi/9+robot(3)))                        % Simulo que los sensores solo tienen (aprox HC-SR04)
        distC = 40;        % un rango de vision de 20 grados
    end
    if (ang >= (-pi/9+robot(3)) || ang <= (2*pi/9+robot(3)))                      % Sensor izquierda
        distL = 40;       % un rango de vision de 20 grados
    end
    if (ang <= (pi/9+robot(3)) || ang >= (2*pi/9+robot(3)))                       % Sensor derecha
        distR = 40;        % un rango de vision de 20 grados
    end
end

function theta = correctTheta(theta)

% Ensure THETA is in [-pi,pi].
if theta > pi
    theta = theta - 2*pi;
end
if theta < -pi
    theta = 2*pi + theta;
end
end
