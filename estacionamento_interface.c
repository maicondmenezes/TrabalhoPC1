#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
#define MAX_String_Modelo 31

struct estacionamento {
        unsigned int id;
        int status;
        unsigned int carro;
        float pesoMaximo;
        float alturaMaxima;
        float comprimentoMaximo;
        float larguraMaxima;
} vagas[MAX];

struct frota {
        char modelo[MAX_String_Modelo];
        float peso;
        float altura;
        float comprimento;
        float largura;
        int estacionado;
        unsigned int chassi;
} carros[MAX];

struct estacionados {
	unsigned int id;
	unsigned int chassiCarro;
	unsigned int idVaga;
	time_t horaEntrada;
	time_t horaSaida;
	time_t tempoTotal;
	float ValorTotal;
} listaDeCarrosEstacionados[MAX];
//Prototipos de funcoes

//funcoes de manipulacao dos veiculos
int PosicaoCarroLivre(void);											//procura no vetor 'carros' pelo primeiro indice livre (carro.chassi=0), caso nÃ£o encontre retorna -1
int BuscarCarroPorChassi (int chassi, int QuantidadeCarros);		    //Retorna o indice 'i' do chassi inserido como parametro, caso nÃ£o encontre retorna -1
void EstacionarCarro(int QuantidadeCarros, int QuantidadeVagas);		//Procura no vetor 'vagas' a primeira vaga livre e disponivel para estacionar o carro
void InserirCarro(char *NomeArquivoCarros, int *QuantidadeCarros);		//Alimenta o  vetor 'carros' com dados de um arquivo externo passado como parametro
void ListarCarroPorChassi(unsigned int chassi); 						//
void ApagarCarroPorChassi(int QuantidadeCarros);
void ImprimirFilaDeCarros(int QuantidadeCarros); 
void SalvarCarros(char *NomeArquivoCarros, int QuantidadeCarros);
void ListarCarros(int QuantidadeCarros);

//funcoes de manipulacao das vagas 
int PosicaoVagaLivre(void);	
int BuscarVagaPorId (int id, int QuantidadeVagas);
int ListarVagaPorId(unsigned int id);
void ImprimirVagasOcupadas(int QuantidadeVagas);
void ImprimirVagasLivres(int QuantidadeVagas);
void SalvarVagas(char *NomeArquivoVagas, int QuantidadeVagas);
void InserirVaga(char *NomeArquivoVagas, int *QuantidadeVagas);
void ApagarVagaPorId(int QuantidadeVagas);
void ListarVagas(int QuantidadeVagas);

//funcoes gerais do sistema
int Menu(void);
int Menu2(int QuantidadeCarros, int QuantidadeVagas);
void Cria_lista(void);
void CriarPainel(void);

//funcao principal
int main(void) {
	int escolha;
	int QtdeCarros;
	int QtdeVagas;
	
	Cria_lista();
	InserirVaga("vagas.txt", &QtdeVagas);
	InserirCarro("veiculos.txt", &QtdeCarros);
	for( ; ; ) {
		escolha = Menu2(QtdeCarros, QtdeVagas);
		switch(escolha) {
			case 1: InserirCarro("veiculos.txt", &QtdeCarros);
			break;
			case 2: InserirVaga("vagas.txt", &QtdeVagas);
			break;
			case 3: ApagarCarroPorChassi(QtdeCarros);
			break;
			case 4: ApagarVagaPorId(QtdeVagas);
			break;
			case 5: ImprimirVagasOcupadas(QtdeVagas);
			break;
			case 6: ImprimirVagasLivres(QtdeVagas);
			break;
			case 7: ImprimirFilaDeCarros(QtdeCarros);
			break;			
			case 8: SalvarVagas("VagasSalvas.txt", QtdeVagas);
			break;
			case 9: SalvarCarros("CarrosSalvos.txt", QtdeCarros);
			break;
			case 10: EstacionarCarro(QtdeCarros, QtdeVagas);
			break;
			case 11: ListarCarros(QtdeCarros);
			break;
			case 0: exit(0);
			break;
		}
	}
}

