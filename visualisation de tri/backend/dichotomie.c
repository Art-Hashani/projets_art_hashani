#include <stdio.h>

// Fonction de tri par dichotomie
void dichotomySort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Effectuer la recherche dichotomique pour insérer la clé à la bonne position
        int left = 0;
        int right = i - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] < key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // Déplacer les éléments plus grands que la clé vers la droite
        while (j >= left) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[left] = key;

        // Affichage de l'étape du tri pour la visualisation
        for (int k = 0; k < n; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n");
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

    printf("Étapes du tri par dichotomie :\n");
    dichotomySort(values, n);

    free(values);
    return 0;
}