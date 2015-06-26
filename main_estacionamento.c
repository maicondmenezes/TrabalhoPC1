#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include </home/maicon/TrabalhoPC1-master/estlista.h>

int main(void) {
	char escolha, opcao;
	unsigned int chassi, id;
	
	char *ArquivoCarros;
	char *ArquivoVagas;
	char *NomeArquivoLog;
	char *NomeArquivoLocacoes;
	
	ListadeCarros Carros;
	Carros.tamanho=0;
	ListadeVagas Vagas;
	Vagas.tamanho=0;
	ListadeEstacionados Locacoes;
	Locacoes.tamanho=0;
	
	NomeArquivoLog="Estacionamento-00-00-0000-00-00-00.log";
	NomeArquivoLocacoes="Locacoes-00-00-0000-00-00-00.est";
	sprintf(NomeArquivoLog,"Estacionamento-%s-%s.log",ObtemStrData(),ObtemStrHora());
	sprintf(NomeArquivoLocacoes, "Locacoes-%s-%s.est",ObtemStrData(),ObtemStrHora());
	
	//AbrirArquivoLog(NomeArquivoLog);
	
	FILE *ArquivoLog;
	
	if((ArquivoLog=fopen(NomeArquivoLog, "w"))==NULL){
		apagaLinha();
		printf("Não foi possivel criar o arquivo %s", NomeArquivoLog);
	}
	fprintf(ArquivoLog, "%s - %s", ObtemStrData(),ObtemStrHora());
		
	for( ; ; ) {
		escolha = MenuPrincipal();
		switch(escolha) {
			
			case 'a':{
				opcao=MenuAbrir();
				if (opcao=='n'){
					
					apagaLinha();
					printf("Digite o nome do arquivo de veículos:");
					scanf("%s", ArquivoCarros);
					InserirCarrosDoArquivo(&Carros, ArquivoCarros);
					
					apagaLinha();
					printf("Digite o nome do arquivo de vagas:");
					scanf("%s", ArquivoVagas);
					InserirVagasDoArquivo(&Vagas, ArquivoVagas);
					break;
					
				}else if (opcao=='s'){
					apagaLinha();
					printf("Digite o nome do arquivo de veículos:");
					scanf("%s", ArquivoCarros);
					CarregarCarrosDoArquivo(&Carros, ArquivoCarros);
					
					apagaLinha();
					printf("Digite o nome do arquivo de vagas:");
					scanf("%s", ArquivoVagas);
					CarregarVagasDoArquivo(&Vagas, ArquivoVagas);
					break;
				}
				break;
			}
			
			case 'e':{
				
				apagaLinha();
				printf("Digite um Chassi de um carro: ");
				scanf("%u", &chassi);
				
				apagaLinha();
				printf("Digite o ID de uma vaga: ");
				scanf("%u", &id);
				if (EstacionarCarro(&Locacoes, &Carros, &Vagas, chassi, id)){
					
					fprintf(ArquivoLog, " Entrada - Sucesso - Carro Chassi: %u - Vaga ID: %u  - %s\n", chassi,id,ObtemStrHora());
					
				}else{
					fprintf(ArquivoLog, " Entrada - Falha - Carro Chassi: %u - Vaga ID: %u  - %s\n", chassi,id,ObtemStrHora());
				}
								
				break;	
			}
			
			case 'p':{
				
				apagaLinha();
				printf("Digite o numero do chassi do carro a ser estacionado:");
				scanf("%u", &chassi);
				
				if (PesquisarVaga(&Carros, &Vagas, chassi)){
					fprintf(ArquivoLog, " Entrada - Sucesso - Carro Chassi: %u - Vaga ID: %u  - %s\n", chassi,0,ObtemStrHora());
				
				}else{
					fprintf(ArquivoLog, " Entrada - Falha - Carro Chassi: %u - Vaga ID: %u  - %s\n", chassi,0,ObtemStrHora());
				}
				
				break;	
			}
			
			case 's':{
				
				apagaLinha();
				printf("Digite o ID da vaga que será liberada:");
				scanf("%u", &id);
				if (RetirarCarro(&Vagas, id, &Carros)){
					fprintf(ArquivoLog, " Saída - Sucesso - Carro Chassi: %u - Vaga ID: %u  - %s\n", chassi,0,ObtemStrHora());
				
				}else{
					fprintf(ArquivoLog, " Saída - Falha - Carro Chassi: %u - Vaga ID: %u  - %s\n", chassi,0,ObtemStrHora());
				}
				break;	
				
			}
			
			case 'l':{
				
				apagaLinha();
				printf("Digite o nome que deseja dar ao arquivo de veículos:");
				scanf("%s", ArquivoCarros);
				if(SalvarCarrosNoArquivo(&Carros, ArquivoCarros)){
					fprintf(ArquivoLog, " Saída - Sucesso - Carro Chassi: %u - Vaga ID: %u  - %s\n", 0,0,ObtemStrHora());
				
				}else{
					fprintf(ArquivoLog, " Saída - Falha - Carro Chassi: %u - Vaga ID: %u  - %s\n", 0,0,ObtemStrHora());
				}
				
				apagaLinha();
				printf("Digite o nome que desja dar ao arquivo de vagas:");
				scanf("%s", ArquivoVagas);
				if(SalvarVagasNoArquivo(&Vagas, ArquivoVagas)){
					fprintf(ArquivoLog, " Saída - Sucesso - Carro Chassi: %u - Vaga ID: %u  - %s\n", 0,0,ObtemStrHora());
				
				}else{
					fprintf(ArquivoLog, " Saída - Falha - Carro Chassi: %u - Vaga ID: %u  - %s\n", 0,0,ObtemStrHora());
				}
				
				
				if(SalvarLocacoesNoArquivo(&Locacoes, NomeArquivoLocacoes)){
					fprintf(ArquivoLog, " Saída - Sucesso - Carro Chassi: %u - Vaga ID: %u  - %s\n", 0,0,ObtemStrHora());
				
				}else{
					fprintf(ArquivoLog, " Saída - Falha - Carro Chassi: %u - Vaga ID: %u  - %s\n", 0,0,ObtemStrHora());
				}
				
				break;	
				
			}
			
			case 'r':{
				
				MenuRelatorios();
				break;	
				
			}
			
			case 'f':{
				fclose(ArquivoLog);
				exit(0);
			}
				 
			
		}
	}
}


