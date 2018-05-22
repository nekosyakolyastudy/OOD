#pragma once
#include "IDocument.h"
#include "CCommandHistory.h"

class CDocument :
	public IDocument
{
public:

	void SetTitle(const std::string & title) override;
	std::string GetTitle() const override;

	bool CanUndo() const override;
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

	size_t GetItemsCount()const override;

	CConstDocumentItem GetItem(size_t index)const override;
	CDocumentItem GetItem(size_t index) override;

	void Save(const boost::filesystem::path& path) const override;
	void DeleteItem(size_t index) override;
	std::shared_ptr<IImage> InsertImage(const boost::filesystem::path& path, int width, int height,
		boost::optional<size_t> position = boost::none) override;




	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, boost::optional<size_t> position = boost::none) override;



private:
	std::string m_title;
	CCommandHistory m_history;
	std::vector<CDocumentItem> m_items;
};
