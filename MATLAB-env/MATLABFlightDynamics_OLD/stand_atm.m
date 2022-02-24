
function rho = stand_atm(ALT)

if (ALT <= 11000) 
   T_atm = 288.15-0.0065*ALT;
   p_atm = 101325*(T_atm/288.15)^(9.81/(287*0.0065)); 
else 
   T_atm = 216.65;
   p_atm = 22632*exp(-9.81*(ALT-11000)/(287*216.65)); 
end    

rho = p_atm/(287*T_atm);