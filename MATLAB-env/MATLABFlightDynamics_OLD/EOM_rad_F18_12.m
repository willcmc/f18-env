%---------------------------6DOF Eq.of Motion of F-18/HARV-----------------------------%

clear all
clc
close all


global m g Ixx Iyy Izz Ixz rho S b cbar Tm

%---------------------Geometric / mass properties data-------------------------%
m = 36100/2.2046; % 36100 lbs
g = 9.81; % m/s2
W = m*g; % N
Ixx = 22789*14.59/10.764; % slugs ft2 -> Kg m2
Iyy = 176809*14.59/10.764;
Izz = 191744*14.59/10.764;
Ixz = -2305*14.59/10.764;
rho_sl = 1.225; % density @ sea-level
S = 400.0*0.3048*0.3048; % ft2 -> m2 (Wing planform area)
b = 37.4*0.3048; % ft -> m (Wing Span)
cbar = 11.52*0.3048; % ft -> m; Mean Aerodynamic Chord (MAC)
max_thrust = 32000*g/2.2046; % F-18 max. thrust (sea-level) static: 16000 lbs x 2

xcg = 0.238*cbar; % CG location referenced from the leading edge of the mean aerodynamic chord 
% mlgear_loc = 0.39*cbar; % Main landing gear location 

xe=0;
ye=0;
ALT=8000;

%----------------------------------------------------------------------------%


[ALPHA_BREAK,clift,clift_q,cd0,cd_q,cd_de,cy_b,croll_b,croll_p,croll_r,cm,cm_q,cn_b,cn_p,cy_r,...
    clift_de,cy_da,cy_dr,croll_da,cn_da,cn_r,cy_p,croll_dr,cn_dr,cm_de,cy_de,croll_de,cn_de] = Aerodata_rad;



global del_e del_a del_r eta  CD0 CD_q CD_de CL0 CL_q CL_de CY_b CY_p CY_r CY_de CY_da CY_dr...
    Cl_b Cl_p Cl_r Cl_de Cl_da Cl_dr Cn_b Cn_p Cn_r Cn_de Cn_da Cn_dr Cm0 Cm_q Cm_de
 
d2r=pi/180; %deg to rad conversion
r2d=180/pi; %rad to deg conversion

V=100;
alpha=21.9467*d2r;%5.0142;  %deg value converted to rad
beta=0*d2r; %deg value converted to rad
p=0*d2r;    %deg/sec value converted to rad/sec
q=0*d2r;    %deg/sec value converted to rad/sec
r=0*d2r;    %deg/sec value converted to rad/sec
phi=0*d2r;  %deg value converted to rad
theta=21.9467*d2r;%7.0142;   % theta=alpha+gamma  %deg value converted to rad
psi=0*d2r;  %deg value converted to rad

IC=[V;alpha;beta;p;q;r;phi;theta;psi;xe;ye;ALT];  

del_e=-5.2406*d2r;%-0.2409;     %deg value converted to rad
del_a=0*d2r;        %deg value converted to rad
del_r=0*d2r;        %deg value converted to rad
eta= 0.6156;%0.3404;

t0=0;
tf=100;
Ts=0.1;  %step size=0.1sec

x=IC;
X=zeros(1+(tf-t0)/Ts,length(IC));
X(1,:)=IC';

ETA=zeros(tf/Ts,1);
tic;
for i=1:tf/Ts
    
%     if i>=100 
%         del_e=(-5.2406+2.0)*d2r;
%     else
%         del_e=0*d2r;
%     end

%     if i>=100 & i<120
%         eta=(0.6156+0.1);        
%     else
%         if i>=120 & i<140
%             eta=(0.6156-0.1);
%         else
%             eta=0.6156;
%         end         
%     end
    
%         if i>=100 
%             eta=(0.6156+0.1);
%         end



%     if i>=100 && i<120
%         del_r=3.0*d2r;
%     else
%         del_r=0;
%     end

