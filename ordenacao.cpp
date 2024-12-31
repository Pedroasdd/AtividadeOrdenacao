#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NOMES 1000
#define MAX_TAMANHO_NOME 100

void bubbleSort(char nomes[][MAX_TAMANHO_NOME], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(nomes[j], nomes[j + 1]) > 0) {
                char temp[MAX_TAMANHO_NOME];
                strcpy(temp, nomes[j]);
                strcpy(nomes[j], nomes[j + 1]);
                strcpy(nomes[j + 1], temp);
            }
        }
    }
}

void selectionSort(char nomes[][MAX_TAMANHO_NOME], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(nomes[j], nomes[min_idx]) < 0) {
                min_idx = j;
            }
        }
        char temp[MAX_TAMANHO_NOME];
        strcpy(temp, nomes[min_idx]);
        strcpy(nomes[min_idx], nomes[i]);
        strcpy(nomes[i], temp);
    }
}

void insertionSort(char nomes[][MAX_TAMANHO_NOME], int n) {
    for (int i = 1; i < n; i++) {
        char key[MAX_TAMANHO_NOME];
        strcpy(key, nomes[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(nomes[j], key) > 0) {
            strcpy(nomes[j + 1], nomes[j]);
            j--;
        }
        strcpy(nomes[j + 1], key);
    }
}

void merge(char nomes[][MAX_TAMANHO_NOME], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    char L[n1][MAX_TAMANHO_NOME], R[n2][MAX_TAMANHO_NOME];

    for (int i = 0; i < n1; i++)
        strcpy(L[i], nomes[left + i]);
    for (int j = 0; j < n2; j++)
        strcpy(R[j], nomes[mid + 1 + j]);

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            strcpy(nomes[k], L[i]);
            i++;
        } else {
            strcpy(nomes[k], R[j]);
            j++;
        }
        k++;
    }

    while (i < n1) {
        strcpy(nomes[k], L[i]);
        i++;
        k++;
    }

    while (j < n2) {
        strcpy(nomes[k], R[j]);
        j++;
        k++;
    }
}

void mergeSort(char nomes[][MAX_TAMANHO_NOME], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(nomes, left, mid);
        mergeSort(nomes, mid + 1, right);
        merge(nomes, left, mid, right);
    }
}

void imprimirNomes(char nomes[][MAX_TAMANHO_NOME], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s", nomes[i]);
    }
}

int carregarNomes(const char *caminho, char nomes[][MAX_TAMANHO_NOME]) {
    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    int count = 0;
    while (fgets(nomes[count], MAX_TAMANHO_NOME, arquivo) && count < MAX_NOMES) {
        count++;
    }

    fclose(arquivo);
    return count;
}

int main() {
    char nomes[MAX_NOMES][MAX_TAMANHO_NOME];
    int totalNomes;
    char caminhoArquivo[] = "C:\\Users\\phlop\\Downloads\\nomes2.txt";

    totalNomes = carregarNomes(caminhoArquivo, nomes);
    if (totalNomes == -1) {
        return 1;
    }

    int opcao;
    do {
        printf("\nMenu de Ordenacao:\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                bubbleSort(nomes, totalNomes);
                printf("\nNomes ordenados (Bubble Sort):\n");
                imprimirNomes(nomes, totalNomes);
                break;
            case 2:
                selectionSort(nomes, totalNomes);
                printf("\nNomes ordenados (Selection Sort):\n");
                imprimirNomes(nomes, totalNomes);
                break;
            case 3:
                insertionSort(nomes, totalNomes);
                printf("\nNomes ordenados (Insertion Sort):\n");
                imprimirNomes(nomes, totalNomes);
                break;
            case 4:
                mergeSort(nomes, 0, totalNomes - 1);
                printf("\nNomes ordenados (Merge Sort):\n");
                imprimirNomes(nomes, totalNomes);
                break;
            case 5:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
