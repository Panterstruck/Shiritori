#pragma once
#include <vector>
#include <string>
#include "Entry.h"
#include "Link.h"

using Chain = std::vector<Link>;

class ChainFinder
{
public:
	static std::vector<Chain> FindLinks(const std::vector<Entry>& entries);
	static std::vector<Chain> ChainLinks(std::vector<Chain>& openChains, const std::vector<Chain>& links);

private:
	static bool IsMatch(const Entry& leftEntry, Language leftLanguage, const Entry& rightEntry, Language rightLanguage);
	static std::vector<Link> LinkEntries(const Entry& leftEntry, Language leftLanguage, const Entry& rightEntry, Language rightLanguage);
};

