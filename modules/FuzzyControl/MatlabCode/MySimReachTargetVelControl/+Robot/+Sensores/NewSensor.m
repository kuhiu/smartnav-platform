classdef NewSensor
    %UNTITLED Summary of this class goes here
    %   Crea un cono y tiene un metodo para poder girarlo.
    
    properties
        X
        Y
        ubicacion
        apertura
        largo
        rotacion
    end
    
    methods
        function obj = NewSensor()     % Crea el objeto 
            obj.X = 0;
            obj.Y = 0;
        end
        
        function obj = TrasladarYRotar(obj)     % Rota y traslada el cono 
            obj.X = [ (obj.ubicacion(1)-(obj.largo*tand(obj.apertura))) obj.ubicacion(1) (obj.ubicacion(1)+(obj.largo*tand(obj.apertura))) (obj.ubicacion(1)-(obj.largo*tand(obj.apertura)))];
            obj.Y = [obj.ubicacion(2)+obj.largo obj.ubicacion(2) obj.ubicacion(2)+obj.largo obj.ubicacion(2)+obj.largo];
        end
    end
end

