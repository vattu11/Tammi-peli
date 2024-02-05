 /*
 * Tammi yhdelle pelaajalle
 * gameboard.cpp tiedosto
 * Sisältää GameBoard funktioiden määrittelyt
 * 
 * Ohjelman kirjoittaja
 * Nimi: Valtteri Sutelainen
 * */
#include "gameboard.hh"
#include <iostream>
#include <vector>

GameBoard::GameBoard(char piece, Board* board):

    piece_(piece), board_(board)
{
}

GameBoard::~GameBoard(){}


// Tulostaa pelilaudan
void GameBoard::print() const
{
    // Tulostetaan yläreuna

    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');

    // Tulostetaan otsikkorivi

    std::cout << "|   | ";
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << i + 1 << " ";
    }
    std::cout << "|" << std::endl;

    // Tulostetaan viiva otsikkorivin alle

    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '-');

    // Tulostetaan pelilaudan varsinainen sisältö

for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < SIZE; ++j)
        {     
            // Tulostaa pelilaudan ja täyttää sen piece merkeillä.
            std::cout << (*board_)[i][j].piece_ << " ";
        }

    std::cout << "|" << std::endl;
}
    // Tulostetaan alareuna
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');

}


// Tulostaa annetun pituisen rivin annettua tulostumerkkiä.
void GameBoard::print_line(unsigned int length, char fill_character) const
{
    for(unsigned int i = 0; i < length; ++i)
    {
        std::cout << fill_character;
    }
    std::cout << std::endl;
}


// Nämä funktiot saavat parametrinaan rivin ja sarakkeen, jolla tiedetään mihin kohtaan pelilautaa pelimerkki lisätään tai poistetaan.


// Koska vektori alkaa indeksistä 0, mutta pelilauta alkaa indeksistä 1, tulee parametrien arvoista col ja row vähentää 1.

// Tarkistaa onko annettu kohta tyhjä palauttaa true tai false
bool GameBoard::ifEmpty(int row, int col) {


        if((*board_)[col-1][row-1].piece_ == ' '){

            return true;

        } 

        return false;

     }

// Lisää pelimerkin laudalle

void GameBoard::addPiece(int row, int col) {

        (*board_)[col-1][row-1].piece_ = piece_ ;

     }
        

    

// Poistaa pelimerkin laudalta

void GameBoard::removePiece(int row, int col) {

    // Poistetaan pelilaudalta nappula annetusta kohdasta ja korvataan tämä tyhjällä merkillä

    
    (*board_)[col-1][row-1].piece_ = ' ';

}


// Laskee montako pelimerkkiä on jäljellä
void GameBoard::piecesLeft() const{

    int i = 0;
    int j = 0;
    int pieces = 0;

    // Pelilaudan koko on 8x8, joten käydään läpi kaikki 8x8 kohdat ja lasketaan montako pelimerkkiä on jäljellä
    for(i = 0; i < 8; ++i)
    {
        for(j = 0; j < 8; ++j)
        {
            if((*board_)[i][j].piece_ == piece_){
                pieces++;
            }
        }

    }

    std::cout << pieces << " piece(s) left." << std::endl;
}