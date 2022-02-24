%=====================%
% Equations of Motion %
%=====================%
function [F,FORCES,MOMENTS,DCG] =  Equations_of_Motion(x,g,ALPHA_BREAK,F18_Aerodata,Thrust,Geom,F18_Geom_damaged,F18_Aerodata_damaged,rho,Cntl)
global damage 

d2r   = pi/180; %deg to rad conversion
r2d   = 180/pi; %rad to deg conversion

%=========================================================================%
%         Aerodynamic Coeffecient Assignment to local variables           %
%=========================================================================%

clift       =  F18_Aerodata(:,1);    % Coefficient of Lift due to Angle of Attack
clift_q     =  F18_Aerodata(:,2);    % Coefficient of Lift due to Pitch rate
clift_de    =  F18_Aerodata(:,3);    % Coefficient of Lift due to Both Stabilator deflection
clift_del   =  F18_Aerodata(:,4);    % Coefficient of Lift due to Left Stabilator deflection
clift_der   =  F18_Aerodata(:,5);    % Coefficient of Lift due to Right Stabilator deflection
cd0         =  F18_Aerodata(:,6);    % Coefficient of Drag at Zero Lift
cd_q        =  F18_Aerodata(:,7);    % Coefficient of Drag due to Pitch rate
cd_de       =  F18_Aerodata(:,8);    % Coefficient of Drag due to Both Stabilator deflection
cd_del      =  F18_Aerodata(:,9);    % Coefficient of Drag due to Left Stabilator deflection
cd_der      =  F18_Aerodata(:,10);   % Coefficient of Drag due to Right Stabilator deflection
cm          =  F18_Aerodata(:,11);   % Coefficient of Pitching Moment due to Angle of Attack
cm_de       =  F18_Aerodata(:,12);   % Coefficient of Pitching Moment due to Both Stabilator deflection
cm_del      =  F18_Aerodata(:,13);   % Coefficient of Pitching Moment due to Left Stabilator deflection
cm_der      =  F18_Aerodata(:,14);   % Coefficient of Pitching Moment due to Right Stabilator deflection
cm_q        =  F18_Aerodata(:,15);   % Coefficient of Pitching Moment due to Pitch rate
cy_b        =  F18_Aerodata(:,16);   % Coefficient of Side Force due to Angle of Side Slip   
cy_p        =  F18_Aerodata(:,17);   % Coefficient of Side Force due to Roll rate
cy_r        =  F18_Aerodata(:,18);   % Coefficient of Side Force due to Yaw rate
cy_de       =  F18_Aerodata(:,19);   % Coefficient of Side Force due to Both Stabilator deflection
cy_del      =  F18_Aerodata(:,20);   % Coefficient of Side Force due to Left Stabilator deflection
cy_der      =  F18_Aerodata(:,21);   % Coefficient of Side Force due to Right Stabilator deflection
cy_da       =  F18_Aerodata(:,22);   % Coefficient of Side Force due to Aileron deflection
cy_dr       =  F18_Aerodata(:,23);   % Coefficient of Side Force due to Rudder deflection
croll_b     =  F18_Aerodata(:,24);   % Coefficient of Rolling Moment due to Angle of Side Slip 
croll_p     =  F18_Aerodata(:,25);   % Coefficient of Rolling Moment due to Roll rate
croll_r     =  F18_Aerodata(:,26);   % Coefficient of Rolling Moment due to Yaw rate
croll_de    =  F18_Aerodata(:,27);   % Coefficient of Rolling Moment due to Both Stabilator deflection
croll_del   =  F18_Aerodata(:,28);   % Coefficient of Rolling Moment due to Left Stabilator deflection
croll_der   =  F18_Aerodata(:,29);   % Coefficient of Rolling Moment due to Right Stabilator deflection
croll_da    =  F18_Aerodata(:,30);   % Coefficient of Rolling Moment due to Aileron deflection
croll_dr    =  F18_Aerodata(:,31);   % Coefficient of Rolling Moment due to Rudder deflection
cn_b        =  F18_Aerodata(:,32);   % Coefficient of Yawing  Moment due to Angle of Side Slip 
cn_p        =  F18_Aerodata(:,33);   % Coefficient of Yawing  Moment due to Roll rate
cn_r        =  F18_Aerodata(:,34);   % Coefficient of Yawing  Moment due to Yaw rate
cn_de       =  F18_Aerodata(:,35);   % Coefficient of Yawing  Moment due to Both Stabilator deflection
cn_del      =  F18_Aerodata(:,36);   % Coefficient of Yawing  Moment due to Left Stabilator deflection
cn_der      =  F18_Aerodata(:,37);   % Coefficient of Yawing  Moment due to Right Stabilator deflection
cn_da       =  F18_Aerodata(:,38);   % Coefficient of Yawing  Moment due to Aileron deflection
cn_dr       =  F18_Aerodata(:,39);   % Coefficient of Yawing  Moment due to Rudder deflection
CLAD        =  F18_Aerodata(:,40);   % Coefficient of Lift due to Rate of change of Angle of Attack (Not from same database)
CMAD        =  F18_Aerodata(:,41);   % Coefficient of Pitching Moment due to Rate of change of Angle of Attack (Not from same database)

