#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>




//Créer une structure comportant les informations d'une case
struct Zone{
    bool nord;
    bool sud;
    bool est;
    bool ouest;
    int passage;
    int valeur;
    bool resolu;
};
typedef struct Zone Zone;

//i=hauteur, j=largeur (dans tout le projet)
//Créer une grille de case,initialiser tout les murs et passages. (false=0)
Zone** cellules(int hauteur, int largeur){
    Zone** grille = malloc(hauteur*sizeof(Zone*));
    for(int i=0;i<hauteur;i++){
        grille[i] = malloc(largeur*sizeof(Zone));
        for(int j=0;j<largeur;j++){
            Zone Case = {true,true,true,true,0,j+(largeur-1)*i+i,false};
            grille[i][j] = Case;
        }
    }
    return grille;
}

//Vérifier si toutes les valeurs de la grilles sont égales
bool verification(int hauteur , int largeur, Zone** grille){
    int val = grille[0][0].valeur;
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            if(val != grille[i][j].valeur) return false;
        }  
    }
    return true;
}

void afficher_texte(TTF_Font *police, SDL_Surface *surface, char *texte, int x, int y) {
    SDL_Color couleur_texte = {255, 255, 255}; // blanc
    SDL_Surface *surface_texte = TTF_RenderText_Blended(police, texte, couleur_texte);
    SDL_Rect position_texte = {x, y, 0, 0};
    SDL_BlitSurface(surface_texte, NULL, surface, &position_texte);
    SDL_FreeSurface(surface_texte);
}

void afficherTexte(SDL_Renderer* renderer, TTF_Font* font, const char* texte, int x, int y) {
    // Création de la couleur du texte (blanc)
    SDL_Color textColor = {255, 255, 255, 255};

    // Création de la surface du texte
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, texte, textColor);
    if (textSurface == NULL) {
        printf("Erreur lors de la création de la surface du texte : %s\n", TTF_GetError());
        return;
    }

    // Création de la texture du texte
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        printf("Erreur lors de la création de la texture du texte : %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    // Libération de la surface du texte (plus nécessaire une fois la texture créée)
    SDL_FreeSurface(textSurface);

    // Obtention des dimensions du texte
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    // Position du texte
    SDL_Rect textRect;
    textRect.x = x;
    textRect.y = y;
    textRect.w = textWidth;
    textRect.h = textHeight;

    // Affichage du texte
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Libération de la texture du texte
    SDL_DestroyTexture(textTexture);
}


//Afficher le labyrinthe

void creerFenetre(SDL_Window** window, SDL_Renderer** renderer, TTF_Font** font) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() != 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return;
    }

    // Création de la fenêtre
    *window = SDL_CreateWindow("Labyrinthe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return;
    }

    // Création du renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    // Chargement de la police de caractères
    *font = TTF_OpenFont("arial.ttf", 24);
    if (*font == NULL) {
        printf("Erreur lors du chargement de la police de caractères : %s\n", TTF_GetError());
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        TTF_Quit();
        SDL_Quit();
        return;
    }
}

