#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char palavra[10];

void sortear() {
	int i, tam = 0;
	
	FILE*arquivo;
	arquivo = fopen("lista_de_palavras.txt", "r");
	srand(time(NULL));
	
	while(tam != 6){
		int num = rand()%6622;
		
		for(i = 0; i < num; i++) {
			if(NULL != fgets(palavra, 10, arquivo)) {
				if(i == num - 1) {
					tam = strlen(palavra);
					if(tam == 6) {
						break;
					}
				}
			}
		}
		rewind(arquivo);
	}
	fclose(arquivo);
}

int score(char nome[], int tentativas, float tempo) {
	FILE*arquivo;
	arquivo = fopen("score.txt", "a");
	
	fprintf(arquivo, "|%18s|%24d|%19f|\n", nome, tentativas, tempo);
	
	fclose(arquivo);
	return 0;
}

int main() {
	int tentativas, j, cont, certas;
	char nome[15], chute[10];
	double tempo;
    unsigned int c;
	
	sortear();
	clock_t begin = clock();
	for(tentativas = 0; tentativas < 6; tentativas++) {
		gets(chute);
		
		printf("\n");
		certas = 0;
		for(c = 0; c < strlen(chute); c++) {
			if(chute[c] == palavra[c]) {
				printf("^");
				certas++;
			} else {
				cont = 0;
				for(j = 0; j < 6; j++) {
					if(palavra[j] == chute[c]) {
						cont ++;
					}
				}
				if(cont == 0) {
					printf("X");
				} else {
					printf("!");
				}
			}
		}
		if(certas == 5) {
			printf("Acertou!!!\n");
			printf("Agora vamos te colocar no ranking, digite o seu nome: ");
			gets(nome);
			clock_t end = clock();
			tempo = (double)(end - begin) / CLOCKS_PER_SEC;
			score(nome, tentativas, tempo);
			break;
		}
	}
	printf("%s\n", palavra);
	return 0;
}
