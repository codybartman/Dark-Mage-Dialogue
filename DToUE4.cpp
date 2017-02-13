// DToUE4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <locale>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <Windows.h>


using namespace std;

//Set up Dialogue Tables
vector<string> UProperties;
vector<vector<string>> TableContents;
vector<vector<vector<string>>> ParsedTables;
vector<string> TotalTableNames;
int UPropertiesLength;
int NumberOfTables;

//read a line
string aLine;
bool firstRow;

//Read Dialoguetable
ifstream CurrentTableUnParsed;
//Read Quest Log
fstream QuestLogUnParsed;
vector<vector<string>> QuestTable;
vector<string> QuestColumnHeaders;
int NumberOfQuestColumns;
string FQuestTable = "FQuestTable";


//Write Header
ofstream Header;
void WriteDTHeader();

//Write .ccp
ofstream Cpp;
void WriteCpp();




//Parse Table
void ParseCSV(const string& csvSource, vector<vector<string>>& TableContents)
{
	bool inQuote(false);
	bool newLine(false);
	bool blankField(true);
	string field;
	//TableContents.clear();
	vector<string> line;

	string::const_iterator aChar = csvSource.begin();
	while (aChar != csvSource.end())
	{
		switch (*aChar)
		{
			//if it's a backslash skip
			case '\\':
				newLine = false;
				blankField = false;
				break;
			case '\'':
				//skip quote on variable titles
				if (firstRow)
				{
					newLine = false;
					blankField = false;
					break;
				}
				//Write it in as \' in subsequent lines
				else
				{
					newLine = false;
					field.push_back('\\');
					field.push_back('\'');
					blankField = false;
					break;
				}
			//If in Quotes use special rules		
			case '\"':
				newLine = false;
				inQuote = !inQuote;
				blankField = false;
				break;

			case ',':
				newLine = false;
				if (inQuote == true)
				{
					field += *aChar;
					blankField = false;
				}
				else
				{
					line.push_back(field);
					field.clear();
					blankField = true;
				}
				break;
			//If it's the first line don't allow spaces
			case ' ':
				if (!firstRow)
				{
					field.push_back(*aChar);
				}
				newLine = false;
				blankField = false;
				break;

			case '\n':
			case '\r':
				if (inQuote == true)
				{
					field += *aChar;
					blankField = false;
				}
			
				else
				{
					if (newLine == false)
					{
						line.push_back(field);
						TableContents.push_back(line);
						field.clear();
						line.clear();
						newLine = true;
					}
				}
				break;

			default:
				newLine = false;
				field.push_back(*aChar);
				blankField = false;
				break;
		}

		aChar++;
	}
	if (blankField)
	{
		newLine = false;
		field[0] = '\0';
		blankField = false;
	}

	//if line is empty 
	if (line.size())
	{
		//go to next line(leave this one empty) good
		line.push_back(field);
		TableContents.push_back(line);
	}

}


