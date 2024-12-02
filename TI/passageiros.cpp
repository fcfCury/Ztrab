#include <iostream>   // Biblioteca para entrada e saída de dados
#include <cstdio>     // Biblioteca para funções de input/output com C
#include <string>     // Biblioteca para manipulação de strings em C++
#include <cctype>     // Biblioteca para funções de verificação de caracteres (como isdigit())
#include <cstring>    // Biblioteca para funções de manipulação de strings C-style (como strlen())
#include <fstream>    // Biblioteca para manipulação de arquivos

// Incluir o cabeçalho para usar a estrutura e a função
#include "fc.h"
#include "passageiros.h"

using namespace std;

// Variável global para armazenar os dados do passageiro
passageiro p; 

/*
 * Função: registrarPassageiro
 * Objetivo: Coletar e registrar os dados de um novo passageiro.
 * 
 * Entradas: Nenhuma
 * Saídas: Nenhuma (os dados são salvos no arquivo "passageiros.txt")
 * 
 * Descrição: 
 * Esta função coleta os seguintes dados de um passageiro:
 * - Nome
 * - Endereço
 * - Telefone (validação feita em uma função separada)
 * - Fidelidade (verifica se o passageiro é fiel, atribuindo pontos)
 * A função também atribui um código único ao passageiro, baseado no último código registrado no arquivo.
 * Após coletar os dados, os mesmos são registrados em um arquivo de texto ("passageiros.txt").
 * O código do passageiro é exibido para que ele se lembre.
 */
void registrarPassageiro()
{
    cin.ignore(); // Limpa o buffer de entrada (necessário após o uso de getline)
    
    // Coleta o nome do passageiro
    cout << "Digite o seu nome: ";
    getline(cin, p.nome);

    // Coleta o endereço do passageiro
    cout << "Digite o seu endereco: ";
    getline(cin, p.endereco);

    // Valida o telefone do passageiro (função externa já definida)
    while (validaTelefone(p.telefone) != 0); // Reutilizando função genérica para validar o telefone

    // Validação para saber se o passageiro é fiel ou não
    do
    {
        cout << "Fidelidade(s/n): ";
        cin >> p.fidelidade;

        // Caso o valor não seja 's'/'S' ou 'n'/'N', pede novamente a entrada
        if (p.fidelidade != 's' && p.fidelidade != 'n' && p.fidelidade != 'S' && p.fidelidade != 'N')
        {
            cout << "Formato inválido, escreva [S] para sim e [N] para não.\n";
        }
    } while (p.fidelidade != 's' && p.fidelidade != 'n' && p.fidelidade != 'S' && p.fidelidade != 'N');

    // Inicializa pontos de fidelidade
    p.pontos_fidelidade = 0;

    // Atribui um código único ao passageiro, baseado no último código registrado
    p.codigo = obterUltimoCodigo("passageiros.txt") + 1; // Reutilizando função genérica para pegar o último código

    // Abre o arquivo "passageiros.txt" no modo de append (acrescentar)
    ofstream arquivo("passageiros.txt", ios::app);
    if (!arquivo)  // Verifica se houve erro ao abrir o arquivo
    {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return;  // Caso haja erro, a função retorna sem continuar
    }

    // Escreve os dados do passageiro no arquivo
    arquivo << "Nome: " << p.nome << endl;
    arquivo << "Endereço: " << p.endereco << endl;
    arquivo << "Telefone: " << p.telefone << endl;
    arquivo << "Fidelidade: " << (p.fidelidade == 's' || p.fidelidade == 'S' ? "Sim" : "Não") << endl;
    arquivo << "Pontos Fidelidade: " << p.pontos_fidelidade << endl;
    arquivo << "Codigo: " << p.codigo << endl;
    arquivo << "----------------------------------------" << endl;

    arquivo.close();  // Fecha o arquivo

    // Exibe o código do passageiro para que ele se lembre
    cout << "[Seu código é: " << p.codigo << " Lembre-se dele!]\n";
}
