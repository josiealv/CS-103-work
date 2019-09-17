// hangman.cpp
// Hangman game illustrates string library functions,
// character arrays, arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype. we'll define this below.
int processGuess(char* word, const char* targetWord, char guess);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
const char* wordBank[] = {"computer", "president", "trojan", "program",
    "coffee", "library", "football", "popcorn",
    "science", "engineer"};

const int numWords = 10;

int main()
{
    srand(time(0));
    char guess;
    bool wordGuessed = false;
    int numTurns = 10;
    
    // Pick a random word from the wordBank
    const char* targetWord = wordBank[rand() % numWords];
    
    // More initialization code as needed
    char word[80];  // a blank array to use to build up the answer
    for (int b = 0; b < strlen (targetWord); b++)
    {
        word [b] = '*';
        
    }// It should be initialized with *'s and then
    //  change them to the actual letters when the
    //  user guesses the letter
   
    for (int g = numTurns; g > 0; g--)
    {
        int correctL = 0;
        cout << "Current word: ";
        
        for (int c = 0; c< strlen(targetWord); c++)
        {
            cout << word[c];
        }
        
        cout << endl;
        
        cout << g << " " << "remain...Enter a letter to guess: " << endl;
        
        cin >> guess;
        
        int count_guess = processGuess (word, targetWord, guess);
        
        if (count_guess > 0)
        {
            correctL += count_guess;
            if (correctL == strlen(targetWord))
            {
                wordGuessed = true;
                break;
            }
            while (count_guess > 0 && correctL != strlen(targetWord))
            {
                cout << "Current word: ";
                
                for (int c = 0; c < strlen(targetWord); c++)
                {
                    cout << word[c];
                }
                
                cout << endl;
                
                cout << g << " " << "remain...Enter a letter to guess: " << endl;
                
                cin >> guess;
                
                int count_guess2 = processGuess (word, targetWord, guess);
                count_guess = count_guess2;
                correctL += count_guess2;
                
                int right = 0;
                
                for (int r = 0; r < strlen(targetWord); r++)
                {
                    if (word [r] == targetWord [r])
                    {
                        right++;
                    }
                }
                
                if (right == strlen(targetWord))
                {
                    wordGuessed = true;
                    break;
                }
            }
        }
        
        if (wordGuessed == true)
        {
            break;
        }
    }
    
    
    if (wordGuessed == true)
    {
        cout << "The word was ";
        for (int w = 0; w < strlen (targetWord); w++)
        {
            cout << targetWord [w];
        }
        cout << ". ";
        cout << "You win!" << endl;
    }
    else
    {
        cout << "Too many turns...You lose!" << endl;
    }
    
    
    
    // An individual game continues until a word
    //  is guessed correctly or 10 turns have elapsed
    
    
    
    
    // Print out end of game status
    
    
    
    return 0;
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found
int processGuess(char* word, const char* targetWord, char guess)
{
    int num_right=0;
    for (int i = 0; i < strlen(targetWord); i++)
    {
        if (guess == targetWord [i])
        {
            word [i] = guess;
            num_right++;
        }
        
    }
    return num_right;
    
}

