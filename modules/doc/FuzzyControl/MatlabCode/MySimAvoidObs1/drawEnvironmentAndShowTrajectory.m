
function drawEnvironmentAndShowTrajectory(obstacle,target,robot,plotTitle,varargin)

% Expand figure horizontally to tile the simulation environments.
h = figure;
h.Position = [h.Position(1:2) 3*h.Position(3) h.Position(4)];
numTasks = size(target,1);

% Draw each simulation environment.
for i = 1:numTasks
    o = obstacle(i,:);
    t = target(i,:);
    r = robot(i,:);
    subplot(1,numTasks,i)
    if ~isempty(varargin)
        results = getNavigationResults(varargin{1},o,t,r);
        showSimulationEnvironment(o,t,r,results)
    else
        showSimulationEnvironment(o,t,r)
    end
    title([plotTitle ': ' num2str(i)])
end

end