void afficherlabyrinthe(int hauteur, int largeur, Zone** grille, int rep) {
    const int CELL_SIZE = 50;
    const int WINDOW_WIDTH = largeur * CELL_SIZE;
    const int WINDOW_HEIGHT = hauteur * CELL_SIZE;

    // Variables de fenêtre et de rendu
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;

    // Création de la fenêtre et initialisation des ressources
    creerFenetre(&window, &renderer, &font);
    if (window == NULL || renderer == NULL || font == NULL) {
        return;
    }

    // Boucle principale de l'application
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
/*******²

    // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
  
        // Dessiner le carre
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // ligne haut
        SDL_RenderDrawLine(renderer, 100, 100, (largeur * 50) + 50, 100);
        // ligne bas
        SDL_RenderDrawLine(renderer, 100, (hauteur * 50) + 50,  (largeur * 50) + 50, (hauteur * 50) + 50);
        // ligne gauche
        SDL_RenderDrawLine(renderer, 100, 100, 100, (hauteur * 50) + 50);
        // ligne droite
         SDL_RenderDrawLine(renderer, (largeur * 50) + 50,  100, (largeur * 50) + 50, (hauteur * 50) + 50);
************/
        // Effacement de l'écran avec une couleur de fond (noir)
        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        //SDL_RenderClear(renderer);

        // Afficher le labyrinthe (Cellules et murs)
        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < largeur; j++) {
                int x1 = (j+1) * CELL_SIZE;
                int y1 = (i+1) * CELL_SIZE;
                int x2 = x1 + CELL_SIZE;
                int y2 = y1 + CELL_SIZE;

		//printf("X1 : %d  X2 : %d Y1 : %d Y2 : %d \n",x1,x2,y1,y2);
                // Dessin de la cellule
                SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
                SDL_RenderFillRect(renderer, &(SDL_Rect){x1, y1, CELL_SIZE, CELL_SIZE});

                // Dessin des murs nord, sud, est, ouest
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                if (grille[i][j].nord) {
                    SDL_RenderDrawLine(renderer, x1, y1, x2, y1);
                }
                if (grille[i][j].sud) {
                    SDL_RenderDrawLine(renderer, x1, y2, x2, y2);
                }
                if (grille[i][j].est) {
                    SDL_RenderDrawLine(renderer, x2, y1, x2, y2);
                }
                if (grille[i][j].ouest) {
                    SDL_RenderDrawLine(renderer, x1, y1, x1, y2);
                }

                // Afficher valeur dans la case ou pas (personnel)
                if (rep == 2 || rep == 4) {
                    char valeur[10];
                    sprintf(valeur, "%d", grille[i][j].valeur);
                    afficherTexte(renderer, font, valeur, x1 + 10, y1 + 10);
                }
            }
        }

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}


//Supprimer des murs aléatoirement et changer les valeurs des cases
void generer(int hauteur, int largeur, Zone** grille, int rep){
    int i,j,h,l,direction,val,val2;
    srand(time(NULL));
   
    while(verification(hauteur,largeur,grille) != true){
        direction = rand()%4;
        //Afficher grille chaques étape
        if(rep == 2 || rep == 4) afficherlabyrinthe(hauteur,largeur,grille,rep);
       
        if(direction==0){ //0 = NORD = haut
            i = (rand()%(hauteur-1))+1; // i est entre 1 et 4
            j = rand()%largeur;
            if(rep == 2 || rep == 4){
                printf("\n");
                printf("Nord, %d, %d \n\n\n\n", i, j);
            }
            if(grille[i][j].passage<=1 && grille[i][j].valeur != grille[i-1][j].valeur){
                grille[i][j].nord = false;
                grille[i-1][j].sud = false;
                grille[i][j].passage += 1;
                val = grille[i][j].valeur;
                val2 = grille[i-1][j].valeur;
                for(h=0;h<hauteur;h++){
                    for(l=0;l<largeur;l++){
                        if(grille[h][l].valeur == val) grille[h][l].valeur = val2;
                    }
                }
            }
        }if(direction==1){ //1 = SUD = bas
            i = rand()%(hauteur-1);// i est entre 0 et 3
            j = rand()%largeur;
            if(rep == 2 || rep == 4){
                printf("\n");
                printf("Sud, %d, %d \n\n\n\n", i, j);
            }
            if(grille[i][j].passage<=0 && grille[i][j].valeur != grille[i+1][j].valeur){
                grille[i][j].sud = false;
                grille[i+1][j].nord = false;
                grille[i][j].passage += 1;
                val = grille[i][j].valeur;
                val2 = grille[i+1][j].valeur;
                for(h=0;h<hauteur;h++){
                    for(l=0;l<largeur;l++){
                        if(grille[h][l].valeur == val) grille[h][l].valeur = val2;
                    }
                }
            }
        }if(direction==2){ //2 = EST = droite
            i = rand()%hauteur;
            j = rand()%(largeur-1);//j est entre 0 et 4
            if(rep == 2 || rep == 4){
                printf("\n");
                printf("Est, %d, %d \n\n\n\n", i, j);
            }
            if(grille[i][j].passage<=0 && grille[i][j].valeur != grille[i][j+1].valeur){
                grille[i][j].est = false;
                grille[i][j+1].ouest = false;
                grille[i][j].passage += 1;
                val = grille[i][j].valeur;
                val2 = grille[i][j+1].valeur;
                for(h=0;h<hauteur;h++){
                    for(l=0;l<largeur;l++){
                        if(grille[h][l].valeur == val) grille[h][l].valeur = val2;
                    }
                }
            }
        }if(direction==3){ //3 = OUEST = gauche
            i = rand()%hauteur;
            j = rand()%(largeur-1)+1; // j est entre 1 et 4
            if(rep == 2 || rep == 4){
                printf("\n");
                printf("Ouest, %d, %d \n\n\n\n", i, j);
            }
            if(grille[i][j].passage<=1 && grille[i][j].valeur != grille[i][j-1].valeur){
                grille[i][j].ouest = false;
                grille[i][j-1].est = false;
                grille[i][j].passage += 1;
                val = grille[i][j].valeur;
                val2 = grille[i][j-1].valeur;
                for(h=0;h<hauteur;h++){
                    for(l=0;l<largeur;l++){
                        if(grille[h][l].valeur == val) grille[h][l].valeur = val2;
                    }
                }
            }
        }
    }
}

