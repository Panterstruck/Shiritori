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

int Link::GetId() const
{
	return entry->GetId();
}

Language Link::GetLanguage() const
{
	return language;
}

bool Link::EndsWithN() const
{
	return entry->EndsWithN(language);
}

std::string Link::GetEnding() const
{
	return entry->GetEnding(language);
}

std::string Link::GetBeginning() const
{
	return entry->GetBeginning(language);
}

bool Link::IsValidLink() const
{
	return !EndsWithN() && GetBeginning() != GetEnding();
}

bool Link::operator==(const Link& other) const
{
	return this->GetId() == other.GetId();
}
