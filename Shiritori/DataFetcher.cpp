#include <print>
#include <stdexcept>
#include <format>
#include "DataFetcher.h"

using json = nlohmann::json;

std::vector<Entry> DataFetcher::GetAnilistEntriesByUser(std::string username, std::string startDate)
{
	std::vector<Entry> entries;
	httplib::Client client("https://graphql.anilist.co");
	auto requestPayload = BuildRequest(username);
	auto response = client.Post("/", requestPayload.dump(), "application/json");

	if (!response)
		throw std::runtime_error(std::format("Network error: {}", httplib::to_string(response.error())));

	if (response->status != 200)
		throw std::runtime_error(std::format("AniList rejected the request. Status: {}. Message: {}", response->status, response->body));

	std::println("Retrieving valid Entries for user {} Status: {}", username, response->status);
	entries = ReadEntries(response, startDate);
	return entries;
}

nlohmann::json DataFetcher::BuildRequest(std::string username)
{
	std::string query = R"(
        query ($user: String)
		{
			MediaListCollection(userName: $user, type: ANIME, status: COMPLETED)
			{
				lists
				{
					entries
					{
						startedAt { year month day }
						media
						{
							id
							format
							episodes
							duration
							title { romaji english }
						}
					}
				}
			}
		}
    )";

	json requestPayload =
	{
		{"query", query},
		{"variables",
			{
				{"user", username}
			}
		}
	};
	return requestPayload;
}

std::vector<Entry> DataFetcher::ReadEntries(httplib::Result& response, std::string challengeStartDate)
{
	json data = json::parse(response->body);
	std::vector<Entry> entries;

	for (const auto& list : data["data"]["MediaListCollection"]["lists"])
	{
		for (const auto& entryNode : list["entries"])
		{
			auto media = entryNode["media"];
			auto startedAt = entryNode["startedAt"];

			std::string format = media["format"].is_null() ? "" : media["format"].get<std::string>();

			if (!IsAfterChallengeEntry(startedAt, challengeStartDate))
				continue;

			if (!IsValidLength(media))
				continue;

			if (!IsValidFormat(media))
				continue;

			entries.push_back(CreateEntry(media));
		}
	}

	DedupeEntries(entries);
	return entries;
}

bool DataFetcher::IsValidFormat(nlohmann::json media)
{
	std::string format;
	if (!media["format"].is_null())
		format = media["format"].get<std::string>();
	return format != "MUSIC";
}

bool DataFetcher::IsAfterChallengeEntry(nlohmann::json startedAt, std::string challengeStartDate)
{
	int year = startedAt["year"].is_null() ? 0 : startedAt["year"].get<int>();
	int month = startedAt["month"].is_null() ? 0 : startedAt["month"].get<int>();
	int day = startedAt["day"].is_null() ? 0 : startedAt["day"].get<int>();
	return std::format("{:04}-{:02}-{:02}", year, month, day) >= challengeStartDate;
}

bool DataFetcher::IsValidLength(nlohmann::json media)
{
	int episodes = media["episodes"].is_null() ? 1 : media["episodes"].get<int>();
	int duration = media["duration"].is_null() ? 0 : media["duration"].get<int>();
	return episodes * duration >= 60;
}

Entry DataFetcher::CreateEntry(nlohmann::json media)
{
	int id = media["id"].get<int>();
	std::string romaji, english;

	if (!media["title"]["romaji"].is_null())
		romaji = media["title"]["romaji"].get<std::string>();

	if (!media["title"]["english"].is_null())
		english = media["title"]["english"].get<std::string>();

	return Entry(id, romaji, english);
}

void DataFetcher::DedupeEntries(std::vector<Entry>& entries)
{
	std::ranges::sort(entries, {}, [](const Entry& entry) { return entry.GetId(); });
	auto duplicate_range = std::ranges::unique(entries, {}, [](const Entry& entry) { return entry.GetId(); });
	entries.erase(duplicate_range.begin(), duplicate_range.end());
}
