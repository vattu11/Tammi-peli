 /*
 * Tammi yhdelle pelaajalle
 * gameboard.hh tiedosto
 * Sisältää luokan GameBoard metodien määrittelyt
 * 
 * Ohjelman kirjoittaja
 * Nimi: Valtteri Sutelainen
 * */


#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <iostream>
#include <vector>

// Pelilaudan koko

const unsigned int SIZE = 8;

// Vasemmanpuoleisimman sarakkeen koko, tarvitaan pelilaudan tulostamisessa

const unsigned int LEFT_COLUMN_WIDTH = 5;

// GameBoard-luokka

class GameBoard;
using Board = std::vector< std::vector< GameBoard > >;

class GameBoard{
public:
    // Rakentaja: tarvittaessa voit lisätä parametreja

    GameBoard(char piece, Board* board);

    //tuhoaja
    ~GameBoard();

    // Tulostaa pelilaudan.
    void print() const;

    // Lisää pelilaudalle uuden pelinappulan.
    void addPiece(int row, int col);
    // Poistaa pelilaudalta pelinappulan.
    void removePiece(int row, int col);
    // Tarkistaa onko halutussa paikassa pelinappulaa.
    bool ifEmpty(int row, int col);
    // Antaa montako pelinappulaa on laudalla jäljellä.
    void piecesLeft() const;

private:
    // Tulostaa annetun pituisen rivin annettua tulostumerkkiä.

    void print_line(unsigned int length, char fill_character) const;


    // Pelilaudan sisältö

    char piece_;
    Board* board_;

};

#endif // GAMEBOARD_HH