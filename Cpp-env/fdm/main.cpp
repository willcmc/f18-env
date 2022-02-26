// Include Files
#include "main.h"

int main()
{
  AerodataF18 Aero;

  double F18_Aerodata[1107];
  double ALPHA_BREAK[27];
  double Geom[17];

  Aero.Aerodata(Geom, ALPHA_BREAK, F18_Aerodata);
    
  Visualizer viz("127.0.0.1", 5000, "generic");
  
  return 0;
}