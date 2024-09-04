#include <stdio.h>
#include <stdlib.h>
void triPairImpair(int arr[], int n, FILE *fichier) {
    int trie = 0;

    while (!trie) {
        trie = 1;

        // Comparaison et échange des éléments pairs
        for (int i = 0; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                // Échanger les éléments pairs
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                trie = 0;

                // Enregistrer l'étape du tri dans le fichier.
                for (int j = 0; j < n; j++) {
                    fprintf(fichier, "%d ", arr[j]);
                }
                fprintf(fichier, "\n");
            }
        }

        // Comparaison et échange des éléments impairs
        for (int i = 1; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                // Échanger les éléments impairs
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                trie = 0;

                // Enregistrer l'étape du tri dans le fichier
                for (int j = 0; j < n; j++) {
                    fprintf(fichier, "%d ", arr[j]);
                }
                fprintf(fichier, "\n");
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

    int n = argc - 1;
    int *values = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        values[i] = atoi(argv[i + 1]);
    }

    // Afficher les valeurs initiales à la console
    printf("Valeurs initiales :\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");

    // Ouvrir le fichier de sortie en mode écriture
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sortie.\n");
        return 1;
    }

    // Écrire les valeurs initiales dans le fichier
    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "%d ", values[i]);
    }
    fprintf(outputFile, "\n");

    printf("Étapes du tri par dichotomie :\n");

    // Appeler la fonction de tri en passant le fichier de sortie
    triPairImpair(values, n,outputFile);

    // Fermer le fichier de sortie
    fclose(outputFile);

    free(values);
    

    return 0;
}