//corpos das funcoes

void Cria_lista(void) {
/*cria a lista de carros e vagas, assumindo
 valor 0 para o status e o id das vagas, indicando
 uma vaga livre, o chassi dos carros recebe o valor zero 
 indicando uma posição livre*/
	int i;
	
	for( i=0; i<MAX; i++){
		vagas[i].id=0;	
        vagas[i].status=0;
        vagas[i].carro=0;
     }
     for( i=0; i<MAX; i++){
		carros[i].estacionado=0;
		carros[i].chassi=0;		
	 }
			
}

int Menu(void) {
	int c=0;
	
	do {
		printf("-- MENU:\n");
		printf("\t 1. Inserir um veî¤µlo\n");
		printf("\t 2. Inserir uma vaga\n");
		printf("\t 3. Apagar um veî¤µlo\n");
		printf("\t 4. Apagar uma vaga\n");
                printf("\t 5. Listar vagas ocupadas\n");
		printf("\t 6. Listar vagas livres\n");
                printf("\t 7. Listar carros estacionados\n");
		printf("\t 8. Salvar Vagas\n");
		printf("\t 9. Salvar Carros\n");
		printf("\t 10. Estacionar Carros\n");
		printf("\t 11. Listar Carros\n");
		printf("\t 0. Sair\n");
		printf("-- Digite sua escolha: ");
		scanf("%d", &c);
	} while(c<0 || c>12);
	
	getchar();
	
	return c;
}

int Menu2(int QuantidadeCarros, int QuantidadeVagas) {
	int c=0;
	do {
		printf("\e[H\e[2J");
		printf("\n %c[%d;%df",0x1B,1,1);
		printf("-- MENU--\n");
		printf("%c[%d;%dm | A%c[%dm",27,40,32,27,0);
		printf("%c[%d;%dmbrir%c[%dm",27,40,33,27,0);
		
		printf("%c[%d;%dm | E%c[%dm",27,40,32,27,0);
		printf("%c[%d;%dmntrar%c[%dm",27,40,33,27,0);
		
		printf("%c[%d;%dm | P%c[%dm",27,40,32,27,0);
		printf("%c[%d;%dmesquisar%c[%dm",27,40,33,27,0);

		printf("%c[%d;%dm | S%c[%dm",27,40,32,27,0);
		printf("%c[%d;%dmair%c[%dm",27,40,33,27,0);

		printf("%c[%d;%dm | S%c[%dm",27,40,32,27,0);
		printf("%c[%d;%dmalvar%c[%dm",27,40,33,27,0);
		
		printf("%c[%d;%dm | R%c[%dm",27,40,32,27,0);
		printf("%c[%d;%dmelatorios%c[%dm",27,40,33,27,0);

		printf("%c[%d;%dm | F%c[%dm",27,40,32,27,0);
		printf("%c[%d;%dmim |%c[%dm\n",27,40,33,27,0);

		printf("-- Veiculos em Espera--\n");
		ImprimirFilaDeCarros(QuantidadeCarros);
		printf("\n");
		printf("-- Vagas Livres--\n");
		ImprimirVagasLivres(QuantidadeVagas);
		printf("\n %c[%d;%df",0x1B,QuantidadeCarros+4,01);
		scanf("%d", &c);
		
	} while(c<0 || c>7);
	
	getchar();
	
	return c;
}

int PosicaoVagaLivre(void) {
	int i;
	
	for( i=0; vagas[i].id && i< MAX; i++);
	
	if( i == MAX ) return -1;
	
	return i;
}

int PosicaoCarroLivre(void) {
	int i;
	
	for( i=0; carros[i].chassi && i<MAX; i++);
	
	if( i == MAX ) return -1;
	
	return i;
}

