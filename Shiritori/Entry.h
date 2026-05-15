#pragma once
#include <string>

class Entry
{
public:
	enum Language 
	{
		ROMANJI, ENGLISH
	};

	Entry(std::string romanjiTitle, std::string englishTitle);
	std::string GetTitle(Language language);
	std::string GetTitle();

	std::string GetBeginning(Language language);
	std::string GetBeginning();

	std::string GetEnding(Language language);
	std::string GetEnding();

	Language language;

private:
	std::string romanjiTitle;
	std::string englishTitle;
};
