function cost = getNavigationCost(results)
% GETNAVIGATIONCOST - Returns cost of a navigation trajectory, which is the
% travelled distance of a collision-free navigation. The cost is set to
% 200, if the navigation is not safe.

%  Copyright 2018 The MathWorks, Inc.

if results.notSafe || ~results.reachedTarget
    cost = 200;
else
    cost = results.travelledDistance;
end

end