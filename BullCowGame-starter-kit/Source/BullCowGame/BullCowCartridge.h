// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void EndGame(bool win);
	void InitGame();
	void inputChecker(const FString& Input, FString& Word);
	void wordlistprocessor(TArray<FString> wordlist);
	bool isIsogram(const FString& Input);
	void GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const;
	// Your declarations go below!
	private:
	TArray<FString> wordlist;
	TArray<FString> validwords;
	FString word;
	int32 tries;
	bool Gameover;
};
