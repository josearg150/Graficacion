#include "mapeo.h"
void Mapeo::ventana(float WX1,float WY1,float WX2,float WY2)
{
       XWmin=WX1;
       YWmin=WY1;
       XWmax=WX2;
       YWmax=WY2;
}
void Mapeo::puerto(int VX1,int VY1,int VX2,int VY2)
{
      XPVmin=VX1;
      YPVmin=VY1;
      XPVmax=VX2;
      YPVmax=VY2;
}
void Mapeo::mapear(int X,int Y,int &XT, int &YT, int L,int M)
{
      float s1,s2;
      s1=(XPVmax-XPVmin)/(XWmax-XWmin);
      s2=(YPVmax-YPVmin)/(YWmax-YWmin);
      //ESTAS VARIABLES REGRESAN SU VALOR POR REFERENCIA   &
      XT=floor((s1*(X-XWmin)+XPVmin+L)+0.5);
       //USAR redondear o round
      YT=floor((s2*(YWmin-Y)-YPVmin+M)+0.5);

}

