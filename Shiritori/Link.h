#pragma once
#include <memory>
#include "Entry.h"

class Link
{
public:
	Link(Entry entry, Language language);

	std::string GetTitle() const;
	Language GetLanguage() const;
	bool EndsWithN() const;
	std::string GetEnding() const;
	std::string GetBeginning() const;
	bool IsValidLink() const;

	bool operator==(const Link& other) const;

private:
	std::shared_ptr<Entry> entry;
	Language language;

	int GetId() const;
};

