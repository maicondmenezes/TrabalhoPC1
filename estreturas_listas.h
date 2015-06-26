#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include </home/maicon/TrabalhoPC1-master/estacionamento_system.h>

#define MAX 100
#define MAX_String_Modelo 31

typedef struct estacionamento {
        unsigned int id;
        float pesoMaximo;
        float alturaMaxima;
        float comprimentoMaximo;
        float larguraMaxima;
        int livre;
        unsigned int chassiDoCarro;
        int totalEstacionados;
        int totalFalhas;
        struct estacionamento *proximo;       
        
} vaga;

typedef struct frota {
        char modelo[MAX_String_Modelo];
        unsigned int chassi;
        float peso;
        float altura;
        float comprimento;
        float largura;
        int estacionado;
        
        struct frota *proximo;
        
} carro;

typedef struct estacionados {
	unsigned int idLocacao;
	unsigned int chassiCarro;
	unsigned int idVaga;
	struct estacionados *proximo;
			
} locacao;

typedef struct descritorDeVaga{
	int tamanho;
	vaga *inicio;	
} ListadeVagas;

typedef struct descritorDeCarro{
	int tamanho;
	carro *inicio;	
} ListadeCarros;

typedef struct descritorDeLocacao{
	int tamanho;
	locacao *inicio;	
} ListadeEstacionados;

//funções de carros~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
carro *BuscarCarroPorChassi (ListadeCarros *l, unsigned int chassi){
	
	carro *p;
	
	p = l->inicio;
	while (p != NULL && p->chassi!=chassi)
		p = p->proximo;
	return p;
}

void ListarFilaDeCarros(ListadeCarros *l){
	int contador=0;
	carro *p;
	
	printf("%c[%d;%dm | chassi |      modelo do veî¤µlo         |    peso   |  altura  |  largura  | comprimento |%c[%dm\n",27,4,33,27,0);
	printf("%c[%d;%dm%c[%dm",27,40,31,27,5);
	 for (p=l->inicio; p!= NULL; p=p->proximo){
		 while(contador<10){
			 if(!p->estacionado){
				 printf(" | %-6u | %-30s | %9.2f | %8.2f | %9.2f | %11.2f |\n",
				 p->chassi, p->modelo, p->peso, p->altura, p->largura, p->comprimento);
				 contador++;
			 }
		}
	 }		
}

void InserirCarro(ListadeCarros *l, char modeloDoCarro[MAX_String_Modelo], unsigned int chassiDoCarro, float pesoDoCarro, float alturaDoCarro, float larguraDoCarro, float comprimentoDoCarro,int estacionadoDoCarro){
	carro *nova;
	
	nova = malloc( sizeof (carro));
	strcpy(nova->modelo,modeloDoCarro);
	nova->chassi      =chassiDoCarro;
	nova->peso        =pesoDoCarro;
	nova->altura      =alturaDoCarro;
	nova->largura     =larguraDoCarro;
	nova->comprimento =comprimentoDoCarro;
	nova->estacionado =estacionadoDoCarro;	
	nova->proximo = l->inicio;
	l->inicio = nova;
	l->tamanho++;
}

int InserirCarrosDoArquivo(ListadeCarros *l, char *NomeArquivoCarros){
	char linha[256];
	char modelo[MAX_String_Modelo];
    unsigned int chassi;
    float peso;
    float altura;
    float comprimento;
    float largura;
       
	FILE *ArquivoCarros;
	/* Esta condicional verifica se o arquivo existe 
	 * e se foi possível abrir, caso negativo encerra a função  
         * */
	if((ArquivoCarros = fopen(NomeArquivoCarros,"r"))==NULL){
		
		apagaLinha();
		printf("Não foi possível abrir o arquivo '%s'.", NomeArquivoCarros);
		return 0; //
	}
	/*Laço de repetição para alimentar o vetor de veículos
	 * enquanto o arquivo não termina
	 * as interações são controladas pelo incremento do ponteiro *QuantidadeCarros 
         * */             
               while(fgets(linha, 256, ArquivoCarros)!=NULL){
                        
                        strcpy(modelo,strtok(linha, ","));
                        chassi     =atoi(strtok(NULL, ","));
                        peso       =atof(strtok(NULL, ","));
                        altura     =atof(strtok(NULL, ","));
                        largura    =atof(strtok(NULL, ","));
                        comprimento=atof(strtok(NULL, ","));
                        InserirCarro(l, modelo, chassi, peso, altura, largura, comprimento, 0);
                }
       fclose(ArquivoCarros);
       return 1;
         
}

