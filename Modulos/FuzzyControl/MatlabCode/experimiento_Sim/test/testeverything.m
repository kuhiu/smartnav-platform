clc;
close all;
clear all;

large = 4;      % Largo del cono
angle = 20/2;   % Apertura del cono
ubicacion = [1,1];   % Ubicacion del punto superior del triangulo
ang = 0;      % degrees

X = [ (ubicacion(1)-(large*tand(angle))) ubicacion(1) (ubicacion(1)+(large*tand(angle))) (ubicacion(1)-(large*tand(angle)))];
Y = [ubicacion(2)+large ubicacion(2) ubicacion(2)+large ubicacion(2)+large];
Xrot =  (X-ubicacion(1))*cosd(ang) + (Y-ubicacion(2))*sind(ang) + ubicacion(1);
Yrot = -(X-ubicacion(1))*sind(ang) + (Y-ubicacion(2))*cosd(ang) + ubicacion(2);

b = polyshape(Xrot,Yrot);
p = plot(b);
hold on;


large = 4;      % Largo del cono
angle = 20/2;   % Apertura del cono
ubicacion = [2,2];   % Ubicacion del punto superior del triangulo
ang = 0;        % degrees

X2 = [ (ubicacion(1)-(large*tand(angle))) ubicacion(1) (ubicacion(1)+(large*tand(angle))) (ubicacion(1)-(large*tand(angle)))];
Y2 = [ubicacion(2)+large ubicacion(2) ubicacion(2)+large ubicacion(2)+large];
Xrot2 =  (X2-ubicacion(1))*cosd(ang) + (Y2-ubicacion(2))*sind(ang) + ubicacion(1);
Yrot2 = -(X2-ubicacion(1))*sind(ang) + (Y2-ubicacion(2))*cosd(ang) + ubicacion(2);

a = polyshape(Xrot2,Yrot2);
plot(a)

c = intersect(a,b);
plot(c);



% set(p, 'XDataSource', 'Xrot', 'YDataSource', 'Yrot')
% linkdata on;
% refreshdata;
% drawnow;




% large = 4;
% angle = 20/2;
% ubicacion = [10,1];
% 
% display(large*tand(angle));
% x = [ (ubicacion(1)-(large*tand(angle))) ubicacion(1) (ubicacion(1)+(large*tand(angle))) (ubicacion(1)-(large*tand(angle)))];
% y = [ubicacion(2) large ubicacion(2) ubicacion(2)];
% 
% plot(x,y);
% area(x,y);
% xlim([0 25])
% ylim([-2 25])


% x2 = [1 2];
% y2 = [4 4];
% p = plot(x2,y2);
% xlim([0 100])
% ylim([2.5 4])
% xlabel('Iteration')
% ylabel('Approximation for \pi')
% 
% p.XDataSource = 'x2';
% p.YDataSource = 'y2';
% 
% denom = 1;
% k = -1;
% for t = 3:100
%     denom = denom + 2;
%     x2(t) = t;
%     y2(t) = 3;
%     refreshdata
%     drawnow
%     pause(1)
%     k = -k;
% end
%     r = [1 10];
%     p = plot(r(1),r(2),'o');
%     xlim([0 25])
%     ylim([0 25])
%     p.XDataSource = 'r(1)';
%     p.YDataSource = 'r(2)';
%     linkdata on;
%     
% for t = 1:10
%     r(1) = r(1) + 1;
%     display(r(1))
%     refreshdata
%     pause(0.2)
% end