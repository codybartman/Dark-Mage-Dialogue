//Copyright 2016 Carlody Games. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "DialogueTable.generated.h"


//My USTRUCT
USTRUCT(Blueprintable)
struct FQuestTable
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
		TArray<FString> QuestLog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
		TArray<FString> Quest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
		TArray<FString> Steps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
		TArray<FString> QuestDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
		TArray<FString> QuestVisible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
		TArray<FString> WhatYouredoingintheQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
		TArray<FString> Reward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
		TArray<int32> Payment;

	//Constructor
	FQuestTable()
	{
	
	}
};

//My USTRUCT
USTRUCT(Blueprintable)
struct FTable
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> LogNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<int32> QuestionIDCarlyUseOnly;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<int32> QuestionAnswered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<int32> Answer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> CharacterSpeaking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> Dialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> Answer0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> PR_0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> Answer1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> PR_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> Answer2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> PR_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> Answer3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> PR_3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> EndConversation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> OpenStorefront;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> LogJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> StartQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> EndSubQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTable")
		TArray<FString> EndQuest;

	//Constructor
	FTable()
	{
	
	}
};

//Set up execute paths from SetTable
UENUM(BlueprintType)
enum class ESetTableOut : uint8
{
	TableOut,
	NoTableFound
};


//Set up execute paths out from Find Row
UENUM(BlueprintType)
enum class EMyEnum : uint8
{
	RowOut,
	NoRowFound
};

UCLASS()
class KNIGHTPARTY_API ADialogueTable : public AActor
{
GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADialogueTable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Set up MyQuestTable
	UPROPERTY(EditAnywhere, Category = "Quests")
		FQuestTable MyQuestTable; 

	//Set up MyTable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DialogueTable)
		FTable MyTable;

	UFUNCTION(Category = "Quests")
		void SetQuestLog();

	UFUNCTION(BlueprintCallable, Category = "DialogueTable", Meta = (ExpandEnumAsExecs = "MyBranches"))
		void SetTable(FString TableName, ESetTableOut& MyBranches);

	UFUNCTION(BlueprintCallable, Category = "DialogueTable", Meta = (ExpandEnumAsExecs = "Branches"))
		void GetRow(FString LogNumber, int32& QuestionIDCarlyUseOnly, int32& QuestionAnswered, int32& Answer, FString& CharacterSpeaking, FString& Dialogue, FString& Answer0, FString& PR_0, FString& Answer1, FString& PR_1, FString& Answer2, FString& PR_2, FString& Answer3, FString& PR_3, FString& EndConversation, FString& OpenStorefront, FString& LogJump, FString& StartQuest, FString& EndSubQuest, FString& EndQuest, EMyEnum& Branches);


};