int CarregarCarrosDoArquivo(ListadeCarros *l, char *NomeArquivoCarros){
	char linha[256];
	char modelo[MAX_String_Modelo];
	unsigned int chassi;
	float peso;
	float altura;
	float largura;
	float comprimento;
	int estacionado;
	
	FILE *ArquivoCarros;
	/* Esta condicional verifica se o arquivo existe 
	 * e se foi possível abrir, caso negativo encerra a função  
         * */
	if((ArquivoCarros = fopen(NomeArquivoCarros,"rb"))==NULL){
		apagaLinha();
		printf("Não foi possível abrir o arquivo '%s'.  ", NomeArquivoCarros);
		return 0; //
	}
	/*Laço de repetição para alimentar o vetor de veículos
	 * enquanto o arquivo não termina
	 * as interações são controladas pelo incremento do ponteiro *QuantidadeCarros 
         * */             
               while(fgets(linha, 256, ArquivoCarros)!=NULL){
                        
                        strcpy(modelo,strtok(linha, ","));
                        chassi     =atoi(strtok(NULL, ","));
                        peso       =atof(strtok(NULL, ","));
                        altura     =atof(strtok(NULL, ","));
                        largura    =atof(strtok(NULL, ","));
                        comprimento=atof(strtok(NULL, ","));
                        estacionado=atoi(strtok(NULL, ","));
                        InserirCarro(l, modelo, chassi, peso, altura, largura, comprimento, estacionado);
                }
       fclose(ArquivoCarros);
       return 1;
         
}

int SalvarCarrosNoArquivo(ListadeCarros *l, char *NomeArquivoCarros){
	carro *p;
	FILE *CarrosAtuais;
	

	if((CarrosAtuais=fopen(NomeArquivoCarros, "wb"))==NULL){
		apagaLinha();
		printf("Não foi possivel criar o arquivo %s", NomeArquivoCarros);
		return 0;
	}
	
	 for (p=l->inicio; p!= NULL; p=p->proximo){
		fprintf(CarrosAtuais, "%s,%u,%f,%f,%f,%f,%d\n", 
		p->modelo,
		p->chassi, 
		p->peso, 
		p->altura, 
		p->largura, 
		p->comprimento,
		p->estacionado);
	}
	fclose(CarrosAtuais);
	return 1;
	
}

//funções de vagas~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
vaga *BuscarVagaPorId(ListadeVagas *l, unsigned int id){
	
	vaga *p;
	
	p = l->inicio;
	while (p != NULL && p->id!=id)
		p = p->proximo;
	return p;
}

void ListarVagasLivres(ListadeVagas *l){
	int contador=0;
	vaga *p;
	printf("%c[%d;%dm | ID  | Peso Maximo | Altura Maxima | Largura Maxima | Comprimento Maximo |%c[%dm\n",27,4,33,27,0);
	printf("%c[%d;%dm%c[%dm",27,40,31,27,5);
	 for (p=l->inicio; p!= NULL; p=p->proximo){
		 while(contador<10){
			 if(!p->livre){
				 printf(" | %3d | %11.2f | %13.2f | %14.2f | %18.2f |\n",
				 p->id,
				 p->pesoMaximo,
				 p->alturaMaxima,
				 p->larguraMaxima,
				 p->comprimentoMaximo);
			 }
		}
	}
}

void InserirVaga(ListadeVagas *l, unsigned int id, float pesoMaximoDaVaga, float alturaMaximaDaVaga, float larguraMaximaDaVaga, float comprimentoMaximoDaVaga, int VagaLivre, unsigned int chassiCarroNaVaga, int totalEstacionadosDaVaga, int totalFalhasDaVaga){
	vaga *nova;
	
	nova = malloc( sizeof (vaga));
	nova->id                =id;
	nova->pesoMaximo        =pesoMaximoDaVaga;
	nova->alturaMaxima      =alturaMaximaDaVaga;
	nova->larguraMaxima     =larguraMaximaDaVaga;
	nova->comprimentoMaximo =comprimentoMaximoDaVaga;
	nova->livre             =VagaLivre;
	nova->chassiDoCarro     =chassiCarroNaVaga;
	nova->totalEstacionados =totalEstacionadosDaVaga;
	nova->totalFalhas       =totalFalhasDaVaga;
	nova->proximo = l->inicio;
	l->inicio = nova;
	l->tamanho++;
	
}

