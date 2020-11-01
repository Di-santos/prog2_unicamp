#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "locadora.h"
#include "locacao.h"
#include "cliente.h"
#include "veiculo.h"

// Fun��o para cadastrar novos clientes
void novoCliente(struct clientes cliente[], int *qnt_cliente, int *qnt_max_cliente){
	int i;
	char cpf[15], name[100], cnh[15], telefone[20];

	// Verifica se existe espa�o e aloca caso n�o tenha
	if (*qnt_max_cliente - *qnt_cliente <= 10){
		reallocSizeCliente(cliente, *qnt_max_cliente + 20);
		(*qnt_max_cliente) = (*qnt_max_cliente) + 20;
	}

	// Verifica o index a ser cadastrado
	for (i=0; i<*qnt_cliente; i++){
		if (strcmp(cliente[i].cpf, "0") == 0){
			break;
		}
	}

	// Obtem o CPF
	printf("Insira o CPF (apenas n�meros): ");
	fflush(stdin);
	gets(cpf);
	// Verifica a exist�ncia do cliente
	if (verifyExistCliente(cliente, cpf, *qnt_cliente) == 1){
		// Cliente j� est� cadastrado
		clearScreen();
		printf("Cliente j� cadastrado\n\n");
	} else{
		// Cliente n�o est� cadastrado
		// Coleta os dados e armazena
		strcpy(cliente[i].cpf, cpf);

		printf("Insira o nome: ");
		gets(name);
		strcpy(cliente[i].name, name);

		printf("Insira a CNH (apenas n�meros): ");
		gets(cnh);
		strcpy(cliente[i].cnh, cnh);
		
		printf("Insira o telefone (apenas n�meros): ");
		gets(telefone);
		strcpy(cliente[i].telefone, telefone);

		(*qnt_cliente)++;

		clearScreen();
		printf("\n\nCliente cadastrado com sucesso\n\n");
	}
}

// Fun��o para editar clientes
void editarCliente(struct clientes cliente[], int *qnt_cliente, int *qnt_max_cliente){
	int i;
	int found = 0;
	char cpf[15], name[100], cnh[15], telefone[20];

	// Obtem o CPF
	printf("Insira o CPF do cliente a ser alterado: ");
	fflush(stdin);
	gets(cpf);

	// Verifica a exist�ncia do cliente
	for (i=0; i<*qnt_cliente; i++){
		if (strcmp(cliente[i].cpf, cpf) == 0){
			found = 1;
			break;
		}
	}

	// Altera os dados do cliente ou exibe o erro
	if (found == 0){
		clearScreen();
		printf("Cliente n�o encontrado\n\n");
	}  else{
		strcpy(cliente[i].cpf, cpf);

		printf("Insira o nome: ");
		gets(name);
		strcpy(cliente[i].name, name);

		printf("Insira a CNH (apenas numeros): ");
		gets(cnh);
		strcpy(cliente[i].cnh, cnh);
		
		printf("Insira o telefone (apenas numeros): ");
		gets(telefone);
		strcpy(cliente[i].telefone, telefone);

		clearScreen();
		printf("\n\nCliente alterado com sucesso\n\n");
	}
}

// Fun��o para excluir um cliente
void excluirCliente(struct clientes cliente[], int *qnt_cliente, int *qnt_max_cliente, int *qnt_cliente_excluido){
	int i;
	int found = 0;
	char cpf[15], conf;

	// Obtem o CPF
	printf("Insira o CPF do cliente a ser exclu�do: ");
	fflush(stdin);
	gets(cpf);

	// Verifica a exist�ncia do cliente
	for (i=0; i<*qnt_cliente; i++){
		if (strcmp(cliente[i].cpf, cpf) == 0){
			found = 1;
			break;
		}
	}

	if (found == 0){
		// Cliente n�o encontrado
		clearScreen();
		printf("Cliente n�o encontrado\n\n");
	}  else{
		// Confirma��o adicional
		printf("Tem certeja que deseja excluir o cliente de CPF %s (S/N): ", cliente[i].cpf);
		scanf(" %c", &conf);
		clearScreen();
		
		if (conf == 'S'){
			strcpy(cliente[i].cpf, "0");
			printf("\n\nCliente excluido com sucesso\n\n");
			(*qnt_cliente)--; 
			(*qnt_cliente_excluido)++;
		} else{
			printf("\n\nOperação cancelada\n\n");
		}
	}
}

// Fun��o para consultar o cliente
void consultarCliente(struct clientes cliente[], struct veiculos veiculo[] ,int *qnt_cliente, int *qnt_max_cliente, int *qnt_veiculo, int *qnt_max_veiculo){
	int i, j;
	int found2 = 0;
	int found = 0;
	char cpf[15], name[100], cnh[15], telefone[20];

	// Obtem o CPF
	printf("Insira o CPF do cliente a ser consultado: ");
	fflush(stdin);
	gets(cpf);

	// Verifica a exist�ncia do cliente
	for (i=0; i<*qnt_cliente; i++){
		if (strcmp(cliente[i].cpf, cpf) == 0){
			found = 1;
			break;
		}
	}

	if (found == 0){
		// Cliente n�o encontrado
		clearScreen();
		printf("Cliente n�o encontrado\n\n");
	} else{
		// Exibe os dados do cliente
		printf("Nome: %s\n", cliente[i].name);
		printf("CPF: %s\n", cliente[i].cpf);
		printf("CNH: %s\n", cliente[i].cnh);
		printf("Telefone: %s\n", cliente[i].telefone);
			
		// Procura e exibe os dados das loca��es do cliente (se houver)
		for (j=0; j<*qnt_veiculo; j++){
			if (strcmp(veiculo[j].cpfAluguel, cpf) == 0){
				found2++;
				if (found2 == 1){
					printf("\nO cliente possui os seguintes ve�culos alugados:\n");
				}
				printf(" - %s %s %d\n", veiculo[j].marca, veiculo[j].modelo, veiculo[j].ano);
			}
		}
		if (found2 == 0){
			printf("O cliente n�o possui ve�culos alugados");
		}
		printf("\n\n");
	}
}

// Fun��o para listar todos clientes
void listarCliente(struct clientes cliente[], int *qnt_cliente){
	int i;
	clearScreen();

	for (i=0; i<(*qnt_cliente); i++){
		if (strlen(cliente[i].cpf) > 2){
			printf("Nome: %s\n", cliente[i].name);
			printf("CPF: %s\n", cliente[i].cpf);
			printf("CNH: %s\n", cliente[i].cnh);
			printf("Telefone: %s\n\n", cliente[i].telefone);	
		}
	}
}
