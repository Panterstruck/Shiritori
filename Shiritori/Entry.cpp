#include <cctype>
#include "Entry.h"

Entry::Entry(std::string romanjiTitle, std::string englishTitle)
	: romanjiTitle(romanjiTitle)
	, englishTitle(englishTitle)
	, sanitizedRomanjiTitle(SanitizeTitle(romanjiTitle))
	, sanitizedEnglishTitle(SanitizeTitle(englishTitle))
	, id(GenerateId())
{
}

std::string Entry::GetTitle(Language language) const
{
	if (language == ROMANJI)
		return sanitizedRomanjiTitle;
	else if (language == ENGLISH)
		return sanitizedEnglishTitle;
	return std::string();
}

std::string Entry::GetBeginning(Language language) const
{
	if (language == ROMANJI)
		return sanitizedRomanjiTitle.substr(0, 2);
	else if (language == ENGLISH)
		return sanitizedEnglishTitle.substr(0, 2);
	return std::string();
}

std::string Entry::GetEnding(Language language) const
{
	if (language == ROMANJI)
		return sanitizedRomanjiTitle.substr(sanitizedRomanjiTitle.size() - 2 , 2);
	else if (language == ENGLISH)
		return sanitizedEnglishTitle.substr(sanitizedEnglishTitle.size() - 2, 2);
	return std::string();
}

int Entry::GetId() const
{
	return id;
}

int Entry::GenerateId()
{
	static int counter = 0;
	return ++counter;
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
