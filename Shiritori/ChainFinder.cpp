#include "ChainFinder.h"

std::vector<Chain> ChainFinder::FindChains(const std::vector<Entry> entries)
{
    std::vector<Chain> chains;

	// find all links: pairs of entries where the last two letters of one match the first two of the next.
	// save this pair with the language config of each entry in some sort of object
	for (size_t position = 0; position < entries.size(); position++)
	{

	}

	// then use the list of links to find longer chains. implies that the object may need to be able to contain more than 2, but also be able to handle single entries

    return chains;
}
