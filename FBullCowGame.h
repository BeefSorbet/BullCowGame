#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Not_Lowercase,
	Wrong_Length,
	Non_Letter_Used
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	void Reset();
	FBullCowCount SubmitValidGuess(FString); // counts bulls & cows and increases try #

private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
