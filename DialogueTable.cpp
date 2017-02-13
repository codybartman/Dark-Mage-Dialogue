//Copyright 2016 Carlody Games. All Rights Reserved.

#include "KnightParty.h"
#include "DialogueTable.h"

//Sets default values
ADialogueTable::ADialogueTable()
{
// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADialogueTable::BeginPlay()
{
	Super::BeginPlay();
SetQuestLog();
}

//Called every frame
	void ADialogueTable::Tick( float DeltaTime )
{
Super::Tick( DeltaTime );
}

void ADialogueTable::GetRow(FString LogNumber, int32& QuestionIDCarlyUseOnly, int32& QuestionAnswered, int32& Answer, FString& CharacterSpeaking, FString& Dialogue, FString& Answer0, FString& PR_0, FString& Answer1, FString& PR_1, FString& Answer2, FString& PR_2, FString& Answer3, FString& PR_3, FString& EndConversation, FString& OpenStorefront, FString& LogJump, FString& StartQuest, FString& EndSubQuest, FString& EndQuest, EMyEnum& Branches)
{
	//Does LogNumber Exist
	bool LogFound = MyTable.LogNumber.Contains(LogNumber);
	int32 LogIndex = MyTable.LogNumber.Find(LogNumber);
	if (LogFound)
	{
		LogNumber = MyTable.LogNumber[LogIndex];
		QuestionIDCarlyUseOnly = MyTable.QuestionIDCarlyUseOnly[LogIndex];
		QuestionAnswered = MyTable.QuestionAnswered[LogIndex];
		Answer = MyTable.Answer[LogIndex];
		CharacterSpeaking = MyTable.CharacterSpeaking[LogIndex];
		Dialogue = MyTable.Dialogue[LogIndex];
		Answer0 = MyTable.Answer0[LogIndex];
		PR_0 = MyTable.PR_0[LogIndex];
		Answer1 = MyTable.Answer1[LogIndex];
		PR_1 = MyTable.PR_1[LogIndex];
		Answer2 = MyTable.Answer2[LogIndex];
		PR_2 = MyTable.PR_2[LogIndex];
		Answer3 = MyTable.Answer3[LogIndex];
		PR_3 = MyTable.PR_3[LogIndex];
		EndConversation = MyTable.EndConversation[LogIndex];
		OpenStorefront = MyTable.OpenStorefront[LogIndex];
		LogJump = MyTable.LogJump[LogIndex];
		StartQuest = MyTable.StartQuest[LogIndex];
		EndSubQuest = MyTable.EndSubQuest[LogIndex];
		EndQuest = MyTable.EndQuest[LogIndex];
		Branches = EMyEnum::RowOut;
	}

	else
	{
		Branches = EMyEnum::NoRowFound;
	}
}
void ADialogueTable::SetQuestLog()
{
		FString TableQuestLog[] = {"Find Nebby.0", "Find Nebby.Low", "Find Nebby.Skip", "Find Nebby.High", "Find Nebby.John", "Find Nebby.Convince", "Find Nebby.Return", "Manticore Trouble.0", "Manticore Trouble.Coin", "Manticore Trouble.Favor", "", "", "", "", "", "", };
		MyQuestTable.QuestLog.Append(TableQuestLog, ARRAY_COUNT(TableQuestLog));

		FString TableQuest[] = {"Find Nebby", "Find Nebby", "Find Nebby", "Find Nebby", "Find Nebby", "Find Nebby", "Find Nebby", "Manticore Trouble", "Manticore Trouble", "Manticore Trouble", "", "", "", "", "", "", };
		MyQuestTable.Quest.Append(TableQuest, ARRAY_COUNT(TableQuest));

		FString TableSteps[] = {"0", "Low", "Skip", "High", "John", "Convince", "Return", "0", "Coin", "Favor", "", "", "", "", "", "", };
		MyQuestTable.Steps.Append(TableSteps, ARRAY_COUNT(TableSteps));

		FString TableQuestDisplayName[] = {"Find Nebby", "Negotiate Low", "Skip Negotiate", "Negotiate High", "Find John", "Convince Jim to return to Guy Purple", "Return to Guy Purple", "Manticore Trouble", "Take the coin", "Take the favor", "", "", "", "", "", "", };
		MyQuestTable.QuestDisplayName.Append(TableQuestDisplayName, ARRAY_COUNT(TableQuestDisplayName));

		FString TableQuestVisible[] = {"visible", "hidden", "hidden", "hidden", "visible", "visible", "visible", "visible", "hidden", "hidden", "", "", "", "", "", "", };
		MyQuestTable.QuestVisible.Append(TableQuestVisible, ARRAY_COUNT(TableQuestVisible));

		FString TableWhatYouredoingintheQuest[] = {"Captain Guy Purple has lost his ship the Nebuchadnezzar, and his crew. Find his ship and report back with it\'s location. ", "", "", "", "Find the first mate John", "First mate John\'s name is actually Jim, convince him to return to the captain with you.", "Make your way back to Guy Purple and receive your reward.", "Help the young monster hunter stop the manticore", "", "", "", "", "", "", "", "", };
		MyQuestTable.WhatYouredoingintheQuest.Append(TableWhatYouredoingintheQuest, ARRAY_COUNT(TableWhatYouredoingintheQuest));

		FString TableReward[] = {"Potion_Strong", "", "", "", "", "", "", "", "", "Novice Monster Hunter Favor", "", "", "", "", "", "", };
		MyQuestTable.Reward.Append(TableReward, ARRAY_COUNT(TableReward));

		int32 TablePayment[] = {0, 50, 100, 150, 20, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, };
		MyQuestTable.Payment.Append(TablePayment, ARRAY_COUNT(TablePayment));

}

void ADialogueTable::SetTable(FString TableName, ESetTableOut& MyBranches)
{
	if (TableName == "Guy_Purple")
	{
		MyBranches = ESetTableOut::TableOut;

		FString TableLogNumber[] = {"0.0", "1.0", "2.0", "3.0", "4.0", "5.0", "6.0", "6.1", "5.1", "1.2", "1.3", "11.0", "12.0", "13.0", "14.0", "15.0", };
		MyTable.LogNumber.Append(TableLogNumber, ARRAY_COUNT(TableLogNumber));

		int32 TableQuestionIDCarlyUseOnly[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, };
		MyTable.QuestionIDCarlyUseOnly.Append(TableQuestionIDCarlyUseOnly, ARRAY_COUNT(TableQuestionIDCarlyUseOnly));

		int32 TableQuestionAnswered[] = {0, 1, 2, 3, 4, 5, 6, 6, 5, 1, 1, 11, 12, 13, 14, 15, };
		MyTable.QuestionAnswered.Append(TableQuestionAnswered, ARRAY_COUNT(TableQuestionAnswered));

		int32 TableAnswer[] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 0, 0, 0, 0, 0, };
		MyTable.Answer.Append(TableAnswer, ARRAY_COUNT(TableAnswer));

		FString TableCharacterSpeaking[] = {"GuyPurple", "GuyPurple", "GuyPurple", "GuyPurple", "GuyPurple", "GuyPurple", "GuyPurple", "GuyPurple", "GuyPurple", "GuyPurple", "GuyPurple", "GuyPurple", "Jim", "GuyPurple", "GuyPurple", "GuyPurple", };
		MyTable.CharacterSpeaking.Append(TableCharacterSpeaking, ARRAY_COUNT(TableCharacterSpeaking));

		FString TableDialogue[] = {"Ahh, Good morn. What brings you to my humble shop", "I do have a small task", "I do have a small task", "You see I lost my ship, The Nebuchadnezzar", "Oh but it is, yesterday I made just a short journey to Albien. But my crew has  gone missing along with ole\' Nebby. I need you to find Nebby and you\'ll get a bonus if you can find my first mate, uhh John I think his name was.", "Looking to negotiate are you? I\'ll pay you 100 talons for the ship and 20 for the 1st mate.", "Of course of course, anything for Nebby. Make it 150. Now go Quickly!", "Dangerous? I don\'t need a coward\'s help. You\'ll do it for 50. That or get out of my sight.", "Thank you, thank you I\'ll pay you 150 talons for the safe return of Nebby and an additional 20 talons if you find my first mate", "Yes, Here are my goods", "You have news!", "And my first mate John? He has a lot of explaining to do.", "Hey captain, I didn\'t mean to worry you. But thanks to Black Mage it was all worth it.", "You can tell me all about it over dinner. I\'m just glad to have Nebby back… and my crew as well.", "Back to business though. Black Mage, I\'m very grateful for your help. Here is the agreed upon sum, plus the bonus for finding John. Also please take just one more thing, this potion comes from Jermady and is the strongest I\'ve come across in my travels.", "You can tell me all about it over dinner. I\'m just glad to have Nebby back… and my crew as well.", };
		MyTable.Dialogue.Append(TableDialogue, ARRAY_COUNT(TableDialogue));

		FString TableAnswer0[] = {"Do you have any work for me?", "FALSE", "FALSE", "I thought this was going to be a small problem", "Bonus, we haven\'t even negotiated the princial yet.", "Surely a captain with such fine repute can afford a little more", "FALSE", "FALSE", "FALSE", "", "We found your ship just one town over. ", "Actually his name is Jim, and he\'s here with quite a story to tell.", "FALSE", "", "Thank you Captain, I\'m glad things turned out in the end. We\'ll see you around.", "", };
		MyTable.Answer0.Append(TableAnswer0, ARRAY_COUNT(TableAnswer0));

		FString TablePR_0[] = {"Find_Nebby-", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "Find_Nebby_2", "FALSE", "FALSE", "FALSE", "FALSE", };
		MyTable.PR_0.Append(TablePR_0, ARRAY_COUNT(TablePR_0));

		FString TableAnswer1[] = {"Can I see your merchandise?", "FALSE", "FALSE", "FALSE", "Of Course we\'ll help you", "It\'s awfully Dangerous inquireing around these parts, make it 150, and 30 for the mate.", "FALSE", "FALSE", "FALSE", "FALSE", "Actually we were hoping you had some piece of information that could help us.", "We never were able to find him", "FALSE", "FALSE", "FALSE", "FALSE", };
		MyTable.Answer1.Append(TableAnswer1, ARRAY_COUNT(TableAnswer1));

		FString TablePR_1[] = {"FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", };
		MyTable.PR_1.Append(TablePR_1, ARRAY_COUNT(TablePR_1));

		FString TableAnswer2[] = {"I have to go.", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", };
		MyTable.Answer2.Append(TableAnswer2, ARRAY_COUNT(TableAnswer2));

		FString TablePR_2[] = {"FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", };
		MyTable.PR_2.Append(TablePR_2, ARRAY_COUNT(TablePR_2));

		FString TableAnswer3[] = {"About Nebby", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", };
		MyTable.Answer3.Append(TableAnswer3, ARRAY_COUNT(TableAnswer3));

		FString TablePR_3[] = {"Find_Nebby", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", };
		MyTable.PR_3.Append(TablePR_3, ARRAY_COUNT(TablePR_3));

		FString TableEndConversation[] = {"FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "TRUE", "TRUE", "TRUE", "TRUE", "FALSE", "FALSE", "FALSE", "FALSE", "TRUE", "TRUE", };
		MyTable.EndConversation.Append(TableEndConversation, ARRAY_COUNT(TableEndConversation));

		FString TableOpenStorefront[] = {"FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", };
		MyTable.OpenStorefront.Append(TableOpenStorefront, ARRAY_COUNT(TableOpenStorefront));

		FString TableLogJump[] = {"FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", };
		MyTable.LogJump.Append(TableLogJump, ARRAY_COUNT(TableLogJump));

		FString TableStartQuest[] = {"None", "None", "None", "None", "None", "None", "Find Nebby.0", "None", "Find Nebby.0", "None", "None", "None", "None", "None", "None", "None", };
		MyTable.StartQuest.Append(TableStartQuest, ARRAY_COUNT(TableStartQuest));

		FString TableEndSubQuest[] = {"None", "None", "None", "None", "None", "None", "None", "None", "None", "None", "None", "None", "None", "None", "None", "None", };
		MyTable.EndSubQuest.Append(TableEndSubQuest, ARRAY_COUNT(TableEndSubQuest));

		FString TableEndQuest[] = {"None", "None", "None", "None", "None", "None", "None", "None", "None", "None", "None", "None", "None", "None", "None", "None", };
		MyTable.EndQuest.Append(TableEndQuest, ARRAY_COUNT(TableEndQuest));

	}
	else if (TableName == "Novice_MonsterHunter")
	{
		MyBranches = ESetTableOut::TableOut;

		FString TableLogNumber[] = {"0.0", "1.0", "2.0", "3.0", "4.0", "5.0", "5.1", "3.1", "8.0", "8.1", "", "", "", "", };
		MyTable.LogNumber.Append(TableLogNumber, ARRAY_COUNT(TableLogNumber));

		int32 TableQuestionIDCarlyUseOnly[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, , , , , };
		MyTable.QuestionIDCarlyUseOnly.Append(TableQuestionIDCarlyUseOnly, ARRAY_COUNT(TableQuestionIDCarlyUseOnly));

		int32 TableQuestionAnswered[] = {0, 1, 2, 3, 4, 5, 5, 3, 8, 8, , , , , };
		MyTable.QuestionAnswered.Append(TableQuestionAnswered, ARRAY_COUNT(TableQuestionAnswered));

		int32 TableAnswer[] = {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, , , , , };
		MyTable.Answer.Append(TableAnswer, ARRAY_COUNT(TableAnswer));

		FString TableCharacterSpeaking[] = {"Novice MonsterHunter", "Novice MonsterHunter", "Novice MonsterHunter", "Knight", "Novice MonsterHunter", "Novice MonsterHunter", "Novice MonsterHunter", "Novice MonsterHunter", "Knight", "Novice MonsterHunter", "", "", "", "", };
		MyTable.CharacterSpeaking.Append(TableCharacterSpeaking, ARRAY_COUNT(TableCharacterSpeaking));

		FString TableDialogue[] = {"Hello, are you an adventurer like myself?", "Ohh good, I have a contract that might be a bit over my head.", "There has been a manticore destroying the local livestock. I was hired to slay the beast, but I can\'t seem to find it.", "They\'re attracted to the smell of cooked meat. Lamb in particular.", "That\'s an excellent idea, rather chasing the manticore, I\'ll lure it to me. As payment for your help would you rather have 100 talons or have me owe you a favor?", "That is usually the prefered payment. I wish you the best of luck, and hope to meet again", "Ohh thank goodness, I don\'t have many talons left. I\'ll find some way to pay you back.", "Well If you can help me I could perhaps pay a 100 talon consulting fee. ", "They\'re attracted to the smell of cooked meat. Lamb in particular.", "Okay come back if you change your mind.", "", "", "", "", };
		MyTable.Dialogue.Append(TableDialogue, ARRAY_COUNT(TableDialogue));

		FString TableAnswer0[] = {"I am!", "I\'m sure we can handle it.", "We have quite the opposite problem. While on the road manticores continually find our camp.", "", "We\'d prefer the coins.", "Best of luck to you as well.", "I hope to see you again.", "Perhaps some advice, While on the road manticores continually find our camp.", "", "Goodbye", "", "", "", "", };
		MyTable.Answer0.Append(TableAnswer0, ARRAY_COUNT(TableAnswer0));

		FString TablePR_0[] = {"FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "", "", "", "", };
		MyTable.PR_0.Append(TablePR_0, ARRAY_COUNT(TablePR_0));

		FString TableAnswer1[] = {"Who\'s asking?", "FALSE", "Lets talk numbers first.", "FALSE", "A favor among friends is far more valuable. ", "FALSE", "FALSE", "Sorry, we can\'t work for so little.", "FALSE", "FALSE", "", "", "", "", };
		MyTable.Answer1.Append(TableAnswer1, ARRAY_COUNT(TableAnswer1));

		FString TablePR_1[] = {"FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "", "", "", "", };
		MyTable.PR_1.Append(TablePR_1, ARRAY_COUNT(TablePR_1));

		FString TableAnswer2[] = {"FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "", "", "", "", };
		MyTable.Answer2.Append(TableAnswer2, ARRAY_COUNT(TableAnswer2));

		FString TablePR_2[] = {"FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "", "", "", "", };
		MyTable.PR_2.Append(TablePR_2, ARRAY_COUNT(TablePR_2));

		FString TableAnswer3[] = {"FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "", "", "", "", };
		MyTable.Answer3.Append(TableAnswer3, ARRAY_COUNT(TableAnswer3));

		FString TablePR_3[] = {"FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "", "", "", "", };
		MyTable.PR_3.Append(TablePR_3, ARRAY_COUNT(TablePR_3));

		FString TableEndConversation[] = {"FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "TRUE", "TRUE", "FALSE", "FALSE", "TRUE", "", "", "", "", };
		MyTable.EndConversation.Append(TableEndConversation, ARRAY_COUNT(TableEndConversation));

		FString TableOpenStorefront[] = {"FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "", "", "", "", };
		MyTable.OpenStorefront.Append(TableOpenStorefront, ARRAY_COUNT(TableOpenStorefront));

		FString TableLogJump[] = {"FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "FALSE", "4.0", "FALSE", "", "", "", "", };
		MyTable.LogJump.Append(TableLogJump, ARRAY_COUNT(TableLogJump));

		FString TableStartQuest[] = {"None", "None", "None", "None", "Manticore Trouble.0", "None", "None", "None", "None", "None", "", "", "", "", };
		MyTable.StartQuest.Append(TableStartQuest, ARRAY_COUNT(TableStartQuest));

		FString TableEndSubQuest[] = {"None", "None", "None", "None", "None", "Manticore Trouble.Coin", "Manticore Trouble.Favor", "None", "None", "None", "", "", "", "", };
		MyTable.EndSubQuest.Append(TableEndSubQuest, ARRAY_COUNT(TableEndSubQuest));

		FString TableEndQuest[] = {"None", "None", "None", "None", "None", "Manticore Trouble.0", "Manticore Trouble.0", "None", "None", "None", "", "", "", "", };
		MyTable.EndQuest.Append(TableEndQuest, ARRAY_COUNT(TableEndQuest));

	}
	else
	{
		MyTable.LogNumber.Empty();
		MyBranches = ESetTableOut::NoTableFound;
	}
}