m    = Geom(1);    % Mass of Aircraft 
S    = Geom(2);    % Wing Reference area
b    = Geom(3);    % Wing Span
cbar = Geom(4);    % Mean Aerodynamic Chord
Ixx  = Geom(5);    % Mass Moment of Inertia about X axis
Iyy  = Geom(6);    % Mass Moment of Inertia about Y axis
Izz  = Geom(7);    % Mass Moment of Inertia about Z axis
Ixz  = Geom(8);    % Product Mass Moment of Inertia about XZ axis
Ixy  = Geom(9);    % Product Mass Moment of Inertia about XY axis
Iyz  = Geom(10);   % Product Mass Moment of Inertia about YZ axis
xcg  = Geom(11);   % CG location referenced from the leading edge of Mean Aerodynamic Chord as % MAC
xref = Geom(12);   % CG to the Reference point(Aerodynamic database) distance along X axis 
yref = Geom(13);   % CG to the Reference point(Aerodynamic database) distance along Y axis 
zref = Geom(14);   % CG to the Reference point(Aerodynamic database) distance along Z axis 
Xeng = Geom(15);   % CG to the Engine distance along X axis 
Yeng = Geom(16);   % CG to the Engine distance along Z axis
Zeng = Geom(17);   % CG to the Engine distance along Z axis


%=========================================================================%
%    Damaged Aerodynamic Coeffecient Assignment to local variables        %
%=========================================================================%

d_CLv    =  F18_Aerodata_damaged(:,1);   
d_CDv    =  F18_Aerodata_damaged(:,2);
d_Cmv    =  F18_Aerodata_damaged(:,3);
d_CYv    =  F18_Aerodata_damaged(:,4);
d_Clv    =  F18_Aerodata_damaged(:,5);
d_Cnv    =  F18_Aerodata_damaged(:,6);
d_Cl_dav =  F18_Aerodata_damaged(:,7);
d_Cn_dav =  F18_Aerodata_damaged(:,8);
d_CL_dav =  F18_Aerodata_damaged(:,9);
d_CD_dav =  F18_Aerodata_damaged(:,10);
d_Cm_dav =  F18_Aerodata_damaged(:,11);
d_Cl_qv  =  F18_Aerodata_damaged(:,12);
d_Cm_qv  =  F18_Aerodata_damaged(:,13);
d_CL_qv  =  F18_Aerodata_damaged(:,14);
d_CL_pv  =  F18_Aerodata_damaged(:,15);
d_CD_pv  =  F18_Aerodata_damaged(:,16);
d_Cm_pv  =  F18_Aerodata_damaged(:,17);
d_Cl_pv  =  F18_Aerodata_damaged(:,18);
d_Cl_rv  =  F18_Aerodata_damaged(:,19);

dm    = F18_Geom_damaged(1); 
dxcg  = F18_Geom_damaged(2); 
dycg  = F18_Geom_damaged(3); 
dzcg  = F18_Geom_damaged(4); 
dIxx  = F18_Geom_damaged(5);
dIyy  = F18_Geom_damaged(6);
dIzz  = F18_Geom_damaged(7);
dIxz  = F18_Geom_damaged(8);
dIxy  = F18_Geom_damaged(9);
dIyz  = F18_Geom_damaged(10);

%=========================================================================%
%         State and Control Vectors Assignment to local variables         %
%=========================================================================%

Del_er  = Cntl(1);    % Stabilator deflection Right
Del_el  = Cntl(2);    % Stabilator deflection Left
Del_a   = Cntl(3);    % Aileron deflection
Del_r   = Cntl(4);    % Rudder deflection
Thrtl_r = Cntl(5);    % Throttle Setting as % of Right Engine
Thrtl_l = Cntl(6);    % Throttle Setting as % of Left Engine
P_tvcr  = Cntl(7);    % Pitch Thrust Vectoring Nozzle deflection Right Engines 
P_tvcl  = Cntl(8);    % Pitch Thrust Vectoring Nozzle deflection Left Engines
Y_tvcr  = Cntl(9);    % Yaw Thrust Vectoring Nozzle deflection Right Engines
Y_tvcl  = Cntl(10);   % Yaw Thrust Vectoring Nozzle deflection Left Engines

Vel   = real(x(1));       % Velocity
Alpha = real(x(2));       % Angle of Attack
Beta  = real(x(3));       % Angle of Side Slip
p     = real(x(4));       % Roll rate
q     = real(x(5));       % Pitch rate
r     = real(x(6));       % Yaw rate
Phi   = real(x(7));       % Roll angle
Theta = real(x(8));       % Pitch angle
Psi   = real(x(9));       % Yaw angle
Xe    = real(x(10));      % X location from starting point
Ye    = real(x(11));      % Y location from starting point
Alt   = real(x(12));      % Altitude

RE_Thrust = Thrust(1);  % Right Engine Thrust
LE_Thrust = Thrust(2);  % Left Engine Thrust

qbar  = 0.5*rho*Vel^2;  % Dynamic pressure

%=========================================================================%
%               Aerodynamic Coeffecient Interpolation                     %
%=========================================================================%
Alfad = real(Alpha)*r2d;  % The Aerodata is in Degrees 

CD0    = Interp1_akim(ALPHA_BREAK,cd0,Alfad,1,27);
CD_q   = Interp1_akim(ALPHA_BREAK,cd_q,Alfad,1,27)*r2d;
CD_de  = Interp1_akim(ALPHA_BREAK,cd_de,Alfad,1,27)*r2d;
CD_der = Interp1_akim(ALPHA_BREAK,cd_der,Alfad,1,27)*r2d;
CD_del = Interp1_akim(ALPHA_BREAK,cd_del,Alfad,1,27)*r2d;