void EstacionarCarro(int QuantidadeCarros, int QuantidadeVagas) {
	int i, indiceCarro=0;
	unsigned int chassi;
	
	printf("Digite o numero do chassi do carro a ser estacionado:");
	scanf("%u", &chassi);

	indiceCarro=BuscarCarroPorChassi(chassi, QuantidadeCarros);
	
	if (indiceCarro!=-1){
				
		for( i=0;i<QuantidadeVagas || vagas[i].status==0 ;i++){
			if(carros[indiceCarro].peso        <vagas[i].pesoMaximo &&
			   carros[indiceCarro].altura      <vagas[i].alturaMaxima &&    
			   carros[indiceCarro].comprimento <vagas[i].comprimentoMaximo &&
			   carros[indiceCarro].largura     <vagas[i].larguraMaxima){
				   
				vagas[i].status = 1;
				vagas[i].carro = chassi;
				carros[indiceCarro].estacionado = 1;
				break;				
			}				
		}
	
		
	}if( i != QuantidadeVagas )
		printf("O carro chassi %u foi estacionado na vaga %d\n", chassi, i+1);
	else
		printf("Não existe vaga disponivel no estacionamento para este véiculo\n");
}

void ApagarVagaPorId(int QuantidadeVagas) {
	int id;
	int posicao;
	char opcao;
	
	printf("Digite o ID da vaga a ser excluÃ­da:");
	scanf("%d", &id);
	posicao = BuscarVagaPorId(id, QuantidadeVagas);
	
	if (posicao < 0)
		printf("A vaga de ID '%d' nÃ£o exite no cadastro! \n", id);
	else{
		while(opcao != 's' && opcao != 'n'){
			printf("VocÃª realmente deseja excluir a vaga ID '%d' do cadastro? (s/n) \n", id);
			opcao = tolower(getchar());
		}
		
		if (opcao == 's'){
			vagas[posicao].id=0;
			printf("A vaga id:%u foi excluÃ­do do sistema\n", id);			
		}
			
	}
}

int BuscarVagaPorId(int id, int QuantidadeVagas){
	int i=0;
	
	while (i<QuantidadeVagas && vagas[i].id != id){
		i++;
	}
	
	if (i == QuantidadeVagas)
		return -1;
	return i;
}

int BuscarCarroPorChassi (int chassi, int QuantidadeCarros){
	int i;
	
	for (i=0;i<QuantidadeCarros && carros[i].chassi != chassi;i++);	
	
	if (i != QuantidadeCarros)
		return i;
	else
		return -1;
}

void ApagarCarroPorChassi(int QuantidadeCarros){
	unsigned int chassi;
	int posicao;
	char opcao;
	
	printf("Digite o chassi do carro a ser excluÃ­do:");
	scanf("%u", &chassi);
	posicao = BuscarCarroPorChassi(chassi, QuantidadeCarros);
	
	if (posicao < 0)
		printf("O carro de chassi '%u' nÃ£o exite no cadastro! \n", chassi);
	else{
		
		while (opcao != 's' && opcao != 'n'){
			printf("VocÃª realmente deseja excluir o carro chassi NÂº %u do cadastro? (s/n)\n", chassi);
			opcao = tolower(getchar());
		}
		
		if (opcao == 's'){
			carros[posicao].chassi=0;
			printf("O carro chassi NÂº%u foi excluÃ­do do sistema\n", chassi);
		}			
	}
}

