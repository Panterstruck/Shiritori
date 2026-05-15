#include "Entry.h"

Entry::Entry(std::string romanjiTitle, std::string englishTitle)
	: romanjiTitle(romanjiTitle), englishTitle(englishTitle)
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