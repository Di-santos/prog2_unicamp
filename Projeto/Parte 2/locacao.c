#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "locadora.h"
#include "locacao.h"
#include "cliente.h"
#include "veiculo.h"
#include <time.h>

// Fun��o para loca��o de ve�culos
void locacaoVeiculo(struct clientes cliente[], struct veiculos veiculo[], struct locacoes locacao[], int *qnt_cliente, int *qnt_veiculo, int *qnt_locacao, int *qnt_max_locacao){
	int i, j, found, found2;
	char placa[10], cpf[15], dataDev[20], data[20];
	strcpy(data, "");
	
	// Verifica se existe espa�o e aloca caso n�o tenha
	if (*qnt_max_locacao - *qnt_locacao <= 10){
		reallocSizeLocacao(locacao, *qnt_max_locacao + 20);
		(*qnt_max_locacao) = (*qnt_max_locacao) + 20;
	}

	printf("Insira a placa do ve�culo a ser locado: ");
	fflush(stdin);
	gets(placa);

	// Procura o ve�culo
	for (i=0; i<*qnt_veiculo; i++){
		if (strcmp(veiculo[i].placa, placa) == 0){
			found = 1;
			break;
		}
	}

	if (found == 0){
		// N�o encontrou o ve�culo
		clearScreen();
		printf("Ve�culo n�o encontrado\n\n");
	}  else{
		// Encontrou o ve�culo
		if (veiculo[i].state == 0){
			printf("Ve�culo j� se encontra locado\n\n");
		} else{
			// Ve�culo est� dispon�vel
			printf("Insira o CPF do contratante (apenas n�meros): ");
			fflush(stdin);
			gets(cpf);

			// Procura o cliente
			for (j=0; j<*qnt_cliente; j++){
				if (strcmp(cliente[j].cpf, cpf) == 0){
					found2 = 1;
					break;
				}
			}
			if (found2 == 0){
				// N�o encontrou o cliente
				clearScreen();
				printf("Cliente n�o encontrado\n\n");
				
			} else{
				// Encontrou o cliente
				printf("Insira a data de devolu��o (dd/mm/aaaa): ");
				gets(dataDev);
				strcpy(locacao[(*qnt_locacao)].dataDev, dataDev);

				strcpy(veiculo[i].cpfAluguel, cliente[j].cpf);
				locacao[(*qnt_locacao)].id = (*qnt_locacao) + 1;
				locacao[(*qnt_locacao)].tipo = 1;
				strcpy(locacao[(*qnt_locacao)].cpf, cliente[j].cpf);
				strcpy(locacao[(*qnt_locacao)].name, cliente[j].name);
				strcpy(locacao[(*qnt_locacao)].placa, veiculo[i].placa);
				strcpy(locacao[(*qnt_locacao)].marca, veiculo[i].marca);
				strcpy(locacao[(*qnt_locacao)].modelo, veiculo[i].modelo);
				strcpy(locacao[(*qnt_locacao)].telefone, cliente[j].telefone);
				locacao[(*qnt_locacao)].ano = veiculo[i].ano;
				veiculo[i].state = 0;

				// Pega a data atual do sistema e define como data de loca��o
				time_t mytime;
				mytime = time(NULL);
				struct tm tm = *localtime(&mytime);
				snprintf(data, 20, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
				strcpy(locacao[(*qnt_locacao)].data, data);

				(*qnt_locacao)++;
				clearScreen();
				printf("Loca��o efetuada com sucesso\n\n");
			}
		}
	}
}

// Fun��o para devolu��o de ve�culos
void devolucaoVeiculo(struct clientes cliente[], struct veiculos veiculo[], struct locacoes locacao[], int *qnt_cliente, int *qnt_veiculo, int *qnt_locacao, int *qnt_max_locacao){
	int i, j, found, found2;
	char placa[10], cpf[15], dataDev[20], data[20];
	strcpy(data, "");
	
	// Verifica se existe espa�o e aloca caso n�o tenha
	if (*qnt_max_locacao - *qnt_locacao <= 10){
		reallocSizeLocacao(locacao, *qnt_max_locacao + 20);
		(*qnt_max_locacao) = (*qnt_max_locacao) + 20;
	}

	printf("Insira a placa do ve�culo a ser devolvido: ");
	fflush(stdin);
	gets(placa);

	// Procura o ve�culo
	for (i=0; i<*qnt_veiculo; i++){
		if (strcmp(veiculo[i].placa, placa) == 0){
			found = 1;
			break;
		}
	}

	if (found == 0){
		// N�o encontrou o ve�culo
		clearScreen();
		printf("Ve�culo n�o encontrado\n\n");
	}  else{
		if (veiculo[i].state == 1){
			printf("Ve�culo n�o est� locado\n\n");
		} else{
			// Encontrou o ve�culo
			printf("Insira o CPF do contratante (apenas n�meros): ");
			fflush(stdin);
			gets(cpf);

			// Procura o cliente
			for (j=0; j<*qnt_cliente; j++){
				if (strcmp(cliente[j].cpf, cpf) == 0){
					found2 = 1;
					break;
				}
			}
			if (found2 == 0){
				// N�o encontrou o cliente
				clearScreen();
				printf("Cliente n�o encontrado\n\n");
				
			} else{
				// Encontrou o cliente
				// Define os dados da devolu��o
				strcpy(veiculo[i].cpfAluguel, "0");
				locacao[(*qnt_locacao)].id = (*qnt_locacao) + 1;
				locacao[(*qnt_locacao)].tipo = 0;
				strcpy(locacao[(*qnt_locacao)].cpf, cliente[j].cpf);
				strcpy(locacao[(*qnt_locacao)].name, cliente[j].name);
				strcpy(locacao[(*qnt_locacao)].placa, veiculo[i].placa);
				strcpy(locacao[(*qnt_locacao)].marca, veiculo[i].marca);
				strcpy(locacao[(*qnt_locacao)].modelo, veiculo[i].modelo);
				strcpy(locacao[(*qnt_locacao)].telefone, cliente[j].telefone);
				locacao[(*qnt_locacao)].ano = veiculo[i].ano;
				veiculo[i].state = 1;
				strcpy(locacao[(*qnt_locacao)].dataDev, "0");

				// Pega a data atual do sistema e define como data de devolu��o
				time_t mytime;
				mytime = time(NULL);
				struct tm tm = *localtime(&mytime);
				snprintf(data, 20, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
				strcpy(locacao[(*qnt_locacao)].data, data);

				(*qnt_locacao)++;
				clearScreen();
				printf("Devolu��o efetuada com sucesso\n\n");
			}
		}
	}
}

// Fun��o para listar o hist�rico de opera��es
void relatorioLocacao(struct locacoes locacao[], int *qnt_locacao){
	int i;
	clearScreen();

	for (i=0; i<(*qnt_locacao); i++){
		if (locacao[i].tipo == 1){
			printf("Loca��o (id = %d)\n", locacao[i].id);
		} else{
			printf("Devolu��o (id = %d)\n", locacao[i].id);
		}
		printf("%s %s %d\n", locacao[i].marca, locacao[i].modelo, locacao[i].ano);
		printf("Data: %s\n", locacao[i].data);
		printf("CPF: %s\n", locacao[i].cpf);
		printf("Nome: %s (Tel: %s)\n\n", locacao[i].name, locacao[i].telefone);
	}
}
