#pragma once
#include <vector>
#include "Entry.h"
#include "ChainFinder.h"

void ExportChainsToCSV(const std::vector<Chain>& terminatedChains, const std::string& filename);
