#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <print>
#include "DataFetcher.h"

using json = nlohmann::json;

std::vector<Entry> DataFetcher::GetAnilistEntriesByUser(std::string username, std::string startDate)
{
	std::vector<Entry> entries;
	httplib::Client client("https://graphql.anilist.co");
	std::string query = R"(
        query ($user: String) {
          MediaListCollection(userName: $user, type: ANIME, status: COMPLETED) {
            lists {
              entries {
                startedAt { year month day }
                media {
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

	auto response = client.Post("/", requestPayload.dump(), "application/json");

	if (response)
	{
		if (response->status == 200)
		{
			std::println("Success!");
			auto entries = ReadEntries(response, startDate);
		}
		else
		{
			std::println(stderr, "AniList rejected the request. Status: {}", response->status);
			std::println(stderr, "Error Message: {}", response->body);
		}
	}
	else
	{
		// This triggers if your firewall blocks it, or if SSL fails to initialize
		std::println(stderr, "Network error: {}", httplib::to_string(response.error()));
	}

	std::println("Status: {}", response->status);

	return entries;
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
			if (!IsValidFormat(media))
				continue;

			if (!IsAfterChallengeEntry(startedAt, challengeStartDate))
				continue;

			if (!IsValidLength(media))
				continue;

			entries.emplace_back(CreateEntry(media));
		}
	}
	return entries;
}

Entry DataFetcher::CreateEntry(nlohmann::json media)
{
	int id = media["id"].get<int>();
	std::string romaji, english;

	if (!media["title"]["romaji"].is_null())
		romaji = media["title"]["romaji"].get<std::string>();

	if (!media["title"]["english"].is_null())
		english = media["title"]["english"].is_null();

	return Entry(id, romaji, english);
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
