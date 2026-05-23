#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <print>
#include "Main.h"
#include "ChainFinder.h"
#include "DataFetcher.h"
#include "UserQuerier.h"

int main()
{
	std::string filename = "shiritori.csv";

	try
	{
		auto url = UserQuerier::PromptForCommentUrl();
		auto [username, startDate] = UserQuerier::ParseChallengeComment(url);
		auto entries = DataFetcher::GetAnilistEntriesByUser(username, startDate);
		std::println("Successfully loaded {} entries for the Shiritori algorithm.", entries.size());

		auto terminatedChains = ChainFinder::FindChains(entries);
		ExportChainsToCSV(terminatedChains, "chains.tsv");
	}
	catch (const std::exception& e)
	{
		std::println(stderr, "Fatal error during data retrieval:\n{}", e.what());
		return -1;
	}

	return 0;
}

void ExportChainsToCSV(const std::vector<Chain>& chains, const std::string& filename)
{
	std::ofstream file(filename);

	if (!file.is_open())
	{
		std::println(stderr, "Error: Could not open {} for writing.", filename);
		return;
	}

	for (const auto& chain : chains)
	{
		for (size_t i = 0; i < chain.size(); ++i)
		{
			const auto& link = chain[i];
			std::string title = link.GetTitle();
			file << title;

			if (i < chain.size() - 1)
				file << "\t";
		}
		file << "\n";
	}

	file.close();
	std::println("Successfully exported {} chains to {}", chains.size(), filename);
}
