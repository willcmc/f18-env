% code to run the F-18 Model

%%%%%%%%%%%%%%%%
% Descriptions %
%%%%%%%%%%%%%%%%

% x %

%1 Velocity (m/s)
%2 Angle of Attack (rad)
%3 Angle of Side Slip (rad)
%4 Roll rate 
%5 Pitch rate
%6 Yaw rate
%7 Roll angle
%8 Pitch angle
%9 Yaw angle
%10 X location from starting point
%11 Y location from starting point
%12 Altitude

% Cntl %

%1 Stabilator deflection Right
%2 Stabilator deflection Left
%3 Aileron deflection
%4 Rudder deflection
%5 Throttle Setting as % of Right Engine
%6 Throttle Setting as % of Left Engine
%7 Pitch Thrust Vectoring Nozzle deflection Right Engines 
%8 Pitch Thrust Vectoring Nozzle deflection Left Engines
%9 Yaw Thrust Vectoring Nozzle deflection Right Engines
%10 Yaw Thrust Vectoring Nozzle deflection Left Engines


[Geom, ALPHA_BREAK, F18_Aerodata] = Aerodata;
F18_Geom_damaged = Geom;
F18_Aerodata_damaged = F18_Aerodata;

Ts = 0.5;
global damage;
damage = 0;
x = [200 2*pi/180 0 0 0 0 0 1.2*pi/180 0 0.1 0.1 1000]';

for Time = 1:3
    display("T = " + num2str(Time));
    [T_atm, p_atm, rho, Mach, g] = Atmosphere(x);
    delta_e = 1*pi/180;
    Cntl = [delta_e delta_e 0 0 1 1 0 0 0 0];
    Thrust = Engine(Time, Ts, x, Cntl, Mach, g);
    delta_x = Equations_of_Motion(x,g,ALPHA_BREAK,F18_Aerodata,Thrust,Geom,F18_Geom_damaged,F18_Aerodata_damaged,rho,Cntl);
    x = x + Ts*delta_x;
end