CL0    = Interp1_akim(ALPHA_BREAK,clift,Alfad,1,27);
CL_q   = Interp1_akim(ALPHA_BREAK,clift_q,Alfad,1,27)*r2d;
CL_de  = Interp1_akim(ALPHA_BREAK,clift_de,Alfad,1,27)*r2d;
CL_der = Interp1_akim(ALPHA_BREAK,clift_der,Alfad,1,27)*r2d;
CL_del = Interp1_akim(ALPHA_BREAK,clift_del,Alfad,1,27)*r2d;

CY_b   = Interp1_akim(ALPHA_BREAK,cy_b,Alfad,1,27)*r2d; 
CY_p   = Interp1_akim(ALPHA_BREAK,cy_p,Alfad,1,27)*r2d; 
CY_r   = Interp1_akim(ALPHA_BREAK,cy_r,Alfad,1,27)*r2d; 
CY_de  = Interp1_akim(ALPHA_BREAK,cy_de,Alfad,1,27)*r2d; 
CY_der = Interp1_akim(ALPHA_BREAK,cy_der,Alfad,1,27)*r2d;
CY_del = Interp1_akim(ALPHA_BREAK,cy_del,Alfad,1,27)*r2d;
CY_da  = Interp1_akim(ALPHA_BREAK,cy_da,Alfad,1,27)*r2d; 
CY_dr  = Interp1_akim(ALPHA_BREAK,cy_dr,Alfad,1,27)*r2d;

Cl_b   = Interp1_akim(ALPHA_BREAK,croll_b,Alfad,1,27)*r2d; 
Cl_p   = Interp1_akim(ALPHA_BREAK,croll_p,Alfad,1,27)*r2d; 
Cl_r   = Interp1_akim(ALPHA_BREAK,croll_r,Alfad,1,27)*r2d; 
Cl_de  = Interp1_akim(ALPHA_BREAK,croll_de,Alfad,1,27)*r2d; 
Cl_der = Interp1_akim(ALPHA_BREAK,croll_der,Alfad,1,27)*r2d; 
Cl_del = Interp1_akim(ALPHA_BREAK,croll_del,Alfad,1,27)*r2d; 
Cl_da  = Interp1_akim(ALPHA_BREAK,croll_da,Alfad,1,27)*r2d; 
Cl_dr  = Interp1_akim(ALPHA_BREAK,croll_dr,Alfad,1,27)*r2d;

Cn_b   = Interp1_akim(ALPHA_BREAK,cn_b,Alfad,1,27)*r2d;
Cn_p   = Interp1_akim(ALPHA_BREAK,cn_p,Alfad,1,27)*r2d;
Cn_r   = Interp1_akim(ALPHA_BREAK,cn_r,Alfad,1,27)*r2d;
Cn_de  = Interp1_akim(ALPHA_BREAK,cn_de,Alfad,1,27)*r2d;
Cn_der = Interp1_akim(ALPHA_BREAK,cn_der,Alfad,1,27)*r2d;
Cn_del = Interp1_akim(ALPHA_BREAK,cn_del,Alfad,1,27)*r2d;
Cn_da  = Interp1_akim(ALPHA_BREAK,cn_da,Alfad,1,27)*r2d;
Cn_dr  = Interp1_akim(ALPHA_BREAK,cn_dr,Alfad,1,27)*r2d;

Cm0    = Interp1_akim(ALPHA_BREAK,cm,Alfad,1,27);
Cm_q   = Interp1_akim(ALPHA_BREAK,cm_q,Alfad,1,27)*r2d;
Cm_de  = Interp1_akim(ALPHA_BREAK,cm_de,Alfad,1,27)*r2d;
Cm_der = Interp1_akim(ALPHA_BREAK,cm_der,Alfad,1,27)*r2d;
Cm_del = Interp1_akim(ALPHA_BREAK,cm_del,Alfad,1,27)*r2d;

CL_Ad = Interp1_akim(ALPHA_BREAK,CLAD,Alfad,1,27)*r2d;
Cm_Ad = Interp1_akim(ALPHA_BREAK,CMAD,Alfad,1,27)*r2d;


d_CL    =  Interp1_akim(ALPHA_BREAK,d_CLv,Alfad,1,27);
d_CD    =  Interp1_akim(ALPHA_BREAK,d_CDv,Alfad,1,27);
d_Cm    =  Interp1_akim(ALPHA_BREAK,d_Cmv,Alfad,1,27);
d_CY    = -Interp1_akim(ALPHA_BREAK,d_CYv,Alfad,1,27);
d_Cl    = -Interp1_akim(ALPHA_BREAK,d_Clv,Alfad,1,27);
d_Cn    =  Interp1_akim(ALPHA_BREAK,d_Cnv,Alfad,1,27);
d_Cl_da = -Interp1_akim(ALPHA_BREAK,d_Cl_dav,Alfad,1,27)*r2d;
d_Cn_da = -Interp1_akim(ALPHA_BREAK,d_Cn_dav,Alfad,1,27)*r2d;
d_CL_da = -Interp1_akim(ALPHA_BREAK,d_CL_dav,Alfad,1,27)*r2d;
d_CD_da = -Interp1_akim(ALPHA_BREAK,d_CD_dav,Alfad,1,27)*r2d;
d_Cm_da = -Interp1_akim(ALPHA_BREAK,d_Cm_dav,Alfad,1,27)*r2d;
d_Cl_q  = -Interp1_akim(ALPHA_BREAK,d_Cl_qv,Alfad,1,27)*r2d;
d_Cm_q  =  Interp1_akim(ALPHA_BREAK,d_Cm_qv,Alfad,1,27)*r2d;
d_CL_q  =  Interp1_akim(ALPHA_BREAK,d_CL_qv,Alfad,1,27)*r2d;
d_CL_p  =  Interp1_akim(ALPHA_BREAK,d_CL_pv,Alfad,1,27)*r2d;
d_CD_p  =  Interp1_akim(ALPHA_BREAK,d_CD_pv,Alfad,1,27)*r2d;
d_Cm_p  =  Interp1_akim(ALPHA_BREAK,d_Cm_pv,Alfad,1,27)*r2d;
d_Cl_p  =  Interp1_akim(ALPHA_BREAK,d_Cl_pv,Alfad,1,27)*r2d;
d_Cl_r  =  Interp1_akim(ALPHA_BREAK,d_Cl_rv,Alfad,1,27)*r2d;

