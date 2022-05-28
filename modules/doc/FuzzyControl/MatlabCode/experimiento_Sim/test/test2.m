clc;
close all;
clear all;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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

point = polyshape([1 1],[1 2]);
plot(point);

%min_dist_between_two_polygons(struct(cono), struct(cono) );


