#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo_f
{
    char *titulo;
    char *texto;
    int idade;
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

    if (vazia_fila(f))
    {
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

void imprime_fila(fila_t *f)
{
    nodo_f_t *aux;

    if (vazia_fila(f))
        return;

    aux = f->ini;
    while (aux)
    {
        printf("\n%s\n", aux->titulo);
        printf("%s\n", aux->texto);
        printf("== \n");
        aux = aux->prox;
    }
}

int insere_fila(fila_t *f, char *titulo, char *texto)
{
    nodo_f_t *novo;

    if (vazia_fila(f))
    {
        if (!(f->ini = malloc(sizeof(nodo_f_t))))
            return 0;

        (f->ini)->titulo = (char *)malloc(33 * sizeof(char));
        (f->ini)->texto = (char *)malloc(513 * sizeof(char));

        strcpy((f->ini)->titulo, titulo);
        strcpy((f->ini)->texto, texto);

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

        novo->titulo = (char *)malloc(33 * sizeof(char));
        novo->texto = (char *)malloc(513 * sizeof(char));

        strcpy(novo->titulo, titulo);
        strcpy(novo->texto, texto);

        novo->idade = 0;
        novo->prox = NULL;
        (f->fim)->prox = novo;
        f->fim = novo;
        (f->tamanho)++;

        return 1;
    }
}

int retira_fila(fila_t *f)
{
    nodo_f_t *primeiroElemento;

    if (vazia_fila(f))
        return 0;

    primeiroElemento = f->ini;

    f->ini = f->ini->prox;
    (f->tamanho)--;

    free(primeiroElemento->titulo);
    free(primeiroElemento->texto);
    free(primeiroElemento);

    return 1;
}

void requisita(char *titulo, char *texto)
{
    getchar();

    printf("\nDigite o título: ");
    fgets(titulo, 33, stdin);
    printf("Digite o texto: ");
    fgets(texto, 513, stdin);
}

void aumenta_idade(fila_t *f)
{
    nodo_f_t *aux;

    if (vazia_fila(f))
        return;

    aux = f->ini;
    while (aux)
    {
        aux->idade++;
        aux = aux->prox;
    }
}

fila_t *remove_invalidas(fila_t *f)
{
    fila_t *aux;

    if (vazia_fila(f))
        return f;

    aux = f;
    while (!vazia_fila(aux) && aux->ini->idade > 3)
    {
        retira_fila(aux);
    }

    return aux;
}

void cadastrarNoticia(fila_t *breakingNews, fila_t *informes)
{
    int opcaoTexto;

    char *titulo = (char *)malloc(33 * sizeof(char));
    char *texto = (char *)malloc(513 * sizeof(char));

    printf("\n(0) Breaking news \n");
    printf("(1) Informe \n");
    scanf("%d", &opcaoTexto);
    requisita(titulo, texto);

    if (opcaoTexto == 0)
        insere_fila(breakingNews, titulo, texto);
    else
        insere_fila(informes, titulo, texto);

    free(titulo);
    free(texto);
}

fila_t *fecharEdicao(fila_t *breakingNews, fila_t *informes, fila_t *edicao)
{
    remove_invalidas(breakingNews);
    remove_invalidas(informes);

    if (vazia_fila(breakingNews) && vazia_fila(informes))
    {
        printf("\nEsta edição foi pulada por falta de notícias!\n");
        return edicao;
    }
    else if (!vazia_fila(breakingNews) && breakingNews->tamanho >= 2)
    {
        insere_fila(edicao, breakingNews->ini->titulo, breakingNews->ini->texto);
        retira_fila(breakingNews);

        insere_fila(edicao, breakingNews->ini->titulo, breakingNews->ini->texto);
        retira_fila(breakingNews);

        return edicao;
    }
    else if (breakingNews->tamanho == 1)
    {
        insere_fila(edicao, breakingNews->ini->titulo, breakingNews->ini->texto);
        retira_fila(breakingNews);

        if (informes->tamanho >= 1)
        {
            insere_fila(edicao, informes->ini->titulo, informes->ini->texto);
            retira_fila(informes);
        }
    }
    else if (informes->tamanho >= 2)
    {
        insere_fila(edicao, informes->ini->titulo, informes->ini->texto);
        retira_fila(informes);

        insere_fila(edicao, informes->ini->titulo, informes->ini->texto);
        retira_fila(informes);
    }
    else if (informes->tamanho == 1)
    {
        insere_fila(edicao, informes->ini->titulo, informes->ini->texto);
        retira_fila(informes);
    }

    return edicao;
}

void imprimeOpcoesPrograma()
{
    printf("\n(1) Cadastrar notícia \n");
    printf("(2) Fechar edição \n");
    printf("(3) Sair \n");
}

void opcoesPrograma(int opcao, fila_t *breakingNews, fila_t *informes, fila_t *edicao)
{
    switch (opcao)
    {
    case 1:
        cadastrarNoticia(breakingNews, informes);
        break;
    case 2:
        fecharEdicao(breakingNews, informes, edicao);
        imprime_fila(edicao);
        aumenta_idade(breakingNews);
        aumenta_idade(informes);
        break;
    case 3:
        printf("\nFim!\n");
        break;
    default:
        printf("Digite uma função válida \n");
        break;
    }
}

int main()
{
    int opcao = 0;
    fila_t *breakingNews, *informes, *edicao;

    breakingNews = cria_fila();
    informes = cria_fila();

    while (opcao != 3)
    {
        edicao = cria_fila();

        imprimeOpcoesPrograma();
        scanf("%d", &opcao);
        opcoesPrograma(opcao, breakingNews, informes, edicao);

        destroi_fila(edicao);
    }

    destroi_fila(breakingNews);
    destroi_fila(informes);

    return 0;
}