int InserirVagasDoArquivo(ListadeVagas *l, char *NomeArquivoVagas){
        char linha[256];
        unsigned int id;
        float pesoMaximo;
        float alturaMaxima;
        float larguraMaxima;
        float comprimentoMaximo;

	FILE *ArquivoVagas;
	/* Esta condicional verifica se o arquivo existe 
	 * e se foi possível abrir, caso negativo encerra a função  */
	if((ArquivoVagas = fopen(NomeArquivoVagas,"r"))==NULL){
		apagaLinha();
		printf("Não foi possível abrir o arquivo '%s'.  ", NomeArquivoVagas);
		return 0; //
	}
	
	/*Laço de repetição para alimentar o vetor de veículos
	 * enquanto o arquivo não termina
	 * as interações são controladas pelo incremento da variavel i*/
	 while(fgets(linha, 256, ArquivoVagas)!=NULL){
		
		id                =atoi(strtok(linha,","));
		pesoMaximo        =atof(strtok(NULL,",")); 
		alturaMaxima      =atof(strtok(NULL,",")); 
		larguraMaxima     =atof(strtok(NULL,",")); 
		comprimentoMaximo =atof(strtok(NULL,","));
		InserirVaga(l, id, pesoMaximo, alturaMaxima, larguraMaxima, comprimentoMaximo,0,0,0,0);		
	}
	fclose(ArquivoVagas);
	return 1;
}

int CarregarVagasDoArquivo(ListadeVagas *l, char *NomeArquivoVagas){
        char linha[256];
        unsigned int id;
        float pesoMaximo;
        float alturaMaxima;
        float comprimentoMaximo;
        float larguraMaxima;
        int livre;
        unsigned int chassiDoCarro;
        int totalEstacionados;
        int totalFalhas;

	FILE *ArquivoVagas;
	/* Esta condicional verifica se o arquivo existe 
	 * e se foi possível abrir, caso negativo encerra a função  */
	if((ArquivoVagas = fopen(NomeArquivoVagas,"rb"))==NULL){
		apagaLinha();
		printf("Não foi possível abrir o arquivo '%s'.  ", NomeArquivoVagas);
		return 0; //
	}
	
	/*Laço de repetição para alimentar o vetor de veículos
	 * enquanto o arquivo não termina
	 * as interações são controladas pelo incremento da variavel i*/
	 while(fgets(linha, 256, ArquivoVagas)!=NULL){
		
		id                =atoi(strtok(linha,","));
		pesoMaximo        =atof(strtok(NULL,",")); 
		alturaMaxima      =atof(strtok(NULL,",")); 
		larguraMaxima     =atof(strtok(NULL,",")); 
		comprimentoMaximo =atof(strtok(NULL,","));
		livre             =atoi(strtok(NULL,","));
		chassiDoCarro     =atoi(strtok(NULL,","));
		totalEstacionados =atoi(strtok(NULL,","));
		totalFalhas       =atoi(strtok(NULL,","));
		InserirVaga(l,id, pesoMaximo, alturaMaxima, larguraMaxima, comprimentoMaximo,livre,chassiDoCarro,totalEstacionados,totalFalhas);		
	}
	fclose(ArquivoVagas);
	return 1;
}

int SalvarVagasNoArquivo(ListadeVagas *l, char *NomeArquivoVagas){
	vaga *p;
	
	FILE *VagasAtuais;
		
	if((VagasAtuais=fopen(NomeArquivoVagas, "wb"))==NULL){
		apagaLinha();
		printf("Não foi possivel criar o arquivo %s", NomeArquivoVagas);
		return 0;
	}
	
	for (p=l->inicio; p!= NULL; p=p->proximo){
		
		fprintf(VagasAtuais,"%u,%f,%f,%f,%f,%d,%u,%d,%d\n",
		p->id,
		p->pesoMaximo,
		p->alturaMaxima,
		p->larguraMaxima,
		p->comprimentoMaximo,
		p->livre,
		p->chassiDoCarro,
		p->totalEstacionados,
		p->totalFalhas);
	}		
	fclose(VagasAtuais);
	return 1;
}

//funções de locação~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void InserirLocacao(ListadeEstacionados *l,unsigned int chassi, unsigned int id){
	locacao *nova;
		
	nova = malloc( sizeof (locacao));
	nova->idLocacao  =l->tamanho;
	nova->chassiCarro=chassi;
	nova->idVaga     =id;
	nova->proximo = l->inicio;
	l->inicio = nova;
	l->tamanho++;
	
}

