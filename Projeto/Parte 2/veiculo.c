#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "locadora.h"
#include "locacao.h"
#include "cliente.h"
#include "veiculo.h"

// Fun��o para cadastrar novos ve�culos
void novoVeiculo(struct veiculos veiculo[], int *qnt_veiculo, int *qnt_max_veiculo){
	int i, ano;
	char placa[10], marca[50], modelo[75];

	// Verifica se existe espa�o e aloca caso n�o tenha
	if (*qnt_max_veiculo - *qnt_veiculo <= 10){
		reallocSizeVeiculo(veiculo, *qnt_max_veiculo + 20);
		(*qnt_max_veiculo) = (*qnt_max_veiculo) + 20;
	}

	// Verifica o index a ser cadastrado
	for (i=0; i<*qnt_veiculo; i++){
		if (strcmp(veiculo[i].placa, "0") == 0){
			break;
		}
	}

	// Obtem a placa
	printf("Insira a placa (sem h�fen): ");
	fflush(stdin);
	gets(placa);
	// Verifica a exist�ncia do veiculo
	if (verifyExistVeiculo(veiculo, placa, *qnt_veiculo) == 1){
		clearScreen();
		printf("Ve�culo j� cadastrado\n\n");
	} else{
		// Obtem os dados e cadastra
		strcpy(veiculo[i].placa, placa);

		printf("Insira a marca: ");
		gets(marca);
		strcpy(veiculo[i].marca, marca);

		printf("Insira o modelo: ");
		gets(modelo);
		strcpy(veiculo[i].modelo, modelo);
		
		printf("Insira o ano: ");
		scanf("%d", &veiculo[i].ano);

		veiculo[i].state = 1;
		strcpy(veiculo[i].cpfAluguel, "0");

		(*qnt_veiculo)++;

		clearScreen();
		printf("\n\nVe�culo cadastrado com sucesso\n\n");
	}
}

// Fun��o para excluir um ve�culo
void excluirVeiculo(struct veiculos veiculo[], int *qnt_veiculo, int *qnt_max_veiculo, int *qnt_veiculo_excluido){
	int i;
	int found = 0;
	char placa[10], conf;

	// Obtem a placa
	printf("Insira a placa do ve�culo a ser exclu�do: ");
	fflush(stdin);
	gets(placa);

	// Verifica a exist�ncia do veiculo
	for (i=0; i<*qnt_veiculo; i++){
		if (strcmp(veiculo[i].placa, placa) == 0){
			found = 1;
			break;
		}
	}

	if (found == 0){
		// Ve�culo n�o encontrado
		clearScreen();
		printf("Veiculo n�o encontrado\n\n");
	}  else{
		// Confirma��o de exclus�o
		printf("Tem certeja que deseja excluir o ve�culo de placa %s (S/N): ", veiculo[i].placa);
		scanf(" %c", &conf);
		clearScreen();
		
		if (conf == 'S'){
			strcpy(veiculo[i].placa, "0");
			printf("\n\nVe�culo exclu�do com sucesso\n\n");
			(*qnt_veiculo)--; 
			(*qnt_veiculo_excluido)++;
		} else{
			printf("\n\nOpera��o cancelada\n\n");
		}
	}
}

// Fun��o para consultar um ve�culo
void consultarVeiculo(struct veiculos veiculo[], int *qnt_veiculo, int *qnt_max_veiculo, int *qnt_cliente, int *qnt_max_cliente, struct clientes cliente[]){
	int i, j;
	int found = 0;
	char placa[10];

	// Obtem a placa
	printf("Insira a placa do ve�culo a ser exibido: ");
	fflush(stdin);
	gets(placa);

	// Verifica a exist�ncia do ve�culo
	for (i=0; i<*qnt_veiculo; i++){
		if (strcmp(veiculo[i].placa, placa) == 0){
			found = 1;
			break;
		}
	}

	if (found == 0){
		clearScreen();
		printf("Ve�culo n�o encontrado\n\n");
	}  else{
		printf("\n\nMarca: %s\n", veiculo[i].marca);
		printf("Modelo: %s\n", veiculo[i].modelo);
		printf("Ano: %d\n", veiculo[i].ano);
		printf("Placa: %s\n", veiculo[i].placa);
		if (veiculo[i].state == 1){
			printf("Estado: Dispon�vel\n\n");
		} else{
			printf("Estado: Alugado\n");
			printf("\nDados do Contratante:\n");
			for (j=0; j<*qnt_cliente; j++){
				if (strcmp(cliente[j].cpf, veiculo[i].cpfAluguel) == 0){
					printf("Nome: %s\n", cliente[j].name);
					printf("CPF: %s\n", cliente[j].cpf);
					printf("CNH: %s\n", cliente[j].cnh);
					printf("Telefone: %s\n\n", cliente[j].telefone);
					break;
				}
			}
		}
	}
}

// Fun��o para listar todos os ve�culos
void listarVeiculo(struct veiculos veiculo[], int *qnt_veiculo){
	int i;
	clearScreen();

	for (i=0; i<(*qnt_veiculo); i++){
		if (strlen(veiculo[i].placa) > 2){
			printf("Marca: %s\n", veiculo[i].marca);
			printf("Modelo: %s\n", veiculo[i].modelo);
			printf("Ano: %d\n", veiculo[i].ano);
			printf("Placa: %s\n", veiculo[i].placa);
			if (veiculo[i].state == 1){
				printf("Estado: Dispon�vel\n\n");
			} else{
				printf("Estado: Alugado pelo cliente de CPF: %s\n\n", veiculo[i].cpfAluguel);
			}
		}
	}
}
