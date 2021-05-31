#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define dimensao 20
#define TamMax 100

struct Posicao { // estrutura que vai ser ultilizada para
    int x;		//definir posiçoes.
    int y;
} posicao;

struct Posicao frutaPosicao, cobraPosicao; // controle de posiçao da fruta // controle de posicao da cobra
struct Posicao atual, depois; // variaveis auxiliar para salvar as posiçoes da calda
int caldaPosicaoX[TamMax],caldaPosicaoY[TamMax]; // Alem do controle de calda, tambem definimos o tamanho maximo.
int  pontuacao, calda = 0 ; //tamanho da calda e pontuação.

void gerarDoce() { //funçao geradora de doce.
	int b;
 do {
	b = 1; 
    srand((unsigned) time(NULL)); // Gerador de numero aleatorio.
    frutaPosicao.x = rand() % dimensao; //gera numero aleatorio para o surgimento da fruta.
    frutaPosicao.y = rand() % dimensao;
    
    int m;
    for (m = 0; m < pontuacao; m++){
    	if ((frutaPosicao.x == caldaPosicaoY[m]) && (frutaPosicao.y == caldaPosicaoX[m])){ // verifica se o doce foi gerado dentro da cobra, se sim, repete,
			b = 0;
    	}
    } 
 }while(b == 0); // se o doce for gerado dentro da cobra ele repete a funçao. 
}

