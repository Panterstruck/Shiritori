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

private:
	std::string romanjiTitle;
	std::string englishTitle;
};

