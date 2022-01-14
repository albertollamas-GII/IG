// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: ObjRevolucion.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************

class ObjRevolucion : public Malla3D
{
public:
    ObjRevolucion();
    ObjRevolucion(const std::string &archivo, int num_instancias, bool tapa_sup = true, bool tapa_inf = true, char eje = 'y');
    ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup = true, bool tapa_inf = true, char eje = 'y');
    void calcularCoordTexturas();

protected:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf, char eje = 'y');
    std::vector<Tupla3f> perfil;
    int instancias;
    int tam_perfil = 0;
    

private:
    Tupla3f tapa_superior, tapa_inferior;
    bool abajoarriba = true, sup_creada = false, inf_creada = false;
    double distanciaPuntos(Tupla3f v1, Tupla3f v2);
};

#endif
