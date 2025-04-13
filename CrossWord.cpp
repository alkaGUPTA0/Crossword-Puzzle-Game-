#include "CrosswordGame.h"

CrosswordGame::CrosswordGame(int n) : size(n), score(0) {
    grid.resize(size, std::vector<char>(size, '-'));
}

void CrosswordGame::loadWords(const std::vector<std::string>& words, const std::vector<std::string>& wordHints) {
    wordList = words;
    for (size_t i = 0; i < words.size(); ++i) {
        hints[words[i]] = wordHints[i];
    }
}

bool CrosswordGame::canPlaceWordHorizontally(int row, int col, const std::string& word) {
    if (col + word.length() > size) return false;
    for (size_t i = 0; i < word.length(); ++i) {
        if (grid[row][col + i] != '-' && grid[row][col + i] != word[i])
            return false;
    }
    return true;
}

bool CrosswordGame::canPlaceWordVertically(int row, int col, const std::string& word) {
    if (row + word.length() > size) return false;
    for (size_t i = 0; i < word.length(); ++i) {
        if (grid[row + i][col] != '-' && grid[row + i][col] != word[i])
            return false;
    }
    return true;
}

void CrosswordGame::placeWordHorizontally(int row, int col, const std::string& word) {
    for (size_t i = 0; i < word.length(); ++i) {
        grid[row][col + i] = word[i];
    }
}

void CrosswordGame::placeWordVertically(int row, int col, const std::string& word) {
    for (size_t i = 0; i < word.length(); ++i) {
        grid[row + i][col] = word[i];
    }
}

void CrosswordGame::removeWordHorizontally(int row, int col, const std::string& word) {
    for (size_t i = 0; i < word.length(); ++i) {
        grid[row][col + i] = '-';
    }
}

void CrosswordGame::removeWordVertically(int row, int col, const std::string& word) {
    for (size_t i = 0; i < word.length(); ++i) {
        grid[row + i][col] = '-';
    }
}

bool CrosswordGame::solve(int index) {
    if (index >= wordList.size()) return true;
    std::string word = wordList[index];
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (canPlaceWordHorizontally(r, c, word)) {
                placeWordHorizontally(r, c, word);
                if (solve(index + 1)) return true;
                removeWordHorizontally(r, c, word);
            }
            if (canPlaceWordVertically(r, c, word)) {
                placeWordVertically(r, c, word);
                if (solve(index + 1)) return true;
                removeWordVertically(r, c, word);
            }
        }
    }
    return false;
}

bool CrosswordGame::generatePuzzle() {
    return solve(0);
}

void CrosswordGame::displayGrid() {
    for (const auto& row : grid) {
        for (char ch : row) std::cout << ch << " ";
        std::cout << std::endl;
    }
}

void CrosswordGame::startTimer() {
    startTime = std::chrono::high_resolution_clock::now();
}

void CrosswordGame::stopTimer() {
    endTime = std::chrono::high_resolution_clock::now();
}

void CrosswordGame::showTimeTaken() {
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    std::cout << "\nTime Taken: " << duration << " seconds.\n";
}

int CrosswordGame::getScore() const {
    return score;
}

void CrosswordGame::playGame() {
    startTimer();
    std::cout << "\nStart guessing words based on hints:\n";

    for (const auto& entry : hints) {
        std::cout << "Hint: " << entry.second << std::endl;
        std::string guess;
        std::cout << "Your guess: ";
        std::cin >> guess;

        if (guess == entry.first) {
            std::cout << "Correct!\n";
            score += 10;
        } else {
            std::cout << "Wrong! The word was: " << entry.first << "\n";
            score -= 5;
        }
    }

    stopTimer();
    showTimeTaken();
    std::cout << "Your Final Score: " << getScore() << "\n";
}

void CrosswordGame::savePuzzle(const std::string& filename) {
    std::ofstream fout(filename);
    for (const auto& row : grid) {
        for (char ch : row) fout << ch << " ";
        fout << "\n";
    }
    fout.close();
}

void CrosswordGame::loadPuzzle(const std::string& filename) {
    std::ifstream fin(filename);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fin >> grid[i][j];
        }
    }
    fin.close();
}
