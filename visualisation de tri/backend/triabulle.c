#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int arr[], int n,FILE *file) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Échange des éléments si arr[j] est supérieur à arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                for (int k = 0; k < n; k++) {
                    fprintf(file, "%d ", arr[k]);
                }
                fprintf(file, "\n");
                // Affichage de l'étape du tri à des fins de visualisation
                for (int k = 0; k < n; k++) {
                    printf("%d ", arr[k]);
                }
                printf("\n");
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Veuillez fournir les valeurs à trier.\n");
        return 1;
    }
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier de sortie.\n");
        return 1;
    }
    
    int n = argc - 1;
    int *values = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        values[i] = atoi(argv[i + 1]);
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", values[i]);
    }
    fprintf(file, "\n");
    printf("Étapes du tri à bulles :\n");
    bubbleSort(values, n,file);

    free(values);
    return 0;
}
