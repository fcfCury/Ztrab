#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>

#include "reserva.h"

using namespace std;

reserva r;

void registrarReserva() {
    cin.ignore(); // Limpa o buffer de entrada

    cout << "Digite o codigo do seu voo: ";
    cin >> r.codigo_voo;

    cout << "Digite o numero do seu assento: ";
    cin >> r.numero_assento;

    // Procurar a tarifa do voo no arquivo `voos.txt`
    ifstream voos("voos.txt");
    if (!voos.is_open()) {
        cout << "Erro ao abrir o arquivo voos.txt." << endl;
        return;
    }

    string linha;
    bool vooEncontrado = false;
    int tarifa = 0;

    while (getline(voos, linha)) {
        if (linha.find("Codigo: ") != string::npos) {
            int codigoVoo = stoi(linha.substr(8));
            if (codigoVoo == r.codigo_voo) {
                while (getline(voos, linha)) {
                    if (linha.find("Tarifa: ") != string::npos) {
                        tarifa = stoi(linha.substr(8));
                        vooEncontrado = true;
                        break;
                    }
                }
            }
        }
        if (vooEncontrado) break;
    }
    voos.close();

    if (!vooEncontrado) {
        cout << "Voo não encontrado no arquivo voos.txt." << endl;
        return;
    }

    cout << "O valor da tarifa para este voo é: R$ " << tarifa << endl;

    // Abrir o arquivo `assentos.txt` para atualizar o status do assento
    ifstream assentos("assentos.txt");
    if (!assentos.is_open()) {
        cout << "Erro ao abrir o arquivo assentos.txt." << endl;
        return;
    }

    ofstream tempAssentos("assentos_temp.txt");
    if (!tempAssentos.is_open()) {
        cout << "Erro ao criar o arquivo temporário para assentos." << endl;
        return;
    }

    bool assentoAtualizado = false;

    while (getline(assentos, linha)) {
        tempAssentos << linha << endl;

        if (linha.find("Voo: ") != string::npos) {
            int codigoVoo = stoi(linha.substr(5));
            if (codigoVoo == r.codigo_voo) {
                getline(assentos, linha);
                tempAssentos << linha << endl;

                if (linha.find("Numero: ") != string::npos) {
                    int numeroAssento = stoi(linha.substr(8));
                    if (numeroAssento == r.numero_assento) {
                        getline(assentos, linha);
                        if (linha == "Livre") {
                            tempAssentos << "Ocupado" << endl;
                            assentoAtualizado = true;
                        } else {
                            tempAssentos << linha << endl;
                            cout << "Assento já está ocupado. Escolha outro." << endl;
                            return;
                        }
                        continue;
                    }
                }
            }
        }
    }

    assentos.close();
    tempAssentos.close();

    if (!assentoAtualizado) {
        remove("assentos_temp.txt");
        cout << "Assento não encontrado no voo especificado." << endl;
        return;
    }

    remove("assentos.txt");
    rename("assentos_temp.txt", "assentos.txt");

    cout << "Digite o seu codigo de passageiro: ";
    cin >> r.codigo_passageiro;

    // Atualizar o arquivo `passageiros.txt`
    ifstream passageiros("passageiros.txt");
    if (!passageiros.is_open()) {
        cout << "Erro ao abrir o arquivo passageiros.txt." << endl;
        return;
    }

    ofstream tempPassageiros("passageiros_temp.txt");
    if (!tempPassageiros.is_open()) {
        cout << "Erro ao criar o arquivo temporário para passageiros." << endl;
        return;
    }

    bool passageiroEncontrado = false;

    while (getline(passageiros, linha)) {
        tempPassageiros << linha << endl;

        if (linha.find("Codigo: ") != string::npos) {
            int codigoPassageiro = stoi(linha.substr(8));
            if (codigoPassageiro == r.codigo_passageiro) {
                passageiroEncontrado = true;
                tempPassageiros << "Voo codigo: " << r.codigo_voo << endl;

                string fidelidadeLinha, pontosLinha;
                getline(passageiros, fidelidadeLinha);
                tempPassageiros << fidelidadeLinha << endl;

                if (fidelidadeLinha.find("Fidelidade: Sim") != string::npos) {
                    getline(passageiros, pontosLinha);
                    int pontos = stoi(pontosLinha.substr(18));
                    pontos += 10;
                    tempPassageiros << "Pontos Fidelidade: " << pontos << endl;
                    cout << "Pontos de fidelidade atualizados para o passageiro: " << pontos << endl;
                }
            }
        }
    }

    passageiros.close();
    tempPassageiros.close();

    if (!passageiroEncontrado) {
        remove("passageiros_temp.txt");
        cout << "Passageiro não encontrado." << endl;

        // Reverter reserva do assento
        ifstream revertAssentos("assentos.txt");
        ofstream tempRevert("assentos_temp.txt");

        while (getline(revertAssentos, linha)) {
            tempRevert << linha << endl;

            if (linha.find("Voo: ") != string::npos) {
                int codigoVoo = stoi(linha.substr(5));
                if (codigoVoo == r.codigo_voo) {
                    getline(revertAssentos, linha);
                    tempRevert << linha << endl;

                    if (linha.find("Numero: ") != string::npos) {
                        int numeroAssento = stoi(linha.substr(8));
                        if (numeroAssento == r.numero_assento) {
                            getline(revertAssentos, linha);
                            if (linha == "Ocupado") {
                                tempRevert << "Livre" << endl;
                            } else {
                                tempRevert << linha << endl;
                            }
                            continue;
                        }
                    }
                }
            }
        }

        revertAssentos.close();
        tempRevert.close();
        remove("assentos.txt");
        rename("assentos_temp.txt", "assentos.txt");
        return;
    }

    remove("passageiros.txt");
    rename("passageiros_temp.txt", "passageiros.txt");

    cout << "Reserva registrada com sucesso!" << endl;
}

