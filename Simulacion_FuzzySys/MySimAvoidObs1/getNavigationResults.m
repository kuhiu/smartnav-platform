function results = getNavigationResults(fis,obstacle,target,robot)
% GETNAVIGATIONRESULTS - Returns navigation results for the specified
% positions of the OBSTACLE, TARGET, and ROBOT. The specified fuzzy
% system, FIS is used to generate weight for the obstacle avoidance
% subtask.
% The navigation results include the robot's (x,y) trajectory, the total
% travelled distance, and a flag that shows if the navigation was safe,
% i.e. if there was a collision with the obstacle during the navigation.

%  Copyright 2018 The MathWorks, Inc.

% Initialize variables.
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
samplePeriod = 0.1;
speed = 0.5;

% Determine initial distances and angles of the target and obstacle.
[disT,delAngT] = getDistanceAndAngle(target,robot);
[disO,delAngO] = getDistanceAndAngle(obstacle,robot);

% Run simulation
for i = 1:100/samplePeriod
    
    % Calculate ratio of the obstacle and target distances.
    alpha = disO/disT;
    
    % Calculate difference between the target and obstacle orientations.
    theta_t_o = abs(correctTheta(delAngT-delAngO));
    
    % Evaluate the fuzzy inference system to generate the weight.
    w = evalfis(fis,[alpha theta_t_o],options);
    
    % Get the resultant force vector.
    x = -w*(obstacle(1)-robot(1)) + (1-w)*(target(1)-robot(1));
    y = -w*(obstacle(2)-robot(2)) + (1-w)*(target(2)-robot(2));
    
    % Get direction of the resultant force vector.
    theta = atan2(y,x);
    
    % Limit the change in robot's direction in [-pi/4,pi/4].
    delTheta = correctTheta(theta-robot(3));
    thetaThreshold = pi/4;
    if delTheta > thetaThreshold
        delTheta = thetaThreshold;
    elseif delTheta < -thetaThreshold
        delTheta = -thetaThreshold;
    end
    robot(3) = correctTheta(robot(3)+delTheta);

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
    travelledDistance = travelledDistance + ...
        sqrt((robot(1)-prx)^2+(robot(2)-pry)^2);
    
    % Update distance and angle to the target.
    [disT,delAngT] = getDistanceAndAngle(target,robot);
    
    % End simulation if target is reached.
    if disT<=0.75
        reachedTarget = true;
        break
    end
    
    % Update distance and angle to the obstacle.
    [disO,delAngO] = getDistanceAndAngle(obstacle,robot);
    
    % End simulation if the robto collides with the obstacle.
    if disO <= 1
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

end

function [dist,ang] = getDistanceAndAngle(loc,robot)

% Calculate distance of LOC from ROBOT and determine orientation of LOC
% with respect to ROBOT's heading direction.
dx = loc(1)-robot(1);
dy = loc(2)-robot(2);
dist = sqrt(dx^2+dy^2);
ang = correctTheta(atan2(dy,dx)-robot(3));
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