% CD0    = interp1(ALPHA_BREAK,cd0,Alfad,'makima');
% CD_q   = interp1(ALPHA_BREAK,cd_q,Alfad,'makima')*r2d;
% CD_de  = interp1(ALPHA_BREAK,cd_de,Alfad,'makima')*r2d;
% CD_der = interp1(ALPHA_BREAK,cd_der,Alfad,'makima')*r2d;
% CD_del = interp1(ALPHA_BREAK,cd_del,Alfad,'makima')*r2d;
% 
% CL0    = interp1(ALPHA_BREAK,clift,Alfad,'makima');
% CL_q   = interp1(ALPHA_BREAK,clift_q,Alfad,'makima')*r2d;
% CL_de  = interp1(ALPHA_BREAK,clift_de,Alfad,'makima')*r2d;
% CL_der = interp1(ALPHA_BREAK,clift_der,Alfad,'makima')*r2d;
% CL_del = interp1(ALPHA_BREAK,clift_del,Alfad,'makima')*r2d;
% 
% CY_b   = interp1(ALPHA_BREAK,cy_b,Alfad,'makima')*r2d; 
% CY_p   = interp1(ALPHA_BREAK,cy_p,Alfad,'makima')*r2d; 
% CY_r   = interp1(ALPHA_BREAK,cy_r,Alfad,'makima')*r2d; 
% CY_de  = interp1(ALPHA_BREAK,cy_de,Alfad,'makima')*r2d; 
% CY_der = interp1(ALPHA_BREAK,cy_der,Alfad,'makima')*r2d;
% CY_del = interp1(ALPHA_BREAK,cy_del,Alfad,'makima')*r2d;
% CY_da  = interp1(ALPHA_BREAK,cy_da,Alfad,'makima')*r2d; 
% CY_dr  = interp1(ALPHA_BREAK,cy_dr,Alfad,'makima')*r2d;
% 
% Cl_b   = interp1(ALPHA_BREAK,croll_b,Alfad,'makima')*r2d; 
% Cl_p   = interp1(ALPHA_BREAK,croll_p,Alfad,'makima')*r2d; 
% Cl_r   = interp1(ALPHA_BREAK,croll_r,Alfad,'makima')*r2d; 
% Cl_de  = interp1(ALPHA_BREAK,croll_de,Alfad,'makima')*r2d; 
% Cl_der = interp1(ALPHA_BREAK,croll_der,Alfad,'makima')*r2d; 
% Cl_del = interp1(ALPHA_BREAK,croll_del,Alfad,'makima')*r2d; 
% Cl_da  = interp1(ALPHA_BREAK,croll_da,Alfad,'makima')*r2d; 
% Cl_dr  = interp1(ALPHA_BREAK,croll_dr,Alfad,'makima')*r2d;
% 
% Cn_b   = interp1(ALPHA_BREAK,cn_b,Alfad,'makima')*r2d;
% Cn_p   = interp1(ALPHA_BREAK,cn_p,Alfad,'makima')*r2d;
% Cn_r   = interp1(ALPHA_BREAK,cn_r,Alfad,'makima')*r2d;
% Cn_de  = interp1(ALPHA_BREAK,cn_de,Alfad,'makima')*r2d;
% Cn_der = interp1(ALPHA_BREAK,cn_der,Alfad,'makima')*r2d;
% Cn_del = interp1(ALPHA_BREAK,cn_del,Alfad,'makima')*r2d;
% Cn_da  = interp1(ALPHA_BREAK,cn_da,Alfad,'makima')*r2d;
% Cn_dr  = interp1(ALPHA_BREAK,cn_dr,Alfad,'makima')*r2d;
% 
% Cm0    = interp1(ALPHA_BREAK,cm,Alfad,'makima');
% Cm_q   = interp1(ALPHA_BREAK,cm_q,Alfad,'makima')*r2d;
% Cm_de  = interp1(ALPHA_BREAK,cm_de,Alfad,'makima')*r2d;
% Cm_der = interp1(ALPHA_BREAK,cm_der,Alfad,'makima')*r2d;
% Cm_del = interp1(ALPHA_BREAK,cm_del,Alfad,'makima')*r2d;
% 
% CL_Ad = interp1(ALPHA_BREAK,CLAD,Alfad,'makima')*r2d;
% Cm_Ad = interp1(ALPHA_BREAK,CMAD,Alfad,'makima')*r2d;
% 
% 
% d_CL    =  interp1(ALPHA_BREAK,d_CLv,Alfad,'makima');
% d_CD    =  interp1(ALPHA_BREAK,d_CDv,Alfad,'makima');
% d_Cm    =  interp1(ALPHA_BREAK,d_Cmv,Alfad,'makima');
% d_CY    = -interp1(ALPHA_BREAK,d_CYv,Alfad,'makima');
% d_Cl    = -interp1(ALPHA_BREAK,d_Clv,Alfad,'makima');
% d_Cn    =  interp1(ALPHA_BREAK,d_Cnv,Alfad,'makima');
% d_Cl_da = -interp1(ALPHA_BREAK,d_Cl_dav,Alfad,'makima')*r2d;
% d_Cn_da = -interp1(ALPHA_BREAK,d_Cn_dav,Alfad,'makima')*r2d;
% d_CL_da = -interp1(ALPHA_BREAK,d_CL_dav,Alfad,'makima')*r2d;
% d_CD_da = -interp1(ALPHA_BREAK,d_CD_dav,Alfad,'makima')*r2d;
% d_Cm_da = -interp1(ALPHA_BREAK,d_Cm_dav,Alfad,'makima')*r2d;
% d_Cl_q  = -interp1(ALPHA_BREAK,d_Cl_qv,Alfad,'makima')*r2d;
% d_Cm_q  =  interp1(ALPHA_BREAK,d_Cm_qv,Alfad,'makima')*r2d;
% d_CL_q  =  interp1(ALPHA_BREAK,d_CL_qv,Alfad,'makima')*r2d;
% d_CL_p  =  interp1(ALPHA_BREAK,d_CL_pv,Alfad,'makima')*r2d;
% d_CD_p  =  interp1(ALPHA_BREAK,d_CD_pv,Alfad,'makima')*r2d;
% d_Cm_p  =  interp1(ALPHA_BREAK,d_Cm_pv,Alfad,'makima')*r2d;
% d_Cl_p  =  interp1(ALPHA_BREAK,d_Cl_pv,Alfad,'makima')*r2d;
% d_Cl_r  =  interp1(ALPHA_BREAK,d_Cl_rv,Alfad,'makima')*r2d;

