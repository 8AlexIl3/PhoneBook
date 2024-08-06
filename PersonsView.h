#pragma once
#pragma once


/////////////////////////////////////////////////////////////////////////////
// CPersonsView

class CPersonsView : public CListView
{

	// Macros
	// ----------------
	DECLARE_DYNCREATE(CPersonsView)
		DECLARE_MESSAGE_MAP()


		// Constructor / Destructor
		// ----------------
public:
	CPersonsView() noexcept;
	virtual ~CPersonsView();


	//MFC message handlers
	// ----------------

protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnInsertPerson();
	afx_msg void OnRefresh();


	//MFC Overrides
	// ----------------
private:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;

	virtual void OnInitialUpdate() override; // called first time after construct

	//Methods
	// ----------------
private:
	CPersonsDocument* GetDocument() const;

	/// <summary> Called by pressing insert</summary>
	/// <returns>TRUE if successful/FALSE if NOT</returns>
	bool InsertPerson();

	/// <summary> Called by pressing enter key while selected a city </summary>
	/// <returns>TRUE if successful/FALSE if NOT</returns>
	bool SelectPerson();

	/// <summary> Called by pressing delete key while selected a city </summary>
	/// <returns>TRUE if successful/FALSE if NOT</returns>
	bool DeletePerson();

	/// <summary> Called by pressing delete key while selected a city </summary>
	/// <returns>TRUE if successful/FALSE if NOT</returns>
	bool UpdatePerson();

	/// <summary> Show all cities currently in the document</summary>
	/// <returns>TRUE if successful/FALSE if NOT</returns>
	void DisplayData();

	///<returns>Index of the users cursel on the list control</returns>
	/// <returns>TRUE if successful/FALSE if NOT</returns>
	long GetRowIndex();


	//Members
	// ----------------
private:
	/// <summary> List control associated with the document upon initialization</summary>
	CListCtrl& m_oListCtrl;


	// Implementaion
	// ----------------
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

#ifndef _DEBUG  // debug version in PersonsView.cpp
inline CPersonsDocument* CPersonsView::GetDocument() const
{
	return reinterpret_cast<CPersonsDocument*>(m_pDocument);
}
#endif

#define FIRST_NAME_COLUMN 0
#define LAST_NAME_COLUMN 1
#define CITY_ID_COLUMN 2
#define ADDRESS_COLUMN 3

#define DEFAULT_COLUMN_WIDTH 100

#define INDEX_NOT_FOUND		-1

#define ERROR_FETCHING_PERSON L"Данните не могат да бъдат заредени"
#define PERSON_CANNOT_BE_SELECTED L"Човекът не може да бъде избран вмомента"
#define PERSON_CANNOT_BE_DELETED L"Човекът не може да бъде изтрит"
#define PERSON_NOT_IN_TABLE L"Човекът вече не съществува"