#include "fc.h"

#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <limits.h> // Para o valor INT_MAX
#include <sstream>
#include <regex>
#include <string>

using namespace std;

/*
 * Função: validaTelefone
 * Objetivo: Validar o formato de um número de telefone fornecido pelo usuário.
 *
 * Entradas:
 * - telefone (string): O número de telefone a ser validado. O telefone deve ser fornecido no formato (XX)XXXXXXXXX.
 *
 * Saídas:
 * - Retorna 0 se o telefone for válido.
 * - Retorna 1 se o telefone for inválido (quando o formato ou conteúdo não estiver correto).
 *
 * Descrição:
 * Esta função valida se o número de telefone fornecido segue as seguintes regras:
 * 1. Deve começar com um parêntese '(' e terminar com ')'.
 * 2. O código de área (dois primeiros dígitos após '(') deve conter apenas números.
 * 3. Não deve conter espaços ou letras.
 * 4. O número de telefone deve ter entre 8 e 9 dígitos após o código de área.
 *
 * A função retorna 0 se todas as condições forem atendidas, caso contrário, retorna 1 e exibe uma mensagem de erro.
 */
int validaTelefone(std::string &telefone)
{
    cout << "Digite o telefone no formato (XX)XXXXXXXXX: ";
    getline(cin, telefone); // Lê o número de telefone do usuário

    // Verifica o formato: deve começar com '(' e ter ')'
    if (telefone[0] != '(' || telefone[3] != ')')
    {
        cout << "Formato invalido, comece com parenteses.\n";
        return 1; // Retorna 1 se o formato estiver errado
    }

    // Verifica se o código de área são números
    if (!isdigit(telefone[1]) || !isdigit(telefone[2]))
    {
        cout << "O codigo de area deve conter apenas numeros.\n";
        return 1; // Retorna 1 se o código de área não for numérico
    }

    // Verifica espaços extras ou caracteres inválidos
    for (char c : telefone)
    {
        if (isspace(c)) // Se encontrar espaços, retorna erro
        {
            cout << "O telefone não pode conter espaços.\n";
            return 1;
        }
        if (isalpha(c)) // Se encontrar letras, retorna erro
        {
            cout << "O telefone nao pode conter letras.\n";
            return 1;
        }
    }

    // Verifica se o número tem entre 8 e 9 dígitos após o código de área
    int count = 0;
    for (size_t i = 4; i < telefone.size(); i++) // A partir do índice 4, conta os dígitos
    {
        if (isdigit(telefone[i]))
            count++; // Conta quantos dígitos são encontrados
    }

    if (count < 8 || count > 9) // Verifica se o número tem entre 8 e 9 dígitos
    {
        cout << "O numero de telefone deve ter entre 8 e 9 digitos.\n";
        return 1; // Retorna 1 se o número de telefone for inválido
    }

    return 0; // Retorna 0 se o telefone for válido
}

/*
 * Função: obterUltimoCodigo
 * Objetivo: Obter o último número presente em um arquivo, independentemente do formato.
 *
 * Entradas:
 * - nomeArquivo (string): O nome do arquivo que será lido.
 *
 * Saídas:
 * - Retorna o último número encontrado no arquivo (int).
 * - Retorna 0 se o arquivo não puder ser aberto.
 *
 * Descrição:
 * A função lê o arquivo linha por linha, procurando a palavra "Codigo: ". Quando encontrada,
 * extrai o número que aparece em seguida e armazena como o último código encontrado.
 *
 * Exemplo de uso:
 * - Se o arquivo contiver as linhas:
 *   ```
 *   Nome: João
 *   Codigo: 42
 *   Codigo: 56
 *   ```
 *   A função retornará 56.
 */
