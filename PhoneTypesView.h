#pragma once


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesView

class CPhoneTypesView : public CListView
{

	// Macros
	// ----------------
	DECLARE_DYNCREATE(CPhoneTypesView)
		DECLARE_MESSAGE_MAP()


		// Constructor / Destructor
		// ----------------
public:
	CPhoneTypesView() noexcept;
	virtual ~CPhoneTypesView();


	//MFC message handlers
	// ----------------

protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnInsertPhoneType();
	afx_msg void OnUpdatePhoneType();
	afx_msg void OnDeletePhoneType();
	afx_msg void OnRefresh();


	//MFC Overrides
	// ----------------
private:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;

	virtual void OnInitialUpdate() override; // called first time after construct

	//Methods
	// ----------------
private:
	CPhoneTypesDocument* GetDocument() const;

	/// <summary> Called by pressing insert</summary>
	/// <returns>TRUE if successful/FALSE if NOT</returns>
	bool InsertPhoneType();

	/// <summary> Called by pressing enter key while selected a PhoneType </summary>
	/// <returns>TRUE if successful/FALSE if NOT</returns>
	bool SelectPhoneType();

	/// <summary> Called by pressing delete key while selected a PhoneType </summary>
	/// <returns>TRUE if successful/FALSE if NOT</returns>
	bool DeletePhoneType();

	/// <summary> Called by pressing delete key while selected a PhoneType </summary>
	/// <returns>TRUE if successful/FALSE if NOT</returns>
	bool UpdatePhoneType();

	/// <summary> Show all PhoneTypes currently in the document</summary>
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

#ifndef _DEBUG  // debug version in PhoneTypesView.cpp
inline CPhoneTypesDocument* CPhoneTypesView::GetDocument() const
{
	return reinterpret_cast<CPhoneTypesDocument*>(m_pDocument);
}
#endif

#define PHONE_TYPE_COLUMN	0

#define DEFAULT_COLUMN_WIDTH 150

#define INDEX_NOT_FOUND -1

#define ЕRROR_FETCHING_PHONE_TYPE L"Данните не могат да бъдат заредени\n"
#define PHONE_TYPE_CANNOT_BE_SELECTED L"Планът не може да бъде избран вмомента"
#define PHONE_TYPE_CANNOT_BE_DELETED L"Планът не може да бъде изтрит"
#define PHONE_TYPE_NOT_IN_TABLE L"Планът вече не съществува"