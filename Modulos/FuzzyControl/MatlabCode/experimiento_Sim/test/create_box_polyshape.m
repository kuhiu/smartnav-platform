function cuadrado = create_box_polyshape(ubicacion,ancho, largo, i)
    Xo = (ubicacion{i}(1,1)-ancho/2);
    X1 = (ubicacion{i}(1,1)+ancho/2);
    Yo = (ubicacion{i}(1,2)-largo/2);
    Y1 = (ubicacion{i}(1,2)+largo/2);
    cuadrado = polyshape( [Xo Xo X1 X1] , [ Yo Y1 Y1 Yo] );
end

