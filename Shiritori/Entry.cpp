#include <cctype>
#include "Entry.h"

Entry::Entry(int id, std::string romajiTitle, std::string englishTitle)
	: id(id)
	, romajiTitle(romajiTitle)
	, englishTitle(englishTitle)
	, sanitizedRomajiTitle(SanitizeTitle(romajiTitle))
	, sanitizedEnglishTitle(SanitizeTitle(englishTitle))
{
}

std::string Entry::GetTitle(Language language) const
{
	if (language == ROMAJI)
		return romajiTitle;
	else if (language == ENGLISH)
		return englishTitle;
	return std::string();
}

std::string Entry::GetBeginning(Language language) const
{
	std::string beginning;
	if (language == ROMAJI)
		beginning = sanitizedRomajiTitle;
	else if (language == ENGLISH)
		beginning = sanitizedEnglishTitle;

	if (beginning.size() >= 2)
		beginning = beginning.substr(0, 2);
	return beginning;
}

std::string Entry::GetEnding(Language language) const
{
	std::string ending;
	if (language == ROMAJI)
		ending = sanitizedRomajiTitle;
	else if (language == ENGLISH)
		ending = sanitizedEnglishTitle; 

	if (ending.size() >= 2)
		ending = ending.substr(ending.size() - 2, 2);
	return ending;
}

int Entry::GetId() const
{
	return id;
}

bool Entry::StartsWithN(Language language) const
{
	std::string title;
	if (language == ROMAJI)
		title = sanitizedRomajiTitle;
	else if (language == ENGLISH)
		title = sanitizedEnglishTitle;

	if (title.size() >= 1)
		title = title.substr(0, 1);
	return title == "N";
}

bool Entry::EndsWithN(Language language) const
{
	std::string title;
	if (language == ROMAJI)
		title = sanitizedRomajiTitle;
	else if (language == ENGLISH)
		title = sanitizedEnglishTitle;

	if (title.size() >= 1)
		title = title.substr(title.size() - 1, 1);
	return title == "N";
}

std::string Entry::SanitizeTitle(const std::string& input)
{
	std::string result;
	result.reserve(input.size());

	for (char c : input)
	{
		if (std::isalpha(static_cast<unsigned char>(c)))
			result.push_back(std::toupper(static_cast<unsigned char>(c)));
	}

	return result;
}
