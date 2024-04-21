#include "Leaderboard.h"

///////////////////////////
// WRITTEN BY TUCKER DAY //
///////////////////////////

// standard libraries
#include <fstream>

// header a
#include "Leaderboard.h"

using namespace std;

Leaderboard::Leaderboard(const char* fn)
{
	// save the file name for use in saving on close
	fileName = fn;

	fstream input(fn, ios_base::in | ios_base::binary);

	if (input.fail())
	{
		printf("Save file does not exist. Using default values.\n");
		FillDefault();
	}
	else
	{
		short index = 0; // current entry being writen to

		// loop through the entire file or until the leaderboard is full and copy it into the entries
		while (!input.eof() && index < MAX_ENTRIES)
		{
			int score = 0;
			input.read((char*)&score, sizeof(int));
			Entries[index] = score;
			index++;
		}
	}
	input.close();
}

int Leaderboard::GetEntry(int index)
{
	return Entries[index];
}

short Leaderboard::AddEntry(int score)
{
	// compare the score passed in to the entries in the leaderboard from bottom to top
	int placement = MAX_ENTRIES;
	while (Entries[placement - 1] < score && placement != 0) { placement--; }

	// check that the score should be added into the leaderboard
	if (placement != MAX_ENTRIES)
	{
		// move other entries down to make room for the new entry
		for (int i = MAX_ENTRIES - 2; i >= placement; i--)
		{
			Entries[i + 1] = Entries[i];
		}

		// insert score into new entry
		Entries[placement] = score;
	}
	
	// return first through tenth place, or 0 if not placed
	short place = (placement >= MAX_ENTRIES) ? 0 : placement + 1;

	return place;
}

void Leaderboard::Save()
{
	// create an output stream
	fstream output(fileName, ios_base::out | ios_base::binary);

	if (output.fail())
	{
		printf("Save failed");
	}
	else
	{
		for (int i = 0; i < MAX_ENTRIES; i++)
		{
			output.write((char*)&Entries[i], sizeof(int));
		}
	}
	output.close();
}

void Leaderboard::FillDefault()
{
	// fill each leaderboard entry with placeholder data
	for (int e = 0; e < MAX_ENTRIES; e++)
	{
		Entries[e] = (MAX_ENTRIES - e) * 1000;
	}
}