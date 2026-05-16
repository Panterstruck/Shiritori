#pragma once
#include <vector>
#include "Entry.h"
#include "ChainFinder.h"

std::vector<Entry> ImportEntries(std::string& filename);
void ExportChainsToCSV(const std::vector<Chain>& terminatedChains, const std::string& filename);