void InserirCarro(char *NomeArquivoCarros, int *QuantidadeCarros){
	char clearenvclinha[256];
	
	*QuantidadeCarros=0;
	FILE *ArquivoCarros;
	/* Esta condicional verifica se o arquivo existe 
	 * e se foi possível abrir, caso negativo encerra a função  
         * */
	if((ArquivoCarros = fopen(NomeArquivoCarros,"r"))==NULL){
		printf("Não foi possível abrir o arquivo '%s'. \n", NomeArquivoCarros);
		return; //
	}

	/*Laço de repetição para alimentar o vetor de veículos
	 * enquanto o arquivo não termina
	 * as interações são controladas pelo incremento do ponteiro *QuantidadeCarros 
         * */
	               
                while(fgets(linha, 256, ArquivoCarros)!=NULL){
                        
                        strcpy(carros[*QuantidadeCarros].modelo,strtok(linha, ","));
                        carros[*QuantidadeCarros].chassi     =atoi(strtok(NULL, ","));
                        carros[*QuantidadeCarros].peso       =atof(strtok(NULL, ","));
                        carros[*QuantidadeCarros].altura     =atof(strtok(NULL, ","));
                        carros[*QuantidadeCarros].largura    =atof(strtok(NULL, ","));
                        carros[*QuantidadeCarros].comprimento=atof(strtok(NULL, ","));
                        (*QuantidadeCarros)++;
                }
       fclose(ArquivoCarros);
}

void ImprimirFilaDeCarros(int QuantidadeCarros){
	int i;
	
	printf("%c[%d;%dm | chassi |      modelo do veî¤µlo         |    peso   |  altura  |  largura  | comprimento |%c[%dm\n",27,4,33,27,0);
	printf("%c[%d;%dm%c[%dm",27,40,31,27,5);
	 for( i=0; i<QuantidadeCarros-1; i++){
		if(!carros[i].estacionado){
			printf(" | %-6u | %-30s | %9.2f | %8.2f | %9.2f | %11.2f |\n",
			carros[i].chassi, 
			carros[i].modelo, 
			carros[i].peso, 
			carros[i].altura, 
			carros[i].largura, 
			carros[i].comprimento);
		}
	 }		
}

void ImprimirVagasOcupadas(int QuantidadeVagas){
	int i;
	
	printf(" | ID | Peso Maximo | Altura Maxima | Largura Maxima | Comprimento Maximo | Carro Estacionado |\n");
	for(i=0; i<QuantidadeVagas;i++){
		if(vagas[i].id && vagas[i].status){
			printf(" | %-3d | %-11.2f | %-13.2f | %-14.2f | %-18.2f | %-17u |\n",
			vagas[i].id,
			vagas[i].pesoMaximo,
			vagas[i].alturaMaxima,
			vagas[i].larguraMaxima,
			vagas[i].comprimentoMaximo,
			vagas[i].carro);
		}			
	}
}

void ImprimirVagasLivres(int QuantidadeVagas){
	int i;
	printf("%c[%d;%dm | ID  | Peso Maximo | Altura Maxima | Largura Maxima | Comprimento Maximo |%c[%dm\n",27,4,33,27,0);
	printf("%c[%d;%dm%c[%dm",27,40,31,27,5);
	for(i=0; i<QuantidadeVagas;i++){
		if(vagas[i].id && !vagas[i].status){
			printf(" | %3d | %11.2f | %13.2f | %14.2f | %18.2f |\n",
			vagas[i].id,
			vagas[i].pesoMaximo,
			vagas[i].alturaMaxima,
			vagas[i].larguraMaxima,
			vagas[i].comprimentoMaximo);
		}
	}
}

void SalvarVagas(char *NomeArquivoVagas, int QuantidadeVagas){
	
	FILE *VagasAtuais;
	int i;

	
	if((VagasAtuais=fopen(NomeArquivoVagas, "w"))==NULL){
		printf("Não foi possivel criar o arquivo %s", NomeArquivoVagas);
		return;
	}
	
	
	fprintf(VagasAtuais, " | ID | Ocupada? | Peso Maximo | Altura Maxima | Largura Maxima | Comprimento Maximo | Carro Estacionado |\n");
	for( i=0;i<QuantidadeVagas;i++){
		if(vagas[i].id)
			fprintf(VagasAtuais, " | %-3d | %-8d | %-11.2f | %-13.2f | %-14.2f | %-18.2f | %-17u |\n",
			vagas[i].id,
			vagas[i].status,
			vagas[i].pesoMaximo,
			vagas[i].alturaMaxima,
			vagas[i].larguraMaxima,
			vagas[i].comprimentoMaximo,
			vagas[i].carro);
	}
	fclose(VagasAtuais);
}

