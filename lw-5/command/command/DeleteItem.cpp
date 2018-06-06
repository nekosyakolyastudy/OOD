﻿#include "stdafx.h"
#include "DeleteItem.h"

CDeleteItem::CDeleteItem(std::vector<CDocumentItem>& items, size_t index)
	: m_items(items)
	, m_index(index)
	, m_item(std::make_shared<CDocumentItem>(nullptr, nullptr))
{
}

CDeleteItem::~CDeleteItem()
{
	//если выполнена и это картинка то из images удаляем
	auto image = m_item->GetImage();
	if (m_executed && image)
	{
		boost::system::error_code errorCode;
		boost::filesystem::remove(image->GetPath(), errorCode);
		if (errorCode)
		{
			std::cout << errorCode.message() << std::endl;
		}
	}
}

void CDeleteItem::DoExecute()
{
	m_item = std::make_shared<CDocumentItem>(m_items.at(m_index));

	m_items.erase(m_items.begin() + m_index);
}

void CDeleteItem::DoUnexecute()
{
	m_items.emplace(m_items.begin() + m_index, *m_item);
}
