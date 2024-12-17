#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#include "string.h"
#include "unistd.h"

int tamanho = 1;

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
typedef struct
{ // estrutura dos times;
    int qtdLutadores;
    int qtdVivos;
    int score;
    Lutadores *lista;
} Times;

void toStringLutadores(Lutadores lista)
{ // imprime todas as infromações de um lutador especifico
    if (lista.existe == 1)
    {
        printf("\n Nome: %s", lista.nome);
        printf("\n Id: %s", lista.id);
        printf("\n Dano: %i", lista.dano);
        printf("\n Vida: %i", lista.vida);
        printf("\n Iniciativa: %i", lista.iniciativa);
        printf("\n Existe: Lutador existe");
        printf("\n Time: %i", lista.equipe);
        if (lista.vivo)
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
    }
}

int novoLutador(int posicao, Times *timeTemp, int numTime, Times time2)
{ // função que define os dados de um lutador;

    if (posicao < 0 || posicao > timeTemp->qtdLutadores)
    { // verifica se está dentro do vetor;
        printf("\nPosição Inválida!\n");
        return 0;
    }
    if (timeTemp->lista[posicao].existe == 1)
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
        if (strcmp(timeTemp->lista[i].id, idTemp) == 0 && timeTemp->lista[i].existe == 1)
        {
            printf("\nJá existe um lutador com este ID!\n");
            timeTemp->lista[posicao].existe = 0;
            return 0;
        }
    }
    for (int i = 0; i < tamanho; i++)
    {
        if (strcmp(time2.lista[i].id, idTemp) == 0 && time2.lista[i].existe == 1)
        {
            printf("\nJá existe um lutador com este ID!\n");
            timeTemp->lista[posicao].existe = 0;
            return 0;
        }
    }
    strcpy(timeTemp->lista[posicao].id, idTemp); // registra os dados restantes do lutado;
    printf("\nDigite o nome do Lutador: \n");
    scanf("%s", timeTemp->lista[posicao].nome);
    getchar();
    timeTemp->lista[posicao].iniciativa = rand() % 99 + 1;
    timeTemp->lista[posicao].vida = 100;
    timeTemp->lista[posicao].dano = rand() % 9 + 1;
    timeTemp->lista[posicao].existe = 1;
    timeTemp->lista[posicao].equipe = numTime;
    timeTemp->lista[posicao].vivo = true;
    timeTemp->qtdVivos += 1;
    timeTemp->qtdLutadores += 1;
    tamanho++;
    return 1;
}

void insereTimes(Times *timeTemp, int numTime, Times time2)
{
    char escolha;

    int cont = 0;
    printf("\nINSIRA OS LUTADORES DO TIME %i\n", numTime);
    do
    {

        printf("\nDeseja adicionar um novo lutador?\n(s/n)\n");
        scanf(" %c", &escolha);
        getchar();

        switch (escolha)
        {
        case 's':
        case 'S':
            novoLutador(cont, timeTemp, numTime, time2);
            Lutadores *temp = realloc(timeTemp->lista, (timeTemp->qtdLutadores + 1) * sizeof(Lutadores));
            if (temp == NULL)
            {
                printf("Erro na alocação de memória!\n");
                return;
            }
            timeTemp->lista = temp;
            cont++;
            break;

        case 'n':
        case 'N':
            cont = timeTemp->qtdLutadores + 1;
            break;

        default:
            printf("\nTecla inválida!\n");
            break;
        }
    } while (cont <= timeTemp->qtdLutadores);
}

void alocacaoLutadores(Times *time1, Times *time2)
{
    insereTimes(time1, 1, *time2);

    insereTimes(time2, 2, *time1);
}

Lutadores *Buscar(Times time1, Times time2, char *id)
{

    for (int i = 0; i < time1.qtdLutadores; i++)
    {
        if (time1.lista[i].existe == 1)
        {
            if (strcmp(time1.lista[i].id, id) == 0)
            {
                toStringLutadores(time1.lista[i]);
                return &time1.lista[i];
            }
        }
    }
    for (int i = 0; i < time2.qtdLutadores; i++)
    {
        if (time2.lista[i].existe == 1)
        {
            if (strcmp(time2.lista[i].id, id) == 0)
            {
                toStringLutadores(time2.lista[i]);
                return &time1.lista[i];
            }
        }
    }

    printf("\nLutador não encontrado!");

    return NULL;
}

