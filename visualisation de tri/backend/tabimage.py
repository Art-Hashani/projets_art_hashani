import matplotlib.pyplot as plt
import os
def create_table_image(step,current_row, previous_row, output_path, color_mapping=None):
    if color_mapping is None:
        color_mapping = {}

    
    fig, ax = plt.subplots(figsize=(10, 4))  # Ajustez la taille de la figure ici
    ax.axis('tight')
    ax.axis('off')

    # Comparaison entre la ligne actuelle et la précédente
    cell_colors = ['lightblue' if current_row[i] != previous_row[i] else 'white' for i in range(len(current_row))]

    ax.table(cellText=[current_row], cellColours=[cell_colors], loc='center', cellLoc='center', colLabels=None)
    plt.title(f"Étape {step}")  # Ajout du titre avec le numéro de l'étape

    plt.savefig(output_path, bbox_inches='tight', pad_inches=0.1)
    plt.close()

def create_sorted_table_image(sorted_data, output_path):
    fig, ax = plt.subplots(figsize=(10, 4))  # Ajustez la taille de la figure ici
    ax.axis('tight')
    ax.axis('off')

    # Toutes les valeurs en blanc
    cell_colors = ['white' for _ in range(len(sorted_data[0]))]

    ax.table(cellText=[sorted_data[-1]], cellColours=[cell_colors], loc='center', cellLoc='center', colLabels=None)
    ax.set_title('Tableau trié', fontsize=16)  # Ajustez la taille du titre ici

    plt.savefig(output_path, bbox_inches='tight', pad_inches=0.1)
    plt.close()

if __name__ == "__main__":
   # Delete PNG files starting with the script's directory
    script_directory = os.path.dirname(os.path.abspath(__file__))
    for file_name in os.listdir(script_directory):
        if file_name.endswith('.png') and file_name.startswith('output_'):
            file_path = os.path.join(script_directory, file_name)
            os.remove(file_path)
            print(f"Deleted file: {file_path}")
    for file_name in os.listdir(script_directory):
        if file_name.endswith('.png') and file_name.startswith('sorted_table_'):
            file_path = os.path.join(script_directory, file_name)
            os.remove(file_path)
            print(f"Deleted file: {file_path}")

    # Remplacez 'output.txt' par le chemin de votre fichier texte contenant les données du tableau
    with open('output.txt', 'r') as file:
        previous_row = None
        data = [] 
        i=0
        for i, line in enumerate(file):
            current_row = line.split()

            # Pour chaque ligne du fichier, créez une image avec un nom de fichier unique
            output_image_path = f'output_{i + 1}.png'

            if previous_row is not None:
                create_table_image(i+1,current_row, previous_row, output_image_path)
            else:
                # Pour la première ligne, pas de comparaison avec la ligne précédente
                create_table_image(i+1,current_row, current_row, output_image_path)

            previous_row = current_row
            data.append(current_row)
            print(f"L'image du tableau pour la ligne {i + 1} a été créée avec succès à {output_image_path}")

        # Création de l'image finale avec la dernière ligne seulement et le titre "Tableau trié"
        sorted_output_path = f'sorted_table_{i + 2}.png'
        create_sorted_table_image(data, sorted_output_path)
        print(f"L'image du tableau trié a été créée avec succès à {sorted_output_path}")