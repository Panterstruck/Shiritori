#pragma once
#include "UserQuerier.h"
#include <stdexcept>
#include <print>
#include <chrono>
#include <iostream>
#include "httplib.h"

using json = nlohmann::json;

std::string UserQuerier::PromptForCommentUrl()
{
	std::string url;

	while (true)
	{
		std::print("Enter the URL to your AniList challenge comment: ");
		std::getline(std::cin, url);

		if (url.empty())
		{
			std::println("Error: Input cannot be empty. Please try again.");
			continue;
		}

		if (url.find("anilist.co/forum/thread/") == std::string::npos)
		{
			std::println("Error: That doesn't look like a valid AniList comment URL.");
			std::println("Example: https://anilist.co/forum/thread/44430/comment/1234567");
			continue;
		}

		break;
	}

	return url;
}

std::pair<std::string, std::string> UserQuerier::ParseChallengeComment(const std::string& commentUrl)
{
	httplib::Client client("https://graphql.anilist.co");
	int commentId = ExtractCommentIdFromUrl(commentUrl);
	json requestPayload = BuildPayload(commentId);
	auto response = client.Post("/", requestPayload.dump(), "application/json");

	if (!response)
		throw std::runtime_error(std::format("Network error: {}", httplib::to_string(response.error())));

	if (response->status != 200)
		throw std::runtime_error(std::format("API Error {}: {}", response->status, response->body));

	std::println("Retrieving challenge info from comment-ID: {} Status: {}", commentId, response->status);

	json data = json::parse(response->body);
	auto& commentsArray = data["data"]["ThreadComment"];
	if (commentsArray.empty())
		throw std::runtime_error("AniList returned no comments for that ID.");

	auto& commentData = commentsArray[0];
	std::string username = commentData["user"]["name"].get<std::string>();

	long long rawTime = commentData["createdAt"].get<long long>();
	std::chrono::sys_seconds timePoint{ std::chrono::seconds{rawTime} };
	std::string dateString = std::format("{:%F}", timePoint);

	return { username, dateString };
}

int UserQuerier::ExtractCommentIdFromUrl(const std::string& url)
{
	size_t lastSlash = url.find_last_of('/');
	if (lastSlash != std::string::npos)
		return std::stoi(url.substr(lastSlash + 1));

	throw std::invalid_argument("Invalid AniList comment URL.");
}

nlohmann::json UserQuerier::BuildPayload(const int commentId)
{
	const std::string commentQuery = R"(
		query ($id: Int)
		{
			ThreadComment(id: $id)
			{
				user { name }
				createdAt
			}
		}
		)";

	json requestPayload = {
		{"query", commentQuery},
		{"variables", {
			{"id", commentId}
		}}
	};

	return requestPayload;
}
