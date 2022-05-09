function showSimulationEnvironment(obstacle,target,robot,navigationResults)

% Show the robot trajectory in the simulation environment.

% Radius of the robot, target, and obstacle.
radius = 1; % 1m
largo_obstaculo = 1;
ancho_obstaculo = 1;

% Use 25mx25m simulation environment.
axis([0 25 0 25]);

% Set equal aspect ratio.
pbaspect([1 1 1])

% Temporary plots to enable legends.
hold on
plot(robot(1),robot(2)+radius,'ob','LineWidth',radius*1,'MarkerFaceColor','b')
plot(robot(1),robot(2)+radius,'or','LineWidth',radius*1,'MarkerFaceColor','r')
plot(robot(1),robot(2)+radius,'og','LineWidth',radius*1,'MarkerFaceColor','g')
hold off

% Draw obstacle.
%rectangle('Position',[obstacle(1)-0.5*radius obstacle(2)+0.5*radius radius radius], ...
    %'Curvature',[1 1],'FaceColor','b','EdgeColor','b')

rectangle('Position',[obstacle(1)-0.5*radius obstacle(2)+0.5*radius ancho_obstaculo largo_obstaculo], ...
    'Curvature',[0 0],'FaceColor','b','EdgeColor','b')

% Draw target.
rectangle('Position',[target(1)-0.5*radius target(2)+0.5*radius radius radius], ...
    'Curvature',[1 1],'FaceColor','r','EdgeColor','r')

% Draw robot.
rectangle('Position',[robot(1)-0.5*radius robot(2)+0.5*radius radius radius], ...
    'Curvature',[1 1],'FaceColor','g','EdgeColor','g')

% Add labels, title, and legends.
xlabel('x (m)'),ylabel('y (m)')
title('Simulation Environment for Robot Navigation')
legend(["Obstacle" "Target" "Robot"])

% Plot the robot trajectory if specified.
if nargin == 4
    x = navigationResults.x;
    y = navigationResults.y;
    for i = 1:numel(x)
        rectangle('Position',[x(i)-0.5*radius y(i)+0.5*radius radius radius], ...
            'Curvature',[1 1],'FaceColor','g','EdgeColor','g')
    end
end

end

