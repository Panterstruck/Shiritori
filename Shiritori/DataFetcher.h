#pragma once
#include <vector>
#include <string>
#include "Entry.h"
#include "httplib.h"
#include "json.hpp"

class DataFetcher
{
public:
	static std::vector<Entry> GetAnilistEntriesByUser(std::string username, std::string startDate);

private:
	static nlohmann::json BuildRequest(std::string username);
	static std::vector<Entry> ReadEntries(httplib::Result& response, std::string startDate);
	static bool IsValidFormat(nlohmann::json media);
	static bool IsAfterChallengeEntry(nlohmann::json startedAt, std::string challengeStartDate);
	static bool IsValidLength(nlohmann::json media);
	static Entry CreateEntry(nlohmann::json media);
	static void DedupeEntries(std::vector<Entry>& entries);
};
