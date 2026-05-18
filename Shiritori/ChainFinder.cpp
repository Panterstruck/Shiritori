#include <algorithm>
#include "ChainFinder.h"
#include "Link.h"

std::vector<Chain> ChainFinder::FindLinks(const std::vector<Entry>& entries)
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
			const Language languages[] = { ROMAJI, ENGLISH };

			for (auto leftLanguage : languages)
			{
				for (auto rightLanguage : languages)
				{
					// Forward Check: Left -> Right
					if (IsMatch(leftEntry, leftLanguage, rightEntry, rightLanguage))
						chains.emplace_back(LinkEntries(leftEntry, leftLanguage, rightEntry, rightLanguage));

					// Reverse Check: Right -> Left
					if (IsMatch(rightEntry, rightLanguage, leftEntry, leftLanguage))
						chains.emplace_back(LinkEntries(rightEntry, rightLanguage, leftEntry, leftLanguage));
				}
			}
		}
	}

	return chains;
}

std::vector<Chain> ChainFinder::ChainLinks(std::vector<Chain>& openChains, const std::vector<Chain>& links)
{
	std::vector<Chain> terminatedChains;
	std::vector<Chain> nextGenChains;

	for (auto& chain : openChains)
	{
		std::vector<Chain> extendedChains;
		auto& left = chain.back();

		if (!left.EndsWithN())
		{
			for (auto& link : links)
			{
				auto& right = link.front();
				auto& next = link.back();
				if (left == right
					&& left.GetLanguage() == right.GetLanguage()
					&& !std::ranges::contains(chain, next))
				{
					auto newChain = chain;
					newChain.push_back(next);
					extendedChains.push_back(std::move(newChain));
				}
			}
		}

		if (extendedChains.empty())
			terminatedChains.push_back(chain);
		else
		{
			for (auto& newChain : extendedChains)
				nextGenChains.push_back(std::move(newChain));
		}
	}

	openChains = std::move(nextGenChains);
	return terminatedChains;
}

bool ChainFinder::IsMatch(const Entry& leftEntry, Language leftLanguage, const Entry& rightEntry, Language rightLanguage)
{
	if (rightEntry.StartsWithN(rightLanguage))
		return false;
	return leftEntry.GetEnding(leftLanguage) == rightEntry.GetBeginning(rightLanguage);
}

std::vector<Link> ChainFinder::LinkEntries(const Entry& leftEntry, Language leftLanguage, const Entry& rightEntry, Language rightLanguage)
{
	std::vector<Link> links;
	links.emplace_back(leftEntry, leftLanguage);
	links.emplace_back(rightEntry, rightLanguage);
	return links;
}
