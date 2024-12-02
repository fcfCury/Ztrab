#ifndef TRIPULACAO_H
#define TRIPULACAO_H

using namespace std; 

// Definindo a estrutura tripulacao
typedef struct tripulacao
{
    int codigo;          // Código único para cada membro da tripulação
    string nome;         // Nome do membro da tripulação
    string cargo;        // Cargo do membro da tripulação (ex: Piloto, Copiloto, Comissário, etc.)
    string telefone;     // Número de telefone do membro da tripulação
} tripulacao;           // 'tripulacao' é o nome da estrutura, representando um membro da tripulação

// Declaração da função que registra a tripulação
void registraTripulacao(); // Função que registra os dados de um membro da tripulação

#endif
