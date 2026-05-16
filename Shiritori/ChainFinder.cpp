#include "ChainFinder.h"
#include "Link.h"

std::vector<Chain> ChainFinder::FindChains(const std::vector<Entry> entries)
{
	std::vector<Chain> chains;

	// find all links: pairs of entries where the last two letters of one match the first two of the next.
	// save this pair with the language config of each entry in some sort of object
	for (size_t left = 0; left < entries.size(); left++)
	{
		auto& leftEntry = entries.at(left);
		for (size_t right = left + 1; right < entries.size(); right++)
		{
			auto& rightEntry = entries.at(right);

			if (leftEntry.GetEnding(ROMANJI) == rightEntry.GetBeginning(ROMANJI))
				chains.emplace_back(LinkEntries(leftEntry, ROMANJI, rightEntry, ROMANJI));
			if (rightEntry.GetEnding(ROMANJI) == leftEntry.GetBeginning(ROMANJI))
				chains.emplace_back(LinkEntries(rightEntry, ROMANJI, leftEntry, ROMANJI));

			if (leftEntry.GetEnding(ROMANJI) == rightEntry.GetBeginning(ENGLISH))
				chains.emplace_back(LinkEntries(leftEntry, ROMANJI, rightEntry, ENGLISH));
			if (rightEntry.GetEnding(ROMANJI) == leftEntry.GetBeginning(ENGLISH))
				chains.emplace_back(LinkEntries(rightEntry, ROMANJI, leftEntry, ENGLISH));

			if (leftEntry.GetEnding(ENGLISH) == rightEntry.GetBeginning(ROMANJI))
				chains.emplace_back(LinkEntries(leftEntry, ENGLISH, rightEntry, ROMANJI));
			if (rightEntry.GetEnding(ENGLISH) == leftEntry.GetBeginning(ROMANJI))
				chains.emplace_back(LinkEntries(rightEntry, ENGLISH, leftEntry, ROMANJI));

			if (leftEntry.GetEnding(ENGLISH) == rightEntry.GetBeginning(ENGLISH))
				chains.emplace_back(LinkEntries(leftEntry, ENGLISH, rightEntry, ENGLISH));
			if (rightEntry.GetEnding(ENGLISH) == leftEntry.GetBeginning(ENGLISH))
				chains.emplace_back(LinkEntries(rightEntry, ENGLISH, leftEntry, ENGLISH));
		}
	}

	// then use the list of links to find longer chains. implies that the object may need to be able to contain more than 2, but also be able to handle single entries

	return chains;
}

std::vector<Link> ChainFinder::LinkEntries(const Entry& leftEntry, Language leftLanguage, const Entry& rightEntry, Language rightLanguage)
{
	std::vector<Link> links;
	links.emplace_back(leftEntry, leftLanguage);
	links.emplace_back(rightEntry, rightLanguage);
	return links;
}
