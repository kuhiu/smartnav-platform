classdef Posicion2d
    
    properties
        x
        y
        theta
    end
    
    methods
        function obj = Pose2D(x, y, theta)
           obj.x = x;
           obj.y = y;
           obj.theta = theta;
        end
        
        function obj = set_pose(obj, pose)
            obj.x = pose(1);
            obj.y = pose(2);
            obj.theta = pose(3);
        end
        
        function T = get_transformation_matrix(obj)
            T = [ cos(obj.theta) -sin(obj.theta) obj.x;
                  sin(obj.theta)  cos(obj.theta) obj.y;
                               0               0     1];
        end
        
    end
end

