#pragma once
#include "FBullCowGame.h"
#include <map>

//To make Unreal friendly
#define TMAP std::map

using int32 = int;

FBullCowGame::FBullCowGame(){ Reset();} //default constructor 

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const { 
	TMAP<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,15},{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset()
{

	const FString HIDDEN_WORD = "plane";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}




EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}


// receives a valid guess, increments turn,and returns count 
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();

	// loop through all letters in the guess
	for (int32 GChar = 0; GChar < WordLength; GChar++) {
		// compare letters against all the hidden word
		for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
			if (MyHiddenWord[MHWChar] == Guess[GChar]) {
				if (MHWChar == GChar) { //  if theyre in the same place
					BullCowCount.Bulls++; //increment bulls
				}
				else {
					BullCowCount.Cows++; 	// increment cow if not
				}
			}				
		}
	}
	if (BullCowCount.Bulls == MyHiddenWord.length())
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms 
	if (Word.length() <= 1)
	{
		return true;
	}

	TMAP<char, bool> LetterSeen;

	for (char Letter : Word)
	{
		Letter = tolower(Letter);

		if (!LetterSeen[Letter])
		{
			LetterSeen[Letter] = true;
		}
		else
		{
			return false;
		}
		
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
	
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

