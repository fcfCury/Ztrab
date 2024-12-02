#include <iostream>
#include <fstream>
#include <cstring>

#include "tripulacao.h"
#include "fc.h" // Incluindo o arquivo de funções comuns

/*
 * Função: registraTripulacao
 * Objetivo: Registrar os dados de um tripulante em um arquivo de texto.
 * 
 * Entradas: Nenhuma diretamente da função (dados são coletados através do usuário).
 * 
 * Saídas: 
 * - Nenhuma, mas os dados do tripulante são gravados em um arquivo chamado "tripulantes.txt".
 * 
 * Descrição:
 * Esta função coleta e registra as informações de um tripulante, como:
 * 1. Nome
 * 2. Cargo
 * 3. Telefone (validado utilizando a função `validaTelefone` para garantir que o telefone esteja no formato correto).
 * 4. Código (gerado automaticamente com base no último código registrado no arquivo "tripulacao.txt", obtido através da função `obterUltimoCodigo`).
 * 
 * O código do tripulante é então exibido ao usuário para que ele o memorize. Após isso, os dados são salvos em um arquivo de texto, "tripulantes.txt", em formato de texto simples.
 * A função garante que o arquivo seja aberto corretamente para a escrita e que os dados sejam salvos no final do arquivo.
 * 
 * Fluxo da função:
 * 1. O nome e cargo são coletados do usuário.
 * 2. O telefone é validado até que um formato correto seja inserido.
 * 3. O código do tripulante é gerado com base no último código registrado no arquivo "tripulacao.txt".
 * 4. As informações do tripulante são registradas no arquivo "tripulantes.txt".
 * 5. O código do tripulante é exibido para o usuário.
 */

using namespace std;

tripulacao t; // Variável global

void registraTripulacao() {
    cin.ignore();         // Ignora o caractere de nova linha restante no buffer
    cout << "Digite o seu nome: ";
    getline(cin, t.nome); // Lê uma linha inteira, permitindo espaços

    cout << "Digite o seu cargo: ";
    getline(cin, t.cargo); // Lê uma linha inteira, permitindo espaços

    // Reutiliza a função validaTelefone para garantir que o telefone seja válido
    do {
        // Continua pedindo até que o telefone seja válido
    } while (validaTelefone(t.telefone) != 0);

    // Atribuindo o código antes de salvar no arquivo
    t.codigo = obterUltimoCodigo("tripulantes.txt") + 1; // Aqui chamamos a função para pegar o último código e incrementamos.

    // Agora, registrando os dados em um arquivo txt
    ofstream arquivo("tripulantes.txt", ios::app); // Abre o arquivo em modo de append (adicionar no final)

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    // Escreve as informações do tripulante no arquivo
    arquivo << "Nome: " << t.nome << endl;
    arquivo << "Cargo: " << t.cargo << endl;
    arquivo << "Telefone: " << t.telefone << endl;
    arquivo << "Codigo: " << t.codigo << endl;
    arquivo << "----------------------------------------" << endl;

    // Fecha o arquivo
    arquivo.close();

    cout << "[ Seu codigo eh: " << t.codigo << " Lembre-se dele! ]" << endl;
}
