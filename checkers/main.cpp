/* Tammi yhdelle pelaajalle
 *
 * Aluksi tulostetaan pelilauta joka on 8x8 ruudukko tästä poistetaan keskeltä 4x4 ruudukko,
 * jotta se täsmää tehtävänannon kanssa.
 * Pelimerkkiä voi liikuttaa yhden askeleen kerran toisen pelimerkin yli jolloin se syö tämän merkin.
 * Pelaajan tavoitteena on syödä kaikki paitsi yksi nappula laudalta.
 * Pelinappulat liikkuvat viistosti minne vain suuntaan.
 * Kun käyttäjä antaa merkin "q" voidaan ohjelma lopettaa.
 * Lopuksi pelilauta tulostaa kuinka monta siirtoa ja kuinka monta pelimerkkiä on jäljellä laudalla.
 *
 * Ohjelman kirjoittaja
 * Nimi: Valtteri Sutelainen
 * */
#include "gameboard.hh"
#include "gameboard.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>

// Päivittää pelilaudan tilanteen. Käytännössä laskee mistä mihin ruutuun päädytään ja mitkä pelimerkit poistetaan pelilaudalta.

void boardUpdate(int startRow, int startCol, int endRow, int endCol, GameBoard gameboard, int &moves)
{

    //  Tarkistetaan mihin suuntaan pelimerkki liikkuu ja poistetaan pelimerkki alkuperäiseltä paikalta

    if (startCol < endCol && startRow < endRow)
    {
        gameboard.removePiece(startRow, startCol);
        startCol++;
        startRow++;
    }
    else if (startCol < endCol && startRow > endRow)
    {
        gameboard.removePiece(startRow, startCol);
        startCol++;
        startRow--;
    }
    else if (startCol > endCol && startRow > endRow)
    {
        gameboard.removePiece(startRow, startCol);
        startCol--;
        startRow--;
    }
    else if (startCol > endCol && startRow < endRow)
    {
        gameboard.removePiece(startRow, startCol);
        startCol--;
        startRow++;
    }

    // Kun tiedämme minne suuntaan pelimerkki liikkuu voidaan siirtää pelimerkki oikealla paikalle ja poistaa

    if (startRow > endRow && startCol > endCol)
    {

        gameboard.removePiece(startRow, startCol);
        gameboard.addPiece(startRow - 1, startCol - 1);
    }

    else if (startRow < endRow && startCol < endCol)
    {

        gameboard.removePiece(startRow, startCol);
        gameboard.addPiece(startRow + 1, startCol + 1);
    }

    else if (startRow > endRow && startCol < endCol)
    {

        gameboard.removePiece(startRow, startCol);
        gameboard.addPiece(startRow - 1, startCol + 1);
    }

    else if (startRow < endRow && startCol > endCol)
    {

        gameboard.removePiece(startRow, startCol);
        gameboard.addPiece(startRow + 1, startCol - 1);
    }

    // Lisätään yksi siirto

    moves++;
}

// Poistaa pelilaudan keskeltä 4x4 alueen
void delete4x4area(GameBoard gameboard)
{
    for (unsigned int i = 3; i < 7; ++i)
    {

        for (unsigned int j = 3; j < 7; ++j)
        {

            gameboard.removePiece(i, j);
        }
    }
}

