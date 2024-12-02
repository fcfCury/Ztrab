#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <limits> // Para usar INT_MAX
#include "voo.h"
#include "fc.h" // Incluindo o cabeçalho da função geral

using namespace std;

// Variável global para armazenar os dados do voo
voo v;

/**
 * Verifica se o tripulante com o código e cargo especificados existe no arquivo "tripulantes.txt".
 * 
 * @param codigoTripulante Código do tripulante a ser verificado.
 * @param cargoEsperado Cargo esperado para o tripulante ("piloto", "copiloto", "comissario", etc.).
 * @return true se o tripulante existir e o cargo for correspondente, false caso contrário.
 */
bool verificarTripulante(int codigoTripulante, const string& cargoEsperado) {
    ifstream arquivo("tripulantes.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo tripulantes.txt!" << endl;
        return false;
    }

    string linha;
    int codigoLido;
    string cargoLido;

    while (getline(arquivo, linha)) {
        if (linha.find("Codigo: ") != string::npos) {
            codigoLido = stoi(linha.substr(8)); // Extrai o código do tripulante
        }

        if (linha.find("Cargo: ") != string::npos) {
            cargoLido = linha.substr(7); // Extrai o cargo do tripulante
        }

        // Verifica se o código e o cargo correspondem
        if (codigoLido == codigoTripulante && cargoLido == cargoEsperado) {
            arquivo.close();
            return true; // Tripulante válido
        }
    }

    arquivo.close();
    return false; // Tripulante não encontrado ou cargo incompatível
}

void registraVoo() {
    cin.ignore(); // Limpa o buffer de entrada

    // Valida a data do voo
    do {
        cout << "Digite a data do voo (formato: DD/MM/AAAA): ";
        getline(cin, v.data);
        if (!validaData(v.data)) {
            cout << "Data invalida. Tente novamente.\n";
        }
    } while (!validaData(v.data));

    // Valida o horário do voo
    do {
        cout << "Digite a hora do voo (formato: HH:MM): ";
        getline(cin, v.hora);
        if (!validaHorario(v.hora)) {
            cout << "Horario invalido. Tente novamente.\n";
        }
    } while (!validaHorario(v.hora));

    // Coleta a origem e destino
    cout << "Digite a origem do voo: ";
    getline(cin, v.origem);

    cout << "Digite o destino do voo: ";
    getline(cin, v.destino);

    // Código do avião
    cout << "Digite o codigo do aviao: ";
    cin >> v.codigo_aviao;

    // Valida piloto
    do {
        cout << "Digite o codigo do piloto: ";
        cin >> v.codigo_piloto;
        if (!verificarTripulante(v.codigo_piloto, "piloto")) {
            cout << "Piloto inválido. Verifique o código ou cargo e tente novamente.\n";
        }
    } while (!verificarTripulante(v.codigo_piloto, "piloto"));

    // Valida copiloto
    do {
        cout << "Digite o codigo do copiloto: ";
        cin >> v.codigo_copiloto;
        if (v.codigo_copiloto == v.codigo_piloto) {
            cout << "O copiloto não pode ser o mesmo que o piloto.\n";
            continue;
        }
        if (!verificarTripulante(v.codigo_copiloto, "piloto")) {
            cout << "Copiloto inválido. Verifique o código ou cargo e tente novamente.\n";
        }
    } while (v.codigo_copiloto == v.codigo_piloto || !verificarTripulante(v.codigo_copiloto, "piloto"));

    // Valida comissário
    do {
        cout << "Digite o codigo do comissario: ";
        cin >> v.codigo_comissario;
        if (v.codigo_comissario == v.codigo_piloto || v.codigo_comissario == v.codigo_copiloto) {
            cout << "O comissário não pode ter o mesmo código que o piloto ou copiloto.\n";
            continue;
        }
        if (!verificarTripulante(v.codigo_comissario, "comissario")) {
            cout << "Comissário inválido. Verifique o código ou cargo e tente novamente.\n";
        }
    } while (v.codigo_comissario == v.codigo_piloto || 
             v.codigo_comissario == v.codigo_copiloto || 
             !verificarTripulante(v.codigo_comissario, "comissario"));

    // Define o código do voo e o status
    v.codigo = obterUltimoCodigo("voos.txt") + 1;
    v.status = (v.codigo_piloto && v.codigo_copiloto) ? "Ativo" : "Inativo";

    // Solicita a tarifa
    cout << "Digite a tarifa do voo: ";
    cin >> v.tarifa;

    // Registra no arquivo "voos.txt"
    ofstream arquivo("voos.txt", ios::app);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo voos.txt!" << endl;
        return;
    }

    // Sequência de escrita ajustada
    arquivo << "Data: " << v.data << endl;
    arquivo << "Hora: " << v.hora << endl;
    arquivo << "Origem: " << v.origem << endl;
    arquivo << "Destino: " << v.destino << endl;
    arquivo << "CodigAviao: " << v.codigo_aviao << endl;
    arquivo << "CodigPiloto: " << v.codigo_piloto << endl;
    arquivo << "CodigCopiloto: " << v.codigo_copiloto << endl;
    arquivo << "CodigoComissario: " << v.codigo_comissario << endl;
    arquivo << "Status: " << v.status << endl;
    arquivo << "Codigo: " << v.codigo << endl; // Código do voo antes da tarifa
    arquivo << "Tarifa: " << v.tarifa << endl; // Tarifa vem por último
    arquivo << "----------------------------------------" << endl;

    arquivo.close();
    cout << "[O código do voo é: " << v.codigo << " Lembre-se dele!]\n";
}