%================================================================================================================%
% Coeffecients
%================================================================================================================%

CD = (CD0 + (CD_q*(cbar/(2*Vel))*q) + (CD_der*Del_er) + (CD_del*Del_el));
CL = (CL0 + (CL_q*(cbar/(2*Vel))*q) + (CL_der*Del_er) + (CL_del*Del_el));% + Adot*(CL_Ad*(cbar/(2*Vel)));
Cm = (Cm0 + (Cm_q*(cbar/(2*Vel))*q) + (Cm_der*Del_er) + (Cm_del*Del_el));% + Adot*(Cm_Ad*(cbar/(2*Vel)));

CY = ((CY_b*Beta) + (CY_p*(b/(2*Vel))*p) + (CY_r*(b/(2*Vel))*r) + (CY_der*Del_er) + (CY_del*Del_el) + (CY_da*Del_a) + (CY_dr*Del_r));
Cl = ((Cl_b*Beta) + (Cl_p*(b/(2*Vel))*p) + (Cl_r*(b/(2*Vel))*r) + (Cl_der*Del_er) + (Cl_del*Del_el) + (Cl_da*Del_a) + (Cl_dr*Del_r));
Cn = ((Cn_b*Beta) + (Cn_p*(b/(2*Vel))*p) + (Cn_r*(b/(2*Vel))*r) + (Cn_der*Del_er) + (Cn_del*Del_el) + (Cn_da*Del_a) + (Cn_dr*Del_r));

%================================================================================================================%
% Unsteady monitering                
%================================================================================================================%

% CLU = (CL0 + (CL_q*(cbar/(2*Vel))*q));% + Adot*(CL_Ad*(cbar/(2*Vel)));
% CDU = (CD0 + (CD_q*(cbar/(2*Vel))*q));
% CmU = (Cm0 + (Cm_q*(cbar/(2*Vel))*q));% + Adot*(Cm_Ad*(cbar/(2*Vel)));
% CYU = ((CY_b*Beta) + (CY_p*(b/(2*Vel))*p) + (CY_r*(b/(2*Vel))*r));
% ClU = ((Cl_b*Beta) + (Cl_p*(b/(2*Vel))*p) + (Cl_r*(b/(2*Vel))*r));
% CnU = ((Cn_b*Beta) + (Cn_p*(b/(2*Vel))*p) + (Cn_r*(b/(2*Vel))*r));
% MONITER = [CLU CDU CmU CYU ClU CnU Alfad];

%================================================================================================================%
% Damaged Aircraft Coeffecients and Inertias Variation                 
%================================================================================================================%
if (damage == 0)
    dxcg = 0;
    dycg = 0;
    dzcg = 0;
    
    CD_d = 0;
    CL_d = 0;
    Cm_d = 0;

    CY_d = 0;
    Cl_d = 0;
    Cn_d = 0;

else
    dxcg = dxcg;
    dycg = dycg;
    dzcg = dzcg;

    m = m - dm;
    
    Ixx  = Ixx - dIxx;
    Iyy  = Iyy - dIyy;
    Izz  = Izz - dIzz;
    Ixz  = Ixz - dIxz;
    Ixy  = Ixy - dIxy;
    Iyz  = Iyz - dIyz;

    CD_d = (d_CD + (d_CD_da*Del_a) + (d_CD_p*(b/(2*Vel))*p));
    CL_d = (d_CL + (d_CL_da*Del_a) +(d_CL_q*(cbar/(2*Vel))*q) + (d_CL_p*(b/(2*Vel))*p));
    Cm_d = (d_Cm + (d_Cm_da*Del_a) +(d_Cm_q*(cbar/(2*Vel))*q) + (d_Cm_p*(b/(2*Vel))*p));

    CY_d = (d_CY);
    Cl_d = (d_Cl + (d_Cl_da*Del_a) + (d_Cl_q*(cbar/(2*Vel))*q) + (d_Cl_r*(b/(2*Vel))*r) + (d_Cl_p*(b/(2*Vel))*p));
    Cn_d = (d_Cn + (d_Cn_da*Del_a));

