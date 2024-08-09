#pragma once


/////////////////////////////////////////////////////////////////////////////
// CCitiesView

class CCitiesView : public CListView
{

// Macros
// ----------------
	DECLARE_DYNCREATE(CCitiesView)
	DECLARE_MESSAGE_MAP()


// Constructor / Destructor
// ----------------
public:
	CCitiesView() noexcept;
	virtual ~CCitiesView();


//MFC message handlers
// ----------------

protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnInsertCity();
	afx_msg void OnUpdateCity();
	afx_msg void OnDeleteCity();
	afx_msg void OnRefresh();


//MFC Overrides
// ----------------
private:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;

	virtual void OnInitialUpdate() override; // called first time after construct

//Methods
// ----------------
private:
	CCitiesDocument* GetDocument() const;

	/// <summary> Called by pressing insert</summary>
	/// <returns>TRUE if successful/FALSE if NOT</returns>
	bool InsertCity();

	/// <summary> Called by pressing enter key while selected a city </summary>
	/// <returns>TRUE if successful/FALSE if NOT</returns>
	bool SelectCity();

	/// <summary> Called by pressing delete key while selected a city </summary>
	/// <returns>TRUE if successful/FALSE if NOT</returns>
	bool DeleteCity();

	/// <summary> Called by pressing delete key while selected a city </summary>
	/// <returns>TRUE if successful/FALSE if NOT</returns>
	bool UpdateCity();

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

#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CCitiesDocument* CCitiesView::GetDocument() const
   { return reinterpret_cast<CCitiesDocument*>(m_pDocument); }
#endif

#define ID_COLUMN			0
#define CITY_COLUMN			1
#define RESIDENCE_COLUMN	2

#define DEFAULT_COLUMN_WIDTH 150

#define INDEX_NOT_FOUND -1

#define ЕRROR_FETCHING_CITY L"Данните не могат да бъдат заредени\n"
#define CITY_CANNOT_BE_SELECTED L"Градът не може да бъде избран вмомента"
#define CITY_CANNOT_BE_DELETED L"Градът не може да бъде изтрит"
#define CITY_NOT_IN_TABLE L"Градът вече не съществува"