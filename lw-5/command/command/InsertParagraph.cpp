﻿#include "stdafx.h"
#include "InsertParagraph.h"

#include "Paragraph.h"

CInsertParagraph::CInsertParagraph(CCommandHistory& history, std::vector<CDocumentItem>& items, const std::string& text, boost::optional<size_t> position)
	: m_items(items)
	, m_position(position)
{
	InitializationParagraph(history, text);
}

void CInsertParagraph::DoExecute()
{
	size_t index = m_position.get();

	if (index != 0 && m_position >= m_items.size())
	{
		throw std::logic_error("Index should be less than the size of the document");
	}
	if (m_position == boost::none)
	{

		m_items.emplace_back(CDocumentItem(nullptr, m_paragraph));
	}
	else
	{
		m_items.emplace(m_items.begin() + index, CDocumentItem(nullptr, m_paragraph));
	}
}

void CInsertParagraph::DoUnexecute()
{
	if (m_position == boost::none)
	{
		m_items.pop_back();
	}
	else
	{
		m_items.erase(m_items.begin() + m_position.get());
	}
}

void CInsertParagraph::InitializationParagraph(CCommandHistory& history, const std::string& text)
{
	CParagraph paragraph(history);
	paragraph.SetText(text);
	m_paragraph = std::make_shared<CParagraph>(paragraph);
}