void SalvarCarros(char *NomeArquivoCarros, int QuantidadeCarros){
	
	FILE *CarrosAtuais;
	int i;

	
	if((CarrosAtuais=fopen(NomeArquivoCarros, "w"))==NULL){
		printf("Não foi possivel criar o arquivo %s", NomeArquivoCarros);
		return;
	}
	
	
	fprintf(CarrosAtuais, " | chassi |       modelo do veículo       |    peso   |  altura  |  largura  |comprimento| Estacionado? |\n");
	for( i=0; i<QuantidadeCarros; i++){
		if (carros[i].chassi)
		fprintf(CarrosAtuais, " | %-6u | %-30s | %9.2f | %8.2f | %9.2f | %9.2f | %12d |\n", 
		carros[i].chassi, 
		carros[i].modelo, 
		carros[i].peso, 
		carros[i].altura, 
		carros[i].largura, 
		carros[i].comprimento,
		carros[i].estacionado);
	}
	fclose(CarrosAtuais);
	
}

void InserirVaga(char *NomeArquivoVagas, int *QuantidadeVagas){
        char linha[256];

	*QuantidadeVagas=0;
	FILE *ArquivoVagas;
	/* Esta condicional verifica se o arquivo existe 
	 * e se foi possível abrir, caso negativo encerra a função  */
	if((ArquivoVagas = fopen(NomeArquivoVagas,"r"))==NULL){
		printf("Não foi possível abrir o arquivo '%s'. \n", NomeArquivoVagas);
		return; //
	}
	
	/*Laço de repetição para alimentar o vetor de veículos
	 * enquanto o arquivo não termina
	 * as interações são controladas pelo incremento da variavel i*/
	 while(fgets(linha, 256, ArquivoVagas)!=NULL){
		
		vagas[*QuantidadeVagas].id                =atoi(strtok(linha,","));
		vagas[*QuantidadeVagas].pesoMaximo        =atof(strtok(NULL,",")); 
		vagas[*QuantidadeVagas].alturaMaxima      =atof(strtok(NULL,",")); 
		vagas[*QuantidadeVagas].comprimentoMaximo =atof(strtok(NULL,",")); 
		vagas[*QuantidadeVagas].larguraMaxima     =atof(strtok(NULL,","));
		(*QuantidadeVagas)++;		
	}
	fclose(ArquivoVagas);
}
  
void ListarCarros(int QuantidadeCarros){
	int i=0;
	
	printf(" | chassi |       modelo do veî¤µlo        |    peso   |  altura  |  largura  |comprimento| Estacionado |\n");
	for(i=0;i>QuantidadeCarros;i++){
		printf(" | %-6u | %-30s | %9.2f | %8.2f | %9.2f | %9.2f | %12d |\n", 
		carros[i].chassi, 
		carros[i].modelo, 
		carros[i].peso, 
		carros[i].altura, 
		carros[i].largura, 
		carros[i].comprimento,
		carros[i].estacionado);
	}	
}

void ListarVagas(int QuantidadeVagas){
	int i;
	
	printf(" | ID | Status | Peso Maximo | Altura Maxima | Largura Maxima | Comprimento Maximo | Carro Estacionado |\n");
	for(i=0; i<QuantidadeVagas;i++){
		printf(" | %-3d | %6d | %-11.2f | %-13.2f | %-14.2f | %-18.2f | %-17u |\n",
		vagas[i].id,
		vagas[i].status,
		vagas[i].pesoMaximo,
		vagas[i].alturaMaxima,
		vagas[i].larguraMaxima,
		vagas[i].comprimentoMaximo,
		vagas[i].carro);
		}			
}
