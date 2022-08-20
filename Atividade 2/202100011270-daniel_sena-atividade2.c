#include <stdio.h>
#include <stdlib.h> //usado malloc
#include <string.h> //usado strcpy
#include <ctype.h>  //usado toupper


struct tipo
    {
        char Palavra[20];
        void *Prox;
    };
    typedef struct tipo TIPO;


int printarSaida (TIPO *Auxiliar, TIPO *Inicio, TIPO *Atual2, TIPO *Inicio2){

    system("cls");
    system("clear");

    printf("\n\n==== IMPRESSAO ====\n");

    printf("\n > > > ORDENA PALAVRAS < < < \n");
    printf("\n Palavras ordenadas: ");
    Auxiliar = Inicio;
    
    while (Auxiliar != NULL)
    {
        printf(" %s ", Auxiliar->Palavra);
        Auxiliar = Auxiliar->Prox;
    }

    printf("\n\n\n > > > LISTA DE ENTRADA < < < \n");
    printf("\n Palavras em ordem de entrada: ");
    Atual2 = Inicio2;

    while(Atual2 !=NULL){
        printf(" %s ", Atual2->Palavra);
        Atual2 = Atual2->Prox;
    }

    printf("\n\n==== FIM IMPRESSAO ====\n");

    return 0;
}


int main()
{
    TIPO *Inicio, *Fim, *Auxiliar, *Atual, *Anterior;
    TIPO *Inicio2, *Atual2, *Auxiliar2;

    char P[20],
        R = 'S';

    Inicio = NULL;
    Inicio2 = NULL;

    while (R == 'S')
    {

        printarSaida(Auxiliar, Inicio, Atual2, Inicio2);

        printf("\n\n Qual palavra deseja inserir? ");

        scanf(" %s", P);

        Auxiliar = (TIPO *)malloc(sizeof(TIPO));
        Auxiliar2 = (TIPO *)malloc(sizeof(TIPO));

        strcpy(Auxiliar->Palavra, P);
        strcpy(Auxiliar2->Palavra, P);

        Auxiliar->Prox = NULL;
        Auxiliar2->Prox = NULL;

        if (Inicio == NULL)
        { // primeiro elemento da estrutura
            Auxiliar->Prox = NULL;
            Inicio = Auxiliar;
            Fim = Auxiliar;
        }
        else if (strcmp(P, Inicio->Palavra) <= 0)
        { // insere no inicio
            Auxiliar->Prox = Inicio;
            Inicio = Auxiliar;
        }
        else if (strcmp(P, Fim->Palavra) >= 0)
        { // insere no fim
            Fim->Prox = Auxiliar;
            Fim = Auxiliar;
        }
        else
        { // insere no meio - antes do primeiro maior
            Atual = Inicio->Prox;
            Anterior = Inicio;
            while (strcmp(Atual->Palavra, Auxiliar->Palavra) < 0)
            {
                Anterior = Atual;
                Atual = Atual->Prox;
            }
            Anterior->Prox = Auxiliar;
            Auxiliar->Prox = Atual;
        }


        if (Inicio2 == NULL){
            Auxiliar2->Prox = NULL;
            Inicio2 = Auxiliar2;
            Atual2 = Inicio2;
        } else{
            Atual2->Prox = Auxiliar2;
            Atual2 = Auxiliar2;
        }
        
        
        printf("\n\n Digite S se deseja continuar: ");
        scanf(" %c", &R);
        R = toupper(R);
    }

    printarSaida(Auxiliar, Inicio, Atual2, Inicio2);
    printf("\n\n > > > FIM DO PROGRAMA < < < \n");


    free(Inicio);
    Inicio = NULL;
    free(Fim);
    Fim = NULL;
    free(Auxiliar);
    Auxiliar = NULL;
    free(Atual);
    Atual = NULL;
    free(Anterior);
    Anterior = NULL;
    free(Inicio2);
    Inicio2 = NULL;
    free(Atual2);
    Atual2 = NULL;
    free(Auxiliar2);
    Auxiliar2 = NULL;

    return 0;
}