void flush_in() { //resolve o problema de buffer
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

void configuracaoInicial() { //Atribui os primeiros valores para a cobra e o doce.
	int navega;
	printf("..............BEM VINDA PROFESSORA SHARA!!!..........\n");
    printf("ESCOLHA:\n(1)NOVO JOGO!!!\n(2)CONTINUE!!!\n");
	scanf("%d",&navega);
    flush_in();
    if (navega == 1){	 //Configurção padrão. 
    
	    cobraPosicao.x = dimensao / 2; // faz a cobra nasce na metade da tela
	    cobraPosicao.y = dimensao / 2;
	
	    srand((unsigned) time (NULL)); // funcao de aleatoriedade.
	    frutaPosicao.x = rand() % dimensao;
	    frutaPosicao.y = rand() % dimensao;
	    pontuacao = 0;
	}else{    

    FILE *arquivo; // Ponteiro para o arquivo
    arquivo = fopen("cobrinha.txt", "r"); // Carrega cobranha.txt em arquivo

    if (arquivo == NULL){	// testa se o arquivo esta nulo
        printf("deu erro ao ler o arquivo, tente novamente mais tarde");
    }
     // a partir daqui carrega os valores lidos nos seus respectivamente lugares definidos
	fscanf(arquivo,"%d",&pontuacao); 
	fscanf(arquivo, "%d\n%d\n",&frutaPosicao.x, &frutaPosicao.y);
	fscanf(arquivo, "%d\n%d\n",&cobraPosicao.x,&cobraPosicao.y);
	calda = pontuacao;
	int z = 0;
	for (z = 0; z < calda; z++) {                
	fscanf(arquivo, "%d\n%d\n",&caldaPosicaoY[z], &caldaPosicaoX[z]);
	}
   
    fclose(arquivo); // fecha o arquivo
	}
	
	//system("cls"); //Funçao que limpa a tela.	
}

void salvar(){
   	FILE *arquivo; // cria ponteiro para acessar o arquivo.
	arquivo = fopen("cobrinha.txt", "w");  // função fopen() para criar um novo arquivo ou abrir um arquivo existente
	fprintf(arquivo, "%d\n",pontuacao); // gravar um inteiro no arquivo que vc criou	
	fprintf(arquivo, "%d\n%d\n",frutaPosicao.x, frutaPosicao.y);	
	fprintf(arquivo, "%d\n%d\n",cobraPosicao.x, cobraPosicao.y);
	
	int z = 0;
	for (z = 0; z < calda; z++) { // Grava cada posicao de cada segmento (cada X e Y) da cobra no arquivo que eu criei         
	fprintf(arquivo, "%d\n%d\n",caldaPosicaoY[z], caldaPosicaoX[z]);
	}
	fclose(arquivo); // fecha seu arquivo
}

void Controles() { // Controles do Jogo.
    atual.y = cobraPosicao.x; // recebe a posicao atual da cabeça da cobra para ser passado para os segmentos da calda
    atual.x = cobraPosicao.y;
    int a=1;
    char navega;
    do {
        if (kbhit) { //Função que verifica se alguma tecla foi pressionada.
            navega = getch();
        }

        if ((navega != 'a') && (navega != 'r') && (navega != 'R') && (navega != 's') && (navega != 'd') && (navega != 'w') && (navega != 'q')) {
            printf("Teclas permitidas somente 'A','S','D','W' \n Por favor tente novamente\n A qualquer momento pressione Q para sair ou R para salvar \n");
        }
    }while((navega != 'a') && (navega !='s') && (navega != 'd') && (navega != 'w') && (navega !='q') && (navega != 'r') && (navega != 'R'));

    switch(navega) { // funcao para pegar a tecla pressionada.

    case 'w':
        if (cobraPosicao.x == caldaPosicaoY[0] && caldaPosicaoX[0] == cobraPosicao.y - 1 && pontuacao != 0) { // verifica se pode efetuar a movimentaçao.
            a = 0;
        }
        if (cobraPosicao.y == 0){ //Usado para criara ilusao de atravessar parede
        	cobraPosicao.y = dimensao + 1;
		}
        if ( a == 1) {
            cobraPosicao.y --;
        }
        break;

    case 'a':
        if (cobraPosicao.x - 1  == caldaPosicaoY[0] && caldaPosicaoX[0] == cobraPosicao.y && pontuacao != 0) {
            a = 0;
        }
        if (cobraPosicao.x == 0){
        	cobraPosicao.x = dimensao;
		}
        if ( a == 1) {
            cobraPosicao.x --;
        }
        break;

    case 's':
        if (cobraPosicao.x == caldaPosicaoY[0] && caldaPosicaoX[0] == cobraPosicao.y + 1 && pontuacao != 0 ) {
            a = 0;
        }
        if (cobraPosicao.y == dimensao){
        	cobraPosicao.y = -1;
		}
        if ( a == 1) {

            cobraPosicao.y ++;
        }
        break;
        
    case 'd':
        if (cobraPosicao.x + 1  == caldaPosicaoY[0] && caldaPosicaoX[0] == cobraPosicao.y && pontuacao != 0) {
            a = 0;
        }
         if (cobraPosicao.x == dimensao-1){
        	cobraPosicao.x = -1;
		}
        if ( a == 1) {
            cobraPosicao.x ++;
        }
        break;
        
    case 'q': // fechar o jogo.
        printf("Obrigado por jogar");
        exit(1);
        break;
    
    case 'r': // salvar o jogo
    	a = 0;
    	printf("Jogo Salvo com sucesso\n");
    	salvar();
        break;
        
    case 'R':
    	a = 0;
    	printf("Jogo Salvo com sucesso\n");
    	salvar();
        break;
    }
    if ((frutaPosicao.x == cobraPosicao.x) &&   (frutaPosicao.y == cobraPosicao.y)) { // verifica se a cobra comeu a fruta.
        gerarDoce();
        pontuacao ++;
        calda++;
    }
    int m;
    for (m = 0; m < pontuacao; m++){ // verifica se a cobra comeu esbarrou no proprio corpo
    	if ((cobraPosicao.x == caldaPosicaoY[m]) && (cobraPosicao.y == caldaPosicaoX[m])){ // verifica se o doce foi gerado dentro da cobra, se sim, repete,
			printf("Voce morreu, mais sorte na proxima");
			exit(1);
    	}
    } 
    int h;
    if (a == 1) {	 // Verifica se pode efetuar a troca.
        for (h = -1 ; h < calda; h++) { //for para efetuar a troca de posiçoes no segmento do vetor simulando o movimento real da cobra.
            depois.x = caldaPosicaoX[h+1];
            depois.y = caldaPosicaoY[h+1];
            caldaPosicaoX[h+1] = atual.x;
            caldaPosicaoY[h+1] = atual.y;
            atual.x = depois.x;
            atual.y  = depois.y;
        }
    }
    system("cls"); //Funçao que limpa a tela apos ser executado o movimento.
}

void DesenharTela() {
    int i = 0;
    for (i = 0; i <= dimensao + 1; i++) { //parede de cima
        printf("%c",220);
    }
    printf("\n");
    int k, g, j = 0;
    for (k = 0; k <= dimensao; k++) { //K é coluna
        for (j = 0; j <= dimensao; j++) { //J é linha
            int telaCheia = 1; // Invalida a opçao de preencher a matriz com campos vazios
            if (j == 0) { // parede ESQUERDA
                printf("%c",176);
            }
            if (k == cobraPosicao.y && j == cobraPosicao.x ) {
                printf("O"); //onde aparece a CABEÇA da cobra
                telaCheia = 0;
            }
            if (k == frutaPosicao.y && j == frutaPosicao.x ) {
                printf("%c",162);//onde aparece a FRUTA
                telaCheia = 0;
            }
            if (j == dimensao) { // parede DIREITA
                printf("%c\n",176);
            }
            else { // Espaço vago do MEIO
                for (g = 0; g < calda; g++) { // G percorre a matriz e onde deveria existir um fragmento do corpo (calda) ele printa la
                    if ((k == caldaPosicaoX[g]) && (j == caldaPosicaoY[g])) { // para definir uma posiçao é usado um X e um Y, quando conhecidir com J e K, quer dizer que la deveria existir um fragmento.
                        printf("o"); //vai ser printado o corpo da cobra
                        telaCheia = 0;
                    }
                }
                if (telaCheia == 1) {
                    printf(" "); // Completa os espaços vazios
                }
            }
        }
    }
    int w = 0;
    for (w = 0; w <= dimensao + 1; w++) { // parede de BAIXO
        printf("%c",223);
    }
    printf("\n");
    printf("PONTUACAO : %d\n", pontuacao);   
}


int main(void) {
    configuracaoInicial();
    DesenharTela();
    do {
        Controles();
        DesenharTela();
    }while(1);
    return 0;
}