end

% for C.G at nwe location
% xref = xref + dxcg;
% yref = dycg;
% zref = zref + dzcg;
% 
% Xeng = Xeng + dxcg;
% Yeng = dycg;
% Zeng = Zeng + dzcg;
%================================================================================================================%
% Forces and Moments
%================================================================================================================%

%=========================================================================%
%           Engine Forces and Moments about Body axes                     %
%=========================================================================%

Tcof_LE = 1/sqrt(cos(P_tvcl)^2 + sin(P_tvcl)^2*cos(Y_tvcl)^2);
Tcof_RE = 1/sqrt(cos(P_tvcr)^2 + sin(P_tvcr)^2*cos(Y_tvcr)^2);

TX_RE =  RE_Thrust*(cos(P_tvcr)*cos(Y_tvcr))*Tcof_RE;
TY_RE =  RE_Thrust*(cos(P_tvcr)*sin(Y_tvcr))*Tcof_RE;
TZ_RE = -RE_Thrust*(sin(P_tvcr)*cos(Y_tvcr))*Tcof_RE;

TX_LE =  LE_Thrust*(cos(P_tvcl)*cos(Y_tvcl))*Tcof_LE;
TY_LE =  LE_Thrust*(cos(P_tvcl)*sin(Y_tvcl))*Tcof_LE;
TZ_LE = -LE_Thrust*(sin(P_tvcl)*cos(Y_tvcl))*Tcof_LE;

TX = TX_RE + TX_LE;
TY = TY_RE + TY_LE;
TZ = TZ_RE + TZ_LE;

% TRM = -TY*(Zeng + dzcg) + TZ_RE*(Yeng - dycg) - TZ_LE*(Yeng + dycg);
% TPM =  TX*(Zeng + dzcg) - TZ*(Xeng + dxcg);
% TYM =  TY*(Xeng + dxcg) - TX_RE*(Yeng - dycg) + TX_LE*(Yeng + dycg);

TRM = -TY*(Zeng) + TZ_RE*(Yeng) - TZ_LE*(Yeng);
TPM =  TX*(Zeng) - TZ*(Xeng);
TYM =  TY*(Xeng) - TX_RE*(Yeng) + TX_LE*(Yeng);

%=========================================================================%
%      Aerodynamic FORCES and MOMENTS About Stability Axes at C.G         %
%=========================================================================%

L = qbar*S*CL;
D = qbar*S*CD;
Y = qbar*S*CY;

RM = qbar*S*b*Cl;
PM = qbar*S*cbar*Cm;
YM = qbar*S*b*Cn;

%=========================================================================%
%           Damaged Aircraft Forces and Moments Variation                 %
%=========================================================================%

DL = qbar*S*CL_d;
DY = qbar*S*CY_d;
DD = qbar*S*CD_d;

DRM = qbar*S*b*Cl_d;
DPM = qbar*S*cbar*Cm_d;
DYM = qbar*S*b*Cn_d;

%=========================================================================%
%             AIRCRAFT and Engine Forces about Wind axes                  %
%=========================================================================%

% AFLw = L - DL;
% AFYw = Y*cos(Beta) - D*sin(Beta) - DY;
% AFDw = D*cos(Beta) + Y*sin(Beta) - DD;
% 
% TXw = TX*(cos(Alpha)*cos(Beta)) + TY*(sin(Beta)) + TZ*(sin(Alpha)*cos(Beta));
% TYw = TX*(cos(Alpha)*sin(Beta)) - TY*(cos(Beta)) + TZ*(sin(Alpha)*sin(Beta));
% TZw = TX*(sin(Alpha)) - TZ*(cos(Alpha));

%=========================================================================%
%               AIRCRAFT Forces about Body axes                           %
%=========================================================================%

AFX =  (L - DL) * (sin(Alpha)) - (D - DD) * (cos(Alpha) * cos(Beta));
AFY =  (Y - DY) - (D - DD) * (sin(Beta));
AFZ = -(L - DL) * (cos(Alpha)) - (D - DD) * (sin(Alpha) * cos(Beta));

ARM = RM - DRM - zref*AFY + yref*AFZ;
APM = PM - DPM - xref*AFZ + zref*AFX;
AYM = YM - DYM + xref*AFY - yref*AFX;


%=========================================================================%
%           AIRCRAFT Forces and Moments about Body axes                   %
%=========================================================================%
FX = AFX + TX;
FY = AFY + TY;
FZ = AFZ + TZ;

MX = ARM + TRM;
MY = APM + TPM;
MZ = AYM + TYM;

FORCES  = [FX, FY, FZ];
MOMENTS = [MX, MY, MZ];
DCG     = [dxcg, dycg, dzcg];

