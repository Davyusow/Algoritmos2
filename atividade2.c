#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#include "string.h"

int tamanho = 1;

typedef struct
{ // estrutura dos times;
    int indiceInicio;
    int indiceFinal;
    int qtdLutadores;
    int qtdVivos;
} Times;

typedef struct
{ // estrutura do objeto base do lutador;
    char nome[30];
    char id[30];
    int dano;
    int vida;
    int iniciativa;
    int existe;
    bool vivo;
    int equipe;
} Lutadores;

void toStringLutadores(Lutadores *lutador, int posicao)
{ // imprime todas as infromações de um lutador especifico
    if (lutador[posicao].existe == 1)
    {
        printf("\n Nome: %s", lutador[posicao].nome);
        printf("\n Id: %s", lutador[posicao].id);
        printf("\n Dano: %i", lutador[posicao].dano);
        printf("\n Vida: %i", lutador[posicao].vida);
        printf("\n Iniciativa: %i", lutador[posicao].iniciativa);
        printf("\n Existe: Lutador existe");
        printf("\n Time: %i", lutador[posicao].equipe);
        if (lutador[posicao].vivo)
        {
            printf("\n Estado: Vivo\n");
        }
        else
        {
            printf("\n Estado: Morto\n");
        }
    }
    else
    {
        printf("\n Este lutador não existe!");
    }
}

int novoLutador(Lutadores *lutador1, int posicao, Times *timeTemp, int numTime)
{ // função que define os dados de um lutador;
    if (posicao < timeTemp->indiceInicio || posicao >= timeTemp->indiceFinal)
    { // verifica se está dentro do vetor;
        printf("\nPosição Inválida!\n");
        return 0;
    }
    if (lutador1[posicao].existe == 1)
    { // verifica se o lutador já existe;
        printf("\nLutador Já existe!\n");
        return 0;
    }
    char idTemp[30];
    // registra e verifica se um ID de lutador já existe
    printf("\nDigite o ID do lutador: \n");
    scanf(" %s", idTemp);
    getchar();
    for (int i = 0; i < tamanho; i++)
    {
        if (strcmp(lutador1[i].id, idTemp) == 0 && lutador1[i].existe == 1)
        {
            printf("\nJá existe um lutador com este ID!\n");
            return 0;
        }
    }
    strcpy(lutador1[posicao].id, idTemp); // registra os dados restantes do lutado;
    printf("\nDigite o nome do Lutador: \n");
    scanf("%s", lutador1[posicao].nome);
    getchar();
    lutador1[posicao].iniciativa = rand() % 99 + 1;
    lutador1[posicao].vida = 100;
    lutador1[posicao].dano = rand() % 9 + 1;
    lutador1[posicao].existe = 1;
    lutador1[posicao].equipe = numTime;
    lutador1[posicao].vivo = true;
    timeTemp->qtdVivos += 1;

    tamanho++;
    return 1;
}

void insereTimes(Times *timeTemp, Lutadores *lista, int numTime)
{
    char escolha;
    
    int cont =(int) timeTemp->indiceInicio;
    printf("\nINSIRA OS LUTADORES DO TIME %i\n", numTime);
    do
    {
        novoLutador(lista, cont, timeTemp, numTime);

        printf("\nDeseja adicionar um novo lutador?\n(s/n)\n");
        scanf(" %c", &escolha);
        getchar();
        
        switch (escolha)
        {
        case 's':
        case 'S':
            lista = realloc(lista,(timeTemp->indiceFinal + 1)*sizeof(Lutadores));
            timeTemp->indiceFinal++;
            cont++;
            break;

        case 'n':
        case 'N':
            cont = timeTemp->indiceFinal;
            break;

        default:
            printf("\nTecla inválida!\n");
            break;
        }
    } while (cont < timeTemp->indiceFinal);
}

void alocacaoLutadores(Lutadores *lista, Times *time1, Times *time2)
{
    insereTimes(time1, lista, 1);
    time1->qtdLutadores = time1->indiceFinal - time1->indiceInicio;

    time2->indiceInicio = time1->indiceFinal+1;
    time2->indiceFinal = time2->indiceInicio+1;
    
    printf("\ndebug indice inicio = %i",time1->indiceInicio);
    printf("\ndebug indice final = %i",time1->indiceFinal);
    printf("\ndebug indice inicio = %i",time2->indiceInicio);
    printf("\ndebug indice final = %i",time2->indiceFinal);
    
    insereTimes(time2, lista, 2);
    time2->qtdLutadores = time2->indiceFinal - time1->indiceFinal;
}

Lutadores *Buscar(Lutadores *lista, char *id, int tam)
{

    for (int i = 0; i < tam; i++)
    {
        if (lista->existe == 1)
        {
            if (strcmp(lista[i].id, id) == 0)
            {
                toStringLutadores(lista, i);
                return &lista[i];
            }
        }
    }

    printf("\nLutador não encontrado!");

    return NULL;
}

int fugaLutador(Lutadores *lista, char *id, int tam)
{
    Lutadores *temp = Buscar(lista, id, tam);

    if (temp == NULL)
    {
        printf("\nLutador não encontrado!");
        return 0;
    }

    if (temp->vivo)
    {
        temp->existe = 0;
        printf("\nLutador removido com sucesso!");
        return temp->equipe;
    }
    else
    {
        printf("\nO lutador já está morto!");
    }
    return 0;
}

