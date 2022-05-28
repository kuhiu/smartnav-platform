function cost = navigationCostFcn(fis,obstacle,target,robot)
% NAVIGATIONCOSTFCN - Returns total cost of the simulated robot navigation
% in the training environments.

%  Copyright 2018 The MathWorks, Inc.
cost = 0;
for i = 1:size(obstacle,1)
    results = getNavigationResults(fis,obstacle(i,:),target(i,:),robot(i,:));
    cost = cost + getNavigationCost(results);
end

end