bool verif_resolution(int hauteur, int largeur, Zone** grille){
    int i,j;
    for(i=(hauteur-1);i>=0;i=i-1){
        for(int j=(largeur-1);j>=0;j=j-1){
            if(grille[i][j].resolu == false) return false;
        }
    }
    return true;
}

void afficher_resolution(int hauteur,int largeur, Zone** grille, int resolution){
    int i,j;
   
    //Première ligne de sols* (*sol = mur horizontal)
    for(j=0;j<largeur;j++){
        if(j==0) printf("┌───");
        if(j==largeur-1) printf("┐");
        else if(grille[0][j].est == false) printf("────");
        else printf("┬───");
    }
   
    //Afficher le labyrinthe (cellules et murs)
    for(i=0;i<hauteur;i++){
        printf("\n│ "); //Première colonne de murs
        for(j=0;j<largeur;j++){
            //Afficher valeur dans la case ou pas (personnel)
            if(j<largeur){
                if(grille[i][j].valeur == 0){
                    printf("*");
                }else printf(" ");
            }
           
            if(j==(largeur-1) || (grille[i][j].est == true
                && grille[i][j+1].ouest == true)){
                printf(" │ ");
            }else printf("   ");
        }
        printf("\n");
        for(j=0;j<largeur;j++){
            if(i == (hauteur-1) || (grille[i][j].sud == true
                && grille[i+1][j].nord == true)){
                //Dernier ligne sols
                if(i==hauteur-1){
                    if(j==0) printf("└───");
                    if(j==largeur-1) printf("┘");
                    else if(grille[i][j].est == false) printf("────");
                    else printf("┴───");
                }else printf(" ───");
               
            }else printf("    ");
        }
    }
}