// Tarkistaa onko annettu string numero vai ei jos ei ole numero palauttaa false
bool isInteger(const std::string &str)
{
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

// Tarkistaa onko annettu arvo välillä 1-8
bool isValid(int value)
{
    return value >= 1 && value <= 8;
}

int main()
{

    // Muuttujat
    int moves = 0;
    char piece;

    // Kysytään millä merkillä pelilauta tehdään
    std::cout << "Enter piece character: ";
    std::cin >> piece;

    // Luodaan pelilauta
    std::vector<std::vector<GameBoard>> board(SIZE, std::vector<GameBoard>(SIZE, GameBoard(piece, nullptr)));

    // Luodaan pelilauta luokka
    GameBoard gameboard(piece, &board);

    // Poistetaan pelilaudan keskeltä 4x4 alue ja tulostetaan pelilauta tämän jälkeen
    delete4x4area(gameboard);
    gameboard.print();

    // Tehdään looppi, joka jatkaa peliä niinkauan kunnes käyttäjä kirjoittaa "q".

    while (true)
    {
        // Määritetään input ehto trueksi
        bool input = true;

        // kysytään aloitus- ja lopetusruudun koordinaatit
        std::string startRowStr, startColStr, endRowStr, endColStr;

        std::cout << "Enter start point (x, y) and destination point (x, y), or q to quit: ";

        std::getline(std::cin >> std::ws, startRowStr);
        std::istringstream iss(startRowStr);

        iss >> startRowStr;

        // Tarkistetaan käyttäjän syöte vihreiden varalta
        // Tarkistetaan myös haluaako käyttäjä lopettaa pelin kirjoittamalla "q"
        if (startRowStr == "q")
        {
            break;
        }

        iss >> startColStr >> endRowStr >> endColStr;

        // Tarkistetaan onko käyttäjän syöte numeroita, jos ei ole niin tulostetaan "Invalid start/destination point."

        // Tarkistetaan onko käyttäjän syöte numeroita, jos ei ole niin tulostetaan "Invalid start/destination point."
        if (!isInteger(startRowStr) || !isInteger(startColStr) || !isInteger(endRowStr) || !isInteger(endColStr))
        {
            std::cout << "Invalid start/destination point." << std::endl;
            std::cin.sync();
            input = false;
        }

        // Jos input on true voidaan muuttaa stringit numeroiksi, muuten tämä ei olisi mahdollista.

        if (input == true)
        {

            // Muutetaan kaikki stringit numberoiksi
            int startRow = stoi(startRowStr);
            int startCol = stoi(startColStr);
            int endRow = stoi(endRowStr);
            int endCol = stoi(endColStr);

            // Jos pisteet ovat pelilaudan ulkopuolella

            if (!isValid(startRow) || !isValid(startCol) || !isValid(endRow) || !isValid(endCol))
            {
                std::cout << "Invalid start/destination point." << std::endl;
            }
            // Jos aloitus koordinaatit ovat samoja kuin lopetus koordinaatit
            else if (startRow == endRow || startCol == endCol)
            {
                std::cout << "Cannot move from start point to destination point." << std::endl;
            }

            // Jos koorinaatit ovat liian lähellä- tai kaukana toisistaan
            else if ((abs(startRow - endRow) != 2) || (abs(startCol - endCol) != 2))
            {
                std::cout << "Cannot move from start point to destination point." << std::endl;
            }

            // Jos kohderuudussa on jo pelimerkki
            else if (gameboard.ifEmpty(endRow, endCol) == false)
            {
                std::cout << "Cannot move from start point to destination point." << std::endl;
            }

            // Jos pelimerkki välissä
            else if (startRow > endRow && startCol > endCol && gameboard.ifEmpty(startRow - 1, startCol - 1) == true)
            {
                std::cout << "Cannot move from start point to destination point." << std::endl;
            }
            else if (startRow < endRow && startCol < endCol && gameboard.ifEmpty(startRow + 1, startCol + 1) == true)
            {
                std::cout << "Cannot move from start point to destination point." << std::endl;
            }
            else if (startRow > endRow && startCol < endCol && gameboard.ifEmpty(startRow - 1, startCol + 1) == true)
            {
                std::cout << "Cannot move from start point to destination point." << std::endl;
            }
            else if (startRow < endRow && startCol > endCol && gameboard.ifEmpty(startRow + 1, startCol - 1) == true)
            {
                std::cout << "Cannot move from start point to destination point." << std::endl;
            }

            // Jos aloitusruudussa ei ole pelimerkkiä ei voida liikkua
            else if (gameboard.ifEmpty(startRow, startCol) == 1)
            {
                std::cout << "Cannot move from start point to destination point." << std::endl;
            }
            else
            {
                // Päivitetään pelilauta
                boardUpdate(startRow, startCol, endRow, endCol, gameboard, moves);
                gameboard.print();
            }
        }
    }
    // Tulosetetaan lopputiedot
    // Tulostetaan kuinka monta siirtoa tehtiin ja kuinka monta pelimerkkiä laudalla jäljellä.
    std::cout << moves << " move(s) made." << std::endl;
    gameboard.piecesLeft();
    return EXIT_SUCCESS;
}