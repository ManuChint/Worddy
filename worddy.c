#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

int wordle(char chosenword[], char guessword[]);

int main(void)
{
    printf("Welcome to Wordle! The objective of the game is to guess a 5-letter word while using the information given to eventually reach the correct answer. Be warned, you only have 6 tries.\n");

    const char *filename = "answers.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open %s\n", filename);
        return 1;
    }

    int wordcount = 0;
    int chance = 0;
    int randomnumber;
    char answers[11][7];  // Array to hold the words (6 letters for word and '\0' terminator)
    char randomword[7];   // Random word to be guessed
    char guessword[7];    // Word guessed by the user

    // Read all words from the file into the array and close the file
    while (fgets(answers[wordcount], 7, file))
    {
        wordcount++;
    }
    fclose(file);

    // Pick a random word from the list
    srand(time(0));
    randomnumber = rand() % wordcount;
    strcpy(randomword, answers[randomnumber]);

    // User has 6 chances to guess the word
    while (chance < 6)
    {
        printf("\nEnter a 5-letter word: ");
        scanf("%6s", guessword);

        if (wordle(randomword, guessword) == 1)
        {
            return 0;
        }
        chance++;
    }

    printf("\nSorry, your chances are up. The word is %s\n", randomword);
    return 0;
}

int wordle(char chosenword[], char guessword[])
{
    int wordfound = 0;

    // Check if the entire word matches
    if (strcmp(chosenword, guessword) == 0)
    {
        printf("Yes! You guessed the correct answer: %s\n", chosenword);
        return 1;
    }

    // Check if letters match the correct positions
    for (int i = 0; i < 5; i++)
    {
        if (guessword[i] == chosenword[i])
        {
            printf("Letter '%c' in your guess at position %d matches the answer.\n", guessword[i], i + 1);
        }
    }

    // Check if letters are present but in the wrong position
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (guessword[i] == chosenword[j] && i != j)
            {
                printf("Letter '%c' in your guess at position %d is present in the word but in a different position.\n", guessword[i], i + 1);
            }
        }
    }

    printf("No, you did not guess the correct answer.\n");
    return 0;
}
