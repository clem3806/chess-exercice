
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>

#include "chess.h"

using namespace std;

Item::Item(int x, int y) : position_x_(x), position_y_(y) {
}

int Item::getPosX(){
    return position_x_;
}

int Item::getPosY(){
    return position_y_;
}

Piece::Piece(int x, int y, bool c) : Item(x, y), active_(true), couleur_(c) {
}

void Piece::deplacer(int x, int y){
    if(this->deplacementValide(x, y)){
        position_x_ = x;
        position_y_ = y;
    }
}

Roi::Roi(int x, int y, bool c) : Piece(x, y, c), hasnt_moved_(true) {
}

bool Roi::deplacementValide(int x, int y){
    if(abs(position_x_ - x)<=1 && abs(position_y_ - y)<=1){
        return true;
    }
    return false;
}

Dame::Dame(int x, int y, bool c) : Piece(x, y, c) {
}

bool Dame::deplacementValide(int x, int y){
    if((abs(position_x_ - x) == abs(position_y_ - y)) || (position_x_ == x && position_y_ != y) || (position_x_ != x && position_y_ == y) /*check blocked path*/){
        return true;
    }
    return false;
}

Tour::Tour(int x, int y, bool c) : Piece(x, y, c), hasnt_moved_(true) {
}

bool Tour::deplacementValide(int x, int y){
    if((position_x_ == x && position_y_ != y) || (position_x_ != x && position_y_ == y)  /*check blocked path*/){
        return true;
    }
    return false;
}

Cavalier::Cavalier(int x, int y, bool c) : Piece(x, y, c) {
}

bool Cavalier::deplacementValide(int x, int y){
    if(((abs(position_x_ - x)==2) && (abs(position_y_ - y)==1)) || ((abs(position_x_ - x)==1) && (abs(position_y_ - y)==2)) ){
        return true;
    }
    return false;
}

Fou::Fou(int x, int y, bool c) : Piece(x, y, c) {
}

bool Fou::deplacementValide(int x, int y){
    if(abs(position_x_ - x) == abs(position_y_ - y)){
        return true;
    }
    return false;
}

Pion::Pion(int x, int y, bool c) : Piece(x, y, c), a_deja_avance_(false) {
}

bool Pion::deplacementValide(int x, int y){
    if(couleur_){
        if((position_y_== y && (position_x_ == x+1 || (position_x_ == x+2 && a_deja_avance_)))/* || (position_x_ == x+1 && (pion vulnérable au en passant adjacent || (pièce dans la case [x, y] && abs(position_y_ - y) == 1)))*/){
            return true;
        }
        if((position_y_== y && (position_x_ == x-1 || (position_x_ == x-2 && a_deja_avance_)))/* || (position_x_ == x-1 && (pion vulnérable au en passant adjacent || (pièce dans la case [x, y] && abs(position_y_ - y) == 1)))*/){
            return true;
        }
    }
    return false;
}


Plateau::Plateau() {
    listePieces_.push_back(shared_ptr<Item>(new Tour(0, 0, false)));
    listePieces_.push_back(shared_ptr<Item>(new Cavalier(0, 1, false)));
    listePieces_.push_back(shared_ptr<Item>(new Fou(0, 2, false)));
    listePieces_.push_back(shared_ptr<Item>(new Roi(0, 3, false)));
    listePieces_.push_back(shared_ptr<Item>(new Dame(0, 4, false)));
    listePieces_.push_back(shared_ptr<Item>(new Fou(0, 5, false)));
    listePieces_.push_back(shared_ptr<Item>(new Cavalier(0, 6, false)));
    listePieces_.push_back(shared_ptr<Item>(new Tour(0, 7, false)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(1, 0, false)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(1, 1, false)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(1, 2, false)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(1, 3, false)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(1, 4, false)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(1, 5, false)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(1, 6, false)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(1, 7, false)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(6, 0, true)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(6, 1, true)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(6, 2, true)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(6, 3, true)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(6, 4, true)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(6, 5, true)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(6, 6, true)));
    listePieces_.push_back(shared_ptr<Item>(new Pion(6, 7, true)));
    listePieces_.push_back(shared_ptr<Item>(new Tour(7, 0, true)));
    listePieces_.push_back(shared_ptr<Item>(new Cavalier(7, 1, true)));
    listePieces_.push_back(shared_ptr<Item>(new Fou(7, 2, true)));
    listePieces_.push_back(shared_ptr<Item>(new Roi(7, 3, true)));
    listePieces_.push_back(shared_ptr<Item>(new Dame(7, 4, true)));
    listePieces_.push_back(shared_ptr<Item>(new Fou(7, 5, true)));
    listePieces_.push_back(shared_ptr<Item>(new Cavalier(7, 6, true)));
    listePieces_.push_back(shared_ptr<Item>(new Tour(7, 7, true)));
}

string Plateau::verifier_case(int x, int y) {
    for(auto pce : listePieces_){
        if(pce->getPosX() == x && pce->getPosY() == y){
            return pce->getToken();
        }
    }
    return ".";
}

void Plateau::afficher() {
    cout << "     A  B  C  D  E  F  G  H" << endl << "    _______________________" << endl;
    for(int i = 0; i < 8; i++){
        cout << to_string(i+1) << "  | ";
        for(int j = 0; j < 8; j++){
            cout << verifier_case(i, j) << "  ";
        }
        cout << endl;
    }

}



Partie::Partie() {
}

void Partie::afficher() {
    plateau_.afficher();
}

void Partie::changer_joueur() {
    joueur_actuel_ = !joueur_actuel_;
}

bool Partie::verifier_echec(){
    return false;
}

bool Partie::verifier_mat() {
    if(verifier_echec()){
        return true ; //plateau_.verifier_mat();
    }
    return false;
}

bool Partie::verifier_pat() {
    return false; //plateau_.verifier_pat();
}
