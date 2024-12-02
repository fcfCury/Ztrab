#ifndef ASSENTO_H
#define ASSENTO_H

#include <string>
#include "passageiros.h"
#include "tripulacao.h"
#include "voo.h"
#include "reserva.h"
#include "assento.h"

using namespace std;

typedef struct assento
{
    int numero;
    int codigo_voo;
    string status;
}assento;

void registrarAssento();

#endif
