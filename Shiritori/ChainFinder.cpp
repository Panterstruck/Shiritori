#include <algorithm>
#include <ranges>
#include "ChainFinder.h"
#include "Link.h"

std::vector<Chain> ChainFinder::FindChains(const std::vector<Entry>& entries)
{
	auto links = ChainFinder::FindLinks(entries);
	auto chains = links;
	int iteration = 0;
	std::vector<Chain> terminatedChains;

	while (chains.size() > 0 && iteration < entries.size())
	{
		auto nextSet = ChainLinks(chains, links);
		terminatedChains.insert(terminatedChains.end(), nextSet.begin(), nextSet.end());
		iteration++;
	}
	std::ranges::sort(terminatedChains, [](const Chain& a, const Chain& b) { return a.size() > b.size(); });
	return terminatedChains;
}

std::vector<Chain> ChainFinder::FindLinks(const std::vector<Entry>& entries)
{
	std::vector<Chain> chains;

	// find all links: pairs of entries where the last two letters of one match the first two of the next.
	// save this pair with the language config of each entry in a Link object
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
					Link leftLink(leftEntry, leftLanguage);
					Link rightLink(rightEntry, rightLanguage);

					// forwards check: left -> right
					if (leftLink.IsValidLink() && IsMatch(leftLink, rightLink))
						chains.push_back({ leftLink, rightLink });

					// backwards check: right -> left
					if (rightLink.IsValidLink() && IsMatch(rightLink, leftLink))
						chains.push_back({ rightLink, leftLink });
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

		for (auto& link : links)
		{
			auto& right = link.front();
			auto& next = link.back();
			if (left == right
				&& left.GetLanguage() == right.GetLanguage()
				&& !std::ranges::contains(chain, next)
				&& IsFreeConnection(chain, next))
			{
				auto newChain = chain;
				newChain.push_back(next);
				extendedChains.push_back(std::move(newChain));
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

bool ChainFinder::IsMatch(const Link& left, const Link& right)
{
	auto ending = left.GetEnding();
	auto beginning = right.GetBeginning();
	if (ending.length() < 2 || beginning.length() < 2)
		return false;	// the titles don't provide valid 2-letter combinations

	return ending == beginning;
}

bool ChainFinder::IsFreeConnection(const Chain& chain, const Link& entry)
{
	if (entry.EndsWithN())
		return true;

	for (auto& link : chain)
	{
		if (link.GetEnding() == entry.GetEnding())
			return false;
	}

	return true;
}
