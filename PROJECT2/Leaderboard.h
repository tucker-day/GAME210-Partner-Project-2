///////////////////////////
// WRITTEN BY TUCKER DAY //
///////////////////////////

#pragma once

#include <iostream>

const short MAX_ENTRIES = 10;

class Leaderboard {
public:
	Leaderboard(const char* fn);
	~Leaderboard() {};

	int GetEntry(int index);
	short AddEntry(int score);
	void Save();

private:
	std::string fileName = "";
	int Entries[MAX_ENTRIES] = {};

	void FillDefault();
};

