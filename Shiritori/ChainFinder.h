#pragma once
#include <vector>
#include <string>
#include "Entry.h"
#include "Link.h"

using Chain = std::vector<Link>;

class ChainFinder
{
public:
	static std::vector<Chain> FindChains(const std::vector<Entry>& entries);

private:
	static std::vector<Chain> FindLinks(const std::vector<Entry>& entries);
	static std::vector<Chain> ChainLinks(std::vector<Chain>& openChains, const std::vector<Chain>& links);
	static bool IsMatch(const Link& left, const Link& right);
	static bool IsFreeConnection(const Chain& chain, const Link& entry);
};

