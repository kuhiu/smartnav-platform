classdef navegador
    %NAVEGADOR Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        TargetAlcanzado     % Indica si alcanzo el target
        NOseguro            % Indica si colisiono
        DistanciaViajada    % Distancia que viajo el robot
        X                   % Vector de posicion en X del robot
        Y                   % Vector de posicion en Y del robot
        Velocidad           % Velocidad con la que se mueve el robot
        PeriodoDeSampleo    % Sampleo (simulacion)
        options             % Variable options (para evalfis)
        
        fis                 % Sistema difuso
        
        obstacles           % Obstaculos set
        robot               % Robot set
        target              % Target set

        prx                 % Posicion actual del robot en X
        pry                 % Posicion actual del robot en Y
        pra
        p                   % Plot
        
        fid

        dist_al_target
        
        triangle1
        triangle2
        triangle3
        triangle1_polyshape
        triangle2_polyshape
        triangle3_polyshape
        plot_triangle1
        plot_triangle2
        plot_triangle3
        
        polyList
    end
    
    methods
        function nav = navegador()
            %NAVEGADOR Constructor
            nav.TargetAlcanzado = false;
            nav.NOseguro = false;
            nav.DistanciaViajada = 0;
            nav.X = [];
            nav.Y = [];
            nav.Velocidad = 0.2;
            nav.PeriodoDeSampleo = 0.3;
            
            % Inicializacion de variable options (para evalfis)
            nav.options = evalfisOptions;
            nav.options.EmptyOutputFuzzySetMessage = 'none';
            nav.options.NoRuleFiredMessage = 'none';
            nav.options.OutOfRangeInputValueMessage = 'none';
            
            % Leo sistema de control difuso con el diseño implementado por nosotros
            nav.fis = readfis('mamfis');

            % Inicializo obstaculos para cada grafico, posiciones 'X' e 'Y' (-1 => ningun obstaculo en la simulacion)
            nav.obstacles = [ [10 10] [9 10]  [11 10] [12 10] [13 10]];
            nav.robot = [10 4 0];    % El tercer argumento es la orientacion absoluta del robot al iniciar 
            nav.target = [10 15];
            
            nav.prx = 0;
            nav.pry = 0;
            
            nav.fid = [];
            nav.fid = fopen('MyTextFile1.txt','wt');

        end
        
        function nav = GoToTarget(nav,d)
            
            % Guardo en nav.X e nav.Y la posicion inicial del robot
            nav.X(1) = nav.robot(1);
            nav.Y(1) = nav.robot(2);
            nav.prx = nav.robot(1);
            nav.pry = nav.robot(2);
            
            % Creacion de sensores (objeto)
            nav.triangle1 = Robot.Sensores.NewSensor();
            nav.triangle2 = Robot.Sensores.NewSensor();
            nav.triangle3 = Robot.Sensores.NewSensor();
            
            % Parametros fisicos del sensor central
            nav.triangle1.ubicacion = [0,0];
            nav.triangle1.apertura = 35/2;
            nav.triangle1.largo = 3;
            nav.triangle1.rotacion = 0;
            
            % Parametros fisicos del sensor izquierdo
            nav.triangle2.ubicacion = [0,0];
            nav.triangle2.apertura = 35/2;
            nav.triangle2.largo = 3;
            nav.triangle2.rotacion = 0;
            
            % Parametros fisicos del sensor derecho
            nav.triangle3.ubicacion = [0,0];
            nav.triangle3.apertura = 35/2;
            nav.triangle3.largo = 3;
            nav.triangle3.rotacion = 0;
            
            % Actualizacion de la forma del sensor
            nav.triangle1 = nav.triangle1.TrasladarYRotar();
            nav.triangle2 = nav.triangle1.TrasladarYRotar();
            nav.triangle3 = nav.triangle1.TrasladarYRotar();
            
            % Ahora hago que el sensor mire hacia el mismo lado que el robot
            dx = nav.target(1)-nav.robot(1);
            dy = nav.target(2)-nav.robot(2);
            ang = atan2(dy,dx);  	% ang al target
            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            % Transformo el triangulo a un polyshape
            nav.triangle1_polyshape = polyshape(nav.triangle1.Xrot, nav.triangle1.Yrot);
            % Lo traslado a la ubicacion del robot
            nav.triangle1_polyshape = translate(nav.triangle1_polyshape, [nav.robot(1),nav.robot(2)]);
            % Hago que mire hacia el target (igual que el robot)
            nav.triangle1_polyshape = rotate(nav.triangle1_polyshape, -(ang*180/pi - 90), [nav.robot(1), nav.robot(2)] );
            
            nav.triangle2_polyshape = polyshape(nav.triangle2.Xrot, nav.triangle2.Yrot);
            nav.triangle2_polyshape = translate(nav.triangle2_polyshape, [nav.robot(1),nav.robot(2)]);
            nav.triangle2_polyshape = rotate(nav.triangle2_polyshape, -(ang*180/pi-30 -90), [nav.robot(1), nav.robot(2)] );        

            nav.triangle3_polyshape = polyshape(nav.triangle3.Xrot, nav.triangle3.Yrot);
            nav.triangle3_polyshape = translate(nav.triangle3_polyshape, [nav.robot(1),nav.robot(2)]);
            nav.triangle3_polyshape = rotate(nav.triangle3_polyshape, -(ang*180/pi+30 -90), [nav.robot(1), nav.robot(2)] );
            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            
            % Plotea cono o triangulo que hace de sensor
            nav.plot_triangle1 = plot(nav.triangle1_polyshape);
            nav.plot_triangle1.FaceColor = 'blue';
            hold on;
            nav.plot_triangle2 = plot(nav.triangle2_polyshape);
            nav.plot_triangle2.FaceColor = 'blue';    
            hold on;
            nav.plot_triangle3 = plot(nav.triangle3_polyshape);
            nav.plot_triangle3.FaceColor = 'blue';
            hold on;
            grid on;
            % Plotea el movil
            nav.p = plot(nav.robot(1),nav.robot(2),'o');

            % Graficador de posicion inicial del target, robot y obstaculo
            nav.polyList = d.showOTR(nav.obstacles,nav.target,nav.robot, nav.polyList);
            
            % Limito el area de simulacion (25 metros x 25 metros)
            xlim([0 25])
            ylim([0 25])
            
            % Leyenda al grafico
            legend({'Cono', 'Cono' , 'Cono','Vehiculo', 'Obstaculo'},'Location','southwest')
            
            % Estas lineas sirven para actualizar el grafico
            linkdata on;    
            set(nav.p, 'XDataSource', 'nav.robot(1)', 'YDataSource', 'nav.robot(2)')

            % Determina las distancias iniciales al target y al obstaculo.
            nav.dist_al_target = Robot.Sensores.gps(nav.target,nav.robot);
            %[distL_O, distC_O, distR_O] = Robot.Sensores.SensoresDeDistancia(nav.o,nav.robot);  
            
            % Test [dist1,dist2,dist3] inicialmente en 3
            distL_O = 3;
            distC_O = 3;
            distR_O = 3;
            
            dx = nav.target(1)-nav.robot(1);
            dy = nav.target(2)-nav.robot(2);
            ang = atan2(dy,dx);  	% ang al target
            nav.robot(3) = ang;
            
            pause (4);
            
            for i = 2:100/nav.PeriodoDeSampleo
                
                % Para hacer la simulacion mas lenta
                pause(.2)
                
                % Evalua el FIS para conseguir theta
                %Theta = evalfis(nav.fis,[distL_O distC_O distR_O],nav.options); % Theta orientado a cero
                Theta = evalfis(nav.fis,[distR_O,distC_O,distL_O],nav.options); % Theta orientado a cero
                %Theta = nav.correctTheta(Theta);    % Evita que theta sea mayor que un permitido
                %display(Theta);
                nav.pra = nav.robot(3);            % Save previus angle
                
                % Oriento Theta al target...
                dx = nav.target(1)-nav.robot(1);
                dy = nav.target(2)-nav.robot(2);
                ang = atan2(dy,dx);  	% ang al target
                
