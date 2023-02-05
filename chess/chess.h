#pragma once

#include <string>
#include <vector>
#include <memory>

using namespace std;

class Item {
protected:
    int position_x_;
    int position_y_;
public:
    Item(int x, int y);
    Item() = delete;
    int getPosX();
    int getPosY();
    virtual string getToken() {return "U";}
};

class Piece : public Item{
protected:
    bool active_;
    bool couleur_; //true == blanc; false == noir
public:
    Piece(int x, int y, bool c);
    virtual bool deplacementValide(int x, int y) = 0;
    void deplacer(int x, int y);
    bool getCouleur() {return couleur_;}
};

class Roi : public Piece {
private:
    bool hasnt_moved_;
public:
    Roi(int x, int y, bool c);
    bool deplacementValide(int x, int y);
    string getToken() {if(couleur_){return "r";} else{return "R";}}
};

class Dame : public Piece {
public:
    Dame(int x, int y, bool c);
    bool deplacementValide(int x, int y);
    string getToken() {if(couleur_){return "d";} else{return "D";}}
};

class Tour : public Piece {
private:
    bool hasnt_moved_;
public:
    Tour(int x, int y, bool c);
    bool deplacementValide(int x, int y);
    string getToken() {if(couleur_){return "t";} else{return "T";}}
};

class Cavalier : public Piece {
public:
    Cavalier(int x, int y, bool c);
    bool deplacementValide(int x, int y);
    string getToken() {if(couleur_){return "c";} else{return "C";}}
};

class Fou : public Piece {
public:
    Fou(int x, int y, bool c);
    bool deplacementValide(int x, int y);
    string getToken() {if(couleur_){return "f";} else{return "F";}}
};

class Pion : public Piece {
private:
    bool can_be_en_passanted_;
public:
    Pion(int x, int y, bool c);
    bool deplacementValide(int x, int y);
    //string promotion();
    string getToken() {if(couleur_){return "p";} return "P";}
};

/*class Joueur {
private:
    bool couleur_; //true == blanc; false == noir
    string nom_;
public:
    Joueur(string nom, bool couleur);
    bool jouer_coup(int x1, int y1, int x2, int y2);
    void saisir_coup();
};*/

class Plateau{
private:
    vector<shared_ptr<Item>> listePieces_;

public:
    Plateau();
    void afficher();
    void valider_coup(int x1, int y1, int x2, int y2);
    void jouer_coup(int x1, int y1, int x2, int y2);
    bool verifier_echec();
    bool verifier_mat();
    bool verifier_pat();
    string verifier_case(int x, int y);
    bool promotion(Pion& p);
    bool verifier_roque(bool est_petit);
    void faire_roque(bool est_petit);
    void deplacerPiece(int x1, int y1, int x2, int y2);
};

class Partie {
private:
    Plateau plateau_;
    bool joueur_actuel_; //true == blanc; false == noir
    vector<string> historique_coups_;
public:
    Partie();
    void afficher();
    void changer_joueur();
    bool getJoueur(){return joueur_actuel_;}
    void annuler_coup();
    void jouer_coup(int x1, int y1, int x2, int y2);
    bool verifier_echec();
    bool verifier_mat();
    bool verifier_pat();
    bool verifier_roque(bool est_petit);
    void faire_roque(bool est_petit);
};
