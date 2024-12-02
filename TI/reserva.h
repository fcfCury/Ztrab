#ifndef RESERVA_H
#define RESERVA_H

#include <string>
#include "passageiros.h"
#include "tripulacao.h"
#include "voo.h"
#include "reserva.h"
#include "assento.h"

using namespace std;

typedef struct reserva
{
    int codigo_voo;
    int codigo_passageiro;
    int numero_assento;
} reserva;

void registrarReserva();
void baixarReserva();

#endif
