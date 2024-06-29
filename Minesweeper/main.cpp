#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <cmath>
#include <chrono>
#include <string>
#include "Board.h"
#include "Tile.h"
#include "TextureManager.h"

using namespace std;


void setText(sf::Text &text, float x, float y){ sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void drawBoard(Board &gameBoard, sf::RenderWindow &myWindow) {
    int rows = gameBoard.getRows();
    int cols = gameBoard.getCols();
    sf::Sprite topTile;
    sf::Sprite bottomTile;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            Tile &selectedTile = gameBoard.tiles[i][j];

            string topTexture;
            string bottomTexture;
            if (selectedTile.revealed){
                cout << i << "," << j << " is revealed" << endl;
                if (selectedTile.mine){
                    topTexture = "mine";
                    bottomTexture = "tile_hidden";
                }
                else {
                    topTexture = "number_" + to_string(selectedTile.neighborMineCount);
                    bottomTexture = "tile_revealed";
                }
            }
            else {
                bottomTexture = "tile_hidden";
            }
            bottomTile.setTexture(TextureManager::getTexture(bottomTexture));
            bottomTile.setPosition(j * 32, i * 32);
            myWindow.draw(bottomTile);
        }
    }
}


int main() {
    ifstream configFile("files/config.cfg");

    if (!configFile.is_open()) {
        cout << "Configuration file not opened" << endl;
    }

    int columnCount;
    int rowCount;
    int mineCount;
    configFile >> columnCount >> rowCount >> mineCount;


    int width = columnCount * 32;
    int height = (rowCount * 32) + 100;

    sf::RenderWindow window(sf::VideoMode(width, height), "Welcome window", sf::Style::Close);

    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        cout << "font not loaded" << endl;
    }

    // set welcome text
    sf::Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setString("WELCOME TO MINESWEEPER");
    welcomeText.setCharacterSize(24);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(welcomeText, width / 2, height / 2 - 150);


    // set enter name text
    sf::Text enterNameText;
    enterNameText.setFont(font);
    enterNameText.setString("Enter your name:");
    enterNameText.setCharacterSize(20);
    enterNameText.setFillColor(sf::Color::White);
    enterNameText.setStyle(sf::Text::Bold);
    setText(enterNameText, width / 2, height / 2 - 75);

    // text for input
    sf::Text inputNameText;
    inputNameText.setFont(font);
    inputNameText.setString("");
    inputNameText.setCharacterSize(18);
    inputNameText.setFillColor(sf::Color::Yellow);
    inputNameText.setStyle(sf::Text::Bold);
    setText(inputNameText, width / 2, height / 2 - 45);


    // create a string to store username data in
    string userName;

    bool playGame = false;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                playGame = false;
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char charTyped = (char) event.text.unicode;

                    if (isalpha(charTyped)) {
                        if (userName.size() < 1) {
                            charTyped = toupper(charTyped);
                        } else {
                            charTyped = tolower(charTyped);
                        }
                        if (userName.size() < 10) {
                            userName += charTyped;
                        }
                    } else if (charTyped == 8) {  // Backspace key
                        // Remove the last character
                        if (!userName.empty()) {
                            userName.pop_back();
                        }
                    }
                }
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                // Check if at least one character has been input
                if (!userName.empty()) {
                    playGame = true;
                    window.close();
                }
            }
        }

        window.clear(sf::Color::Blue);
        window.draw(welcomeText);
        window.draw(enterNameText);
        inputNameText.setString(userName + "|");
        setText(inputNameText, width / 2, height / 2 - 45);
        window.draw(inputNameText);
        window.display();
    }



    while (playGame) {

        Board myBoard(rowCount, columnCount, mineCount);


        for (int a = 0; a < myBoard.tiles.size(); a++) {
            for (int b = 0; b < myBoard.tiles[a].size(); b++) {

                Tile &test = myBoard.tiles[a][b];
                if (test.isMine()) {
                    cout << "is a mine!" << endl;
                } else if (!test.isMine()) {
                    cout << "is not a mine!" << endl;
                }
                if (test.revealed) {
                    cout << "position " << a << "," << b << " is revealed" << endl;
                } else if (!test.revealed) {
                    cout << "POSITION " << a << "," << b << " is not revealed" << endl;
                }
            }
        }

        sf::RenderWindow gameWindow(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);


        while (gameWindow.isOpen()) {
            gameWindow.clear(sf::Color::White);

            drawBoard(myBoard, gameWindow);
            sf::Event event;
            while (gameWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    playGame = false;
                    gameWindow.close();
                }
            }
            gameWindow.display();
        }

    }
        return 0;
    }
