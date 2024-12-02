#include <iostream>
#include <cstdio>
#include <string>
#include <cctype>
#include <cstring>
#include <fstream>
#include <sstream>
#include <queue> // Para usar std::queue

#include "pesquisa.h"

using namespace std;

string idPesquisa;

void pesquisarPassageiro()
{
    cin.ignore(); // Ignora o caractere de nova linha restante no buffer
    printf("Escreva o nome ou o codigo do passageiro:\n");
    getline(cin, idPesquisa); // Lê uma linha inteira, permitindo espaços

    // Verifica se a entrada contém apenas números
    bool isNumero = true;
    for (char c : idPesquisa)
    {
        if (!isdigit(c))
        {
            isNumero = false;
            break;
        }
    }

    if (isNumero)
    {
        // Se for um número, podemos convertê-lo para int
        int codigo = stoi(idPesquisa); // Converte a string para inteiro

        // Abrir o arquivo onde os dados dos passageiros estão armazenados
        ifstream arquivo("passageiros.txt");

        if (!arquivo.is_open()) {
            cout << "Erro ao abrir o arquivo." << endl;
            return;
        }

        string linha;
        bool encontrado = false;

        // Fila para armazenar as últimas 5 linhas
        queue<string> ultimasLinhas;

        // Percorrer o arquivo linha por linha
        while (getline(arquivo, linha)) {
            // Adicionar a linha atual à fila
            ultimasLinhas.push(linha);

            // Se a fila exceder 5 elementos, remover o mais antigo
            if (ultimasLinhas.size() > 6) {
                ultimasLinhas.pop();
            }

            // Verificar se a linha contém o codigo
            if (linha.find("Codigo: ") != string::npos) {
                // Extrair o codigo da linha
                int codigoRegistro = stoi(linha.substr(8)); // Converte o codigo para int

                // Se o codigo do arquivo for igual ao codigo pesquisado
                if (codigoRegistro == codigo) { 
                    encontrado = true;

                    // Imprimir as informações das 5 linhas anteriores
                    cout << "\nPassageiro encontrado:" << endl;
                    while (!ultimasLinhas.empty()) {
                        cout << ultimasLinhas.front() << endl;
                        ultimasLinhas.pop();
                    }

                    // Continuar imprimindo as linhas a partir da próxima
                    while (getline(arquivo, linha) && linha != "----------------------------------------") {
                        cout << linha << endl;
                    }

                    // Imprimir o separador final
                    cout << "----------------------------------------" << endl;
                    break;
                }
            }
        }

        if (!encontrado) {
            cout << "Passageiro com o codigo " << codigo << " não encontrado." << endl;
        }

        arquivo.close(); // Fecha o arquivo após a pesquisa
    }
    else
    {
        // Caso contrário, trata-se de um nome ou string

        // Abrir o arquivo onde os dados dos passageiros estão armazenados
        ifstream arquivo("passageiros.txt");

        if (!arquivo.is_open()) {
            cout << "Erro ao abrir o arquivo." << endl;
            return;
        }

        string linha;
        bool encontrado = false;

        // Percorrer o arquivo linha por linha
        while (getline(arquivo, linha)) {
            // Verificar se a linha contém o nome
            if (linha.find(idPesquisa) != string::npos) {
                encontrado = true;

                // Imprimir as informações do passageiro
                do {
                    cout << linha << endl;
                } while (getline(arquivo, linha) && linha != "----------------------------------------");

                break;
            }
        }

        if (!encontrado) {
            cout << "Passageiro com o nome " << idPesquisa << " não encontrado." << endl;
        }

        arquivo.close(); // Fecha o arquivo após a pesquisa
    }
}

void pesquisarTripulacao()
{
   cin.ignore(); // Ignora o caractere de nova linha restante no buffer
    printf("Escreva o nome ou o codigo do tripulante:\n");
    getline(cin, idPesquisa); // Lê uma linha inteira, permitindo espaços

    // Verifica se a entrada contém apenas números
    bool isNumero = true;
    for (char c : idPesquisa)
    {
        if (!isdigit(c))
        {
            isNumero = false;
            break;
        }
    }

    if (isNumero)
    {
        // Se for um número, podemos convertê-lo para int
        int codigo = stoi(idPesquisa); // Converte a string para inteiro

        // Abrir o arquivo onde os dados dos passageiros estão armazenados
        ifstream arquivo("tripulantes.txt");

        if (!arquivo.is_open()) {
            cout << "Erro ao abrir o arquivo." << endl;
            return;
        }

        string linha;
        bool encontrado = false;

        // Fila para armazenar as últimas 5 linhas
        queue<string> ultimasLinhas;

        // Percorrer o arquivo linha por linha
        while (getline(arquivo, linha)) {
            // Adicionar a linha atual à fila
            ultimasLinhas.push(linha);

            // Se a fila exceder 5 elementos, remover o mais antigo
            if (ultimasLinhas.size() > 4) {
                ultimasLinhas.pop();
            }

            // Verificar se a linha contém o codigo
            if (linha.find("Codigo: ") != string::npos) {
                // Extrair o codigo da linha
                int codigoRegistro = stoi(linha.substr(8)); // Converte o codigo para int

                // Se o codigo do arquivo for igual ao codigo pesquisado
                if (codigoRegistro == codigo) { 
                    encontrado = true;

                    // Imprimir as informações das 3 linhas anteriores
                    cout << "\nTripulante encontrado:" << endl;
                    while (!ultimasLinhas.empty()) {
                        cout << ultimasLinhas.front() << endl;
                        ultimasLinhas.pop();
                    }

                    // Continuar imprimindo as linhas a partir da próxima
                    while (getline(arquivo, linha) && linha != "----------------------------------------") {
                        cout << linha << endl;
                    }

                    // Imprimir o separador final
                    cout << "----------------------------------------" << endl;
                    break;
                }
            }
        }

        if (!encontrado) {
            cout << "Tripulante com o codigo " << codigo << " não encontrado." << endl;
        }

        arquivo.close(); // Fecha o arquivo após a pesquisa
    }
    else
    {
        // Caso contrário, trata-se de um nome ou string

        // Abrir o arquivo onde os dados dos passageiros estão armazenados
        ifstream arquivo("tripulantes.txt");

        if (!arquivo.is_open()) {
            cout << "Erro ao abrir o arquivo." << endl;
            return;
        }

        string linha;
        bool encontrado = false;

        // Percorrer o arquivo linha por linha
        while (getline(arquivo, linha)) {
            // Verificar se a linha contém o nome
            if (linha.find(idPesquisa) != string::npos) {
                encontrado = true;

                // Imprimir as informações do passageiro
                do {
                    cout << linha << endl;
                } while (getline(arquivo, linha) && linha != "----------------------------------------");

                break;
            }
        }

        if (!encontrado) {
            cout << "Tripulante com o nome " << idPesquisa << " não encontrado." << endl;
        }

        arquivo.close(); // Fecha o arquivo após a pesquisa
    }
}