int fugaLutador(Times time1, Times time2, char *id)
{
    Lutadores *temp = Buscar(time1, time2, id);

    if (temp == NULL)
    {
        printf("\nLutador não encontrado!");
        return 0;
    }
    else if (temp->vivo)
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

void ordenadorIniciativa(Times timeTemp)
{ // inicio da função, parametros x -> vetor, tam -> tamanho do vetor
    int i, j;
    Lutadores chave; // i laço da primeira busca, j -> laço da ordenação, chave é o valor sendo comparado
    for (i = 0; i < timeTemp.qtdLutadores - 1; i++)
    { // percorre os valores do vetor
        if (timeTemp.lista[i].iniciativa < timeTemp.lista[i + 1].iniciativa)
        {                                              // se o valor atual for maior que o valor da frente
            chave = timeTemp.lista[i + 1];             // o novo item comparado é o i+1
            timeTemp.lista[i + 1] = timeTemp.lista[i]; // o valor da frente volta
            timeTemp.lista[i] = chave;                 // o valor comparavel vai pra posição atual
            j = i - 1;                                 // valor para a verificação da lista de maneira decrementativa
            while (j >= 0)
            { // enquanto o j estiver no array
                if (chave.iniciativa > timeTemp.lista[j].iniciativa)
                {                                              // se o valor comparado é menor que o de trás
                    timeTemp.lista[j + 1] = timeTemp.lista[j]; // então troca
                    timeTemp.lista[j] = chave;                 // então troca
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

void Combate(Lutadores *lista1, Lutadores *lista2, int num1, int num2)
{
    printf("\nO Lutador %s ataca causando %i de dano!", lista1[num1].nome, lista1[num1].dano);
    printf("\nO Lutador %s ataca causando %i de dano!", lista2[num2].nome, lista2[num2].dano);
    lista1[num1].vida = lista1[num1].vida - lista2[num2].dano;
    lista2[num2].vida = lista2[num2].vida - lista1[num1].dano;
    printf("\nVida de %s: %i", lista1[num1].nome, lista1[num1].vida);
    printf("\nVida de %s: %i", lista2[num2].nome, lista2[num2].vida);
    printf("\n");
    sleep(1);
}

int main(void)
{
    srand(time(NULL));

    printf("%i", rand() % 100);
    system("clear");
    system("clear");

    Times time1;
    Times time2;

    time1.lista = malloc(sizeof(Lutadores) * 1); // tamanho do array
    time2.lista = malloc(sizeof(Lutadores) * 1);
    // alocação dos lutadores;

    time1.qtdLutadores = 0;
    time2.qtdLutadores = 0;
    time1.qtdVivos = 0;
    time2.qtdVivos = 0;
    char escolha = '0';
    char busca[30];
    int verificador = 0;
    int temp;
    do /// Fase de organização
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
            alocacaoLutadores(&time1, &time2);
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
                for (int i = 0; i < time1.qtdLutadores; i++)
                {
                    toStringLutadores(time1.lista[i]);
                }
                for (int i = 0; i < time2.qtdLutadores; i++)
                {
                    toStringLutadores(time2.lista[i]);
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
                Buscar(time1, time2, busca);
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
                printf("\n Existem %i lutador(es) na partida", time1.qtdLutadores + time2.qtdLutadores);
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

                temp = fugaLutador(time1, time2, busca);
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
    // pós organização
    ordenadorIniciativa(time1);
    ordenadorIniciativa(time2);

    Lutadores adversario1[time1.qtdLutadores];
    Lutadores adversario2[time2.qtdLutadores];

    int num1 = 0;
    for (int i = 0; i < time1.qtdLutadores; i++)
    {
        if (time1.lista[i].existe == 1)
        {
            adversario1[num1] = time1.lista[i];
            num1++;
        }
    }
    num1 = 0;
    for (int i = 0; i < time2.qtdLutadores; i++)
    {
        if (time2.lista[i].existe == 1)
        {
            adversario2[num1] = time2.lista[i];
            num1++;
        }
    }

    system("clear");
    printf("\nLista de lutadores vivos: \n");
    for (int i = 0; i < time1.qtdLutadores; i++)
    {
        toStringLutadores(time1.lista[i]);
    }
    for (int i = 0; i < time2.qtdLutadores; i++)
    {
        toStringLutadores(time2.lista[i]);
    }
    printf("\nLista de lutadores mortos: \n");
    for (int i = 0; i < time1.qtdLutadores; i++)
    {
        if (!adversario1[i].vivo)
        {
            toStringLutadores(adversario1[i]);
        }
    }
    for (int i = 0; i < time2.qtdLutadores; i++)
    {
        if (!adversario1[i].vivo)
        {
            toStringLutadores(adversario1[i]);
        }
    }

    /*Fase de Combate*/
    num1 = 0;
    int num2 = 0;
    do
    {
        printf("\n      Fase De Combate!        ");

        while ((adversario1[num1].vida>0) & (adversario2[num2].vida>0))
        {
            Combate(adversario1, adversario2, num1, num2);
        }
        if (adversario1[num1].vida <= 0)
        {
            printf("\nO lutador %s derrotou o lutador %s!", adversario2[num2].nome, adversario1[num1].nome);
            num1++;
            time1.qtdVivos--;
            ++time2.score;
            printf("\nA pontuação agora é: Time1 %i X Time2 %i", time1.score, time2.score);
        }
        if (adversario2[num2].vida <= 0)
        {
            printf("\nO lutador %s derrotou o lutador %s!", adversario1[num1].nome, adversario2[num2].nome);
            num2++;
            time2.qtdVivos--;
            ++time1.score;
            printf("\nA pontuação agora é: Time1 %i X Time2 %i", time1.score, time2.score);
        }
        if (num1>time1.qtdVivos)
        break;
        if (num2>time2.qtdVivos)
        break;
    } while (time1.qtdVivos > 0 || time2.qtdVivos > 0 || time1.score < 20 || time2.score < 20);

    if (time2.qtdVivos ==0)
    {
        printf("\nO Time 1 sai vitorioso por ter derrotado todos os lutadores do time2!");
    }
    else if (time1.score >= 20)
    {
        printf("\nO Time 1 sai vitorioso por ter alcançado 20 pontos!");
    }

    if (time1.qtdVivos==0)
    {
        printf("\nO Time 2 sai vitorioso por ter derrotado todos os lutadores do time1!");
    }
    else if (time2.score >= 20)
    {
        printf("\nO Time 2 sai vitorioso por ter alcançado 20 pontos!");
    }
    if(time1.score==time2.score){
        printf("\nEMPATE!");
    }

    // Fase de resultados

    return 0;
}