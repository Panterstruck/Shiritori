#pragma once
#include <vector>
#include <string>
#include <ctime>
#include "Entry.h"

class DataFetcher
{
public:
	static std::vector<Entry> GetAnilistEntriesByUser(std::string username, time_t startDate);
};

