#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ================= CONSTANTES =================

#define TAM_NOME 30
#define TAM_COR 100


// ================= STRUCT =================

typedef struct
{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;

} Territorio; //

char *missoes[5] = {
    "Conquistar 3 territorios seguidos",
    "Eliminar todas as tropas da cor vermelha",
    "Conquistar todos os territorios",
    "Ter pelo menos 10 tropas em um territorio",
    "Dominar 2 territorios de cores diferentes"
};


// ================= LIMPAR BUFFER ================

void limparBufferEntrada()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}


// =============== EXIBIR TERRITÓRIOS =================
// função que mostra os territórios:
void exibirTerritorios(
    Territorio *mapa, // A struct territorio esta se ligando ao ponteiro mapa
    int totalterritorios
)
{
    printf("\n======= MAPA DE TERRITORIOS =======\n");

    for (int i = 0; i < totalterritorios; i++)
    {
        printf("\nTerritorio %d\n", i + 1);     //AQUI O PONTEIRO MAPA, VAI DEFINIR TUDO DA STRUCT

        printf("Nome: %s\n", mapa[i].nome);

        printf("Cor: %s\n", mapa[i].cor);

        printf("Tropas: %d\n", mapa[i].tropas);
    }
}
// ====== ATRIBUIÇÃO DE MISSÕES ===========

void atribuirMissao(char* destino, char* missoes[], int totalMissoes)
{
    int indiceSorteado;
    indiceSorteado= rand() %totalMissoes;

    strcpy(destino, missoes[indiceSorteado]);

}

void exibirMissao (char* missao)
{
    printf("missao: %s \n", missao );
}

int verificarMissao (char* missao, Territorio* mapa, int tamanho) 
{
    for (int i= 0; i < tamanho; i++)
{
    if (strcmp(mapa[i].cor, mapa[0].cor) != 0)
    {
       return 0; 
    }
   
}


return 1;
}


// ================= ATAQUE =================

void atacar(
    Territorio *atacante,   //atacante aponta para um territorio"
    Territorio *defensor    //defensor aponta para outro territorio"
)
{
    int dadoAtacante;
    int dadoDefensor;

    // gera números aleatórios de 1 até 6
    dadoAtacante = rand() % 6 + 1;

    dadoDefensor = rand() % 6 + 1;


    printf("\n======= BATALHA =======\n");

    printf("%s atacou %s\n",atacante->nome,defensor->nome); //aqui é apontado o nome do atacante e o nome do defensor "literalmente"

    printf("Dado atacante: %d\n",dadoAtacante);

    printf("Dado defensor: %d\n",dadoDefensor);

    // atacante venceu
    if (dadoAtacante > dadoDefensor)
    {
        printf("\n %s venceu o ataque! \n",atacante->nome);

        // defensor muda de cor
        strcpy(defensor->cor,atacante->cor); //copiar a cor do atacante para o defensor "strcpy copia a string, no caso cor"

        // atacante recebe metade das tropas do defensor
        atacante->tropas = atacante->tropas + (defensor->tropas / 2);

        defensor->tropas = defensor->tropas / 2;
    }

    // defensor venceu
    else
    {
        printf(
            "\n%s defendeu o territorio!\n",
            defensor->nome
        );

        // atacante perde 1 tropa
        atacante->tropas--;
    }
}


// ================= LIBERAR MEMÓRIA =================

void liberarMemoria(Territorio *mapa, char *missaoJogador)
{
    free(mapa);
    free(missaoJogador);

    printf(
        "\nMemoria liberada com sucesso.\n"
    );
}


// ================= MAIN =================

int main()
{
    // inicializa aleatoriedade
    srand(time(NULL));

    int totalterritorios;

    printf("Quantidade de territorios: ");

    scanf("%d", &totalterritorios);

    limparBufferEntrada();


    // ponteiro do mapa
    Territorio *mapa;


    // alocação dinâmica
    mapa = calloc(totalterritorios,sizeof(Territorio));
    // criação do espaço para os territorios e zera a memoria automaticamente

    // verifica erro
    if (mapa == NULL)
    {
        printf(
            "ERRO AO ALOCAR MEMORIA!\n"
        );

        return 1;
    }

//====== MISSAO JOGADOR ================

char *missaoJogador = (char*) malloc (100 * sizeof (char));

atribuirMissao (missaoJogador, missoes, 5);
exibirMissao(missaoJogador);


    // ================= CADASTRO =================

    for (int i = 0; i < totalterritorios; i++) // pecorre todos os territorios 
    {
        printf("\n======= TERRITORIO %d =======\n",i + 1);

        // nome
        printf("Nome do territorio: ");
        fgets(mapa[i].nome,TAM_NOME,stdin);               // fgets é tipo o scanf, sendo mais seguro
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // o fgets guarda o ENTER, por isso é utilizado o: nome[strcspn(nome, "\n")] = '\0';
                                                        // forma de limpar o enter

        // cor
        printf("Cor do exercito: ");
        fgets(mapa[i].cor,TAM_COR,stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';


        // tropas
        printf("Quantidade de tropas: ");
        scanf("%d",&mapa[i].tropas);
        limparBufferEntrada();
    }


    // mostra territórios cadastrados
    exibirTerritorios(
        mapa,
        totalterritorios
    );


    // ================= ESCOLHA DOS TERRITÓRIOS =================

    int numAtacante;
    int numDefensor;

    printf("\n======= ATAQUE =======\n");

    printf("Escolha o territorio atacante: ");

    scanf("%d", &numAtacante);

    printf("Escolha o territorio defensor: ");

    scanf("%d", &numDefensor);


    // converte número para índice
    int indiceAtacante = numAtacante - 1;  // se o usuario escolher o numero 1, o computador vai ler 0// um numero a menos
                                            // ja q o pc le de 0 1 2 3 4 
    int indiceDefensor = numDefensor - 1;


    // verifica índices válidos
    
    if (indiceAtacante >= 0 &&indiceAtacante < totalterritorios &&indiceDefensor >= 0 &&indiceDefensor < totalterritorios)
    {
        // impede atacar mesma cor
        if (
            strcmp(mapa[indiceAtacante].cor,mapa[indiceDefensor].cor) == 0 //strcmp “compara as strings”
        )
        {
            printf(
                "\nNao e permitido atacar territorios da mesma cor.\n"
            );
        }

        else
        {
            // chama função ataque
            atacar(&mapa[indiceAtacante],&mapa[indiceDefensor]);
            

            // exibe atualização
            exibirTerritorios(mapa,totalterritorios);


        if (verificarMissao (missaoJogador,mapa, totalterritorios))
        {
            printf("Missao cumprida! voce venceu");
        }

        }
    }

    else
    {
        printf("\nTerritorio invalido.\n");
    }


    // libera memória
    liberarMemoria(mapa, missaoJogador);
    return 0;
}

