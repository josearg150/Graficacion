#include "Matrix.h"
#include <iostream>

using namespace std;

int main()
{
           Matrix m1(3,3,0);
           for(int i = 0; i <3; i++)
             for(int j = 0; j < 3; j++)
                 m1.SET(i,j,5);
           for(int i = 0; i <3; i++)
           {
             for(int j = 0; j < 3; j++)
                 cout<<  m1.GET(i,j)<<"   ";
             cout<<endl;
           }

           cout<<endl<<endl;
           Matrix m2(m1);//constructor de copia

           for(int i = 0; i <3; i++)
             for(int j = 0; j < 3; j++)
                 m2.SET(i,j,8);
           for(int i = 0; i <3; i++)
           {
             for(int j = 0; j < 3; j++)
                 cout<<  m2.GET(i,j)<<"   ";
             cout<<endl;
           }

           Matrix m3 = m1 * m2;

           for(int i = 0; i <3; i++)
           {
             for(int j = 0; j < 3; j++)
                 cout<<  m3.GET(i,j)<<"   ";
             cout<<endl;
           }


    return 0;
}