int EstacionarCarro(ListadeEstacionados *l, ListadeCarros *lcarros, ListadeVagas *lvagas, unsigned int chassi, unsigned int id ){
	carro *indiceCarro;
	vaga *indiceVaga;
		
    indiceCarro=BuscarCarroPorChassi(lcarros, chassi);
	if(indiceCarro==NULL){
		apagaLinha();
		printf("O carro chassi %u não existe no sistema!", chassi);
		
		return 0;	
		
	}
	
	indiceVaga=BuscarVagaPorId(lvagas, id);
	if(indiceVaga==NULL){
		apagaLinha();
		printf("A vaga ID %u não existe no sistema!", id);
			
		return 0;
		
	}
	
	if (indiceCarro!=NULL && indiceVaga!=NULL){
		
		if(indiceCarro->peso        <indiceVaga->pesoMaximo &&
		   indiceCarro->altura      <indiceVaga->alturaMaxima &&   
		   indiceCarro->comprimento <indiceVaga->comprimentoMaximo &&
		   indiceCarro->largura     <indiceVaga->larguraMaxima){
			   
			   indiceVaga->livre=1;
			   indiceVaga->chassiDoCarro=chassi;
			   indiceVaga->totalEstacionados++;
			   indiceCarro->estacionado=1;
			   InserirLocacao(l, chassi, id);
			   
			   apagaLinha();
			   printf("O carro chassi %u foi estacionado na vaga %u\n", chassi, id);
			   return 1;
				   				   
			   }else{
				   indiceVaga->totalFalhas++;
				   apagaLinha();
				   printf("Não foi possível estacionar o carro nesta vaga");
				   return 0;
			   }
		   }
	   }

int PesquisarVaga(ListadeCarros *lcarros, ListadeVagas *lvagas, unsigned int chassi) {
	carro *indiceCarro;
	vaga *p;
	
	indiceCarro=BuscarCarroPorChassi(lcarros, chassi);
	if(indiceCarro==NULL){
	
		apagaLinha();
		printf("O carro chassi %u não existe no sistema!", chassi);
		return 0;
		
	}else{
			
		for( p=lvagas->inicio;p!=NULL || p->livre==0 ;p=p->proximo){
			if(indiceCarro->peso        <p->pesoMaximo &&
			   indiceCarro->altura      <p->alturaMaxima &&    
			   indiceCarro->comprimento <p->comprimentoMaximo &&
			   indiceCarro->largura     <p->larguraMaxima){
				
				apagaLinha();
				printf("A vaga %d esta disponivel para o carro chassi %u ", p->id, indiceCarro->chassi);
				return 1;
				break;
				
			}				
		}
		
		if(p==NULL){
			apagaLinha();
			printf("Não existe vaga disponivel no estacionamento para este veículo ");
			return 0;
		}
	}
}

int RetirarCarro(ListadeVagas *lvagas, unsigned int id, ListadeCarros *lcarros) {
	
	vaga *indiceVaga;
	carro *indiceCarro;
	
	indiceVaga=BuscarVagaPorId(lvagas, id);
		
	if(indiceVaga==NULL){
		apagaLinha();
		printf("A vaga ID %u não existe no sistema!", id);	
			
		return 0;
		
	}
	
	if(indiceVaga->livre == 0){
		apagaLinha();
		printf("A vaga de ID %u não esta ocupada no momento!", id);
		return 0;
	}else{
		indiceCarro=BuscarCarroPorChassi(lcarros, indiceVaga->chassiDoCarro);
		indiceCarro->estacionado=0;
		apagaLinha();
		printf("O carro %u deixou a vaga de ID %u!", indiceVaga->chassiDoCarro, id);
		indiceVaga->livre=0;
		indiceVaga->chassiDoCarro=0;
		apagaLinha();
		printf("A vaga de ID %u foi liberada!", id);
		return 1;
	} 
}

int SalvarLocacoesNoArquivo(ListadeEstacionados *l, char *NomeArquivoLocacoes){
	locacao *p;
	
	FILE *LocacoesAtuais;
		
	if((LocacoesAtuais=fopen(NomeArquivoLocacoes, "wb"))==NULL){
		apagaLinha();
		printf("Não foi possivel criar o arquivo %s", NomeArquivoLocacoes);
		return 0;
	}
	
	for (p=l->inicio; p!= NULL; p=p->proximo){
		
		fprintf(LocacoesAtuais,"%u,%u,%u\n",
		p->idLocacao,
		p->chassiCarro,
		p->idVaga);
	}		
	fclose(LocacoesAtuais);
	return 1;
}
//funções de relatório~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