int obterUltimoCodigo(const string &nomeArquivo)
{
    ifstream arquivo(nomeArquivo); // Abre o arquivo para leitura

    if (!arquivo.is_open())
    { // Verifica se o arquivo foi aberto corretamente
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 0; // Retorna 0 se o arquivo não pôde ser aberto
    }

    string linha;
    int ultimoCodigo = 0; // Variável para armazenar o último código encontrado

    // Lê o arquivo linha por linha
    while (getline(arquivo, linha))
    {
        // Verifica se a linha contém a palavra "Codigo: "
        size_t pos = linha.find("Codigo: ");
        if (pos != string::npos)
        {
            // Encontra a posição do número após "Codigo: "
            stringstream ss(linha.substr(pos + 8)); // Substring após "Codigo: "
            int numero;
            ss >> numero; // Extrai o número

            // Atualiza o último código encontrado
            ultimoCodigo = numero;
        }
    }

    arquivo.close(); // Fecha o arquivo após a leitura

    return ultimoCodigo; // Retorna o último código encontrado
}

/*
 * Função: validaData
 * Objetivo: Validar o formato e a validade de uma data fornecida no formato DD/MM/AAAA.
 *
 * Entradas:
 * - data (string): A data a ser validada.
 *
 * Saídas:
 * - Retorna true se a data for válida.
 * - Retorna false se a data for inválida.
 *
 * Descrição:
 * Esta função verifica se a data segue o formato DD/MM/AAAA e se os valores de dia, mês
 * e ano são válidos. Também considera anos bissextos para fevereiro.
 */
bool validaData(const string &data)
{
    // Usa uma expressão regular para verificar o formato DD/MM/AAAA.
    regex formato("\\d{2}/\\d{2}/\\d{4}");
    if (!regex_match(data, formato))
    {                 // Verifica se a data corresponde ao formato.
        return false; // Retorna falso se o formato estiver incorreto.
    }

    // Extrai o dia, mês e ano da string.
    int dia = stoi(data.substr(0, 2)); // Extrai os dois primeiros caracteres como dia.
    int mes = stoi(data.substr(3, 2)); // Extrai os dois caracteres após '/' como mês.
    int ano = stoi(data.substr(6, 4)); // Extrai os últimos quatro caracteres como ano.

    // Verifica se o mês está entre 1 e 12.
    if (mes < 1 || mes > 12)
    {
        return false; // Retorna falso se o mês for inválido.
    }

    // Define o número de dias em cada mês (não considerando anos bissextos).
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // Ajusta o número de dias de fevereiro se for um ano bissexto.
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
    {
        diasPorMes[1] = 29;
    }
    // Verifica se o dia está dentro do intervalo válido para o mês.
    if (dia < 1 || dia > diasPorMes[mes - 1])
    {
        return false; // Retorna falso se o dia for inválido.
    }

    return true; // Retorna verdadeiro se a data for válida.
}

/*
 * Função: validaHorario
 * Objetivo: Validar o formato de um horário fornecido no formato HH:MM.
 *
 * Entradas:
 * - horario (string): O horário a ser validado.
 *
 * Saídas:
 * - Retorna true se o horário for válido.
 * - Retorna false se o horário for inválido.
 *
 * Descrição:
 * Esta função verifica se o horário segue o formato HH:MM, onde HH representa as horas
 * (de 0 a 23) e MM representa os minutos (de 0 a 59).
 */
bool validaHorario(const string &horario)
{
    regex formato("\\d{2}:\\d{2}"); // Usa uma expressão regular para verificar o formato HH:MM.
    if (!regex_match(horario, formato))
    {                 // Verifica se o horário corresponde ao formato.
        return false; // Retorna falso se o formato estiver incorreto.
    }

    // Extrai as horas e minutos da string.
    int horas = stoi(horario.substr(0, 2));   // Extrai os dois primeiros caracteres como horas.
    int minutos = stoi(horario.substr(3, 2)); // Extrai os dois últimos caracteres como minutos.

    if (horas < 0 || horas > 23 || minutos < 0 || minutos > 59)
    {                 // Verifica se as horas estão no intervalo de 0 a 23 e se os minutos estão no intervalo de 0 a 59..
        return false; // Retorna falso se as horas forem inválidas.
    }

    return true;
}
