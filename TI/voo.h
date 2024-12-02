#ifndef VOO_H
#define VOO_H

#include <string> // Inclui a biblioteca para usar o tipo 'string'

using namespace std;

// Definindo a estrutura voo
typedef struct voo
{
    int codigo;              // Código do voo (número único para cada voo)
    string nome;             // Nome do voo (se necessário, por exemplo, o nome do operador ou do voo)
    string data;             // Data do voo no formato DD/MM/AAAA
    string hora;             // Hora do voo no formato HH:MM
    string origem;           // Local de origem do voo
    string destino;          // Local de destino do voo
    string status;           // Status ativo/inativo
    float tarifa;           // Preço do voo
    int codigo_aviao;        // Código único do avião
    int codigo_piloto;       // Código único do piloto
    int codigo_copiloto;     // Código único do copiloto
    int codigo_comissario;   //Código único do comissário
} voo; // Definindo 'voo' como um tipo de estrutura

// Declaração da função que registra o voo
void registraVoo(); // Função responsável por registrar os dados de um voo

#endif
