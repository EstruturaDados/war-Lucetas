#include <stdio.h>
#include <string.h>

struct territorio
{
    char nome [30]; //nome do territorio
    char cor [10];  // cor do exercito
    int tropas;     //quantidade de tropas
};

// função pra limpar buffer
void limparbufferentrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // limpa ENTER
}


int main (){

    struct territorio territorios [5]; // vetor com 5 territorios

// cadastros dos exercitos

for (int i= 0; i < 5; i++) { //criação do loop para a criação de exercitos 5)

printf("\n territorio %d\n", i+1); // o indice vai começar pelo 1 n por 0

printf("Nome Do Territorio: ");
fgets(territorios[i].nome,30,stdin); // le o nome
territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove \n

printf("cor do exercito: ");
fgets(territorios[i].cor,10,stdin);//le a cor
territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

printf("Quantidade de tropas: ");
scanf("%d", &territorios[i].tropas);
limparbufferentrada();
//Use um OU outro, nunca os dois juntos 
//getchar ();

}
//exibição:
printf("=======Territorios Cadastrados======");

for (int i = 0; i <5; i++) {

        printf("\nTerritorio %d\n", i+1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);

}



return 0;

}
