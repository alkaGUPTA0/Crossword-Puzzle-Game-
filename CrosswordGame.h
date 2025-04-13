#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <chrono>

class CrosswordGame {
private:
    int size;
    std::vector<std::vector<char>> grid;
    std::vector<std::string> wordList;
    std::map<std::string, std::string> hints;
    int score;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;

    bool canPlaceWordHorizontally(int row, int col, const std::string& word);
    bool canPlaceWordVertically(int row, int col, const std::string& word);
    void placeWordHorizontally(int row, int col, const std::string& word);
    void placeWordVertically(int row, int col, const std::string& word);
    void removeWordHorizontally(int row, int col, const std::string& word);
    void removeWordVertically(int row, int col, const std::string& word);
    bool solve(int index);

public:
    CrosswordGame(int n);
    void loadWords(const std::vector<std::string>& words, const std::vector<std::string>& wordHints);
    bool generatePuzzle();
    void displayGrid();
    void playGame();
    void savePuzzle(const std::string& filename);
    void loadPuzzle(const std::string& filename);
    void startTimer();
    void stopTimer();
    void showTimeTaken();
    int getScore() const;
};
