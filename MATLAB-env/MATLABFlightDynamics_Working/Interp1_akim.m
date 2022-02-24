%===========================================
%  F18 AIRCRAFT DATA 1D AKIMA INTERPOLATION
%===========================================
        
function[COEFF18] = Interp1_akim(AV,FUN,ALFA,NOF,NOR)

    for D = 1:NOR
        if(AV(D) >= ALFA)
            L1=D;
            if(AV(D) == ALFA)
                L2=D;
            else
                L2=D-1;
            end
            break;
        end
    end

    if D == 1
        warning('(AoA) beyond available data.', 1)
        COEFF18 = FUN(D);
        return
    end

    for J = 1:NOF
            
        if(D == L2)             
            COEFF18(J) = FUN(D,J);           
        else
            DELX(3,J) = (FUN(D,J) - FUN(D-1,J)) / (AV(D) - AV(D-1));
            
            if(D <= 3)            
                DELX(4,J) = (FUN(D+1,J) - FUN(D,J)) / (AV(D+1) - AV(D));
                DELX(5,J) = (FUN(D+2,J) - FUN(D+1,J)) / (AV(D+2) - AV(D+1));
                
                if(D <= 2)
                    DELX(2,J) = 2*(DELX(3,J)) - DELX(4,J);
                else
                    DELX(2,J) = (FUN(D-1,J) - FUN(D-2,J)) / (AV(D-1) - AV(D-2));
                end
                
                DELX(1,J) = 2*(DELX(2,J)) - DELX(3,J);            
            else 
                DELX(2,J) = (FUN(D-1,J) - FUN(D-2,J)) / (AV(D-1) - AV(D-2));
                DELX(1,J) = (FUN(D-2,J) - FUN(D-3,J)) / (AV(D-2) - AV(D-3));            
            end
            
            if(D >= NOR-1)            
                DELX(2,J) = (FUN(D-1,J) - FUN(D-2,J)) / (AV(D-1) - AV(D-2));
                DELX(1,J) = (FUN(D-2,J) - FUN(D-3,J)) / (AV(D-2) - AV(D-3));
                
                if(D >= NOR)
                    DELX(4,J) = 2*(DELX(3,J)) - DELX(2,J);
                else
                    DELX(4,J) = (FUN(D+1,J) - FUN(D,J)) / (AV(D+1) - AV(D));
                end
                
                DELX(5,J) = 2*(DELX(4,J)) - DELX(3,J);
                
            else 
                DELX(5,J) = (FUN(D+2,J) - FUN(D+1,J)) / (AV(D+2) - AV(D+1));
                DELX(4,J) = (FUN(D+1,J) - FUN(D,J)) / (AV(D+1) - AV(D));
                
            end
            
            if((D < NOR+1) && (D > 1))            
                DDX2(J) = abs(DELX(4,J) - DELX(3,J));
                DDX3(J) = abs(DELX(2,J) - DELX(1,J));           
                SW(J) = DDX2(J) + DDX3(J);
                
                if(SW(J) == 0.0)
                    DDX2(J) = 0.5;
                    DDX3(J) = 0.5;
                    SW(J)   = 1.0;
                end
                
                T3(J) = (DDX2(J)*DELX(2,J) + DDX3(J)*DELX(3,J))/SW(J);            
                DDX3(J) = abs(DELX(5,J) - DELX(4,J));
                DDX4(J) = abs(DELX(3,J) - DELX(2,J));            
                SW(J) = DDX3(J) + DDX4(J);
                
                if(SW(J) == 0.0)
                    DDX2(J) = 0.5;
                    DDX3(J) = 0.5;
                    SW(J)   = 1.0;
                end        
                T4(J) = (DDX3(J)*DELX(3,J) + DDX4(J)*DELX(4,J))/SW(J);            
            end
            Q0(J) = FUN(D-1,J) ; 
            Q1(J) = T3(J);
            Q2(J) = (2.0*(DELX(3,J) - T3(J)) + DELX(3,J) - T4(J))/(AV(D) - AV(D-1));
            Q3(J) = (-DELX(3,J) - DELX(3,J) + T3(J)+ T4(J))/((AV(D) - AV(D-1))^2);

            DEL        = ALFA - AV(D-1);
            COEFF18(J) = Q0(J) + DEL*(Q1(J) + DEL*(Q2(J) + DEL*Q3(J)));
        end     
    end

%=====================================================================================================================
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%=====================================================================================================================
	