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
	if (language == ROMAJI)
		return sanitizedRomajiTitle.substr(0, 2);
	else if (language == ENGLISH)
		return sanitizedEnglishTitle.substr(0, 2);
	return std::string();
}

std::string Entry::GetEnding(Language language) const
{
	if (language == ROMAJI)
		return sanitizedRomajiTitle.substr(sanitizedRomajiTitle.size() - 2 , 2);
	else if (language == ENGLISH)
		return sanitizedEnglishTitle.substr(sanitizedEnglishTitle.size() - 2, 2);
	return std::string();
}

int Entry::GetId() const
{
	return id;
}

bool Entry::StartsWithN(Language language) const
{
	if (language == ROMAJI)
		return sanitizedRomajiTitle.substr(0, 1) == "N";
	else if (language == ENGLISH)
		return sanitizedEnglishTitle.substr(0, 1) == "N";
	return false;
}

bool Entry::EndsWithN(Language language) const
{
	if (language == ROMAJI)
		return sanitizedRomajiTitle.substr(sanitizedRomajiTitle.size() - 1, 1) == "N";
	else if (language == ENGLISH)
		return sanitizedEnglishTitle.substr(sanitizedEnglishTitle.size() - 1, 1) == "N";
	return false;
}

std::string Entry::SanitizeTitle(const std::string& input)
{
	std::string result;
	// Pre-allocate memory to prevent reallocation overhead during the loop
	result.reserve(input.size());

	for (char c : input)
	{
		// Note: Casting to unsigned char is required by the C++ standard 
		// to prevent undefined behavior with negative char values.
		if (std::isalpha(static_cast<unsigned char>(c)))
			result.push_back(std::toupper(static_cast<unsigned char>(c)));
	}

	return result;
}