//Résolution du labyrinthe
Zone** resoudre(int hauteur, int largeur,Zone**grille){
    int i,j;
    for(i=0;i<hauteur;i++){
        for(j=0;j<largeur;j++) grille[i][j].valeur = 0;
    }
    while(verif_resolution(hauteur,largeur,grille) == false){
        for(i=(hauteur-1);i>=0;i=i-1){
            for(j=(largeur-1);j>=0;j=j-1){
                if(grille[i][j].resolu == false){
                    if(grille[i][j].valeur != 0 || (i==(hauteur-1) && j == (largeur-1))){
                        //Nord
                        if(i>0 && grille[i][j].nord == false && grille[i-1][j].resolu == false){
                            grille[i-1][j].valeur = grille[i][j].valeur + 1;
                        }
                        //Sud
                        if(i<(hauteur-1) && grille[i][j].sud == false && grille[i+1][j].resolu == false){
                            grille[i+1][j].valeur = grille[i][j].valeur + 1;
                        }
                        //Est
                        if(j<(largeur-1) && grille[i][j].est == false && grille[i][j+1].resolu == false){
                            grille[i][j+1].valeur = grille[i][j].valeur + 1;
                        }
                        //Ouest
                        if(j>0 && grille[i][j].ouest == false && grille[i][j-1].resolu == false){
                            grille[i][j-1].valeur = grille[i][j].valeur + 1;
                        }
                        grille[i][j].resolu = true;
                    }
                }
            }
        }
    }

    //Remettre toute les cases à resolu = false
    for(i=0;i<hauteur;i++){
        for(j=0;j<largeur;j++) grille[i][j].resolu = false;
    }


    i=0;
    j=0;
    while(i != (hauteur-1) || j != (largeur-1) ){
        //Nord
        if(i>0 && grille[i][j].nord == false && (grille[i-1][j].valeur <= grille[i][j].valeur) && grille[i-1][j].resolu == false){
            grille[i][j].valeur = 0;
            grille[i][j].resolu = true;
            i--;
        }
        //Sud
        if(i<(hauteur-1) && grille[i][j].sud == false && (grille[i+1][j].valeur <= grille[i][j].valeur) && grille[i+1][j].resolu == false){
            grille[i][j].valeur = 0;
            grille[i][j].resolu = true;
            i++;
        }
        //Est
        if(j<(largeur-1) && grille[i][j].est == false && (grille[i][j+1].valeur <= grille[i][j].valeur) && grille[i][j+1].resolu == false){
            grille[i][j].valeur = 0;
            grille[i][j].resolu = true;
            j++;
        }
        //Ouest
        if(j>0 && grille[i][j].ouest == false && (grille[i][j-1].valeur <= grille[i][j].valeur) && grille[i][j-1].resolu == false){
            grille[i][j].valeur = 0;
            grille[i][j].resolu = true;
            j--;
        }
       
    }
    grille[hauteur-1][largeur-1].valeur = 0;
    grille[hauteur-1][largeur-1].resolu = true;
    return grille;
}

//Crée le labyrinthe
Zone** cree(int hauteur, int largeur, int rep){
    Zone**grille;
    grille = cellules(hauteur,largeur);
    generer(hauteur,largeur,grille,rep); //aléatoire
    return grille;
}

void menu(){
    int largeur,hauteur,rep,resolution;
    Zone** grille;
   
/***********************************************************
    //MENU
    printf("\n###############################################################\n");
    printf("Consigne : Entrez votre chiffre puis taper [Entrer].\n\n");
    printf("Menu : \n");

    printf("(1) Generer un labyrinthe simple.\n");
    printf("(2) Generer un labyrinthe en affichant toutes ses étapes.\n");
    printf("(3) Generer un labyrinthe avec ses valeurs.\n");
    printf("(4) Generer un labyrinthe en affichant ses étapes et ses valeurs.\n");
   
    printf("Votre réponse : ");
    scanf("%d",&rep);
    if(rep > 4){
        printf("\n\n\nERREUR : Chiffre incorrect, il ne correspond à aucune option\n\n\n");
        menu();
    }
    if(rep == 3 || rep == 4){
        printf("\n(CONSEIL) 3x3 maximum pour eviter les décalages\n\n");
    }else printf("\n(CONSEIL) 15x15 maximum pour éviter que ce soit long\n\n");
    printf("Entrez la [hauteur] du labyrinthe : ");
    scanf("%d",&hauteur);
    printf("Entrez maintenant sa [largeur] : ");
    scanf("%d",&largeur);
    grille = cree(hauteur,largeur,rep);
    printf("\nVoila le labyrinthe de taille %d x %d : \n\n", hauteur,largeur);
    afficherlabyrinthe(hauteur,largeur,grille,rep);
    printf("\n\nVoulez vous sa résolution ?\n");
    printf("(1) Oui.\n");
    printf("(autre) Non.\n");
    printf("Votre réponse : ");
    scanf("%d",&resolution);
    if(resolution == 1){
        //Afficher la grille avec sa resolution (programme pas encore fini)
        printf("\n\nVoilà la résolution du labyrinthe : \n");
        printf("\n\nATTENTION : Fontion résolution pas encore vérifiée, erreur possible.\n");
        grille = resoudre(hauteur,largeur,grille);
        afficherlabyrinthe(hauteur,largeur,grille,resolution);
    }
    printf("\n\nFin !\n");
    printf("\n###############################################################\n");
*******************************************************************/
	rep = 1;
	hauteur = 10;
	largeur = 10;
    grille = cree(hauteur,largeur,rep);
    afficherlabyrinthe(hauteur,largeur,grille,rep);
}

int main(){
    menu();
    return 0;
}