%     if i>=100 && i<120
%         del_a=5*d2r;        
% %     else
% %         if i>=1000 && i<1020
% %             del_a=-5*d2r;  
% %         else
% %             del_a=0;
% %         end         
%     end
    
    ETA(i,1)=eta;
    
        
    if (x(12)<= 11000) 
        T_atm = 288.15-0.0065*x(12);
        p_atm = 101325*(T_atm/288.15)^(9.81/(287*0.0065)); 
    else 
        T_atm = 216.65;
        p_atm = 22632*exp(-9.81*(x(12)-11000)/(287*216.65)); 
    end    
    rho = p_atm/(287*T_atm);

    % Tm=0.9*max_thrust*(0.88+0.24*(M-0.6)^1.4)*(rho/rho_sl)^0.8;
    Tm=((rho/rho_sl)^0.7)*max_thrust*(1-exp((x(12)-17000)/2000)); %from Stengel
    % Tm=max_thrust;
    

%     CD0=interp1(ALPHA_BREAK,cd0,x(2));
%     CD_q=interp1(ALPHA_BREAK,cd_q,x(2));
%     CD_de=interp1(ALPHA_BREAK,cd_de,x(2));
% 
%     CL0=interp1(ALPHA_BREAK,clift,x(2));
%     CL_q=interp1(ALPHA_BREAK,clift_q,x(2));
%     CL_de=interp1(ALPHA_BREAK,clift_de,x(2));
% 
%     CY_b=interp1(ALPHA_BREAK,cy_b,x(2)); 
%     CY_p=interp1(ALPHA_BREAK,cy_p,x(2)); 
%     CY_r=interp1(ALPHA_BREAK,cy_r,x(2)); 
%     CY_de=interp1(ALPHA_BREAK,cy_de,x(2)); 
%     CY_da=interp1(ALPHA_BREAK,cy_da,x(2)); 
%     CY_dr=interp1(ALPHA_BREAK,cy_dr,x(2));
% 
%     Cl_b=interp1(ALPHA_BREAK,croll_b,x(2)); 
%     Cl_p=interp1(ALPHA_BREAK,croll_p,x(2)); 
%     Cl_r=interp1(ALPHA_BREAK,croll_r,x(2)); 
%     Cl_de=interp1(ALPHA_BREAK,croll_de,x(2)); 
%     Cl_da=interp1(ALPHA_BREAK,croll_da,x(2)); 
%     Cl_dr=interp1(ALPHA_BREAK,croll_dr,x(2));
% 
%     Cn_b=interp1(ALPHA_BREAK,cn_b,x(2)); 
%     Cn_p=interp1(ALPHA_BREAK,cn_p,x(2)); 
%     Cn_r=interp1(ALPHA_BREAK,cn_r,x(2)); 
%     Cn_de=interp1(ALPHA_BREAK,cn_de,x(2)); 
%     Cn_da=interp1(ALPHA_BREAK,cn_da,x(2)); 
%     Cn_dr=interp1(ALPHA_BREAK,cn_dr,x(2));
% 
%     Cm0=interp1(ALPHA_BREAK,cm,x(2));
%     Cm_q=interp1(ALPHA_BREAK,cm_q,x(2));
%     Cm_de=interp1(ALPHA_BREAK,cm_de,x(2));
    
    
    CD0=interp1(ALPHA_BREAK,cd0,x(2),'spline');
    CD_q=interp1(ALPHA_BREAK,cd_q,x(2),'spline');
    CD_de=interp1(ALPHA_BREAK,cd_de,x(2),'spline');

    CL0=interp1(ALPHA_BREAK,clift,x(2),'spline');
    CL_q=interp1(ALPHA_BREAK,clift_q,x(2),'spline');
    CL_de=interp1(ALPHA_BREAK,clift_de,x(2),'spline');

    CY_b=interp1(ALPHA_BREAK,cy_b,x(2),'spline'); 
    CY_p=interp1(ALPHA_BREAK,cy_p,x(2),'spline'); 
    CY_r=interp1(ALPHA_BREAK,cy_r,x(2),'spline'); 
    CY_de=interp1(ALPHA_BREAK,cy_de,x(2),'spline'); 
    CY_da=interp1(ALPHA_BREAK,cy_da,x(2),'spline'); 
    CY_dr=interp1(ALPHA_BREAK,cy_dr,x(2),'spline');

    Cl_b=interp1(ALPHA_BREAK,croll_b,x(2),'spline'); 
    Cl_p=interp1(ALPHA_BREAK,croll_p,x(2),'spline'); 
    Cl_r=interp1(ALPHA_BREAK,croll_r,x(2),'spline'); 
    Cl_de=interp1(ALPHA_BREAK,croll_de,x(2),'spline'); 
    Cl_da=interp1(ALPHA_BREAK,croll_da,x(2),'spline'); 
    Cl_dr=interp1(ALPHA_BREAK,croll_dr,x(2),'spline');

    Cn_b=interp1(ALPHA_BREAK,cn_b,x(2),'spline'); 
    Cn_p=interp1(ALPHA_BREAK,cn_p,x(2),'spline'); 
    Cn_r=interp1(ALPHA_BREAK,cn_r,x(2),'spline'); 
    Cn_de=interp1(ALPHA_BREAK,cn_de,x(2),'spline'); 
    Cn_da=interp1(ALPHA_BREAK,cn_da,x(2),'spline'); 
    Cn_dr=interp1(ALPHA_BREAK,cn_dr,x(2),'spline');

    Cm0=interp1(ALPHA_BREAK,cm,x(2),'spline');
    Cm_q=interp1(ALPHA_BREAK,cm_q,x(2),'spline');
    Cm_de=interp1(ALPHA_BREAK,cm_de,x(2),'spline');
    

