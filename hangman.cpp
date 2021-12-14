#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class HangMan
{
public:
    HangMan(string w)
    {
        setWord(w);
        initCompletion();
        initFigures();
    }

    void play(){
        cout << "Lets play HangMan!" << endl;

        while (tries < maxTries && !guessed){
            displayFigure(tries);
            displayCompletion();
            char guess = takeGuess();
            if (isAlreadyGuessed(guess)){
                cout << "You have already guessed the letter " << guess << endl;
                continue;
            }
            guessedLetters.push_back(guess);
            vector<int> guessIndices = getCharIndices(guess);
            if(guessIndices.empty()){
                cout << guess << " is not in word." << endl;
                tries++;
                continue;
            }
            completeLetter(guess, guessIndices);
            if (isWon()){
                guessed = true;
                displayCompletion();
            }
        }
        cout << endl;
        if (guessed)
            cout << "You win!" << endl;
        else
            cout << "Game over!\n"
                    "The word was " << word << ".\n";
    }

private:
    const static int maxTries = 6;
    int tries = 0;
    bool guessed = false;
    string word;
    string completion;
    string guessedLetters;
    string figures[maxTries];

    void setWord(string w){
        for(char &chr: w){
            if (chr >= 'a' && chr <= 'z')
                chr = toupper(chr);
        }
        word = w;
    }
    void initFigures(){
        figures[0] = "\n                ________\n                |      |\n                |\n                |\n                |\n                |\n                _\n            ";
        figures[1] = "\n                ________\n                |      |\n                |      0\n                |\n                |\n                |\n                _\n            ";
        figures[2] = "\n                ________\n                |      |\n                |      0\n                |      |\n                |      |\n                |\n                _\n            ";
        figures[3] = "\n                ________\n                |      |\n                |      0\n                |     \\|\n                |      |\n                |\n                _\n            ";
        figures[4] = "\n                ________\n                |      |\n                |      0\n                |     \\|/\n                |      |\n                |\n                _\n            ";
        figures[5] = "\n                ________\n                |      |\n                |      0\n                |     \\|/\n                |      |\n                |     /\n                _\n            ";
    }

    void initCompletion(){
        for (int i=0; i<word.size();i++){
            completion.push_back('_');
        }
    }

    void displayCompletion() const{
        for (char chr: completion){
            cout << chr << " ";
        }
        cout << endl << endl;
    }

    void displayFigure(int stage) const{
        cout << figures[stage] << endl;
    }

    char takeGuess() const{
        char guess;
        cout << "Guess a letter: ";
        cin >> guess;
        return toupper(guess);
    }

    bool isAlreadyGuessed(char letter) const{
        for (char chr:guessedLetters){
            if (letter == chr)
                return true;
        }
        return false;
    }

    vector<int> getCharIndices(char letter) const{
        vector<int> indices;
        for (int i=0;i<word.size();i++){
            if (word[i] == letter)
                indices.push_back(i);
        }
        return indices;
    }

    void completeLetter(char chr, vector<int> indices){
        for (int i: indices)
            completion[i] = chr;
    }

    bool isWon() const{
        for (char chr: completion){
            if (chr=='_')
                return false;
        }
        return true;
    }
};

int main()
{   
    srand(time(0));
    vector<string> wordList = {"hello", "world"};
    HangMan game(wordList[rand()%wordList.size()]);
    game.play();
}