void ordenadorIniciativa(Lutadores *lista, Times timeTemp)
{                    // inicio da função, parametros x -> vetor, tam -> tamanho do vetor
    int i, j, chave; // i laço da primeira busca, j -> laço da ordenação, chave é o valor sendo comparado
    for (i = timeTemp.indiceInicio; i < timeTemp.indiceFinal - 1; i++)
    { // percorre os valores do vetor
        if (lista[i].iniciativa < lista[i + 1].iniciativa)
        {                                                  // se o valor atual for maior que o valor da frente
            chave = lista[i + 1].iniciativa;               // o novo item comparado é o i+1
            lista[i + 1].iniciativa = lista[i].iniciativa; // o valor da frente volta
            lista[i].iniciativa = chave;                   // o valor comparavel vai pra posição atual
            j = i - 1;                                     // valor para a verificação da lista de maneira decrementativa
            while (j >= timeTemp.indiceInicio)
            { // enquanto o j estiver no array
                if (chave > lista[j].iniciativa)
                {                                                  // se o valor comparado é menor que o de trás
                    lista[j + 1].iniciativa = lista[j].iniciativa; // então troca
                    lista[j].iniciativa = chave;                   // então troca
                }
                else
                {          // senão
                    break; // termina a verificação
                }
                j = j - 1; // compara com o anterior
            }
        }
    }
}

int main(void)
{
    srand(time(NULL));

    printf("%i", rand() % 100);
    system("clear");
    system("clear");

    Times time1;
    Times time2;

    Lutadores *listaLutadores;
    listaLutadores = malloc(sizeof(Lutadores) * 1); // tamanho do array
    // alocação dos lutadores;
    time1.indiceInicio = 0;
    time1.indiceFinal = 1;
    time2.indiceFinal = 0;
    time1.qtdLutadores = 0;
    time2.qtdLutadores = 0;
    time1.qtdVivos = 0;
    time2.qtdVivos = 0;
    char escolha = '0';
    char busca[30];
    int verificador = 0;
    int temp;
    do
    {
        printf("\n    Fase de Organização!    ");
        printf("\nDigite 1. para adicionar lutadores.");
        printf("\nDigite 2. para imprimir todos os lutadores.");
        printf("\nDigite 3. para buscar um lutador por id");
        printf("\nDigite 4. imprimir um reltório dos times");
        printf("\nDigite 5. para remover um lutador");
        printf("\nDigite 6. para ir para a próxima fase\n\ncomando: ");
        scanf(" %c", &escolha);
        getchar();
        switch (escolha)
        {
        case '1':
            system("clear");
            alocacaoLutadores(listaLutadores, &time1, &time2);
            verificador++;
            break;
        case '2':
            system("clear");
            if (verificador < 1)
            {
                printf("\nNenhum lutador alocado!\nprecione 1 para alocar os lutadores para você poder lista-los!\n");
            }
            else
            {
                for (int i = 0; i < time2.indiceFinal; i++)
                {
                    toStringLutadores(listaLutadores, i);
                }
            }
            break;

        case '3':
            system("clear");
            if (verificador < 1)
            {
                printf("\nNenhum lutador alocado!\nprecione 1 para alocar os lutadores para você poder busca-lo!\n");
            }
            else
            {
                printf("\nDigite o id do lutador: ");
                scanf(" %s", busca);
                getchar();
                Buscar(listaLutadores, busca, time2.indiceFinal);
            }
            break;

        case '4':
            system("clear");
            if (verificador < 1)
            {
                printf("\nNenhum lutador alocado!\nprecione 1 para alocar os lutadores aos times!\n");
            }
            else
            {
                printf("\n Existem %i lutador(es) na partida", time2.indiceFinal);
                printf("\n Onde o time 1 possui %i lutador(es)", time1.qtdLutadores);
                printf("\n E o time 2 possui %i lutador(es)", time2.qtdLutadores);
                printf("\n Tais que %i lutadores do time1 estão vivos", time1.qtdVivos);
                printf("\n E %i lutadores do time2 estão vivos.\n", time2.qtdVivos);
            }

            break;

        case '5':
            system("clear");
            if (verificador < 1)
            {
                printf("\nNenhum lutador alocado!\nprecione 1 para alocar os lutadores para você poder remove-lo!\n");
            }
            else
            {
                printf("\nDigite o id do lutador: ");
                scanf(" %s", busca);
                getchar();
                temp = fugaLutador(listaLutadores, busca, time2.indiceFinal);
                if (temp == 1)
                {
                    time1.qtdLutadores--;
                    time1.qtdVivos--;
                }
                else if (temp == 2)
                {
                    time2.qtdLutadores--;
                    time2.qtdVivos--;
                }
            }

            break;

        case '6':
            system("clear");
            if (verificador < 1)
            {
                printf("\nNenhum lutador alocado!\nprecione 1 para alocar os lutadores para você poder ir para a próxima fase!\n");
            }
            break;

        case ' ':
            system("clear");
            break;

        default:
            printf("\nTecla inválida!");
            break;
        }
    } while (escolha != '6' || verificador < 1);
    ordenadorIniciativa(listaLutadores, time1);
    ordenadorIniciativa(listaLutadores, time2);
    system("clear");
    for (int i = 0; i < time2.indiceFinal; i++)
    {
        toStringLutadores(listaLutadores, i);
    }

    return 0;
}