void baixarReserva() {
    cin.ignore(); // Limpa o buffer de entrada

    cout << "Digite o codigo do seu voo: ";
    cin >> r.codigo_voo;

    cout << "Digite o numero do seu assento: ";
    cin >> r.numero_assento;

    cout << "Digite o seu codigo de passageiro: ";
    cin >> r.codigo_passageiro;

    // Atualizar o arquivo `assentos.txt`
    ifstream assentos("assentos.txt");
    if (!assentos.is_open()) {
        cout << "Erro ao abrir o arquivo assentos.txt." << endl;
        return;
    }

    ofstream tempAssentos("assentos_temp.txt");
    if (!tempAssentos.is_open()) {
        cout << "Erro ao criar o arquivo temporário para assentos." << endl;
        return;
    }

    string linha;
    bool assentoAtualizado = false;

    while (getline(assentos, linha)) {
        tempAssentos << linha << endl;

        if (linha.find("Voo: ") != string::npos) {
            int codigoVoo = stoi(linha.substr(5));
            if (codigoVoo == r.codigo_voo) {
                getline(assentos, linha);
                tempAssentos << linha << endl;

                if (linha.find("Numero: ") != string::npos) {
                    int numeroAssento = stoi(linha.substr(8));
                    if (numeroAssento == r.numero_assento) {
                        getline(assentos, linha);
                        if (linha == "Ocupado") {
                            tempAssentos << "Livre" << endl;
                            assentoAtualizado = true;
                        } else {
                            tempAssentos << linha << endl;
                        }
                        continue;
                    }
                }
            }
        }
    }

    assentos.close();
    tempAssentos.close();

    if (!assentoAtualizado) {
        remove("assentos_temp.txt");
        cout << "Assento não estava ocupado ou não encontrado." << endl;
        return;
    }

    remove("assentos.txt");
    rename("assentos_temp.txt", "assentos.txt");

    // Atualizar o arquivo `passageiros.txt`
    ifstream passageiros("passageiros.txt");
    if (!passageiros.is_open()) {
        cout << "Erro ao abrir o arquivo passageiros.txt." << endl;
        return;
    }

    ofstream tempPassageiros("passageiros_temp.txt");
    if (!tempPassageiros.is_open()) {
        cout << "Erro ao criar o arquivo temporário para passageiros." << endl;
        return;
    }

    bool vooRemovido = false;

    while (getline(passageiros, linha)) {
        tempPassageiros << linha << endl;

        if (linha.find("Codigo: ") != string::npos) {
            int codigoPassageiro = stoi(linha.substr(8));
            if (codigoPassageiro == r.codigo_passageiro) {
                string proximaLinha;
                while (getline(passageiros, proximaLinha)) {
                    if (proximaLinha.find("Voo codigo: ") != string::npos) {
                        int codigoVoo = stoi(proximaLinha.substr(12));
                        if (codigoVoo == r.codigo_voo && !vooRemovido) {
                            vooRemovido = true;
                            continue; // Não escreve esta linha no novo arquivo
                        }
                    }
                    tempPassageiros << proximaLinha << endl;
                }
                break;
            }
        }
    }

    passageiros.close();
    tempPassageiros.close();

    if (!vooRemovido) {
        remove("passageiros_temp.txt");
        cout << "Passageiro ou voo não encontrado." << endl;
        return;
    }

    remove("passageiros.txt");
    rename("passageiros_temp.txt", "passageiros.txt");

    // Consultar o arquivo `voos.txt` para a tarifa
    ifstream voos("voos.txt");
    if (!voos.is_open()) {
        cout << "Erro ao abrir o arquivo voos.txt." << endl;
        return;
    }

    bool vooEncontrado = false;
    int tarifa = 0;

    while (getline(voos, linha)) {
        if (linha.find("Codigo: ") != string::npos) {
            int codigoVoo = stoi(linha.substr(8));
            if (codigoVoo == r.codigo_voo) {
                vooEncontrado = true;

                // Procurar a tarifa dentro do bloco
                while (getline(voos, linha) && linha.find("Codigo: ") == string::npos) {
                    if (linha.find("Tarifa: ") != string::npos) {
                        tarifa = stoi(linha.substr(8));
                        break;
                    }
                }
                break; // Saímos do loop assim que a tarifa é encontrada
            }
        }
    }

    voos.close();

    if (!vooEncontrado) {
        cout << "Voo não encontrado no arquivo voos.txt." << endl;
    } else {
        cout << "O valor da tarifa de R$ " << tarifa << " será devolvido ao passageiro." << endl;
    }

    cout << "Reserva baixada com sucesso." << endl;
}
