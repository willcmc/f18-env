// Include Files
#include "main.h"
#include "./lib/Aerodata/AerodataF18.h"
#include <iostream>

int main(int, char **)
{
  AerodataF18 Aero;

  double F18_Aerodata[1107];
  double ALPHA_BREAK[27];
  double Geom[17];

  Aero.Aerodata(Geom, ALPHA_BREAK, F18_Aerodata);
  std::cout << Geom[1];
  return 0;
}