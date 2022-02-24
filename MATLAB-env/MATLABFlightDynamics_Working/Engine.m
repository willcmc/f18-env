%==============%
% Engine model %
%==============%
function [Thrust] = Engine(Time, Ts, x, cntl, Mach, g)
persistent Eng_FBK
global     time_traj Altitude

% if(time_traj == 1)
%     x(12) = Altitude;
% end
ALT     = real(x(12));      % Altitude

Mach_breakpoints = [0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9];         % GE F404 Engine simple Real Time model max AB Static thrust breakpoints
Alt_breakpoints  = [0 10000 20000 30000 35000 40000 50000]*0.3048;

[X,Y] = meshgrid(Mach_breakpoints,(Alt_breakpoints));

THRUST = [16000 16000 16250 17180 18230 19230 20330 21940 23290 23810;      % GE F404 Engine simple Real Time model max AB Static thrust
          12160 12225 12560 13310 14140 15030 15760 17030 18370 19890;
           8580  8664  8775  9332  9873 10580 11420 12430 13510 14710;
           5410  5465  5614  6004  6461  7088  7740  8474  9288 10220;
           4105  4143  4278  4573  4927  5378  5890  6674  7512  8211;
           3158  3225  3263  3547  3811  4128  4546  5107  5715  6445;
           1837  1863  1907  2102  2338  2529  2744  3040  3395  3762]*g/2.2046;

Thrust = interp2(X,Y,THRUST,Mach,ALT,'linear');  % max AB Thrust at 100% Throttle for Flight Mach and Altitude

if(Ts <= 0.1)  % Engine dynamics involved for use in Simulation, Ts is time step ususlly <= 0.1 for simulation
    
    RE_Thrtl = (cntl(5) + 0.31)*100;          % Right Engine Throttle converted to PLA scale (31 - 131, >87 --> AB on)
    LE_Thrtl = (cntl(6) + 0.31)*100;          % Left  Engine Throttle converted to PLA scale
    
    RE_Thrtl_old = Eng_FBK(1);                % Retreiving Feedback signal
    LE_Thrtl_old = Eng_FBK(2);

    if(Time <= Ts)                            % Initialize Dynamic Throttle Variable and Difference in throttle Variable
        DRE_Thrtl    = 0;
        DLE_Thrtl    = 0;
        RE_Thrtl_DYN = RE_Thrtl;
        LE_Thrtl_DYN = LE_Thrtl;        
    else                                      % Compute the Difference in throttle from previous value
        DRE_Thrtl    = RE_Thrtl - RE_Thrtl_old;
        DLE_Thrtl    = LE_Thrtl - LE_Thrtl_old;   
        RE_Thrtl_DYN = RE_Thrtl_old;
        LE_Thrtl_DYN = LE_Thrtl_old; 
    end
    
    if(RE_Thrtl <= 87)    % Select Right Engine time constant and Rate limiter based on Throttle settings
        RE_Tou  = 0.625;
        RE_Rlim = 19.03;
    else
        RE_Tou  = 0.55;
        RE_Rlim = 26.81;  
    end 
    
    if(LE_Thrtl <= 87)    % Select Left Engine time constant and Rate limiter based on Throttle settings
        LE_Tou  = 0.625;
        LE_Rlim = 19.03;
    else
        LE_Tou  = 0.55;
        LE_Rlim = 26.81;  
    end     
    
    DRE_Thrtl_Tou = DRE_Thrtl/RE_Tou;  % Compute Rate of change of Throttle
    DLE_Thrtl_Tou = DLE_Thrtl/LE_Tou;
    
    if(DRE_Thrtl_Tou >= RE_Rlim)       % Limit the Rate of change of throttle in Right Engine 
        DRE_Thrtl_Tou = RE_Rlim;
    end
    
    if(DLE_Thrtl_Tou >= LE_Rlim)       % Limit the Rate of change of throttle in Left Engine 
        DLE_Thrtl_Tou = LE_Rlim;
    end
    
    RE_Thrtl_DYN = RE_Thrtl_DYN + DRE_Thrtl_Tou*Ts;     % compute the Dynamic Throttle from rate using Euker's Integration
    LE_Thrtl_DYN = LE_Thrtl_DYN + DLE_Thrtl_Tou*Ts;
    
    RE_Thrtl_old = RE_Thrtl_DYN;                        % Assign variables to be used as feedback to compute change in Throttle 
    LE_Thrtl_old = LE_Thrtl_DYN;
    
    Eng_FBK = [RE_Thrtl_old; LE_Thrtl_old];
    
    RE_Thrust = Thrust*(RE_Thrtl_DYN - 31)/100;          % Right Engine Thrust with Throttle converted back to % scale
    LE_Thrust = Thrust*(LE_Thrtl_DYN - 31)/100;          % Left  Engine Thrust with Throttle converted back to % scale
    
else  % No dynamics involved for use in trim
    
    RE_Thrtl = cntl(5);          % Right Engine Throttle
    LE_Thrtl = cntl(6);          % left Engine Throttle
    
    Eng_FBK = [0.0; 0.0];

    RE_Thrust = Thrust*RE_Thrtl;          % Right Engine Thrust in % scale
    LE_Thrust = Thrust*LE_Thrtl;          % Left Engine Thrust  in % scale
end

Thrust = [RE_Thrust; LE_Thrust];
%------------------------