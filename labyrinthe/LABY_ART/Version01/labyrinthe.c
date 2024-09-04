#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//Créer une structure comportant les informations d'une case

struct Zone {
    bool Nord;
    bool Sud;
    bool Est;
    bool Ouest;
    int  Passage;
    int  Valeur;
    bool Resolu;
};

typedef struct Zone Zone;

//i=Hauteur, j=Largeur (dans tout le projet)
//Créer une Grille de case,initialiser tout les murs et Passages. (false=0)

Zone** Cellules(int Hauteur, int Largeur)
{
    Zone** Grille = malloc(Hauteur*sizeof(Zone*));
    for(int i=0;i<Hauteur;i++){
        Grille[i] = malloc(Largeur*sizeof(Zone));
        for(int j=0;j<Largeur;j++){
            Zone Case = {true,true,true,true,0,j+(Largeur-1)*i+i,false};
            Grille[i][j] = Case;
        }
    }
    return Grille;
}

//Vérifier si toutes les valeurs de la Grilles sont égales

bool Verification(int Hauteur , int Largeur, Zone** Grille)
{
    int val = Grille[0][0].Valeur;
    for(int i=0;i<Hauteur;i++){
        for(int j=0;j<Largeur;j++){
            if(val != Grille[i][j].Valeur) 
		return false;
        }  
    }
    return true;
}

//Afficher le labyrinthe

void Afficher(int Hauteur,int Largeur, Zone** Grille, int Reponse)
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	int i;
	int j;

	int x1;
	int y1;
	int x2;
	int y2;

    SDL_Window* window = SDL_CreateWindow("Labyrinthe", 100, 100, 800, 800, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event event;

    while(!quit)
    {
        // Gérer les événements
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

    // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
   
        // Dessiner le carre
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // ligne haut
        SDL_RenderDrawLine(renderer, 100, 100, (Largeur * 50) + 50, 100);
        // ligne bas
        SDL_RenderDrawLine(renderer, 100, (Hauteur * 50) + 50,  
			(Largeur * 50) + 50, (Hauteur * 50) + 50);
        // ligne gauche
        SDL_RenderDrawLine(renderer, 100, 100, 100, (Hauteur * 50) + 50);
        // ligne droite
         SDL_RenderDrawLine(renderer, (Largeur * 50) + 50,  100, 
			(Largeur * 50) + 50, (Hauteur * 50) + 50);

	y1 = 100 ;
	y2 = 150 ;

        //Afficher le labyrinthe (Cellules et murs)
        for(i=1;i<Hauteur;i++){
        	x1 = 100 ;
        	// x2 = 150 ;		//à essayer
        	x2 = 100 ;

                //Afficher valeur dans la case ou pas (personnel)
                for(j=0;j<Largeur;j++){ 
                        if(j==(Largeur-1) || (Grille[i][j].Est == true && 
				Grille[i][j+1].Ouest == true)){
        			SDL_RenderDrawLine(renderer, x1 , y1, x2, y2);
                        }
                    	else if(Grille[i][j].Est == false) 
        			SDL_RenderDrawLine(renderer, x2, y2, x2 + 50, y2);

                	x1 = x1 + 50;
                	x2 = x2 + 50;
                }
                y1 = y1 + 50;
                y2 = y2 + 50;
	}
        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);
      }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//Supprimer des murs aléatoirement et changer les valeurs des cases
