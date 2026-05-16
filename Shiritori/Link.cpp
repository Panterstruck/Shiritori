#include "Link.h"

Link::Link(Entry entry, Language language)
	: entry(std::make_shared<Entry>(entry))
	, language(language)
{
}

std::string Link::GetTitle() const
{
	return entry->GetTitle(language);
}

std::string Link::GetBeginning() const
{
	return entry->GetBeginning(language);
}

std::string Link::GetEnding() const
{
	return entry->GetEnding(language);
}
