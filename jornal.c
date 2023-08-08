#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

struct nodo_f
{
    char *titulo ;
    char *texto ;
    int idade ;
    struct nodo_f *prox;
};
typedef struct nodo_f nodo_f_t;

struct fila
{
    nodo_f_t *ini;
    nodo_f_t *fim;
    int tamanho; /* numero de elementos na fila */
};
typedef struct fila fila_t;

fila_t *cria_fila()
{
    fila_t *fila;

    if (!(fila = malloc(sizeof(fila_t))))
        return NULL;

    fila->tamanho = 0;

    return fila;
}

int vazia_fila(fila_t *f)
{
    if (f->tamanho == 0)
        return 1;

    return 0;
}

fila_t *destroi_fila(fila_t *f)
{
    nodo_f_t *aux;

    if (vazia_fila(f)){
        free(f);
        f = NULL;
        return f;
    }

    while (f->ini != NULL)
    {
        aux = (f->ini);
        f->ini = f->ini->prox;
        free(aux->titulo);
        free(aux->texto);
        free(aux);
        aux = NULL;
    }
    free(f);
    f = NULL;

    return f;
}

void requisita(char *titulo, char *texto){
    getchar();

    printf("\nDigite o título: ");
    scanf ("%33s", titulo) ;
    printf("Digite o texto: ");
    scanf ("%513s", texto) ;

    printf("\nTítulo 1: %s ", titulo);
    printf("Texto 1: %s ", texto);

}

int insere_fila(fila_t *f, char *titulo, char *texto)
{
    nodo_f_t *novo;

    if (vazia_fila(f))
    {
        if (!(f->ini = malloc(sizeof(nodo_f_t))))
            return 0;

        (f->ini)->titulo = (char*) malloc(33 *sizeof(char));
        (f->ini)->texto = (char*) malloc(513 *sizeof(char));

        strcpy(titulo, (f->ini)->titulo);
        strcpy(texto, (f->ini)->texto);

        printf("\nTitulo: %s\n", titulo);
        printf("Texto: %s\n", texto);

        printf("\n(f->ini)->titulo: %s\n", (f->ini)->titulo);
        printf("(f->ini)->texto: %s\n", (f->ini)->texto);


        (f->ini)->idade = 0;
        (f->ini)->prox = NULL;
        f->fim = f->ini;
        (f->tamanho)++;
        return 1;
    }
    else
    {
        if (!(novo = malloc(sizeof(nodo_f_t))))
            return 0;

        novo->titulo  = (char*) malloc(33 *sizeof(char));
        novo->texto = (char*) malloc(513 *sizeof(char));

        strcpy(titulo, novo->titulo);
        strcpy(texto, novo->texto);
        
        novo->idade = 0;
        novo->prox = NULL;
        (f->fim)->prox = novo;
        f->fim = novo;
        (f->tamanho)++;

        return 1;
    }
}

void imprime_fila(fila_t *f)
{
    nodo_f_t *aux;

    aux = f->ini;
    while (aux)
    {
        printf("%s \n", aux->titulo);
        printf("%s \n", aux->texto);
        printf("== \n");
        aux = aux->prox;
    }

    free(aux);
}

void fecharEdicao(fila_t *breakingNews, fila_t *informes, fila_t *edicao){

}

void imprimeOpcoesPrograma(){
    printf("\n(1) Cadastrar notícia \n");
    printf("(2) Fechar edição \n");
    printf("(3) Sair \n");
}

void opcoesPrograma(int opcao, fila_t *breakingNews, fila_t *informes, fila_t *edicao){
    int opcaoTexto;
    char *titulo = (char *) malloc(33 * sizeof(char));
    char *texto = (char *) malloc(513 * sizeof(char));

    switch (opcao){
    case 1:
        printf("\n(0) Breaking news \n");
        printf("(1) Informe \n");
        scanf("%d", &opcaoTexto);
        requisita(titulo, texto);
        if(opcaoTexto == 0){
            insere_fila(breakingNews, titulo, texto);
            break;
        }
        insere_fila(informes, titulo, texto);
        break;
    case 2:
        printf("Breaking News \n");
        imprime_fila(breakingNews);
        printf("Enformes \n");
        imprime_fila(informes);
        printf("Edicao \n");
        imprime_fila(edicao);
        break;
    case 3:
        printf("\nFim!\n");
        break;
    default:
        printf("Digite uma função válida \n");
        break;
    }
}

int main(){
    int opcao;
    fila_t *breakingNews, *informes, *edicao;

    breakingNews = cria_fila();
    informes = cria_fila();
    edicao = cria_fila();


    while(opcao != 3){
        imprimeOpcoesPrograma();
        scanf("%d", &opcao);
        opcoesPrograma(opcao, breakingNews, informes, edicao);
    }
    

    destroi_fila(breakingNews);
    destroi_fila(informes);
    destroi_fila(edicao);

    return 0;
}
