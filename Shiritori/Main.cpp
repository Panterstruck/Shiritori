#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <print>
#include "Main.h"

int main() 
{
    std::string filename = "shiritori.csv";
    std::vector<Entry> entries = ImportEntries(filename);

    std::println("English title\tRomanji Title");
    for (auto& entry : entries)
        std::println("{}\t{}", entry.GetTitle(Entry::ROMANJI), entry.GetTitle(Entry::ENGLISH));

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

        char delimiter = ',';
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
