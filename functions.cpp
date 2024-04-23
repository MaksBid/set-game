#include "functions.h"

void clearConsole() {
    system("cls"); 
}

void moveCursor(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H"; // ANSI escape code for cursor movement
}

void displayBoard(std::vector<Card>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            // For each card do the printCard() function
            printCard(board[i * 4 + j], 1 + j * 12, 1 + i * 9);
            std::cout << "    " << i * 4 + j + 1 << "  ";  // Prints card number under the cards
        }
    }
    moveCursor(1, 28); // Move cursor under the board for the rest of the menu
}

void printCard(Card card, int xPos, int yPos) {
    char filler; // Borders of the card
    switch (card.getFill()) {
    case SOLID:
        filler = '#'; // Change these values to change borders of cards
        break;
    case HATCHED:
        filler = '/';
        break;
    case EMPTY:
        filler = '^';
        break;
    default:
        break;
    }

    moveCursor(xPos, yPos); // Go to position where we want to print the card
    
    switch (card.getColor()) { 
    case RED: // Set the console color based on card's color (CRED, CGREEN, CBLUE ANSI escape codes defined in functions.h
        std::cout << CRED;
        break;
    case GREEN:
        std::cout << CGREEN;
        break;
    case BLUE:
        std::cout << CBLUE;
        break;
    default: // IDK if this is needed, but let it be
        break;
    }

    // Print top border of the card
    std::cout << filler << filler << filler << filler << filler << filler << filler << filler << filler; 
    
    // Go to next line
    moveCursor(xPos, yPos + 1);
    std::cout << filler << "       " << filler;
    moveCursor(xPos, yPos + 2);

    // Print 1, 2 or 3 times the symbol (based on the card's Amount)
    for (int i = 0; i < card.getAmount(); i++) {
        switch (card.getShape()) { // Check which symbol to print
        case OVAL:
            std::cout << filler << "   " << "O" << "   " << filler; // *   O   * (filler, symbol, filler)
            break;
        case DIAMOND:
            std::cout << filler << "   " << "X" << "   " << filler; // same scheme, but 'X'
            break;
        case WAVE:
            std::cout << filler << "   " << "S" << "   " << filler; // same scheme, but 'S'
            break;
        default:
            break;
        }
        moveCursor(xPos, yPos + 3 + i); // Go to next line
    }
    
    // Print the rest as empty rows example:
    // *   O   *
    // *       *
    // *       *
    for (int i = 0; i < 3 - card.getAmount(); i++) { 
        std::cout << filler << "   " << " " << "   " << filler;
        moveCursor(xPos, yPos + 4 + i);
    }
    
    moveCursor(xPos, yPos + 5);
    std::cout << filler << "       " << filler; 
    moveCursor(xPos, yPos + 6); // Here we finish the bottom of the card
    std::cout << filler << filler << filler << filler << filler << filler << filler << filler << filler << CRESET;
    moveCursor(xPos, yPos + 7);
}

std::vector<Card> generateAllCards() {
    std::vector<Card> deck; // Vector to store all cards

    // Iterate over all combinations of color, shape, amount, and fill
    for (int color = 1; color <= 3; ++color) {
        for (int shape = 1; shape <= 3; ++shape) {
            for (int amount = 1; amount <= 3; ++amount) {
                for (int fill = 1; fill <= 3; ++fill) {
                    // Create a card with the current combination of values
                    Card card(color, shape, amount, fill);
                    // Add the card to the deck
                    deck.push_back(card);
                }
            }
        }
    }

    return deck;
}

void shuffleDeck(std::vector<Card>& deck, int size, int cardNum) {
    srand(static_cast<unsigned int>(time(nullptr)));

    // Start from the last element and swap it with a random one before it
    for (int i = size - 1; i > cardNum; --i) {
        // Generate a random index between 0 and i
        int j = cardNum + rand() % (i - cardNum + 1);

        // Swap arr[i] with the element at the random index
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

bool checkForSet(std::vector<Card>& board)
{
    for (int firstCard = 0; firstCard < 10; firstCard++) { // Iterate from 1st to 10th (11 and 12 checked by inner loops)
        for (int secondCard = 1; secondCard < 11; secondCard++) { // Iterate from 2nd to 11 (1st checked by outer loop)
            for (int thirdCard = 2; thirdCard < 12; thirdCard++) { // Same scheme
                if (board[firstCard].checkSet(board[secondCard], board[thirdCard])) { // If we find at least one set, return true
                    return true;
                }
            }
        }
    }
    return false; // If we got here, there was no set, return false
}

bool saveGame(const std::string fileName, std::vector<Card>& deck, std::vector<Card>& board, int cardNum, int score)
{
    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return false;
    }

    outFile << score << std::endl; // Write the score
    outFile << cardNum << std::endl; // Write the amount of cards played

    for (int i = 0; i < board.size(); i++) { 
        outFile << board[i] << " "; // Write each card from the board (overloaded <<)
    }
    outFile << std::endl;

    for (int i = 0; i < 81; i++) {
        outFile << deck[i] << " "; // Write each card of the deck (overloaded <<)
    }

    return true;
}

bool loadGame(const std::string fileName, std::vector<Card>& deck, std::vector<Card>& board, int* cardNum, int* score)
{
    std::ifstream inFile(fileName);
    int cardInt;
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return false;
    }

    inFile >> *score; // Read the score from the file
    inFile.ignore(); // Ignore endl
    inFile >> *cardNum; // Read amount of cards played
    inFile.ignore(); // Ignore the endl character

    for (int i = 0; i < board.size(); i++) {
        inFile >> cardInt; // Read the number
        board[i].setColor(cardInt / 1000); // Read the data from difits of the number (color,shape,amount,fill)
        board[i].setShape((cardInt / 100) % 10);
        board[i].setAmount((cardInt / 10) % 10);
        board[i].setFill(cardInt % 10);
    }
    inFile.ignore(); // Ignore the endl char
    
    for (int i = 0; i < 81; i++) {
        inFile >> cardInt; // Read the number
        deck[i].setColor(cardInt / 1000); // Read the data from difits of the number (color,shape,amount,fill)
        deck[i].setShape((cardInt / 100) % 10);
        deck[i].setAmount((cardInt / 10) % 10);
        deck[i].setFill(cardInt % 10);
    }
    return true; // Indicate a succesful reading
}
