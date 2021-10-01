#include "matrix.h"

#include <math.h>
#include <assert.h>


Matrix::Matrix()
{
   Mat = NULL;
}

Matrix::Matrix(int nr,int nc, float valor)
{
  ren = nr;
  col = nc;
  Mat = new float*[ren];
  assert(Mat);
  for(int i = 0; i < ren; i++)
  {
      Mat[i] = new float[col];
      assert(Mat[i]);
  }

  for(int i = 0; i < ren; i++)
    for(int j = 0; j < col; j++)
        Mat[i][j] = valor;
}

Matrix::Matrix(float nr,float nc, float **m)
{
  ren = nr;
  col = nc;
  Mat = new float*[ren];
  assert(Mat);
  for(int i = 0; i < ren; i++)
  {
      Mat[i] = new float[col];
      assert(Mat[i]);
  }

  for(int i = 0; i < ren; i++)
    for(int j = 0; j < col; j++)
        Mat[i][j] = m[i][j];
}


Matrix::Matrix(Matrix &m)
{
   ren=m.numRen();
   col=m.numCol();
   Mat =new float*[ren];
   for(int i = 0; i < ren; i++)
  {
     Mat[i] = new float[col];
     assert(Mat[i]);
  }
   for(int i=0; i<ren; i++)
      for( int j=0; j<col; j++)
         Mat[i][j]=m.GETM(i,j);
}

void Matrix::Inicializa(int R, int C)
{
   col=C;
   ren=R;
   Mat=new float *[ren];
   for(int i=0; i<ren; i++)
      Mat[i]=new float[col];
   for(int i=0; i<ren; i++)
      for(int j=0; j<col; j++)
         Mat[i][j]=0;
}

Matrix &Matrix::operator*=(Matrix &mat2)
{
   Matrix aux;
   aux.Inicializa(ren, mat2.numCol());
   for(int i=0; i<ren; i++)
   {
      for(int j=0; j<mat2.numCol(); j++)
      {
         float suma=0;
        // Mat[i][j]=0;
         for(int k=0; k<col; k++)
         {
           suma+=floor(Mat[i][k]*mat2.GETM(k,j)+0.5);
           aux.SETM(i,j,suma);
         }
         //aux.SETM(i,j,suma);
      }
   }
   asignar(aux);
   return *this;
}

Matrix Matrix::operator*(float val)
{
   Matrix temp;
   temp.Inicializa(ren,col);
   for(int i=0; i<ren;i++)
      for(int j=0; j<col; j++)
         temp.SETM(i,j,Mat[i][j]* val);
   return temp;
}


Matrix &Matrix::operator=(Matrix &m)
{
//eliminar el tamaÒo de la matriz destino
  for(int i= 0; i<ren;i++ )
     //Se borran los renglones de la matriz
       delete [] Mat[i];
  //Se borra el arreglo de punteros
  delete []Mat;
//Asignar los nuevos datos de la matriz que llego
  ren=m.numRen();
  col = m.numCol();
  Mat = new float*[ren];
  assert(Mat);
  for(int i = 0; i < ren; i++)
  {
     Mat[i] = new float[col];
     assert(Mat[i]);
  }
  for( int i =0; i < ren; i++)
    for(int j = 0; j < col; j++)
        Mat[i][j] = m.Mat[i][j];

  return *this;
}
/*Matrix &Matrix::operator =(Matrix &mat2)
{
    ren=mat2.numRen();
    col=mat2.numCol();
    for(int i=0;i<ren;i++)
       for(int j=0;j<col;j++)
          Mat[i][j]=mat2.GETM(i,j);
    return *this;
} */

Matrix &Matrix::asignar(Matrix m)
{
    ////
    ren=m.numRen();
    col=m.numCol();
    Mat = new float*[ren];
    assert(Mat);
    for(int i = 0; i < ren; i++)
    {
       Mat[i] = new float[col];
       assert(Mat[i]);
    }
    /////
   for(int i=0;i<m.numRen();i++)
       for(int j=0;j<m.numCol();j++)
                Mat[i][j]=m.GETM(i,j);
   return *this;
}

Matrix::~Matrix()
{
  //Se libera la memoria
  for(int i= 0; i<ren;i++ )
     //Se borran los renglones de la matriz
       delete [] Mat[i];
  //Se borra el arreglo de punteros
  delete []Mat;

}

Matrix &Matrix::Identidad()
{
  for(int i=0; i < ren; i++)
    for( int j = 0; j < col; j++)
      if( i == j)
         Mat[i][i]= 1;
      else
         Mat[i][j]= 0;
  return *this;
}


//---------------TRANSFORMACIONES-----------------------------

Matrix & Matrix::traslacion(Matrix f,Matrix id,int tx,int ty)
{
   id.Identidad(); //MAT. DE TRANSFORMACION
   id.SETM(2,0,tx);
   id.SETM(2,1,ty);

   f*=id;
   this->asignar(f);
   return *this;
}

Matrix &Matrix::escalacion(Matrix f, Matrix id, float sx, float sy)
{
    id.Identidad(); //MAT. DE TRANSFORMACION

    /*
      Sx   0   0
      0    Sy  0
      0    0   1
    */
    id.SETM(0,0,sx);
    id.SETM(1,1,sy);

    f *= id;
    this->asignar(f);
    return *this;
}

Matrix &Matrix::escalacionPuntoFijo(Matrix f, Matrix id, float sx, float sy, int PFx, int PFy)
{
    id.Identidad(); //MAT. DE TRANSFORMACION

    /*
      Sx            0             0
      0             Sy            0
      -PFx*(Sx-1)   -PFy*(sy-1)   1
    */
    float pfx = -PFx*(sx-1);
    float pfy = -PFy*(sy-1);
    id.SETM(0, 0, sx);
    id.SETM(1, 1, sy);
    id.SETM(2, 0, pfx);
    id.SETM(2, 1, pfy);

    f *= id;
    this->asignar(f);
    return *this;
}

Matrix &Matrix::rotacion(Matrix f, Matrix id, float angulo)
{
    id.Identidad(); //MAT. DE TRANSFORMACION

    /*
      Cosθ    Senθ  0
      -Senθ   Cosθ  0
      0       1     1
    */
    float radianes = angulo * M_PI / 180.0 ;
    id.SETM(0, 0, cos(radianes));
    id.SETM(0, 1, sin(radianes));
    id.SETM(1, 0, -sin(radianes));
    id.SETM(1, 1, cos(radianes));

    f *= id;
    this->asignar(f);
    return *this;
}

Matrix &Matrix::rotacionPuntoPivote(Matrix f, Matrix id, float angulo, float pPx, float pPy)
{
  id.Identidad();
  float radianes = angulo * 3.14 / 180.0;

  float ren20 = pPx * (1 - cos(radianes)) + pPy * sin(radianes);
  float ren21 = pPy * (1 - cos(radianes)) -pPx * sin(radianes);

  id.SETM(0, 0, cos(radianes));
  id.SETM(0, 1, sin(radianes));
  id.SETM(1, 0, -sin(radianes));
  id.SETM(1, 1, cos(radianes));
  id.SETM(2, 0, ren20);
  id.SETM(2, 1, ren21);
  f *= id;
  asignar(f);
  return *this;
}


