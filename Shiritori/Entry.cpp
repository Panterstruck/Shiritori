#include "Entry.h"

Entry::Entry(std::string romanjiTitle, std::string englishTitle)
	: romanjiTitle(romanjiTitle)
	, englishTitle(englishTitle)
	, language(ROMANJI)
{
}

std::string Entry::GetTitle(Language language)
{
	if (language == ROMANJI)
		return romanjiTitle;
	else if (language == ENGLISH)
		return englishTitle;
	return std::string();
}

std::string Entry::GetTitle()
{
	return GetTitle(language);
}

std::string Entry::GetBeginning(Language language)
{
	if (language == ROMANJI)
		return romanjiTitle.substr(0, 2);
	else if (language == ENGLISH)
		return englishTitle.substr(0, 2);
	return std::string();
}

std::string Entry::GetBeginning()
{
	return GetBeginning(language);
}

std::string Entry::GetEnding(Language language)
{
	if (language == ROMANJI)
		return romanjiTitle.substr(romanjiTitle.size() - 2 , 2);
	else if (language == ENGLISH)
		return englishTitle.substr(englishTitle.size() - 2, 2);
	return std::string();
}

std::string Entry::GetEnding()
{
	return GetEnding(language);
}
