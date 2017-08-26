/* This is the console executable, that makes use of the BullCow class
This acts the view in a MVC pattern, and is resposnible for all 
user interaction. For game logic see the FBullCowGAme class
*/
#pragma once


#include <iostream>
#include <string>
#include "FBullCowGame.h"

// To make syntax Unreal Friendly
using FText = std::string;
using int32 = int;

//function prototypes
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // initailize a new game


// the entry point for our application
int main()
{ 

	do {
		PrintIntro();
		PlayGame();
		
	} 
	while (AskToPlayAgain());
		
	
	return 0; // exit the application
}


void PrintIntro()
{
	
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// plays single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	
	// loop asking for guesses while the games is NOT won
	// and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		
		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls == " << BullCowCount.Bulls;
		std::cout << "Cows == " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

// loop contiunally until the user gies a valid guess
FText GetValidGuess() 
{
	enum EGuessStatus Status;
	FText Guess = "";
	do
	{
		
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";

		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "please enter all lowercase letters.\n\n";
			break;
		default:
			break;

		}

	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with same hidden word (y/n)?";
	FText Response = "";
	getline(std::cin, Response);
	std::cout << "\n\n";
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations - YOU WON!!!\n";
	} else {
		std::cout << "Oops maybe next time! \n";
	}
}
