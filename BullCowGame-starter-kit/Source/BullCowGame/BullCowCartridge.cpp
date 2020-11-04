// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


void UBullCowCartridge::wordlistprocessor(TArray<FString> wordlist)
{
    for(FString word : wordlist)
    {
        if(word.Len() >= 4 && word.Len() <= 8 && isIsogram(word))
        {
            validwords.Emplace(word);
        }
    }
}

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/listofwords.txt");
    FFileHelper::LoadFileToStringArray(wordlist, *WordListPath);
    wordlistprocessor(wordlist);
    PrintLine(FString::Printf(TEXT("Today we have %d words available"), wordlist.Num()));
    PrintLine(FString::Printf(TEXT("Picking out %d words from them"), validwords.Num()));
    InitGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if(Gameover&&Input=="1")
    {
        InitGame();
        return;
    }
    else if(Gameover)
    {
        return;
    }
    inputChecker(Input, word);
}

void UBullCowCartridge::InitGame()
{
    PrintLine(TEXT("Welcome"));
    tries = 5;
    word = validwords[FMath::RandRange(0,validwords.Num()-1)];
    Gameover = false;
    PrintLine(FString::Printf(TEXT("Today's random word is %s"), *word));
    PrintLine(FString::Printf(TEXT("Guess a %d-character word"), word.Len()));
    PrintLine(FString::Printf(TEXT("Tries: %d"), tries));
}

void UBullCowCartridge::EndGame(bool win)
{
    ClearScreen();
    if(win)
    {
        PrintLine(TEXT("You Win!"));
    }
    else
    {
       PrintLine(TEXT("You Lost!"));
    }
    PrintLine(TEXT("Gameover\nPress 1 to continue"));
    Gameover = true;
}


bool UBullCowCartridge::isIsogram(const FString& Input)
{
    int32 len = Input.Len();
    FString processString = Input.ToLower();
    for (int i = 0; i < len; i++) 
    {
        for(int j = i + 1; j < len; j ++)
        {
            if (processString[i] == processString[j]) 
            return false; 
        } 
    } 
    return true; 
}

void UBullCowCartridge::inputChecker(const FString& Input, FString& Word)
{
    if (Input == Word)
    {
        PrintLine(TEXT("You win"));
        EndGame(1);
    }
    else if (Input.Len() > word.Len())
    {
        PrintLine(TEXT("word too long, try again"));
        return; 
    }
    else if (Input.Len() < word.Len())
    {
        PrintLine(TEXT("word too short, try again"));
        return; 
    }
    else if (!isIsogram(Input))
    {
        PrintLine(TEXT("no repeating letter, try again"));
        return; 
    }
    else
    {
        PrintLine(TEXT("Ur guess is wrong"));
        tries --;
        if (!tries)
        {
            EndGame(0);
        }
        else
        {
            int32 cows = 0;
            int32 bull = 0;
            int32 counter = 0;
            for(char character : Input)
            {
                if (character == word[counter])
                {
                    bull++;
                } 
                counter ++;
            }
            counter = 0;
            for(char characterw : word)
            {
                for(char characteri : Input)
                {
                    if(characterw == characteri)
                    {
                        cows++;
                    }
                }
            }
            cows -= bull;
            PrintLine(FString::Printf(TEXT("Bull: %d, Cow: %d"), bull, cows));
            PrintLine(FString::Printf(TEXT("Tries: %d"), tries));
        }
    }
    
}