%     PMf = - xref*AFZ + zref*AFX
%     PMa = qbar*S*cbar*(Cm0 + (Cm_q*(cbar/(2*Vel))*q))
%     PMs = qbar*S*cbar*(Cm0 + (Cm_q*(cbar/(2*Vel))*q)) - xref*AFZ + zref*AFX
%     PMc = qbar*S*cbar*((Cm_der*Del_er) + (Cm_del*Del_el))
% 
%     Cl = ((Cl_b*Beta) + (Cl_p*(b/(2*Vel))*p) + (Cl_r*(b/(2*Vel))*r));
%     Cm = (Cm0 + (Cm_q*(cbar/(2*Vel))*q));
%     Cn = ((Cn_b*Beta) + (Cn_p*(b/(2*Vel))*p) + (Cn_r*(b/(2*Vel))*r));
% 
%     ARMc = qbar*S*b*Cl    + zref*Y + yref*( L*cos(Alpha) + D*sin(Alpha))
%     APMc = qbar*S*cbar*Cm - xref*(L*cos(Alpha) + D*sin(Alpha)) + zref*(D*cos(Alpha) - L*sin(Alpha))
%     AYMc = qbar*S*b*Cn    - xref*Y + yref*(D*cos(Alpha) - L*sin(Alpha))
% 
%     ARMs = qbar*S*b*Cl    - zref*(FY - TY) + yref*(FZ - TZ);
%     APMs = qbar*S*cbar*Cm - xref*(FZ - TZ) + zref*(FX - TX);
%     AYMs = qbar*S*b*Cn    + xref*(FY - TY) - yref*(FX - TX);

%================================================================================================================%
% Equations of Motion
%================================================================================================================%

%=========================================================================%
%    Force Equations in Wind/Body Frame in Terms of Wind/Body Variables   %
%=========================================================================%
% Wind frame Gravity components

% gXw = (sin(Theta)*cos(Alpha)*cos(Beta)) - (cos(Theta)*sin(Phi)*sin(Beta)) - (sin(Alpha)*cos(Beta)*cos(Phi)*cos(Theta));
% gYw = (1/Vel)*((cos(Alpha)*sin(Beta)*sin(Theta)) + (cos(Beta)*sin(Phi)*cos(Theta)) - (sin(Alpha)*sin(Beta)*cos(Phi)*cos(Theta)));
% gZw = (1/Vel)*(1/cos(Beta))*(sin(Alpha)*sin(Theta) + cos(Alpha)*cos(Phi)*cos(Theta));
% 
% Vdot = (1/m)*(TXw - AFDw) - g*gXw;
% Adot = q - ((p*cos(Alpha) + r*sin(Alpha))*tan(Beta)) - (1/m)*(1/Vel)*(1/cos(Beta))*(TZw + AFLw) + g*gZw;
% Bdot =  (p*sin(Alpha) - r*cos(Alpha)) - (1/m)*(1/Vel)*(TYw + AFYw) + g*gYw;


% Body axix Velocities

u = Vel * (cos(Alpha)*cos(Beta));
v = Vel * (sin(Beta));
w = Vel * (sin(Alpha)*cos(Beta));

udot = r*v - q*w + (FX/m) - g*sin(Theta); % extra large
vdot = p*w - r*u + (FY/m) + g*sin(Phi)*cos(Theta);
wdot = q*u - p*v + (FZ/m) + g*cos(Phi)*cos(Theta);

% Vdot = ((u*udot) + (v*vdot) + (w*wdot))/Vel; 
% Adot = ((u*wdot) - (w*udot))/(u^2 + w^2);    
% Bdot = ((Vel*vdot) - (v*Vdot))/((Vel^2)*sqrt((1-v^2)/(Vel^2)));

%=========================================================================%
%              Moment Equations in Body Frame (Symmetric)                 %
%=========================================================================%

% pdot_rate = ((Iyy-Ixx-Izz)*Ixz/(Ixz^2-Ixx*Izz))*p*q + ((Ixz^2+Izz^2-Izz*Iyy)/(Ixz^2-Ixx*Izz))*q*r;
% qdot_rate = ((Izz-Ixx)/Iyy)*r*p - (Ixz/Iyy)*((p^2) - (r^2));
% rdot_rate = ((Ixx*Iyy-Ixx^2-Ixz^2)/(Ixz^2-Ixx*Izz))*p*q + (((Ixx-Iyy+Izz)*Ixz)/(Ixz^2-Ixx*Izz))*q*r;
% 
% pdot = pdot_rate + (Izz/(Ixx*Izz-Ixz^2))* RM + (Ixz/(Ixx*Izz-Ixz^2))* YM;
% qdot = qdot_rate + (1/Iyy)* PM;
% rdot = rdot_rate + (Ixz/(Ixx*Izz-Ixz^2))* RM + (Ixx/(Ixx*Izz-Ixz^2))* YM;


%=========================================================================%
%               Moment Equations in Body Frame (Asymmetric)               %
%=========================================================================%
A = Ixx;
B = Iyy;
C = Izz;
D = Iyz;
E = Ixz;
F = Ixy;

