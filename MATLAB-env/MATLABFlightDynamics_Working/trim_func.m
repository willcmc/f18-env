function F = trim_func(x)

   % x(1)=alpha
   % x(2)=del_e
   % x(3)=eta

   %x(1) and x(2) are in deg

   global ALPHA_BREAK clift clift_de cd0 cd_de cm cm_de m g S rho Tm V gamma   


   f1=interp1(ALPHA_BREAK,cm,x(1))+(interp1(ALPHA_BREAK,cm_de,x(1)))*x(2); %pitching moment equn.equated to zero

   L=0.5*rho*(V^2)*S*(interp1(ALPHA_BREAK,clift,x(1))+(interp1(ALPHA_BREAK,clift_de,x(1)))*x(2));
   D=0.5*rho*(V^2)*S*(interp1(ALPHA_BREAK,cd0,x(1))+(interp1(ALPHA_BREAK,cd_de,x(1)))*x(2));

   f2=L*cos(gamma*pi/180)-D*sin(gamma*pi/180)+x(3)*Tm*sin((x(1)+gamma)*pi/180)-m*g;    %weight balance equn.
   f3=L*sin(gamma*pi/180)+D*cos(gamma*pi/180)-x(3)*Tm*cos((x(1)+gamma)*pi/180);        %drag balance equn.

   F=[f1;
      f2;
      f3];
   end

