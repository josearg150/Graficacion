#ifndef MATRIX_H
#define MATRIX_H


class Matrix
{
   int col, ren;
   float **Mat;

public:
   Matrix();
   Matrix(int nr,int nc, float valor);//LO AGREGUE DESPUES
   Matrix(float nr,float nc, float **m);//LO AGREGUE DESPUES
   Matrix(Matrix &);
   ~Matrix();
   void SETM(int R, int C, float val){Mat[R][C]=val;}
   float GETM(int R, int C){return Mat[R][C];}
   int numCol(){return col;}
   int numRen(){return ren;}
   void Inicializa(int, int);
   Matrix &operator *=(Matrix &mat2);
   Matrix operator*(float);//Multiplicar por un escalar
   //Matrix & operator =(Matrix &mat2);
   Matrix &operator=(Matrix &m);
   Matrix &asignar(Matrix);
   Matrix &Identidad();

   //TRANSFORMACIONES 2D
   //FigT              Fig     ID     Tx  Ty
   Matrix &traslacion(Matrix,Matrix,int,int);
   Matrix &escalacion(Matrix, Matrix, float, float);
   Matrix &escalacionPuntoFijo(Matrix, Matrix, float, float, int, int);
   Matrix &rotacion(Matrix, Matrix, float);
   Matrix &rotacionPuntoPivote(Matrix, Matrix, float, float, float);
};


#endif // MATRIX_H
