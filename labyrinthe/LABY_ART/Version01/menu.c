#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "labyrinthe.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

void afficher_texte(TTF_Font *police, SDL_Surface *surface, char *texte, int x, int y) {
    SDL_Color couleur_texte = {255, 255, 255}; // blanc
    SDL_Surface *surface_texte = TTF_RenderText_Blended(police, texte, couleur_texte);
    SDL_Rect position_texte = {x, y, 0, 0};
    SDL_BlitSurface(surface_texte, NULL, surface, &position_texte);
    SDL_FreeSurface(surface_texte);
}

int Saisie(SDL_Surface *surface_fenetre, SDL_Window *fenetre, int x, int y) {
    int reponse ;
    char *Text = malloc(100 * sizeof(char));
    strcpy(Text, "");
    TTF_Font *police = TTF_OpenFont("arial.ttf", 24);
    SDL_Event evenement;
    while (1) {
        SDL_WaitEvent(&evenement);
        if (evenement.type == SDL_QUIT) break;
        if (evenement.type == SDL_KEYDOWN && evenement.key.keysym.sym == SDLK_RETURN) {
            break;
        }
        if (evenement.type == SDL_KEYDOWN && evenement.key.keysym.sym == SDLK_BACKSPACE) {
            if (strlen(Text) > 0) {
                Text[strlen(Text)] = '\0';
            }
        }
        if (evenement.type == SDL_TEXTINPUT) {
            if (strlen(Text) < 100) {
                strcat(Text, evenement.text.text);
            }
        }
        reponse = atoi(Text);
        afficher_texte(police, surface_fenetre, Text, x, y);
        SDL_UpdateWindowSurface(fenetre);
    }
    TTF_CloseFont(police);
    // return Text;
    return reponse;
}

int menu() {
    	int reponse;
	int Hauteur, Largeur;

    	TTF_Init();

    	SDL_Init(SDL_INIT_VIDEO);

    	SDL_Window *fenetre = SDL_CreateWindow("Question / Réponse", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    	SDL_Surface *surface_fenetre = SDL_GetWindowSurface(fenetre);

    	TTF_Font *police = TTF_OpenFont("arial.ttf", 24);

    	char saisie[100] = "";

    	afficher_texte(police, surface_fenetre,
                "\n###############################################################\n",
                50, 50);
    	afficher_texte(police, surface_fenetre,
                "Consigne : Entrez votre chiffre puis taper [Entrer].\n\n",
                50, 100);
    	afficher_texte(police, surface_fenetre,
                "(1) Generer un labyrinthe simple.\n",
                50, 150);
    	afficher_texte(police, surface_fenetre,
                "(2) Generer un labyrinthe en affichant toutes ses étapes.\n",
                50, 200);
    	afficher_texte(police, surface_fenetre,
                "(3) Generer un labyrinthe avec ses valeurs.\n",
                50, 250);
    	afficher_texte(police, surface_fenetre,
                "(4) Generer un labyrinthe en affichant ses étapes et ses valeurs.\n",
                50, 300);
    	afficher_texte(police, surface_fenetre,
                "Votre réponse : ",
                50, 350);

    	SDL_UpdateWindowSurface(fenetre);

    	bool Quit = false;
    	SDL_Event evenement;
    	while (!Quit) {
                reponse = Saisie(surface_fenetre, fenetre, 250, 350);

        	// reponse = atoi(saisie);
        	if (reponse == 3 || reponse == 4) {
            		afficher_texte(police, surface_fenetre,
                            	"(CONSEIL) 3x3 maximum pour eviter les décalages",
                            	50, 400);
        	} else if (reponse == 1) {
        		afficher_texte(police, surface_fenetre,
                        	"(CONSEIL) 15x15 maximum pour éviter que ce soit long",
                        	50, 400);
        		afficher_texte(police, surface_fenetre,
                        	"Entrez la [hauteur] du labyrinthe : ",
                        	50, 450);
        		Hauteur = Saisie(surface_fenetre, fenetre, 425, 450);
        		afficher_texte(police, surface_fenetre,
                        	"Entrez maintenant sa [largeur] : ",
                        	50, 500);
        		Largeur = Saisie(surface_fenetre, fenetre, 425, 500);

        		Quit = true;
            	}
                SDL_UpdateWindowSurface(fenetre);
	}
    	TTF_CloseFont(police);
    	TTF_Quit();
    	SDL_DestroyWindow(fenetre);
	Labyrinthe(reponse, Hauteur, Largeur);
    	SDL_Quit();
    	return 0;
}