void Generer(int Hauteur, int Largeur, Zone** Grille, int Reponse)
{
    int i,j,h,l,Direction,val,val2;
    srand(time(NULL));
   
    while(Verification(Hauteur,Largeur,Grille) != true){
        Direction = rand()%4;					 //Afficher Grille chaques étape
        if(Reponse == 2 || Reponse == 4) 
		Afficher(Hauteur,Largeur,Grille,Reponse);
       
        if(Direction==0){ 					//0 = NORD = haut
            i = (rand()%(Hauteur-1))+1; 			// i Est entre 1 et 4
            j = rand()%Largeur;
            if(Reponse == 2 || Reponse == 4){
                printf("\n");
                printf("Nord, %d, %d \n\n\n\n", i, j);
            }
            if(Grille[i][j].Passage<=1 && Grille[i][j].Valeur != Grille[i-1][j].Valeur){
                Grille[i][j].Nord = false;
                Grille[i-1][j].Sud = false;
                Grille[i][j].Passage += 1;
                val = Grille[i][j].Valeur;
                val2 = Grille[i-1][j].Valeur;
                for(h=0;h<Hauteur;h++){
                    for(l=0;l<Largeur;l++){
                        if(Grille[h][l].Valeur == val) Grille[h][l].Valeur = val2;
                    }
                }
            }
        }if(Direction==1){ 					//1 = SUD = bas
            i = rand()%(Hauteur-1);				// i Est entre 0 et 3
            j = rand()%Largeur;
            if(Reponse == 2 || Reponse == 4){
                printf("\n");
                printf("Sud, %d, %d \n\n\n\n", i, j);
            }
            if(Grille[i][j].Passage<=0 && Grille[i][j].Valeur != Grille[i+1][j].Valeur){
                Grille[i][j].Sud = false;
                Grille[i+1][j].Nord = false;
                Grille[i][j].Passage += 1;
                val = Grille[i][j].Valeur;
                val2 = Grille[i+1][j].Valeur;
                for(h=0;h<Hauteur;h++){
                    for(l=0;l<Largeur;l++){
                        if(Grille[h][l].Valeur == val) 
				Grille[h][l].Valeur = val2;
                    }
                }
            }
        }if(Direction==2){ 					//2 = EST = droite
            i = rand()%Hauteur;
            j = rand()%(Largeur-1);				//j Est entre 0 et 4
            if(Reponse == 2 || Reponse == 4){
                printf("\n");
                printf("Est, %d, %d \n\n\n\n", i, j);
            }
            if(Grille[i][j].Passage<=0 && Grille[i][j].Valeur != Grille[i][j+1].Valeur){
                Grille[i][j].Est = false;
                Grille[i][j+1].Ouest = false;
                Grille[i][j].Passage += 1;
                val = Grille[i][j].Valeur;
                val2 = Grille[i][j+1].Valeur;
                for(h=0;h<Hauteur;h++){
                    for(l=0;l<Largeur;l++){
                        if(Grille[h][l].Valeur == val) Grille[h][l].Valeur = val2;
                    }
                }
            }
        }if(Direction==3){ 					//3 = OUEST = gauche
            i = rand()%Hauteur;
            j = rand()%(Largeur-1)+1; 				// j Est entre 1 et 4
            if(Reponse == 2 || Reponse == 4){
                printf("\n");
                printf("Ouest, %d, %d \n\n\n\n", i, j);
            }
            if(Grille[i][j].Passage<=1 && Grille[i][j].Valeur != Grille[i][j-1].Valeur){
                Grille[i][j].Ouest = false;
                Grille[i][j-1].Est = false;
                Grille[i][j].Passage += 1;
                val = Grille[i][j].Valeur;
                val2 = Grille[i][j-1].Valeur;
                for(h=0;h<Hauteur;h++){
                    for(l=0;l<Largeur;l++){
                        if(Grille[h][l].Valeur == val) Grille[h][l].Valeur = val2;
                    }
                }
            }
        }
    }
}


void Labyrinthe(int Reponse, int Hauteur, int Largeur)
{
    // int Largeur, Hauteur, Resolution;
    Zone** Grille;
    // Hauteur=10;
    // Largeur=10;
    // Reponse=1;

    Grille = Cellules(Hauteur,Largeur);
    Generer(Hauteur,Largeur,Grille,Reponse);                            // Aléatoire
    Afficher(Hauteur,Largeur,Grille,Reponse);
}

