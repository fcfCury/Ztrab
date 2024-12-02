#include <iostream> // Para entrada e saída padrão (cout, cin)
#include <cstdio>   // Para funções de entrada e saída como printf, scanf
#include <string>   // Para usar a classe string do C++
#include <limits>   //Para usar numeric_limits

#include "fc.h"          // Funções gerais para operações como obter o último código
#include "passageiros.h" // Funções para registrar passageiros
#include "tripulacao.h"  // Funções para registrar tripulação
#include "voo.h"         // Funções para registrar voos
#include "assento.h"     // Funções para registrar assentos
#include "pesquisa.h"    // Função para pesquisar passageiros e triulantes
#include "reserva.h"     // Função para registrar uma reserva

using namespace std;

int pesqui,res;

int main()
{
    int menu; // Variável para armazenar a opção do menu escolhida pelo usuário

    do
    {
        // Exibe o menu de opções para o usuário
        printf("\n-------------------------------------\n");
        printf(">> SELECIONE UMA OPCAO! <<"
               "\n[1] (Registrar passageiro);"
               "\n[2] (Registrar tripulacao);"
               "\n[3] (Registrar voo);"
               "\n[4] (Registrar assentos);"
               "\n[5] (Reservar assento);"
               "\n[6] (Pesquisar);"
               "\n[0] (Finalizar cadastro);\n");
        printf("|\nV\n");

        // Lê a opção selecionada pelo usuário
        if (scanf("%d", &menu) != 1) {
            // Se a entrada não for um número válido, limpa o erro e ignora o restante da entrada
            cin.clear(); // Limpa o estado de erro do cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora os caracteres restantes
            cout << "Entrada invalida! Por favor, insira um numero valido.\n";
            continue; // Retorna ao início do loop
        }

        // Exibe a linha separadora após a escolha
        printf("-------------------------------------\n");

        // Processa a escolha do usuário com base no valor de 'menu'
        switch (menu)
        {
        case 1:
            registrarPassageiro(); // Chama a função para registrar um passageiro
            break;

        case 2:
            registraTripulacao(); // Chama a função para registrar a tripulação
            break;

        case 3:
            registraVoo(); // Chama a função para registrar um voo
            break;

        case 4:
            registrarAssento(); // Chama a função para registrar um assento
            break;
        
        case 5:
            printf("reservar(1) ou baixar reserva(2)\n");
            scanf("%d",&res);
            if (res==1)
            {
             registrarReserva(); // Chama a função para registrar uma reserva
            }
            if (res==2){
            baixarReserva();
            }
            else
            printf("escolha invalida");
            break;

        case 6:
            printf("passageiro(1) ou tripulacao(2)\n");
            scanf("%d",&pesqui);
            if (pesqui == 1)
            {
                pesquisarPassageiro();
            }
            else if (pesqui == 2)
            {
                pesquisarTripulacao();
            }
            else
            printf("escolha invalida");
            break;

        case 0:
            // Caso o usuário escolha 0, o programa será finalizado sem ações adicionais
            break;
        }

    } while (menu != 0); // O loop continua até o usuário escolher a opção 0 (finalizar)

    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso
}
