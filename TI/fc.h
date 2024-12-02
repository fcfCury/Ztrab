#ifndef FC_H
#define FC_H

#include <string> // Para usar std::string

using namespace std;

  
// Declaração da função para validar o telefone
// A função recebe uma referência para uma string (telefone) e retorna um inteiro
// indicando se o telefone é válido ou não. Retorna 0 para inválido e 1 para válido.
// Parâmetro:
//   telefone: uma string que contém o número de telefone a ser validado.
// Retorno:
//   Um inteiro (0 ou 1), onde 1 indica que o telefone é válido e 0 que é inválido.
int validaTelefone(string &telefone);

// Declaração da função para obter o último código de um arquivo
// A função recebe o nome de um arquivo (nomeArquivo) e retorna o último código
// presente no arquivo, que pode ser usado para atribuir um novo código de forma sequencial.
// Parâmetro:
//   nomeArquivo: o nome do arquivo onde o último código será buscado.
// Retorno:
//   O último código encontrado no arquivo (um número inteiro). 
int obterUltimoCodigo(const string &nomeArquivo);

// Função para validar a data no formato DD/MM/AAAA
// A função recebe uma string representando uma data e verifica se está no formato correto.
// Parâmetro:
//   data: uma string que representa a data a ser validada, no formato DD/MM/AAAA.
// Retorno:
//   Um valor booleano (true ou false), onde true indica que a data é válida e false que é inválida.
bool validaData(const string &data);

// Função para validar o horário no formato HH:MM
// A função recebe uma string representando um horário e verifica se está no formato correto.
// Parâmetro:
//   horario: uma string que representa o horário a ser validado, no formato HH:MM.
// Retorno:
//   Um valor booleano (true ou false), onde true indica que o horário é válido e false que é inválido.
bool validaHorario(const string &horario);

#endif // FC_H
