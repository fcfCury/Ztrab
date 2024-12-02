#include <iostream>
#include <cstdio>
#include <string>
#include <fstream> // Para manipulação de arquivos

#include "assento.h"

using namespace std;

assento a;
char loop;

bool verificarVoo(int codigoVoo)
{
    ifstream voos("voos.txt");
    if (!voos.is_open())
    {
        cerr << "Erro ao abrir o arquivo voos.txt!" << endl;
        return false;
    }

    string linha;
    while (getline(voos, linha))
    {
        if (linha.find("Codigo: ") != string::npos)
        {
            int codigoArquivo = stoi(linha.substr(8)); // Extrai o código do voo
            if (codigoArquivo == codigoVoo)
            {
                voos.close();
                return true; // Voo encontrado
            }
        }
    }

    voos.close();
    return false; // Voo não encontrado
}

bool verificarAssento(int codigoVoo, int numeroAssento)
{
    ifstream assentos("assentos.txt");
    if (!assentos.is_open())
    {
        cerr << "Erro ao abrir o arquivo assentos.txt!" << endl;
        return false;
    }

    string linha;
    while (getline(assentos, linha))
    {
        if (linha.find("Voo: ") != string::npos)
        {
            int codigoArquivo = stoi(linha.substr(5)); // Extrai o código do voo
            if (codigoArquivo == codigoVoo)
            {
                getline(assentos, linha); // Lê a linha com o número do assento
                if (linha.find("Numero: ") != string::npos)
                {
                    int numeroArquivo = stoi(linha.substr(8)); // Extrai o número do assento
                    if (numeroArquivo == numeroAssento)
                    {
                        assentos.close();
                        return true; // Assento já registrado para o voo
                    }
                }
            }
        }
    }

    assentos.close();
    return false; // Assento não encontrado no voo
}

void registrarAssento()
{
    do
    {
        cin.ignore(); // Ignora o caractere de nova linha restante no buffer

        cout << "Digite o codigo do voo: ";
        scanf("%d", &a.codigo_voo);

        if (!verificarVoo(a.codigo_voo))
        {
            cout << "Erro: O codigo do voo nao existe!" << endl;
            continue;
        }

        cout << "Digite o numero do assento: ";
        scanf("%d", &a.numero);

        if (verificarAssento(a.codigo_voo, a.numero))
        {
            cout << "Erro: O assento ja existe para este voo!" << endl;
            continue;
        }

        ofstream arquivo("assentos.txt", ios::app); // Abre o arquivo em modo append
        if (!arquivo.is_open())
        {
            cerr << "Erro ao abrir o arquivo assentos.txt!" << endl;
            return;
        }

        arquivo << "Voo: " << a.codigo_voo << endl;
        arquivo << "Numero: " << a.numero << endl;
        arquivo << "Livre" << endl;
        arquivo << "----------------------------------------" << endl;

        arquivo.close();

        cout << "Assento registrado com sucesso!" << endl;
        cout << "Deseja registrar outro assento? (s ou n): ";
        cin >> loop;

    } while (loop == 's');
}
