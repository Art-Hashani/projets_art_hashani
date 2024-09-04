#include <stdio.h>
#include <stdlib.h>
void triPeigne(int tableau[], int taille, FILE *fichier) {
    int ecart = taille;
    int swap = 1;

    while (ecart > 1 || swap) {
        if (ecart > 1) {
            ecart = (ecart * 10) / 13; // Réduction de l'écart
        }

        swap = 0;

        for (int i = 0; i < taille - ecart; i++) {
            if (tableau[i] > tableau[i + ecart]) {
                // Échanger les éléments si l'élément courant est plus grand que l'élément éloigné de l'écart
                int temp = tableau[i];
                tableau[i] = tableau[i + ecart];
                tableau[i + ecart] = temp;
                swap = 1;

                // Enregistrer l'étape du tri dans le fichier
                
                for (int j = 0; j < taille; j++) {
                    fprintf(fichier, "%d ", tableau[j]);
                }
                fprintf(fichier, "\n");
                // Affichage de l'étape du tri à des fins de visualisation
                for (int k = 0; k < taille; k++) {
                printf("%d ", tableau[k]);
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

    triPeigne(values,n, file);

    fclose(file);
    free(values);
    return 0;
}