%     x=RK_4_rad((t0+(i-1)*Ts),Ts,x);
    
    k1=Ts.*RHS_func_rad_12(t0+(i-1)*Ts,x);
    k2=Ts.*RHS_func_rad_12((t0+(i-1)*Ts+Ts/2),(x+k1/2));
    k3=Ts.*RHS_func_rad_12((t0+(i-1)*Ts+Ts/2),(x+k2/2));
    k4=Ts.*RHS_func_rad_12((t0+(i-1)*Ts+Ts),(x+k3));
    x=x+(k1+2.*k2+2.*k3+k4)/6;
   
%     X(i+1,1)=x(1,1);
    for j=1:12
        X(i+1,j)=x(j,1); 
    end
   
end
toc;

for j=2:9
    X(:,j)=X(:,j).*r2d;     %all angular variables are converted back to deg
end

t=t0:Ts:tf;

figure(1)
 for j=1:3
     subplot(3,1,j)
     plot(t,X(:,j))
%      if IC(j,1)~=0
%         axis([t0 tf 0.95*IC(j,1) 1.05*IC(j,1)]);
%      else
%         axis([t0 tf -0.1 0.1]); 
%      end
     grid on
 end

figure(2)
 for j=1:3
     subplot(3,1,j)
     plot(t,X(:,j+3))
%      if IC(j+3,1)~=0
%         axis([t0 tf 0.95*IC(j+3,1) 1.05*IC(j+3,1)]);
%      else
%         axis([t0 tf -0.1 0.1]);
%      end
     grid on
 end
 
figure(3)
 for j=1:3
     subplot(3,1,j)
     plot(t,X(:,j+6))
%      if IC(j+6,1)~=0
%         axis([t0 tf 0.95*IC(j+6,1) 1.05*IC(j+6,1)]);
%      else
%         axis([t0 tf -0.1 0.1]);
%      end
     grid on
 end 

figure(4)
 for j=1:3
     subplot(3,1,j)
     plot(t,X(:,j+9))
%      if IC(j+9,1)~=0
%         axis([t0 tf 0.95*IC(j+9,1) 1.05*IC(j+9,1)]);
%      else
%         axis([t0 tf -0.1 0.1]);
%      end
     grid on
 end
 
figure(5);
plot(ETA)
 
figure(6)
plot3(X(:,10),X(:,11),X(:,12));
grid on
hold on
plot3(X(1,10),X(1,11),X(1,12),'r*');
hold off
% axis([0 10000 -100 100 7000 9000])

 

