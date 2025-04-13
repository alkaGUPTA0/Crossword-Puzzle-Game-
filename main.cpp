#include "CrosswordGame.h"

int main() {
    CrosswordGame game(10);
    std::vector<std::string> words = {
        "APPLE", "DOG", "TREE", "HOUSE", "RIVER",
        "MOUSE", "PLANE", "CLOUD", "SUGAR", "MUSIC"
    };
    std::vector<std::string> hints = {
        "A red fruit",
        "Man's best friend",
        "Has leaves and grows",
        "People live in it",
        "A flowing body of water",
        "Small animal that likes cheese",
        "Flies in the sky",
        "White fluffy object in the sky",
        "It's sweet and white",
        "We listen to it"
    };

    game.loadWords(words, hints);

    if (game.generatePuzzle()) {
        std::cout << "Generated Crossword Grid:\n";
        game.displayGrid();
        game.playGame();
        game.savePuzzle("crossword.txt");
    } else {
        std::cout << "Failed to generate crossword puzzle.\n";
    }

    return 0;
}