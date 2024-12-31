#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TIMES 20
#define MAX_JOGOS 100
#define MAX_NOME 20

typedef struct {
    char nome[MAX_NOME];
    int pontos;
    int vitorias;
    int empates;
    int derrotas;
    int gols_pro;
    int gols_contra;
    int saldo_gols;
} Time;

void inicializarTimes(Time times[], int *qtdTimes) {
    *qtdTimes = 0;
}

int encontrarOuAdicionarTime(Time times[], int *qtdTimes, const char *nome) {
    for (int i = 0; i < *qtdTimes; i++) {
        if (strcmp(times[i].nome, nome) == 0) {
            return i;
        }
    }

    strcpy(times[*qtdTimes].nome, nome);
    times[*qtdTimes].pontos = 0;
    times[*qtdTimes].vitorias = 0;
    times[*qtdTimes].empates = 0;
    times[*qtdTimes].derrotas = 0;
    times[*qtdTimes].gols_pro = 0;
    times[*qtdTimes].gols_contra = 0;
    times[*qtdTimes].saldo_gols = 0;
    return (*qtdTimes)++;
}

void processarResultado(Time times[], int *qtdTimes, const char *linha) {
    char time1[MAX_NOME], time2[MAX_NOME];
    int gols1, gols2;
    sscanf(linha, "%s %dX%d %s", time1, &gols1, &gols2, time2);

    int idx1 = encontrarOuAdicionarTime(times, qtdTimes, time1);
    int idx2 = encontrarOuAdicionarTime(times, qtdTimes, time2);

    times[idx1].gols_pro += gols1;
    times[idx1].gols_contra += gols2;
    times[idx1].saldo_gols = times[idx1].gols_pro - times[idx1].gols_contra;

    times[idx2].gols_pro += gols2;
    times[idx2].gols_contra += gols1;
    times[idx2].saldo_gols = times[idx2].gols_pro - times[idx2].gols_contra;

    if (gols1 > gols2) {
        times[idx1].pontos += 3;
        times[idx1].vitorias++;
        times[idx2].derrotas++;
    } else if (gols1 < gols2) {
        times[idx2].pontos += 3;
        times[idx2].vitorias++;
        times[idx1].derrotas++;
    } else {
        times[idx1].pontos++;
        times[idx2].pontos++;
        times[idx1].empates++;
        times[idx2].empates++;
    }
}

int compararTimes(const void *a, const void *b) {
    Time *timeA = (Time *)a;
    Time *timeB = (Time *)b;

    if (timeB->pontos != timeA->pontos)
        return timeB->pontos - timeA->pontos;
    if (timeB->vitorias != timeA->vitorias)
        return timeB->vitorias - timeA->vitorias;
    if (timeB->saldo_gols != timeA->saldo_gols)
        return timeB->saldo_gols - timeA->saldo_gols;
    return timeB->gols_pro - timeA->gols_pro;
}

void bubbleSort(Time times[], int qtdTimes) {
    for (int i = 0; i < qtdTimes - 1; i++) {
        for (int j = 0; j < qtdTimes - i - 1; j++) {
            if (compararTimes(&times[j], &times[j + 1]) > 0) {
                Time temp = times[j];
                times[j] = times[j + 1];
                times[j + 1] = temp;
            }
        }
    }
}

void selectionSort(Time times[], int qtdTimes) {
    for (int i = 0; i < qtdTimes - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < qtdTimes; j++) {
            if (compararTimes(&times[j], &times[minIndex]) > 0) {
                minIndex = j;
            }
        }
        Time temp = times[i];
        times[i] = times[minIndex];
        times[minIndex] = temp;
    }
}

void insertionSort(Time times[], int qtdTimes) {
    for (int i = 1; i < qtdTimes; i++) {
        Time chave = times[i];
        int j = i - 1;
        while (j >= 0 && compararTimes(&times[j], &chave) < 0) {
            times[j + 1] = times[j];
            j--;
        }
        times[j + 1] = chave;
    }
}

void merge(Time times[], int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = (esquerda + direita) / 2;
        merge(times, esquerda, meio);
        merge(times, meio + 1, direita);

        Time temp[direita - esquerda + 1];
        int i = esquerda, j = meio + 1, k = 0;

        while (i <= meio && j <= direita) {
            if (compararTimes(&times[i], &times[j]) > 0) {
                temp[k++] = times[i++];
            } else {
                temp[k++] = times[j++];
            }
        }

        while (i <= meio) {
            temp[k++] = times[i++];
        }

        while (j <= direita) {
            temp[k++] = times[j++];
        }

        for (int i = 0; i < k; i++) {
            times[esquerda + i] = temp[i];
        }
    }
}

void imprimirTabela(Time times[], int qtdTimes) {
    printf("\nTabela do Campeonato:\n");
    printf("%-20s %3s %3s %3s %3s %5s %5s %5s\n", "Time", "Pts", "Vit", "Emp", "Der", "SG", "GP", "GC");
    for (int i = 0; i < qtdTimes; i++) {
        printf("%-20s %3d %3d %3d %3d %5d %5d %5d\n", times[i].nome, times[i].pontos, times[i].vitorias,
               times[i].empates, times[i].derrotas, times[i].saldo_gols, times[i].gols_pro, times[i].gols_contra);
    }
}

int main() {
    Time times[MAX_TIMES];
    int qtdTimes;
    char linha[100];
    char caminhoArquivo[] = "C:\\Users\\phlop\\Downloads\\dados.txt";
    int metodoOrdenacao;

    inicializarTimes(times, &qtdTimes);

    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
        processarResultado(times, &qtdTimes, linha);
    }

    fclose(arquivo);

    do {
        printf("\nEscolha o metodo de ordenacao:\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &metodoOrdenacao);

        switch (metodoOrdenacao) {
            case 1:
                bubbleSort(times, qtdTimes);
                break;
            case 2:
                selectionSort(times, qtdTimes);
                break;
            case 3:
                insertionSort(times, qtdTimes);
                break;
            case 4:
                merge(times, 0, qtdTimes - 1);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida\n");
                continue;
        }

        if (metodoOrdenacao != 5) {
            imprimirTabela(times, qtdTimes);
        }

    } while (metodoOrdenacao != 5);

    return 0;
}
