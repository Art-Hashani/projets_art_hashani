#include <stdio.h>
#include <stdlib.h>

void tri_insertion(int arr[], int n, FILE *fichier) {
    int i, cle, j;
    for (i = 1; i < n; i++) {
        cle = arr[i];
        j = i - 1;

        // Déplace les éléments de arr[0..i-1] qui sont plus grands que la clé
        while (j >= 0 && arr[j] > cle) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = cle;

        // Enregistre l'étape actuelle dans le fichier
        for (int k = 0; k < n; k++) {
            fprintf(fichier, "%d ", arr[k]);
        }
        fprintf(fichier, "\n");
        // Affichage de l'étape du tri à des fins de visualisation
        for (int k = 0; k < n; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n");
    }
   
}

void afficher_tableau(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
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

    tri_insertion(values,n, file);

    fclose(file);
    free(values);
    return 0;
}