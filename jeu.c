//-------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------//
//Bibliothèques:
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include <ctype.h>
#define RED "\033[31m"
#define BLUE "\033[34m"
#define WHITE "\033[37m"
//-------------------------------------------------------------------------------------------------------------//
static char plateau[DIMENSION][DIMENSION];
//-------------------------------------------------------------------------------------------------------------//
/*Fonction qui permet de vérifier sur le pion est un roi ou un simple pion*/
char * get_pion(board game , int l , int c){
		if (is_king(game , l , c) == 1){
					return "♚";
				}	
				else return "♟";
}
//-------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------//
/*Fonction qui permet d'afficher le tableau*/
void afficheplateau(board game){
    int c;
    int l ;
    printf("\n");   
    printf("+");
    for (c = 1; c <= DIMENSION; c++)
        printf("---+"); 
    printf("\n");
    
    for (l = 0; l < DIMENSION; l++)
    {
        printf("|");
        for (c = 0; c < DIMENSION; c++)
            if (isalpha(plateau[c][l]))
                printf(" %c |", plateau[c][l]);
                else{
				switch(get_place_holder(game,l,c)){ 
					case 1 : printf("\033[31m%s \033[37m%d|", get_pion(game , l ,  c) , get_digit(game,l,c));
					break ; 
					case 2 : printf("\033[34m%s \033[37m%d|", get_pion(game , l ,  c) , get_digit(game,l,c));
					break;
					default : printf(" %d |" , get_digit(game,l,c));
					break;
				}
			}
        printf("\n");
        printf("+");
        
        for (c = 1 ; c <= DIMENSION; c++)
            printf("---+");
        printf("\n");
    }
    printf("\n");
}
//-------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------//
/*Fonction qui permet de placer les pions de chaque joueur avant le début de la partie*/
void setup_pions(board game){
	int c;
	int l;
	while (get_nb_pieces_on_board(game , 1 )<6){
		printf("Joueur Nord : Chosissez les cordonnées du pion\n");
		printf("Entrez la colonne\n");
		while (scanf("%d" , &c) == 0){
			getchar();
		}
		printf("\n");
		printf("Entrez la ligne\n");
		while (scanf("%d" , &l) == 0){
			getchar();
		}
		enum return_code result = place_piece(game, l, c); 
		if(result == OK){
			printf("Pièce de Nord placée.\n");
			afficheplateau(game);
		}
		else{
			printf("Aïe, pas réussi à placer une pièce.\n");
		}
	}
	while (get_nb_pieces_on_board(game , 2 )<6){
	printf("Joueur Sud : Chosissez les cordonnées du pion\n");
	printf("Entrez la colonne\n");
	while (scanf("%d" , &c) == 0){
			getchar();
	}
	printf("\n");
	printf("Entrez la ligne\n");
	while (scanf("%d" , &l) == 0){
			getchar();
	}
	enum return_code result1 = place_piece(game, l, c); 
	if(result1 == OK){
		printf("Pièce de Sud placée.\n");
		afficheplateau(game);
	}
	else{
		printf("Aïe, pas réussi à placer une pièce.\n");
	}
	}
}
//-------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------//
/*Fonction qui permet d'afficher le nom du joueur (soit NORTH soit SOUTH)*/
char * affichage_player(board game , int player){
	if (player == 1){
		return "NORTH";
	}
	else{
		return "SOUTH";
	}
} 
//-------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------//
/*Fonction qui permet de déplacer une fois un pion pour le joueur NORTH puis pour le joueur SOUTH*/
void deplacer(board game){
	int l1;
	int c1;
	int l;
	int c;
	printf("C'est au joueur %s de déplacer un pion" , affichage_player(game, current_player(game)));
	printf("\n");
	printf("Entrez la colonne du pion que vous souhaitez bouger\n");
	while (scanf("%d" , &c) == 0){
		getchar();
		}
	printf("Entrez la ligne du pion que vous souhaitez bouger\n");
	while (scanf("%d" , &l) == 0){
		getchar();
		}
	while (is_legal_move(game , l , c ) != true){
		printf("Les coordonnées rentrées sont mauvaises\n");
		printf("\n");
		printf("Entrez la colonne du pion que vous souhaitez bouger\n");
	while (scanf("%d" , &c) == 0){
		getchar();
		}
		printf("\n");
		printf("Entrez la ligne du pion que vous souhaitez bouger\n\n");
		while (scanf("%d" , &l) == 0){
			getchar();
		}
	}
		printf("Entrez la colonne ou vous souhaitez vous déplacer\n");
		while (scanf("%d" , &c1) == 0){
		getchar();
		}
		printf("Entrez la ligne ou vous souhaitez vous déplacer\n");
		while (scanf("%d" , &l1) == 0){
		getchar();
		}
			while (quick_move(game, l, c, l1, c1) != OK){
					printf("La pièce ne peut pas être bougée\n");
					printf("\n");
					printf("Entrez la colonne ou vous souhaitez vous déplacer\n");
					while (scanf("%d" , &c1) == 0){
						getchar();
					}
					printf("\n");
					printf("Entrez la ligne ou vous souhaitez vous déplacer\n");
					while (scanf("%d" , &l1) == 0){
						getchar();
					}
			}
		printf("La pièce a été bougée");
		printf("\n");
		afficheplateau(game);
		printf("C'est au joueur %s de déplacer un pion\n" , affichage_player(game, current_player(game)));
}
//-------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------//
/*Fonction qui permet de remplir un tableau automatiquement (Utile pour tester les fonctions sans remplir le tableau manuellement)*/
void setup(board game){
	int c = 0;
	int l = 0;
	while (get_nb_pieces_on_board(game , 1 )<6){
		enum return_code result = place_piece(game, l, c); 
		if(result == OK){
			printf("Pièce de Nord placée.\n");
			afficheplateau(game);
		}
		else{
			printf("Aïe, pas réussi à placer une pièce.\n");
		}
		c++;
	}
	while (get_nb_pieces_on_board(game , 2 )<6){
	l = 5;
	enum return_code result1 = place_piece(game, l, c); 
	if(result1 == OK){
		printf("Pièce de Sud placée.\n");
		afficheplateau(game);
	}
	else{
		printf("Aïe, pas réussi à placer une pièce.\n");
	}
	c -- ;
	}
}
//-------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------//
/* Fonction qui vérifie si le joueur possède un pion capable de réaliser un déplacement*/	
int can_play(board game){
	for(int c = 0 ; c < DIMENSION ; c++){
		for(int l = 0; l < DIMENSION ; l++){
			if (((get_place_holder(game,l,c) == current_player(game)) 
			&& (get_prescribed_move(game) == get_digit(game , l ,c )))){
				return 1;
			}
		}
	}
	return 0;
}
//-------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------//
/*Fonction vérifiant qu'au moins un des pion du joueur ne soit pas entouré par ses propres pions*/
int can_play2(board game){
	for(int c = 0 ; c < DIMENSION ; c++){
		for(int l = 0; l < DIMENSION ; l++){
			if (((get_place_holder(game,l,c+1) !=current_player(game)) || (get_place_holder(game,l,c-1) !=current_player(game)) || (get_place_holder(game,l+1,c) !=current_player(game)) || (get_place_holder(game,l-1,c) !=current_player(game)))){
				return 1;
			}
		}
	}
	return 0;
}
//-------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------//
/*Fonction qui permet de lancer la partie*/
void start_game(board game){
	printf("\n");
	printf("===========================================================================\n");
	printf("========================|PHASE DE SET-UP DES PIONS|========================\n");
	printf("===========================================================================\n");
	printf("\n");
	afficheplateau(game);
	setup_pions(game);
	afficheplateau(game);
	printf("==============================================================\n");
	printf("========================|PHASE DE JEU|========================\n");
	printf("==============================================================\n");
	printf("\n");
	afficheplateau(game);
	while (get_winner(game) == NO_PLAYER){
			deplacer(game);
			afficheplateau(game);
			if (!(can_play(game) && (can_play2(game)))){
			if (get_nb_pieces_on_board(game, current_player(game)) <6){
				int c;
				int l;
				printf("Joueur %s : Chosissez les cordonnées du pion à placer \n" , affichage_player(game, current_player(game)));
				printf("Entrez la colonne\n");
				while (scanf("%d" , &c) == 0){
						getchar();
				}
				printf("\n");
				printf("Entrez la ligne\n");
				while (scanf("%d" , &l) == 0){
						getchar();
				}
				while (insert_pawn(game, l, c) != OK){
					printf("Le Pion ne peut pas être placé.\n");	
					printf("Joueur %s : Chosissez les cordonnées du pion à placer \n" , affichage_player(game, current_player(game)));
					printf("Entrez la colonne\n");
					while (scanf("%d" , &c) == 0){
						getchar();
					}
					printf("\n");
					printf("Entrez la ligne\n");
					scanf("%d" , &l);	
				}
				printf("Le Pion du joueur %s a été placé" , affichage_player(game, current_player(game)));
			}
		}
	}
	if (get_winner(game) == 1){
		printf("========================|BRAVO AU JOUEUR \033[31m%s \033[37mQUI GAGNE LA PARTIE !!|========================\n", affichage_player(game, get_winner(game)));
		printf("\n");
	}
	else {
		printf("========================|BRAVO AU JOUEUR \033[34m%s \033[37mQUI GAGNE LA PARTIE !!|========================\n", affichage_player(game, get_winner(game)));
		printf("\n");
	}
}
//-------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------//
//Programme:
int main(){
	board game = new_random_game();
	start_game(game);
}
//-------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------//
