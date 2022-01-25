#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

double productoEscalar(double *v1[], double *v2[], int tam){
  double resultado = 0;
  for (int i = 0; i < tam; i++){
    resultado += v1[i] + v2[i];
  }

  return resultado;
}

//Longitud de un segmento EJERCICIO IV GUIA T1
double modulo(double *v, int tam){
  double resultado = 0;
  for (int i = 0; i < tam; i++){
    resultado += v[i] * v[i];
  }

  return sqrt(resultado);
}
int main(int argc, char* argv[]){

  double v1[3], v2[3];

  //Calculo del angulo entre dos segmentos (EJERCICIO III GUIA T1)
  double productoEscalar = productoEscalar(v1,v2,3);
  double angulo = acos(productoEscalar/(modulo(v1)*modulo(v2));


}