int main()
{
	
	//openfiles
	HANDLE hFind;
	WIN32_FIND_DATA data;

	//Open Questlog CSV
	QuestLogUnParsed.open(L"D:\\Cody\\KnightPartyWorkingFiles\\Excel\\QuestLog.csv");
	//Clear last table (Just in case)
	TableContents.clear();

	if (QuestLogUnParsed.is_open())
	{
		firstRow = true;
		//Parse each table
		while (!QuestLogUnParsed.eof())
		{
			getline(QuestLogUnParsed, aLine);
			ParseCSV(aLine, TableContents);
			firstRow = false;
		}

	}
	QuestLogUnParsed.close();
	//Set up Table Contents and Columns
	QuestTable = TableContents;
	QuestColumnHeaders = QuestTable[0];
	//Change the first block from None to QuestLog
	// The Header has to stay None because inside excel you need the option to pick quest None.
	QuestColumnHeaders[0] = "QuestLog";
	NumberOfQuestColumns = QuestColumnHeaders.size();


	//Search directory for the tables ending in .csv
	vector<wstring> TableNames;
	hFind = FindFirstFile(L"D:\\Cody\\DialogueTables\\*.csv*", &data);
	if (hFind != INVALID_HANDLE_VALUE) 
	{
		do {
			printf("%ls\n", data.cFileName);
			TableNames.push_back(data.cFileName);
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
	
	//Parse each csv and store the data in .lines
	NumberOfTables = TableNames.size();
	for (int i = 0; i < NumberOfTables; i++)
	{
		//set up file location
		std::wstring FileLocation = TableNames[i];
		FileLocation = L"D:\\Cody\\DialogueTables\\" + FileLocation;
		//open each csv 
		CurrentTableUnParsed.open(FileLocation);
		//Clear last table
		TableContents.clear();

		//Parse each table
		while (!CurrentTableUnParsed.eof())
		{
			getline(CurrentTableUnParsed, aLine);

			ParseCSV(aLine, TableContents);
		}
		
		//Keep all the Tables here
		ParsedTables.push_back(TableContents);

		//grab UProperties
		UProperties = TableContents[0];
		//set up table Names
		TotalTableNames.push_back(UProperties[0]);
		//set the first UProperty to "LogString"
		UProperties[0] = "LogNumber";

		//Close Files
		CurrentTableUnParsed.close();
		Header.close();
		
	}

	//Find number of Uproperties to set
	UPropertiesLength = UProperties.size();
	
	//create Header
	Header.open("D:\\Cody\\DialogueTables\\DialogueTable.h");

	//create .ccp
	Cpp.open("D:\\Cody\\DialogueTables\\DialogueTable.cpp");

	//write Header
	WriteDTHeader();

	//Write the Cpp
	WriteCpp();


	return 0;
}



//Write Header
void WriteDTHeader()
{
	
	//Set up the basics
	Header << "//Copyright 2016 Carlody Games. All Rights Reserved.\n\n"
		"#pragma once\n"
		"\n"

		"#include \"GameFramework/Actor.h\"\n"
		"#include \"DialogueTable.generated.h\"\n"
		"\n\n";
	
	//Set up the USTRUCT for Quest Columns
	Header << "//My USTRUCT\n"
		"USTRUCT(Blueprintable)\n"
		"struct ";
	Header << FQuestTable;
	Header << "\n"
		"{\n"
		"\tGENERATED_USTRUCT_BODY()\n\n";
	
	//Set up each Quest Column
	for (int n = 0; n < NumberOfQuestColumns; n++)
	{
		//Property is the collum we want to work with
		string Property = QuestColumnHeaders[n];

		if (n != 7)
		{
			//write UPROPERTY
			Header << "\tUPROPERTY(EditAnywhere, BlueprintReadWrite, Category = \"Quests\")\n";
			Header << "\t\tTArray<FString> ";
			Header << Property;
			Header << ";\n\n";
		}

		else
		{
			//write UPROPERTY
			Header << "\tUPROPERTY(EditAnywhere, BlueprintReadWrite, Category = \"Quests\")\n";
			Header << "\t\tTArray<int32> ";
			Header << Property;
			Header << ";\n\n";
		}
		
	}

	//Set up the Constructor, Still in the USTRUCT!
	Header << "\t//Constructor\n"
		"\t";
	Header << FQuestTable;
	Header << "()\n"
		"\t{\n"
		"\t\n"
		"\t}\n";

	//Close down the USTRUCT
	Header << "};"
		"\n"
		"\n";

	//Set up the USTRUCT for Dialogue Columns
	Header << "//My USTRUCT\n"
		"USTRUCT(Blueprintable)\n"
		"struct FTable\n"
		"{\n"
		"\tGENERATED_USTRUCT_BODY()\n\n";

	//Set up each Uproperty
	//Set up vector of Properties
	for (int n = 0; n < UPropertiesLength; n++)
	{
		//Property is the collum we want to work with
		string Property = UProperties[n];


		//write UPROPERTY
		Header << "\tUPROPERTY(EditAnywhere, BlueprintReadWrite, Category = \"DialogueTable\")\n";

		//if int32
		if (n > 0 && n < 4)
		{
			Header << "\t\tTArray<int32> ";
			Header << Property;
			Header << ";\n\n";
		}

		else
		{
			Header << "\t\tTArray<FString> ";
			Header << Property;
			Header << ";\n\n";
		}


	}

	//Set up the Constructor, Still in the USTRUCT!
	Header << "\t//Constructor\n"
		"\tFTable()\n"
		"\t{\n"
		"\t\n"
		"\t}\n";

	//Close down the USTRUCT
	Header << "};"
		"\n"
		"\n";
	
	//SetTableENUM
	Header << "//Set up execute paths from SetTable\n"
		"UENUM(BlueprintType)\n"
		"enum class ESetTableOut : uint8\n"
		"{\n"
		"\tTableOut,\n"
		"\tNoTableFound\n"
		"};\n\n\n";

	//UENUM 
	Header << "//Set up execute paths out from Find Row\n"
		"UENUM(BlueprintType)\n"
		"enum class EMyEnum : uint8\n"
		"{\n"
		"\tRowOut,\n"
		"\tNoRowFound\n"
		"};\n\n";

	//Set up the UCLASS
	Header << "UCLASS()\n"
		"class KNIGHTPARTY_API ADialogueTable : public AActor\n"
		"{\n"
		"GENERATED_BODY()\n"
		"\n"
		//Default Values for actor
		"public:\n"
		"\t// Sets default values for this actor's properties\n"
		"\tADialogueTable();\n\n"
		//BeginPlay
		"\t// Called when the game starts or when spawned\n"
		"\tvirtual void BeginPlay() override;\n\n"
		//Tick
		"\t// Called every frame\n"
		"\tvirtual void Tick( float DeltaSeconds ) override;\n\n"
		//Set QuestLog property for USTRUCT
		"\t//Set up MyQuestTable\n"
		"\tUPROPERTY(EditAnywhere, Category = \"Quests\")\n"
		"\t\t";
	Header << FQuestTable;
	Header << " MyQuestTable; \n"
		"\n"
		//Set Table property for USTRUCT
		"\t//Set up MyTable\n"
		"\tUPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DialogueTable)\n"
		"\t\tFTable MyTable;\n"
		"\n"
	//Set QuestLog
		"\tUFUNCTION(Category = \"Quests\")\n"
		"\t\tvoid SetQuestLog();\n"
		"\n"
	//Set Table
		"\tUFUNCTION(BlueprintCallable, Category = \"DialogueTable\", Meta = (ExpandEnumAsExecs = \"MyBranches\"))\n"
		"\t\tvoid SetTable(FString TableName, ESetTableOut& MyBranches);\n"
		"\n"
	//Get Row
		"\tUFUNCTION(BlueprintCallable, Category = \"DialogueTable\", Meta = (ExpandEnumAsExecs = \"Branches\"))\n"
		"\t\tvoid GetRow(";
		//Set each UProperty to be returned from GetRow 
		for (int n = 0; n < UPropertiesLength; n++)
		{
			//Property is the collum we want to work with
			string Property = UProperties[n];
			//Log Number goes in not out
			if (n == 0)
			{
				Header << "FString ";
				Header << Property;
				Header << ", ";
			}
			else if (n > 0 && n < 4)
			{
				Header << "int32& ";
				Header << Property;
				Header << ", ";
			}

			else
			{
				Header << "FString& ";
				Header << Property;
				Header << ", ";
			}

		}
		Header << "EMyEnum& Branches);\n"
		"\n\n"
		"};";

}


//Write cpp
void WriteCpp()
{
	Cpp << "//Copyright 2016 Carlody Games. All Rights Reserved.\n\n"
		"#include \"KnightParty.h\"\n"
		"#include \"DialogueTable.h\"\n"
		"\n"

		//Set up Default values
		"//Sets default values\n"
		"ADialogueTable::ADialogueTable()\n"
		"{\n"
		"// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.\n"
		"PrimaryActorTick.bCanEverTick = true;\n"
		"}\n\n"

		//event beginplay
		"// Called when the game starts or when spawned\n"
		"void ADialogueTable::BeginPlay()\n"
		"{\n"
		"\tSuper::BeginPlay();\n"
		"SetQuestLog();\n"
		"}\n\n"

		//tick
		"//Called every frame\n"
		"\tvoid ADialogueTable::Tick( float DeltaTime )\n"
		"{\n"
		"Super::Tick( DeltaTime );\n"
		"}\n\n"

		//Get Row
		"void ADialogueTable::GetRow(";
	
	//Set each UProperty to be returned from GetRow 
	for (int n = 0; n < UPropertiesLength; n++)
	{
		//Property is the collum we want to work with
		string Property = UProperties[n];
		//Log Number goes in not out
		if (n == 0)
		{
			Cpp << "FString ";
			Cpp << Property;
			Cpp << ", ";
		}
		else if (n > 0 && n < 4)
		{
			Cpp << "int32& ";
			Cpp << Property;
			Cpp << ", ";
		}

		else
		{
			Cpp << "FString& ";
			Cpp << Property;
			Cpp << ", ";
		}

	}


	Cpp << "EMyEnum& Branches)\n"
	"{\n"

	//Does Log Number Exist
	"\t//Does LogNumber Exist\n"
	"\tbool LogFound = MyTable.LogNumber.Contains(LogNumber);\n"
	"\tint32 LogIndex = MyTable.LogNumber.Find(LogNumber);\n"

	//if LogNumber exists
	"\tif (LogFound)\n"
	"\t{\n";
		
	//Each UProperty Sets up a GetRow
	for (int n = 0; n < UPropertiesLength; n++)
	{
		//Property is the collum we want to work with
		string Property = UProperties[n];


		//write UPROPERTY
		Cpp << "\t\t";
		Cpp << Property;
		Cpp << " = MyTable.";
		Cpp << Property;
		Cpp << "[LogIndex];\n";
			
	}
	Cpp << "\t\tBranches = EMyEnum::RowOut;\n"
		"\t}\n"
		"\n"

		"\telse\n"
		"\t{\n"
		"\t\tBranches = EMyEnum::NoRowFound;\n"
		"\t}\n"	
		//Close GetRow
		"}\n";


	//Set QuestLog
	Cpp << "void ADialogueTable::SetQuestLog()\n"
		"{\n";
		for (int n = 0; n < NumberOfQuestColumns; n++)
		{
			//if the property is a FString set it as an FString
			if (n != 7)
			{
				//Set up the UProperty as an FString Array
				Cpp << "\t\tFString Table";
				Cpp << QuestColumnHeaders[n];
				Cpp << "[] = {";
				//Find Number of Rows to run
				int NumberofRows = QuestTable.size();
				for (int nn = 0; nn < NumberofRows; nn++)
				{
					//Skip the first row, it's the Quest Columns
					if (nn != 0)
					{
						//Put each FString in quotes, and add to the FStringArray
						Cpp << "\"";
						vector<string> MyRow = QuestTable[nn];
						Cpp << MyRow[n];
						Cpp << "\", ";
					}


				}
			}

			//else set it as an int32
			else
			{
				//Set up the UProperty as an FString Array
				Cpp << "\t\tint32 Table";
				Cpp << QuestColumnHeaders[n];
				Cpp << "[] = {";
				//Find Number of Rows to run
				int NumberofRows = QuestTable.size();
				for (int nn = 0; nn < NumberofRows; nn++)
				{
					//Skip the first row, it's the Quest Columns
					if (nn != 0)
					{
						vector<string> MyRow = QuestTable[nn];

						if (MyRow[n] == "")
						{
							Cpp << "0";
						}
							
						else
						{
							Cpp << MyRow[n];
						}
						
						Cpp << ", ";
					}


				}
			}

		

			Cpp << "};\n";
			Cpp << "\t\tMyQuestTable.";
			Cpp << QuestColumnHeaders[n];
			Cpp << ".Append(Table";
			Cpp << QuestColumnHeaders[n];
			Cpp << ", ARRAY_COUNT(Table";
			Cpp << QuestColumnHeaders[n];
			Cpp << "));";

			Cpp << "\n\n";
		}
		Cpp << "}\n\n";


	//Set Table
	
	//Set up each Uproperty
	Cpp << "void ADialogueTable::SetTable(FString TableName, ESetTableOut& MyBranches)\n"
		"{\n";
	for (int ti = 0; ti < NumberOfTables; ti++)
	{
		vector<vector<string>> CurrentTableContents = ParsedTables[ti];

		//Set up the Names of the tables
		//if it's the first row use if
		if (ti == 0)
		{
			Cpp << "\tif (TableName == \"";
			Cpp << TotalTableNames[ti];
			Cpp << "\")\n"
				"\t{\n";
		}
		
		//if it's not the first row use else if
		else
		{
			Cpp << "\telse if (TableName == \"";
			Cpp << TotalTableNames[ti];
			Cpp << "\")\n"
				"\t{\n";
		}

		//set enum branch
		Cpp << "\t\tMyBranches = ESetTableOut::TableOut;\n\n";

		//increment through each collum
		for (int n = 0; n < UPropertiesLength; n++)
		{

			//if the Collum is an int
			if (n > 0 && n < 4)
			{
				//Set up the UProperty as an int Array
				Cpp << "\t\tint32 Table";
				Cpp << UProperties[n];
				Cpp << "[] = {";

				//Find Number of Rows to run

				int NumberofRows = CurrentTableContents.size();
				for (int nn = 0; nn < NumberofRows; nn++)
				{
					//Skip the first row, it's the UProperty Title 
					if (nn != 0)
					{
						//Add each cell to the UProperty
						vector<string> MyRow = CurrentTableContents[nn];
						Cpp << MyRow[n];
						Cpp << ", ";
					}


				}

				Cpp << "};\n";
				Cpp << "\t\tMyTable.";
				Cpp << UProperties[n];
				Cpp << ".Append(Table";
				Cpp << UProperties[n];
				Cpp << ", ARRAY_COUNT(Table";
				Cpp << UProperties[n];
				Cpp << "));";

				Cpp << "\n\n";
			}

			else
			{
				//Set up the UProperty as an FString Array
				Cpp << "\t\tFString Table";
				Cpp << UProperties[n];
				Cpp << "[] = {";

				//Find Number of Rows to run
				int NumberofRows = CurrentTableContents.size();
				for (int nn = 0; nn < NumberofRows; nn++)
				{
					//Skip the first row, it's the UProperty Title 
					if (nn != 0)
					{
						//Put each FString in quotes, and add to the UProperty
						Cpp << "\"";
						vector<string> MyRow = CurrentTableContents[nn];
						Cpp << MyRow[n];
						Cpp << "\", ";
					}


				}

				Cpp << "};\n";
				Cpp << "\t\tMyTable.";
				Cpp << UProperties[n];
				Cpp << ".Append(Table";
				Cpp << UProperties[n];
				Cpp << ", ARRAY_COUNT(Table";
				Cpp << UProperties[n];
				Cpp << "));";

				Cpp << "\n\n";
			}

		}
		Cpp << "\t}\n";
	}
	//If no Table has that name
	Cpp << "\telse\n"
		"\t{\n"
		"\t\tMyTable.LogNumber.Empty();\n"
		"\t\tMyBranches = ESetTableOut::NoTableFound;\n"
		"\t}\n";

	//close SetTable
	Cpp << "}";
	

	
}


