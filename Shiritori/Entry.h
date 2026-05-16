#pragma once
#include <string>
#include "Language.h"

class Entry
{
public:

	Entry(std::string romanjiTitle, std::string englishTitle);

	std::string GetTitle(Language language) const;
	std::string GetBeginning(Language language) const;
	std::string GetEnding(Language language) const;
	int GetId() const;

private:
	std::string romanjiTitle;
	std::string englishTitle;

	std::string sanitizedRomanjiTitle;
	std::string sanitizedEnglishTitle;

	int id;

	static int GenerateId();
	static std::string SanitizeTitle(const std::string& input);
};
