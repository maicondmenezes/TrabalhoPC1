#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char *ArquivoDeLog;

struct tm *DataAtual; //estrutura para armazenar data e hora.
time_t Segundos;

void apagaLinha(void){
	printf("\n%c[%d;%df",0x1B,15,01);
	printf("                                                                                ");
	printf("%c[%d;%dm%c[%dm",27,40,31,27,0);
	printf("\n%c[%d;%df",0x1B,15,01);	
}

char *ObtemStrHora(void){
    char *BuffHorario = "00-00-00"; //define um tamanho de 8 bytesà variável;
    time(&Segundos); //obtém a hora em segundos.
    DataAtual = localtime(&Segundos); //ajusta o fuso horário.
    sprintf(BuffHorario,"%02d-%02d-%02d", DataAtual->tm_hour, DataAtual->tm_min, DataAtual->tm_sec);
    return(BuffHorario); //retorna uma strind da data atual.
}

char *ObtemStrData(void){
    char *BuffData = "00-00-0000";  //define um tamanho de 8 bytesà variável;
    time(&Segundos); //obtém a hora em segundos.
    DataAtual = localtime(&Segundos); //ajusta o fuso horário.
    sprintf(BuffData,"%02d-%02d-%04d", DataAtual->tm_mday, DataAtual->tm_mon+1, DataAtual->tm_year+1900);
    return(BuffData); //retorna uma strind da data atual.
}

void AbrirArquivoLog(char *NomeArquivoLog){
	FILE *ArquivoLog;
	
	if((ArquivoLog=fopen(NomeArquivoLog, "w"))==NULL){
		apagaLinha();
		printf("Não foi possivel criar o arquivo %s", NomeArquivoLog);
		return;
	}	
}

char MenuPrincipal(void) {
	char opcao;
	int i;
	do {
		printf("\e[H\e[2J");
		printf("\n %c[%d;%df",0x1B,1,1);
				
		//Abrir -> Chama a função MenuAbrir
		printf("%c[%d;%dm | A%c[%dm",27,40,32,27,0);
		printf("%c[%d;%dmbrir%c[%dm",27,40,33,27,0);
		//Entrar -> Chama a função EstacionarCarro
		printf("%c[%d;%dm | E%c[%dm",27,40,32,27,0);
		printf("%c[%d;%dmntrar%c[%dm",27,40,33,27,0);
		//Pesquisar -> Chama a função PesquisarVaga
		printf("%c[%d;%dm | P%c[%dm",27,40,32,27,0);
		printf("%c[%d;%dmesquisar%c[%dm",27,40,33,27,0);
        //Sair -> Chama a função RetirarCarro 
		printf("%c[%d;%dm | S%c[%dm",27,40,32,27,0);
		printf("%c[%d;%dmair%c[%dm",27,40,33,27,0);
        //Salvar -> Chama a função SalvarCarros e SalvarVagas 
		printf("%c[%d;%dm | Sa%c[%dm",27,40,33,27,0);
		printf("%c[%d;%dml%c[%dm",27,40,32,27,0);
		printf("%c[%d;%dmvar%c[%dm",27,40,33,27,0);
		//Relatórios -> Chama a função MenuRelatorios
		printf("%c[%d;%dm | R%c[%dm",27,40,32,27,0);
		printf("%c[%d;%dmelatorios%c[%dm",27,40,33,27,0);
        //Fim
		printf("%c[%d;%dm | F%c[%dm",27,40,32,27,0);
		printf("%c[%d;%dmim |%c[%dm\n",27,40,33,27,0);
		
		printf("-- Veiculos em Espera--\n");
		printf("%c[%d;%dm | chassi |      modelo do veî¤µlo         |    peso   |  altura  |  largura  | comprimento |%c[%dm\n",27,4,33,27,0);
	    printf("%c[%d;%dm%c[%dm",27,40,31,27,5);
		for(i=0;i<10;i++){
			printf(" | %-6u | %-30s | %9.2f | %8.2f | %9.2f | %11.2f |\n", 0, "vazio",0.0,0.0,0.0,0.0);
		}
		
		printf("\n%c[%d;%dm%c[%dm",27,40,31,27,0);
		printf("Digite uma das letras em destaque do menu acima:");
		printf("\n%c[%d;%dm%c[%dm",27,40,31,27,0);
		printf("-- Vagas Livres--\n");
		printf("%c[%d;%dm | ID  | Peso Maximo | Altura Maxima | Largura Maxima | Comprimento Maximo |%c[%dm\n",27,4,33,27,0);
	    printf("%c[%d;%dm%c[%dm",27,40,31,27,5);
	    for(i=0;i<10;i++){
			printf(" | %3d | %11.2f | %13.2f | %14.2f | %18.2f |\n", 0,0.0,0.0,0.0,0.0);
		}
		
		printf("\n%c[%d;%df",0x1B,15,49);
		printf("%c[%d;%dm%c[%dm",27,40,31,27,0);
		scanf("%c", &opcao);
		
	} while(opcao!='a' && opcao!='e'&& opcao!='p' && opcao!='s' &&
	        opcao!='l' && opcao!='r' && opcao!='f');
	
	getchar();
	
	return opcao;
}

char MenuAbrir(void){
	char opcao;
	
	do{
		apagaLinha();
		printf("Nova Simulação (n) | Simulação Salva (s):");
		scanf("%c", &opcao);
		
	} while(opcao!='n' && opcao!='s');
	getchar();
	return opcao;
}

char MenuRelatorios(void){
	char opcao;
	
	do{
		apagaLinha();
		printf("Relatório de Vagas (v) | Relatório de Tipos de Veículos (t) | Relatório de Veículos Estacionados (e):");
		scanf("%c", &opcao);
		
	} while(opcao!='v' && opcao!='t' && opcao!='e');
	getchar();
	return opcao;
}
