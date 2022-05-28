function dist_al_target = gps(loc,robot)    
    dx = loc(1,1) - robot(1);
    dy = loc(1,2) - robot(2);
    dist_al_target = sqrt(dx^2+dy^2);
end