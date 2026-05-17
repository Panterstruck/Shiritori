#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <print>
#include "DataFetcher.h"
#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;

std::vector<Entry> DataFetcher::GetAnilistEntriesByUser(std::string username, time_t startDate)
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

	json requestPayload = {
		{"query", query},
		{"variables", {
			{"user", username}
		}}
	};

	auto response = client.Post("/", requestPayload.dump(), "application/json");

	if (response)
	{
		if (response->status == 200)
		{
			std::println("Success!");
			std::println("Body: {}", response->body);
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
