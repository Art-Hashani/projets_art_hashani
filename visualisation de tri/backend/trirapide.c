#include <stdio.h>
#include <stdlib.h>

// Fonction pour le tri rapide (Quick Sort)
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Partitionnement du tableau et obtention du pivot
        int pivot = partition(arr, low, high);

        // Affichage de l'étape actuelle du tri
        printf("Étape du tri : ");
        for (int i = low; i <= high; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Tri des sous-tableaux avant et après le pivot
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

// Fonction pour partitionner le tableau
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choix du dernier élément comme pivot
    int i = (low - 1); // Index du plus petit élément

    for (int j = low; j <= high - 1; j++) {
        // Si l'élément actuel est plus petit que le pivot
        if (arr[j] < pivot) {
            i++; // Incrémentation de l'index du plus petit élément
            // Échange des éléments arr[i] et arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Échange de arr[i+1] et arr[high] (pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Veuillez fournir des valeurs à trier.\n");
        return 1;
    }

    int n = argc - 1;
    int *arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    printf("Tableau avant le tri : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    quickSort(arr, 0, n - 1);

    printf("\nTableau après le tri : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}