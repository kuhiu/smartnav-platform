clc;
close all;
clear all;


large = 4;      % Largo del cono
angle = 20/2;   % Apertura del cono
ubicacion = [2,6];   % Ubicacion del punto superior del triangulo
ang = 180;      % degrees

X = [ (ubicacion(1)-(large*tand(angle))) ubicacion(1) (ubicacion(1)+(large*tand(angle))) (ubicacion(1)-(large*tand(angle)))];
Y = [ubicacion(2)+large ubicacion(2) ubicacion(2)+large ubicacion(2)+large];
Xrot =  (X-ubicacion(1))*cosd(ang) + (Y-ubicacion(2))*sind(ang) + ubicacion(1);
Yrot = -(X-ubicacion(1))*sind(ang) + (Y-ubicacion(2))*cosd(ang) + ubicacion(2);
cono = polyshape(Xrot,Yrot);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ubicacion = [0 0];
ancho = 1;
largo = 1;
Xo = (ubicacion(1)-ancho/2);
X1 = (ubicacion(1)+ancho/2);
Yo = (ubicacion(2)-largo/2);
Y1 = (ubicacion(2)+largo/2);

cuadrado = polyshape( [Xo Xo X1 X1] , [ Yo Y1 Y1 Yo ]);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ubicacion = [1 1];
ancho = 1;
largo = 1;
Xo = (ubicacion(1)-ancho/2);
X1 = (ubicacion(1)+ancho/2);
Yo = (ubicacion(2)-largo/2);
Y1 = (ubicacion(2)+largo/2);

cuadrado1 = polyshape( [Xo Xo X1 X1] , [ Yo Y1 Y1 Yo ]);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ubicacion = [2 2];
ancho = 1;
largo = 1;
Xo = (ubicacion(1)-ancho/2);
X1 = (ubicacion(1)+ancho/2);
Yo = (ubicacion(2)-largo/2);
Y1 = (ubicacion(2)+largo/2);

cuadrado2 = polyshape( [Xo Xo X1 X1] , [ Yo Y1 Y1 Yo ]);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Plot
pcone = plot(cono);
hold on;
plot(cuadrado);
hold on;
plot(cuadrado1);
hold on;
plot(cuadrado2);
hold on;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Guardo obstaculos
polyList={cuadrado,cuadrado1,cuadrado2};

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
display(length(polyList));
for i = 1:length(polyList)
    poly = intersect(cono,polyList{i});
    if poly.NumRegions ~= 0
        display("Hubo colision en:");
        display(i);
        pcone.FaceColor = 'red';
    end
end

display(poly.
display(min(poly,[2,6]));


% poly2 = intersect(cuadrado,poly1);
% if poly2.NumRegions ~= 0
%     display("Hubo colision")
% end
% display(poly2);
% plot(poly2);
% hold on;




