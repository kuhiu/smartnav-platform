        function obj = ProximitySensor(parent, type, r_pose, pose, r_min, r_max, phi, varargin)
            obj = obj@simiam.ui.Drawable(parent, r_pose);
            
            obj.type = type;
            obj.location = pose;
            
            T = obj.location.get_transformation_matrix();
            r = r_max;
            r1 = r*tan(phi/4);
            r2 = r*tan(phi/2);
            sensor_cone =  [              0     0   1;
                             sqrt(r^2-r2^2)    r2   1;
                             sqrt(r^2-r1^2)    r1   1;
                                          r     0   1;
                             sqrt(r^2-r1^2)   -r1   1;
                             sqrt(r^2-r2^2)   -r2   1];
            obj.add_surface(sensor_cone*T', [ 0.8 0.8 1 ]);
            set(obj.surfaces.head_.key_.handle_, 'EdgeColor', 'b');
            
            obj.range = r;
            obj.spread = phi;
            
            obj.max_range = r_max;
            obj.min_range = r_min;
            
            switch(length(varargin))
                case 0 
                    obj.map = str2func('simiam.robot.sensor.ProximitySensor.identity_map');
                case 1 
                    if (isa(varargin{1}, 'simiam.robot.sensor.noise.NoiseModel'))
                        obj.map = str2func('simiam.robot.sensor.ProximitySensor.identity_map');
                        obj.noise_model = varargin{1};
                    else
                        obj.map = str2func(varargin{1});
                        obj.noise_model = simiam.robot.sensor.noise.GaussianNoise(0,0);
                    end
                case 2
                    if (isa(varargin{1}, 'simiam.robot.sensor.noise.NoiseModel'))
                        obj.map = str2func(varargin{2});
                        obj.noise_model = varargin{1};
                    else
                        obj.map = str2func(varargin{1});
                        obj.noise_model = varargin{2};
                    end
            end
        end