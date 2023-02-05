#include <iostream>
#include <vector>
#include <memory>
#include <stdlib.h>
#include <conio.h>
#include "chess.h"

using namespace std;

int main()
{
    Partie laPartie;
    int a = 0;
    while(/*laPartie.verifier_mat() && laPartie.verifier_pat() &&*/ a<3){
        laPartie.afficher();
        //laPartie.jouer_coup();
        laPartie.changer_joueur();
        a++;
        cout << "Quelle case a deplacer?" << endl;
        char x1 = getch();
        cout << x1 << "-";
        char y1 = getch();
        cout << y1 << endl << "Deplacer ou?" << endl;
        char x2 = getch();
        cout << x2 << "-";
        char y2 = getch();
        cout << y2 << endl << "Confirmer?" << endl;
        getch();
        laPartie.changer_joueur();
        system("cls");
    }
    if(laPartie.getJoueur()){
        cout << "Blanc a gagne" << endl;
    }
    else{
        cout << "Noir a gagne" << endl;
    }
}
