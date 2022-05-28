function dibujar_obstaculo(obstacle,radius,i)
    rectangle('Position',[obstacle{i}(1,1)-0.5*radius obstacle{i}(1,2)-0.5*radius radius radius], 'Curvature',[0 0],'FaceColor','c','EdgeColor','c')
end

