#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

using namespace std;

// Definindo a estrutura passageiro
typedef struct passageiro
{
    int codigo;            // Código único para cada passageiro
    string nome;           // Nome do passageiro
    string endereco;       // Endereço do passageiro
    string telefone;       // Telefone do passageiro
    char fidelidade;       // Indica se o passageiro é fiel (s/n)
    int pontos_fidelidade; // Número de pontos de fidelidade do passageiro
} passageiro;              // 'passageiro' é o nome da estrutura, representando um passageiro

// Declaração da função que registra o passageiro
void registrarPassageiro();  // Função que registra os dados de um passageiro

#endif
