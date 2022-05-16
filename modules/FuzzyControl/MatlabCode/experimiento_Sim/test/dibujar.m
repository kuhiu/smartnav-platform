classdef dibujar
    %DIBUJAR Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        surfaces
        parent
        pose
    end
    
    methods
        function obj = Drawable(parent, pose)
           obj.pose = pose;
           obj.parent = parent;
           obj.surfaces = mcodekit.list.dl_list();
        end
        
        function surface = add_surface(obj, geometry, color)
            surface = obj.add_surface_with_depth(geometry, color, 1);
        end
        
        function surface = add_surface_with_depth(obj, geometry, color, depth)
            surface_g = geometry;
            T = obj.pose.get_transformation_matrix();
            geometry_t = geometry*T';
            geometry_t(:,3) = depth;
            surface_h = patch('Parent', obj.parent, ...
                              'Vertices', geometry_t, ...
                              'Faces', 1:size(geometry,1), ...
                              'FaceColor', 'flat', ...
                              'FaceVertexCData', color);
            surface = simiam.ui.Surface2D(surface_h, surface_g);
            surface.set_surface_depth(depth);
            surface.transform_surface(T);
            obj.surfaces.append_key(surface);
       end
        
       function update_pose(obj, pose)
            [x, y, theta] = pose.unpack();
            obj.pose.set_pose([x, y, theta]);
            obj.draw_surfaces();
       end
        
    end
end

