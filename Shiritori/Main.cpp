#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <print>
#include "Main.h"
#include "ChainFinder.h"
#include "DataFetcher.h"

int main() 
{
    std::string filename = "shiritori.csv";

    // 1st iteration: put all entries into separate vectors
    std::vector<Entry> entries = ImportEntries(filename);

    auto test = DataFetcher::GetAnilistEntriesByUser("JaguarJack", time_t());

    std::println("English title\tRomanji Title");
    for (auto& entry : entries)
        std::println("{}\t{}", entry.GetTitle(ROMANJI), entry.GetTitle(ENGLISH));

    // 2nd iteration: find all possible links (backwards and forwards)
    auto links = ChainFinder::FindLinks(entries);
    auto chains = links;

    // 3rd iteration: check links against remaining entries (only forwards), remove chains that did not get longer
    int iteration = 0;
    std::vector<Chain> terminatedChains;
    while (chains.size() > 0 && iteration < entries.size())
    {
        auto nextSet = ChainFinder::ChainLinks(chains, links);
        terminatedChains.insert(terminatedChains.end(), nextSet.begin(), nextSet.end());
        iteration++;
        // 4th iteration: repeat prev
    }

    ExportChainsToCSV(terminatedChains, "chains.csv");

    return 0;
}

std::vector<Entry> ImportEntries(std::string& filename)
{
    std::vector<Entry> entries;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::println("Error: Could not open the file {}", filename);
        return entries;
    }

    std::string line;
    int row = 0;
    std::getline(file, line);

    while (std::getline(file, line)) {
        row++;

        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string romajiTitle;
        std::string englishTitle;

        char delimiter = '\t';
        if (std::getline(ss, romajiTitle, delimiter) && std::getline(ss, englishTitle, delimiter))
            entries.emplace_back(romajiTitle, englishTitle);
        else
            std::println("Warning: Row {} is missing a column", filename);
    }

    file.close();
    std::println("Finished reading file.");
    std::println();
    return entries;
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
