#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

struct estacionamento {
unsigned int id;
int status;
unsigned long int carro;
float pesoMaximo;
float alturaMaxima;
float comprimentoMaximo;
float larguraMaxima;
} vagas[MAX];

struct frota {
char modelo[31];
float peso;
float altura;
float comprimento;
float largura;
int estacionado;
unsigned long int chassi;
} carros[MAX];

//declaraÃ§Ã£o de protÃ³tipos de funÃ§Ãµes
int PosicaoCarroLivre(void); 
int PosicaoVagaLivre(void); 
int BuscarPorChassi (int chassi);
int BuscarPorId (int id);
void EstacionarCarro(void);
void InserirVaga(char *NomeArquivoVagas);
void InserirCarro(char *NomeArquivoCarros);
void ApagarVagaPorId(void);
void ListarCarros(void);
int ListarCarroPorChassi(void);
int ListarVagas(void);
int ListarVagaPorId(void);
int Menu(void);
int Livre(void);
void Cria_lista(void);
void CriarPainel(void);
void LerString(char *destino, int tamanho, char *arquivo);
void ApagarPorNome (void);
void ApagarCarroPorChassi(void);
void ImprimirVagasOcupadas(void);
void ImprimirVagasLivres(void);
void ImprimirFilaDeCarros(void);
void SalvarVagas(char *NomeArquivoVagas);
void SalvarCarros(char *NomeArquivoCarros);

//funÃ§Ã£o principal
int main(void) {
	int escolha;
	
	Cria_lista();
	for( ; ; ) {
		escolha = Menu();
		switch(escolha) {
			case 1: InserirCarro("veiculos.txt");
			break;
			case 2: InserirVaga("vagas.txt");
			break;
			case 3: ApagarCarroPorChassi();
			break;
			case 4: ApagarVagaPorId();
			break;
			case 5: ImprimirVagasOcupadas();
			break;
			case 6: ImprimirVagasLivres();
			break;
			case 7: ImprimirFilaDeCarros();
			break;			
			case 8: SalvarVagas("VagasSalvas.txt");
			break;
			case 9: SalvarCarros("CarrosSalvos.txt");
			break;
			case 10: EstacionarCarro();
			break;
			case 11: ListarCarros();
			break;
			case 0: exit(0);
			break;
		}
	}
}

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
		printf("\t 1. Inserir um veículo\n");
		printf("\t 2. Inserir uma vaga\n");
		printf("\t 3. Apagar um veículo\n");
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

int PosicaoVagaLivre(void) {
	int i;
	
	for( i=0; vagas[i].id && i< MAX; i++);
	
	if( i == MAX ) return -1;
	
	return i;
}

int PosicaoCarroLivre(void) {
	int i;
	
	for( i=0; carros[i].chassi && i< MAX; i++);
	
	if( i == MAX ) return -1;
	
	return i;
}

