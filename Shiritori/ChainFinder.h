#pragma once
#include <vector>
#include <string>
#include "Entry.h"

using Chain = std::vector<std::string>;

class ChainFinder
{
public:
	static std::vector<Chain> FindChains(const std::vector<Entry> entries);
};

