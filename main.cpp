#pragma once
#include<iostream>
#include<string>
#include"BullCowGame\FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game

int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskPlayAgain()); // runs AskPlayAgain() and if true restarts the loop
	return 0;
}

void PrintIntro()
{	
	FText Tab = "    ";

	std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;
	std::cout << Tab << Tab << "|BULLS and COWS|\n";
	std::cout << Tab << Tab << "        A fun word game.(TM)\n";
	std::cout << std::endl;
	std::cout << Tab << "Now, I'm thinking of a " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram.\n"; std::cout << std::endl;
	std::cout << Tab << "		Guess it.\n"; std::cout << std::endl;
	std::cout << Tab << "You have " << BCGame.GetMaxTries() << " guesses. Good luck.\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	return;
}

// loop until a valid guess is recieved
FText GetValidGuess()
{	
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Guess Counter: " << CurrentTry << ". Enter a guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Make sure there are no capital letters in your entry.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "An isogram is a word with no repeating letters.\n\n";
			break;
		default:
			// assume valid guess
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looking until we dont get an error
	return Guess;
}

bool AskPlayAgain()
{
	PrintGameSummary();
	std::cout << "Would you like to play again with the same word?(y/n)\n";
	FText Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You've won! ";
	}
	else
	{
		std::cout << "You've lost. ";
	}
	return;
}