void EstacionarCarro(void) {
	int i, indiceCarro=0;
	unsigned long int chassi;
	
	printf("Digite o numero do chassi do carro a ser estacionado:");
	scanf("%lu", &chassi);

	indiceCarro=BuscarPorChassi(chassi);
	printf("O indice do carro %lu é %d\n", chassi, indiceCarro);
	if (indiceCarro!=-1){
				
		for( i=0;i<MAX || vagas[i].status==0 ;i++){
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
	
		
	}if( i != MAX )
		printf("O carro chassi %lu foi estacionado na vaga %d\n", chassi, i);
	else
		printf("Não existe vaga disponivel no estacionamento para este véiculo\n");
}

void ApagarVagaPorId(void) {
	int id;
	int posicao;
	char opcao;
	
	printf("Digite o ID da vaga a ser excluÃ­da:");
	scanf("%d", &id);
	posicao = BuscarPorId(id);
	
	if (posicao < 0)
		printf("A vaga de ID '%d' nÃ£o exite no cadastro! \n", id);
	else{
		do{
			printf("VocÃª realmente deseja excluir a vaga ID '%d' do cadastro? (s/n) \n", id);
			opcao = tolower(getchar());
		}while (opcao != 's' && opcao != 'n');
		
		if (opcao == 's')
			vagas[posicao].id=0;
	}
}

int BuscarPorId(int id){
	int i=0;
	
	while (i<MAX && vagas[i].id != id){
		i++;
	}
	
	if (i == MAX)
		return -1;
	return i;
}

int BuscarPorChassi (int chassi){
	int i;
	
	for (i=0;i<MAX && carros[i].chassi != chassi;i++);	
	
	if (i != MAX)
		return i;
	else
		return -1;
}

void ApagarCarroPorChassi(void){
	unsigned long int chassi;
	int posicao;
	char opcao;
	
	printf("Digite o chassi do carro a ser excluÃ­do:");
	scanf("%lu", &chassi);
	posicao = BuscarPorChassi(chassi);
	
	if (posicao < 0)
		printf("O carro de chassi '%lu' nÃ£o exite no cadastro! \n", chassi);
	else{
		do{
			printf("VocÃª realmente deseja excluir o carro chassi NÂº %lu do cadastro? (s/n) \n", chassi);
			opcao = tolower(getchar());
		}while (opcao != 's' && opcao != 'n');
		
		if (opcao == 's')
			carros[posicao].chassi=0;
	}
}

void InserirCarro(char *NomeArquivoCarros){
	int i=0;
	FILE *ArquivoCarros;
	/* Esta condicional verifica se o arquivo existe 
	 * e se foi possível abrir, caso negativo encerra a função  */
	if((ArquivoCarros = fopen(NomeArquivoCarros,"r"))==NULL){
		printf("Não foi possível abrir o arquivo '%s'. \n", NomeArquivoCarros);
		return; //
	}
	
	/*Laço de repetição para alimentar o vetor de veículos
	 * enquanto o arquivo não termina
	 * as interações são controladas pelo incremento da variavel i*/
	while(!feof(ArquivoCarros)){
		
		/*Função que alimenta a string de modelo do carro
		 * a condicional limpa os espaços em branco após a leitura*/
		/*fgets(carros[i].modelo, 30, ArquivoCarros);
		if(carros[i].modelo[strlen(carros[i].modelo)-1]=='\n')
			carros[i].modelo[strlen(carros[i].modelo)-1]='\0';*/
		
		fscanf(ArquivoCarros, " %s %lu %f %f %f %f", 
		&(carros[i].modelo),
		&(carros[i].chassi),
		&(carros[i].peso), 
		&(carros[i].altura), 
		&(carros[i].comprimento), 
		&(carros[i].largura));
		i++;		
	}
	
	fclose(ArquivoCarros);
}

void ImprimirFilaDeCarros(void){
	int i;
	printf(" | chassi | modelo | peso | altura | largura | comprimento |");
	for( i=0; i< MAX; i++){
		if(carros[i].estacionado)
		printf("|%lu | %s | %f | %f | %f | %f | ", 
		carros[i].chassi, 
		carros[i].modelo, 
		carros[i].peso, 
		carros[i].altura, 
		carros[i].largura, 
		carros[i].comprimento);
	}		
}

void ImprimirVagasOcupadas(void){
	int i;
	printf(" | ID | PesoMax | AlturaMax | LarguraMax | ComprimentoMax | Carro Estacionado |\n");
	
	for( i=0; i< MAX; i++){
		if(vagas[i].status && vagas[i].id)
	        printf(" | %-3d | %-11.2f | %-13.2f | %-14.2f | %-18.2f | %-17lu |\n",
			vagas[i].id,
			vagas[i].pesoMaximo,
			vagas[i].alturaMaxima,
			vagas[i].larguraMaxima,
			vagas[i].comprimentoMaximo,
			vagas[i].carro);
	}
}

void ImprimirVagasLivres(void){
	int i;
	
printf(" | ID | PesoMax | AlturaMax | LarguraMax | ComprimentoMax |\n");
	for( i=0;i<MAX;i++){
		if(!vagas[i].status && vagas[i].id)
			printf(" | %-3d | %-11.2f | %-13.2f | %-14.2f | %-18.2f |\n",
			vagas[i].id,
			vagas[i].pesoMaximo,
			vagas[i].alturaMaxima,
			vagas[i].larguraMaxima,
			vagas[i].comprimentoMaximo);
	}
}

void SalvarVagas(char *NomeArquivoVagas){
	
	FILE *VagasAtuais;
	int i;

	
	if((VagasAtuais=fopen(NomeArquivoVagas, "w"))==NULL){
		printf("Não foi possivel criar o arquivo %s", NomeArquivoVagas);
		return;
	}
	
	
	fprintf(VagasAtuais, " | ID  | Ocupada? | Peso Maximo | Altura Maxima | Largura Maxima | Comprimento Maximo | Carro Estacionado |\n");
	for( i=0;i<MAX;i++){
		if(vagas[i].id)
			fprintf(VagasAtuais, " | %-3d | %-8d | %-11.2f | %-13.2f | %-14.2f | %-18.2f | %-17lu |\n",
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

void SalvarCarros(char *NomeArquivoCarros){
	
	FILE *CarrosAtuais;
	int i;

	
	if((CarrosAtuais=fopen(NomeArquivoCarros, "w"))==NULL){
		printf("Não foi possivel criar o arquivo %s", NomeArquivoCarros);
		return;
	}
	
	
	fprintf(CarrosAtuais, " | chassi |       modelo do veículo        |    peso   |  altura  |  largura  |comprimento| Estacionado? |\n");
	for( i=0; i<MAX; i++){
		if (carros[i].chassi)
		fprintf(CarrosAtuais, " | %-6lu | %-30s | %9.2f | %8.2f | %9.2f | %9.2f | %12d |\n", 
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

void InserirVaga(char *NomeArquivoVagas){

	int i=0;
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
	while(!feof(ArquivoVagas)){
			
		fscanf(ArquivoVagas, " %u %f %f %f %f", 
		&(vagas[i].id),
		&(vagas[i].pesoMaximo), 
		&(vagas[i].alturaMaxima), 
		&(vagas[i].comprimentoMaximo), 
		&(vagas[i].larguraMaxima));
		i++;		
	}
	fclose(ArquivoVagas);
}
  
void ListarCarros(void){
	int i;
	
	printf(" | chassi |       modelo do veículo        |    peso   |  altura  |  largura  |comprimento| Estacionado? |\n");
	for( i=0; i<MAX; i++){
		if (carros[i].chassi)
		printf(" | %-6lu | %-30s | %9.2f | %8.2f | %9.2f | %9.2f | %12d |\n", 
		carros[i].chassi, 
		carros[i].modelo, 
		carros[i].peso, 
		carros[i].altura, 
		carros[i].largura, 
		carros[i].comprimento,
		carros[i].estacionado);
	}
}

