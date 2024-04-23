#pragma once
#include "Card.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <fstream>
#define CRESET   "\033[0m"
#define CRED     "\033[38;5;196m" 
#define CGREEN   "\033[38;5;76m"
#define CBLUE    "\033[36m"

#ifndef _FUNCTIONS_H_

void clearConsole();

void moveCursor(int x, int y);

void displayBoard(std::vector<Card>& board);

void printCard(Card card1, int xPos, int yPos);

std::vector<Card> generateAllCards();

void shuffleDeck(std::vector<Card>& deck, int size, int cardNum);

bool checkForSet(std::vector<Card>& board);

bool saveGame(const std::string fileName, std::vector<Card>& deck, std::vector<Card>& board, int cardNum, int score);

bool loadGame(const std::string fileName, std::vector<Card>& deck, std::vector<Card>& board, int* cardNum, int* score);

#endif // !_FUNCTIONS_H_
