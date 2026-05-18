#pragma once
#include <string>
#include "Language.h"

class Entry
{
public:
	Entry(int id, std::string romajiTitle, std::string englishTitle);

	std::string GetTitle(Language language) const;
	std::string GetBeginning(Language language) const;
	std::string GetEnding(Language language) const;
	int GetId() const;
	bool StartsWithN(Language language) const;
	bool EndsWithN(Language language) const;

private:
	std::string romajiTitle;
	std::string englishTitle;

	std::string sanitizedRomajiTitle;
	std::string sanitizedEnglishTitle;

	int id;

	static std::string SanitizeTitle(const std::string& input);
};
