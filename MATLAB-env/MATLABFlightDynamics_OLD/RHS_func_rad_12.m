function F = RHS_func_rad_12(t0,x)

global m g Tm rho S b cbar CD0 CD_q CD_de  CL0 CL_q CL_de del_e del_a del_r eta CY_b CY_p CY_r CY_de CY_da CY_dr...
    Ixx Iyy Izz Ixz Cl_b Cl_p Cl_r Cl_de Cl_da Cl_dr Cn_b Cn_p Cn_r Cn_de Cn_da Cn_dr Cm0 Cm_q Cm_de  

% x(1)=V
% x(2)=alpha
% x(3)=beta
% x(4)=p
% x(5)=q
% x(6)=r
% x(7)=phi
% x(8)=theta
% x(9)=psi
% x(10)=xe
% x(11)=ye
% x(12)=h

%-----------------------Force Equations in Body Frame but in Terms of Wind-frame Variables--------------------------%
a11=(1/m)*eta*Tm*cos(x(2))*cos(x(3));
a12=-(1/m)*0.5*rho*(x(1)^2)*S*(CD0+CD_q*(cbar/2)*x(5)/x(1)+CD_de*del_e);
a13=-g*(sin(x(8))*cos(x(2))*cos(x(3))-cos(x(8))*sin(x(7))*sin(x(3))-sin(x(2))*cos(x(3))*cos(x(7))*cos(x(8)));
f1=a11+a12+a13;

a21=x(5)-(x(4)*cos(x(2))+x(6)*sin(x(2)))*tan(x(3));
a22=-(1/m)*(1/x(1))*(1/cos(x(3)))*eta*Tm*sin(x(2));
a23=-(1/m)*(1/cos(x(3)))*0.5*rho*x(1)*S*(CL0+CL_q*(cbar/2)*x(5)/x(1)+CL_de*del_e);
a24=(1/x(1))*(1/cos(x(3)))*g*(sin(x(2))*sin(x(8))+cos(x(2))*cos(x(7))*cos(x(8)));
f2=a21+a22+a23+a24;

a31=x(4)*sin(x(2))-x(6)*cos(x(2));
a32=-(1/m)*(1/x(1))*eta*Tm*cos(x(2))*sin(x(3));
a33=-(1/m)*0.5*rho*x(1)*S*(CY_b*x(3)+CY_p*(b/2)*x(4)/x(1)+CY_r*(b/2)*x(6)/x(1)+CY_de*del_e+CY_da*del_a+CY_dr*del_r);
a34=(1/x(1))*g*(cos(x(2))*sin(x(3))*sin(x(8))+cos(x(3))*sin(x(7))*cos(x(8))-sin(x(2))*sin(x(3))*cos(x(7))*cos(x(8)));
f3=a31+a32+a33+a34;
%----------------------------------------------------------------------------------------------------------------------%

%-------------------------------------------------Moment Equations in Body Frame---------------------------------------------------------%
a41=((Iyy-Ixx-Izz)*Ixz/(Ixz^2-Ixx*Izz))*x(4)*x(5);
a42=((Ixz^2+Izz^2-Izz*Iyy)/(Ixz^2-Ixx*Izz))*x(5)*x(6);
a43=(Izz/(Ixx*Izz-Ixz^2))*0.5*rho*(x(1)^2)*S*b*(Cl_b*x(3)+Cl_p*(b/2)*x(4)/x(1)+Cl_r*(b/2)*x(6)/x(1)+Cl_de*del_e+Cl_da*del_a+Cl_dr*del_r);
a44=(Ixz/(Ixx*Izz-Ixz^2))*0.5*rho*(x(1)^2)*S*b*(Cn_b*x(3)+Cn_p*(b/2)*x(4)/x(1)+Cn_r*(b/2)*x(6)/x(1)+Cn_de*del_e+Cn_da*del_a+Cn_dr*del_r);
f4=a41+a42+a43+a44;

a51=((Izz-Ixx)/Iyy)*x(6)*x(4);
a52=-(Ixz/Iyy)*(x(4)^2-x(6)^2);
a53=(1/Iyy)*0.5*rho*(x(1)^2)*S*cbar*(Cm0+Cm_q*(cbar/2)*x(5)/x(1)+Cm_de*del_e);
f5=a51+a52+a53;

a61=((Ixx*Iyy-Ixx^2-Ixz^2)/(Ixz^2-Ixx*Izz))*x(4)*x(5);
a62=(((Ixx-Iyy+Izz)*Ixz)/(Ixz^2-Ixx*Izz))*x(5)*x(6);
a63=(Ixz/(Ixx*Izz-Ixz^2))*0.5*rho*(x(1)^2)*S*b*(Cl_b*x(3)+Cl_p*(b/2)*x(4)/x(1)+Cl_r*(b/2)*x(6)/x(1)+Cl_de*del_e+Cl_da*del_a+Cl_dr*del_r);
a64=(Ixx/(Ixx*Izz-Ixz^2))*0.5*rho*(x(1)^2)*S*b*(Cn_b*x(3)+Cn_p*(b/2)*x(4)/x(1)+Cn_r*(b/2)*x(6)/x(1)+Cn_de*del_e+Cn_da*del_a+Cn_dr*del_r);
f6=a61+a62+a63+a64;
%------------------------------------------------------------------------------------------------------------------------------------------%

%----------------------Kinematic Equations---------------------------%
f7=x(4)+(x(5)*sin(x(7))+x(6)*cos(x(7)))*tan(x(8));

f8=x(5)*cos(x(7))-x(6)*sin(x(7));

f9=(x(5)*sin(x(7))+x(6)*cos(x(7)))*sec(x(8));

f10=x(1)*cos(x(2))*cos(x(3))*cos(x(9))*cos(x(8))...
    +x(1)*sin(x(3))*(-sin(x(9))*cos(x(7))+sin(x(7))*sin(x(8))*cos(x(9)))...
    +x(1)*sin(x(2))*cos(x(3))*(sin(x(7))*sin(x(9))+cos(x(7))*sin(x(8))*cos(x(9)));

f11=x(1)*cos(x(2))*cos(x(3))*sin(x(9))*cos(x(8))...
    +x(1)*sin(x(3))*(cos(x(9))*cos(x(7))+sin(x(7))*sin(x(8))*sin(x(9)))...
    +x(1)*sin(x(2))*cos(x(3))*(-sin(x(7))*cos(x(9))+cos(x(7))*sin(x(8))*sin(x(9)));

f12=x(1)*(cos(x(2))*cos(x(3))*sin(x(8))-sin(x(3))*cos(x(8))*sin(x(7))...
    -sin(x(2))*cos(x(3))*cos(x(8))*cos(x(7)));
%--------------------------------------------------------------------%

F= [f1;
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

