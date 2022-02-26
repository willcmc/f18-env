%==================%
% Atmosphere model %
%==================%
function[T_atm, p_atm, rho, M, g] = Atmosphere(x)
   ALT = real(x(12));       % Altitude (0 to 16 Km)
   Vel = real(x(1));        % Velocity (0 to 250 m/s)
   RE  = 6378.135;          % Radius of Earth
	
   if (ALT <= 11000) 
      T_atm = 288.15 - 0.0065*ALT;                         % Temperature
      p_atm = 101325*(T_atm/288.15)^(9.81/(287*0.0065));   % Pressure
   else 
      T_atm = 216.65;                                       % Temperature
      p_atm = 22632*exp(-9.81*(ALT-11000)/(287*216.65));    % Pressure
   end    

   rho = p_atm/(287*T_atm);        % Density

   R    = 287.1;                                  % Gas constant
   Vson = sqrt(1.4*R*T_atm);                      % Speed of Sound
   M    = Vel/Vson;                               % Mach number
   g    = (9.80665 * (RE/( RE+(ALT/1000)))^2);    % Accleration due to gravity
