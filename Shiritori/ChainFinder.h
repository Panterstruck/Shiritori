#pragma once
#include <vector>
#include <string>
#include "Entry.h"
#include "Link.h"

using Chain = std::vector<Link>;

class ChainFinder
{
public:
	static std::vector<Chain> FindChains(const std::vector<Entry> entries);
	static std::vector<Link> LinkEntries(const Entry& leftEntry, Language leftLanguage, const Entry& rightEntry, Language rightLanguage);
};

