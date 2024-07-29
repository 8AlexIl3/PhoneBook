
// CitiesView.h : interface of the CCitiesView class
//
#pragma once
#define ID_COLUMN			0
#define CITY_COLUMN			1
#define RESIDENCE_COLUMN	2

#define DEFAULT_COLUMN_WIDTH 100

#define INDEX_NOT_FOUND -1

class CCitiesView : public CListView
{
protected: // create from serialization only
	DECLARE_DYNCREATE(CCitiesView)
	DECLARE_MESSAGE_MAP()

	//Constructors and destructors-------------------------------------------------------------------------------------------
public:
	CCitiesView() noexcept;
	virtual ~CCitiesView();


// Implementation

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//MFC message handlers
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnInsertCity();
	afx_msg void OnRefresh();

	//Overrides---------------------------------------------------------------------------------------------------
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;
protected:
	virtual void OnInitialUpdate() override; // called first time after construct

	//Methods ---------------------------------------------------------------------------------------------------------------
private:
	CCitiesDocument* GetDocument() const;
	/// <summary> Called by pressing insert</summary>
	BOOL InsertCity();
	/// <summary> Called by pressing enter key while selected a city </summary>
	BOOL SelectCity();
	/// <summary> Called by pressing delete key while selected a city </summary>
	BOOL DeleteCity();
	/// <summary> Called by pressing delete key while selected a city </summary>
	BOOL UpdateCity();
	/// <summary> Show all cities currently in the document</summary>
	void DisplayData();
	///<returns>Index of the users cursel on the list control</returns>
	long GetTableRowIndex();

	///Members----------------------------------------------------------------------------------------------------
private:
	/// <summary> List control associated with the document upon initialization</summary>
	CListCtrl& m_oListCtrl;
	/// <summary> Pointer to current document</summary>
	CCitiesDocument* m_pDoc;

};

#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CCitiesDocument* CCitiesView::GetDocument() const
   { return reinterpret_cast<CCitiesDocument*>(m_pDocument); }
#endif

