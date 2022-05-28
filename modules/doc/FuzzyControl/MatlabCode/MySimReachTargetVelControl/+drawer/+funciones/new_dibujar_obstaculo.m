function polyList = create_box_polyshape(ubicacion,ancho, largo, i, polyList)
    % Cuadrado
%     Xo = (ubicacion{i}(1,1)-ancho/2);
%     X1 = (ubicacion{i}(1,1)+ancho/2);
%     Yo = (ubicacion{i}(1,2)-largo/2);
%     Y1 = (ubicacion{i}(1,2)+largo/2);
%     cuadrado = polyshape( [Xo Xo X1 X1] , [ Yo Y1 Y1 Yo] );
    r = ancho/2;
    n = 100;
    theta = (0:n-1)*(2*pi/n);
    display(ubicacion);
    x = ubicacion(1,2*i-1) + r*cos(theta);
    y = ubicacion(1,2*i) + r*sin(theta);
    circulo = polyshape(x,y);
    polyList{i} = circulo;
    plot(circulo,'FaceColor','#77AC30');
    hold on;
end