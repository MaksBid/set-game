#include "Card.h"
#include "functions.h"

int main() {
	srand(static_cast<unsigned int>(time(nullptr))); // Initialize random seed
	std::vector<Card> board, deck;
	std::string fileName;
	int cardNum = 0, choice[3], score = 0, answer = 1;
	bool gameStarted = false;

	deck = generateAllCards(); // Fill the deck (sorted)
	shuffleDeck(deck, 81, cardNum); // And now shuffle it

	for (int i = 0; i < 12; i++) { // Fill the board with first 12 cards of the deck
		board.push_back(deck[cardNum]);
		cardNum++;
	}

	while (answer != 0) {
		if (!gameStarted) {
			std::cout << "(1) Start a new game\n(2) Load a game\n(0) Exit\n";
			std::cin >> answer;
			switch (answer) {
			case 1:
				gameStarted = true;
				clearConsole();
				break;
			case 2:
				std::cout << "Enter the name of the file: ";
				std::cin >> fileName;
				loadGame(fileName, deck, board, &cardNum, &score);
				gameStarted = true;
				clearConsole();
				break;
			default:
				break;
			}
		}
		else {
			while (cardNum != 81) {
				if (!checkForSet(board)) { // If there are no sets on the board
					cardNum -= 12; // Draw cards back into the deck and set cardNum 12 cards back
					shuffleDeck(deck, 81, cardNum); // Shuffle the unplayed deck with cards of the board
					board.clear();
					for (int i = 0; i < 12; i++) { // Fill the board with 12 cards of the deck
						board.push_back(deck[cardNum]);
						cardNum++;
					}
					continue;
				}

				displayBoard(board);
				std::cout << "Score: " << score << "\n(13) Save game \n(0) Exit \nEnter 3 cards that you think are set: ";
				std::cin >> choice[0];

				if (choice[0] == 0) { // Exit the current game
					gameStarted = false;
					clearConsole();
					break;
				}
				else if (choice[0] == 13) { // Save the game into a file
					std::cout << "Enter the name of the file: ";
					std::cin >> fileName;
					saveGame(fileName, deck, board, cardNum, score);
					clearConsole();
					continue;
				}

				std::cin >> choice[1] >> choice[2];
				bool isValid = choice[0] <= 0 || choice[1] <= 0 || choice[2] <= 0 || // Check if greater than 0
							   choice[0] > 12 || choice[1] > 12 || choice[2] > 12 || // Check if lower than 12
							   choice[0] == choice[1] || choice[1] == choice[2] || choice[0] == choice[2]; // Check if not the same card
				if (isValid) {
					clearConsole();
					moveCursor(1, 27);
					std::cout << "Invalid values, try again";
					continue;
				}
				if (board[choice[0] - 1].checkSet(board[choice[1] - 1], board[choice[2] - 1])) {
					score += 3;
					clearConsole();
					moveCursor(1, 27);
					std::cout << "SET!";
					for (int i = 0; i < 3; i++) {
						board[choice[i] - 1] = deck[cardNum];
						cardNum++;
					}
				}
				else {
					clearConsole();
					moveCursor(1, 27);
					std::cout << "Not set, try again";
				}
			}
		}
	}
	
	return 0;
}