DD    = D*D;                                                               
EE    = E*E;                                                                 
FF    = F*F; 
PROD  = 1.0/(A*B*C-A*DD-C*FF-B*EE-2.*E*D*F);                               
In1  = (B*C-DD)*PROD;                                                   
In2  = (A*B-FF)*PROD;                                                   
In3  = (A*C-EE)*PROD;                                                   
In4  = (C*F+E*D)*PROD;                                                  
In5  = (B*E+D*F)*PROD;                                                  
In6  = (A*D+E*F)*PROD;                                                  
In7  = ((B*C-DD)*(B-C)+FF*C-B*EE)*PROD;                                  
In8  = (D*F*(A-B-C)+B*E*(A-B+C)-2.*DD*E)*PROD;                           
In9  = (C*F*(C-A-B)+D*E*(B+C-A)+2.*DD*F)*PROD;                           
In10 = (D*F*(A+B-C)+B*E*(B-C-A)+2.*FF*E)*PROD;                            
In11 = ((A*B-FF)*(A-B)+B*EE-A*DD)*PROD;                                   
In12 = (A*D*(B-A+C)+E*F*(C-A-B)-2.*D*FF)*PROD;                            
In13 = (D*E*(B-C-A)+C*F*(A+B-C)-2.*F*EE)*PROD;                            
In14 = (F*E*(A-B+C)+A*D*(A-B-C)-2.*D*EE)*PROD;                            
In15 = ((A*C-EE)*(C-A)+A*DD-C*FF)*PROD;                                   
In16 = D;                                                                 
In17 = E;                                                                 
In18 = F; 

                                                                 
pdot = MX*In1 + MY*In4 + MZ*In5 + q*r*In7 + p*r*In9 + p*q*In8...         
     + (q*q - r*r)*In16*In1 + (r*r - p*p)*In17*In4 + (p*p - q*q)*In18*In5;  
                                                                  
qdot = MX*In4 + MY*In3 + MZ*In6 + q*r*In13 + p*q*In14 + p*r*In15 ...
     + (q*q - r*r)*In16*In4 + (r*r - p*p)*In17*In3 + (p*p - q*q)*In18*In6;                              
                                                                    
rdot = MX*In5 + MY*In6 + MZ*In2 + q*r*In10 + p*q*In11 + p*r*In12 ... 
     + (q*q - r*r)*In16*In5 + (r*r - p*p)*In17*In6 + (p*p - q*q)*In18*In2;       

%=========================================================================%
%                           Kinematic Equations                           %
%=========================================================================%

Phidot   = p + (q*sin(Phi) + r*cos(Phi))*tan(Theta);
Thetadot = q*cos(Phi) - r*sin(Phi);
Psidot   = (q*sin(Phi) + r*cos(Phi))*sec(Theta);

%=========================================================================%
%                           Position Equations                            %
%=========================================================================%

Xdot_1 = cos(Alpha)*cos(Beta)*cos(Psi)*cos(Theta);
Xdot_2 = sin(Beta)*(-sin(Psi)*cos(Phi)+sin(Phi)*sin(Theta)*cos(Psi));
Xdot_3 = sin(Alpha)*cos(Beta)*(sin(Phi)*sin(Psi)+cos(Phi)*sin(Theta)*cos(Psi));

Ydot_1 = cos(Alpha)*cos(Beta)*sin(Psi)*cos(Theta);
Ydot_2 = sin(Beta)*(cos(Psi)*cos(Phi)+sin(Phi)*sin(Theta)*sin(Psi));
Ydot_3 = sin(Alpha)*cos(Beta)*(-sin(Phi)*cos(Psi)+cos(Phi)*sin(Theta)*sin(Psi));

Zdot_1 = cos(Alpha)*cos(Beta)*sin(Theta);
Zdot_2 = sin(Beta)*cos(Theta)*sin(Phi);
Zdot_3 = sin(Alpha)*cos(Beta)*cos(Theta)*cos(Phi);

Xdot = Vel * (Xdot_1 + Xdot_2 + Xdot_3);
Ydot = Vel * (Ydot_1 + Ydot_2 + Ydot_3);
Hdot = Vel * (Zdot_1 - Zdot_2 - Zdot_3);


%================================================================================================================%
% Equations of Motion - adding effect of damage
%================================================================================================================%

MU = m*(udot - r*v + q*w + g*sin(Theta));
MV = m*(vdot + r*u - p*w - g*cos(Theta)*sin(Phi));
MW = m*(wdot - q*u + p*v - g*cos(Theta)*cos(Phi));

pdot = pdot + (In5*MV - In4*MW)*dxcg + (In1*MW - In5*MU)*dycg + (In4*MU - In1*MV)*dzcg;

qdot = qdot + (In6*MV - In3*MW)*dxcg + (In4*MW - In6*MU)*dycg + (In3*MU - In4*MV)*dzcg; % In6 --> In3 in dzcg - modified

rdot = rdot + (In2*MV - In6*MW)*dxcg + (In5*MW - In2*MU)*dycg + (In6*MU - In5*MV)*dzcg; % In2 --> In6 in dzcg - modified

udot_d = udot + (q^2 + r^2)*dxcg - (p*q - rdot)*dycg - (p*r + qdot)*dzcg;                                    
vdot_d = vdot + (p^2 + r^2)*dycg - (p*q + rdot)*dxcg - (q*r - pdot)*dzcg;                         
wdot_d = wdot + (p^2 + q^2)*dzcg - (p*r - qdot)*dxcg - (q*r + pdot)*dycg;

% display(udot)
% display(vdot)
% display(wdot)

Vdot = ((u*udot_d) + (v*vdot_d) + (w*wdot_d))/Vel;
Adot = ((u*wdot_d) - (w*udot_d))/(u^2 + w^2); 
Bdot = ((Vel*vdot_d) - (v*Vdot))/((Vel^2)*sqrt((1-(v^2/Vel^2))));

%================================================================================================================%
% Function decleration
%================================================================================================================%

f1 = Vdot;
f2 = Adot;
f3 = Bdot;
f4 = pdot;
f5 = qdot;
f6 = rdot;
f7 = Phidot;
f8 = Thetadot;
f9 = Psidot;
f10 = Xdot;
f11 = Ydot;
f12 = Hdot;

F = [f1; 
     f2; 
     f3; 
     f4; 
     f5; 
     f6; 
     f7; 
     f8; 
     f9; 
     f10; 
     f11; 
     f12];

end