%                 display((ang + Theta) - nav.robot(3));
%                 if ( ((ang + Theta) - nav.robot(3)) > pi/4 )
%                     excedente = pi/4 - ((ang + Theta) - nav.robot(3)) ;
%                     nav.robot(3) = ang + Theta - excedente ;
%                 elseif ( (ang + Theta) - nav.robot(3) < -pi/4 )
%                     faltante = - pi/4 + ((ang + Theta) - nav.robot(3)) ;
%                     nav.robot(3) = ang + Theta ;
%                 else
%                     nav.robot(3) = ang + Theta;
%                 end
                
                %nav.robot(3) = ang + Theta;
                
                nav.robot(3) = Theta + 90;
                
                % Guardo datos en un archivo para testear
                fprintf(nav.fid,"Las distancias: %d, %d, %d , el angulo: %d \n", distR_O,distC_O,distL_O, Theta);
                
                % Guardo la posicion previa del robot para calcular la distancia recorrida. 
                nav.prx = nav.robot(1);
                nav.pry = nav.robot(2);

                % Actualizo posicion del robot.
                nav.robot(1) = nav.robot(1) + nav.PeriodoDeSampleo * nav.Velocidad * cos(nav.robot(3));
                nav.robot(2) = nav.robot(2) + nav.PeriodoDeSampleo * nav.Velocidad * sin(nav.robot(3));

                % Update trajectory vectors.
                nav.X(i) = nav.robot(1);
                nav.Y(i) = nav.robot(2);
                
                refreshdata(nav.p, 'caller');
                drawnow;
                
                % Update triangle1
                nav.triangle1_polyshape = translate(nav.triangle1_polyshape, [(nav.PeriodoDeSampleo*nav.Velocidad*cos(nav.robot(3))) (nav.PeriodoDeSampleo*nav.Velocidad*sin(nav.robot(3)))]);
                nav.triangle1_polyshape = rotate(nav.triangle1_polyshape, (nav.robot(3)*180/pi - nav.pra*180/pi), [nav.robot(1) nav.robot(2)] );
                nav.plot_triangle1.Shape = nav.triangle1_polyshape;
                
                % Update triangle2
                nav.triangle2_polyshape = translate(nav.triangle2_polyshape, [(nav.PeriodoDeSampleo*nav.Velocidad*cos(nav.robot(3))) (nav.PeriodoDeSampleo*nav.Velocidad*sin(nav.robot(3)))]);
                nav.triangle2_polyshape = rotate(nav.triangle2_polyshape, (nav.robot(3)*180/pi - nav.pra*180/pi), [nav.robot(1) nav.robot(2)] );
                nav.plot_triangle2.Shape = nav.triangle2_polyshape;
                
                % Update triangle3
                nav.triangle3_polyshape = translate(nav.triangle3_polyshape, [(nav.PeriodoDeSampleo*nav.Velocidad*cos(nav.robot(3))) (nav.PeriodoDeSampleo*nav.Velocidad*sin(nav.robot(3)))]);
                nav.triangle3_polyshape = rotate(nav.triangle3_polyshape, (nav.robot(3)*180/pi - nav.pra*180/pi), [nav.robot(1) nav.robot(2)] );
                nav.plot_triangle3.Shape = nav.triangle3_polyshape;
                
                % Chequeo si hubo solapamiento del cono con obstaculo (si hubo colorea el cono y retorna la distancia)
                [distR_O,distC_O,distL_O] = nav.checksolap(d);
                
                % Calculate travelled distance.
                nav.DistanciaViajada = nav.DistanciaViajada + sqrt((nav.robot(1)-nav.prx)^2+(nav.robot(2)-nav.pry)^2);

                % Actualizo distancia al target
                nav.dist_al_target = Robot.Sensores.gps(nav.target,nav.robot);
                
                % Actualizo distancia al obstaculo
                %[distL_O,distC_O,distR_O] = Robot.Sensores.SensoresDeDistancia(nav.o,nav.robot);
                
                % Si alcanzo el target termina la simulacion
                if (nav.dist_al_target <= 0.5)
                    nav.TargetAlcanzado = true;
                    break
                end

                % Si colisiono termina la simulacion
                if (distL_O <= 0.1 || distC_O <= 0.1 || distR_O <= 0.1)
                    nav.NOseguro = true;
                    break
                end

                % Si sale del area de simulacion, termino
                if (nav.robot(1)<0 || nav.robot(1)>25) || (nav.robot(2)<0 || nav.robot(2)>25)
                    nav.NOseguro = true;
                    break
                end
                
            end
            fclose(nav.fid); 
        end

        function [dist3,dist1,dist2] = checksolap(nav,d)
            solap1 = 0;
            solap2 = 0;
            solap3 = 0;
            array_dist1 = [];
            array_dist2 = [];
            array_dist3 = [];
            dist1 = 3;
            dist2 = 3;
            dist3 = 3;
            %display(length(nav.polyList))
            for i = 1:length(nav.polyList)
                poly1 = intersect(nav.triangle1_polyshape,nav.polyList{i});
                poly2 = intersect(nav.triangle2_polyshape,nav.polyList{i});
                poly3 = intersect(nav.triangle3_polyshape,nav.polyList{i});
                if poly1.NumRegions ~= 0
                    %display("Hubo colision1");
                    solap1 = 1;
                    dx = nav.obstacles(1,1) - nav.robot(1);
                    dy = nav.obstacles(1,2) - nav.robot(2);
                    array_dist1(i) = sqrt(dx^2+dy^2) - d.radius;
                    nav.plot_triangle1.FaceColor = 'red';
                else
                    array_dist1(i) = 3;
                end
                if poly2.NumRegions ~= 0
                    %display("Hubo colision2");
                    solap2 = 1;
                    dx = nav.obstacles(1,1) - nav.robot(1);
                    dy = nav.obstacles(1,2) - nav.robot(2);
                    array_dist2(i) = sqrt(dx^2+dy^2) - d.radius;
                    nav.plot_triangle2.FaceColor = 'red';
                else
                    array_dist2(i) = 3;
                end
                if poly3.NumRegions ~= 0
                    solap3 = 1;
                    dx = nav.obstacles(1,1) - nav.robot(1);
                    dy = nav.obstacles(1,2) - nav.robot(2);
                    array_dist3(i) = sqrt(dx^2+dy^2) - d.radius;
                    nav.plot_triangle3.FaceColor = 'red';
                else
                    array_dist3(i) = 3;
                end
            end
            if solap1 == 0
                nav.plot_triangle1.FaceColor = 'blue';
            end
            if solap2 == 0
                nav.plot_triangle2.FaceColor = 'blue';
            end
            if solap3 == 0
                nav.plot_triangle3.FaceColor = 'blue';
            end
            dist1 = min(array_dist1);
            dist2 = min(array_dist2);
            dist3 = min(array_dist3);
            
            display("centro")
            display(array_dist1);
            display(dist1);
            display("izquierda")
            display(array_dist2);
            display(dist2);
            display("derecha")
            display(array_dist3);
            display(dist3);
        end
        
        function Theta = correctTheta(nav, Theta)
            % Ensure THETA is in [-pi,pi].
            if Theta < 0.02 
                Theta = 0;
            end
            if Theta > -0.02 
                Theta = 0;
            end
        end
        
    end
end

