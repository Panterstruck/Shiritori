#pragma once
#include <string>
#include <utility>
#include "json.hpp"

class UserQuerier
{
public:
	static std::string PromptForCommentUrl();
	static std::pair<std::string, std::string> ParseChallengeComment(const std::string& commentUrl);

private:
	static int ExtractCommentIdFromUrl(const std::string& url);
	static nlohmann::json BuildPayload(const int commentId);
};
