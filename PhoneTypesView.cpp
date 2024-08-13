#include "pch.h"
#include "PhoneTypesDocument.h"
#include "PhoneTypesView.h"
#include "PhoneBook.h"
#include "PhoneTypesDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesView

IMPLEMENT_DYNCREATE(CPhoneTypesView, CListView)

BEGIN_MESSAGE_MAP(CPhoneTypesView, CListView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_RBUTTONDOWN()
    ON_WM_UPDATEUISTATE()
    ON_WM_KEYDOWN()
    ON_COMMAND(IDM_INSERT_RECORD, &CPhoneTypesView::OnInsertPhoneType)
    ON_COMMAND(IDM_REFRESH_VIEW, &CPhoneTypesView::OnRefresh)
    ON_COMMAND(IDM_EDIT_RECORD, &CPhoneTypesView::OnUpdatePhoneType)
    ON_COMMAND(IDM_DELETE_RECORD, &CPhoneTypesView::OnDeletePhoneType)
    ON_UPDATE_COMMAND_UI(IDM_EDIT_RECORD, &CPhoneTypesView::OnContextUpdatePhoneType)
    ON_UPDATE_COMMAND_UI(IDM_DELETE_RECORD, &CPhoneTypesView::OnContextDeletePhoneType)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CPhoneTypesView::CPhoneTypesView() noexcept
    : m_oListCtrl(GetListCtrl())
{
}

CPhoneTypesView::~CPhoneTypesView()
{
}


// MFC Overrides
// ----------------

BOOL CPhoneTypesView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CListView::PreCreateWindow(cs);
}

void CPhoneTypesView::OnInitialUpdate()
{
    CListView::OnInitialUpdate();

    m_oListCtrl.ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL);
    m_oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);
    m_oListCtrl.InsertColumn(PHONE_TYPE_COLUMN, _T("Ïëàí"), LVCFMT_LEFT, DEFAULT_COLUMN_WIDTH);

    DisplayData();

}


// MFC message handlers
// ----------------

void CPhoneTypesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CPhoneTypesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

void CPhoneTypesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    DisplayData();
}
void CPhoneTypesView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    UpdatePhoneType();
}
void CPhoneTypesView::OnContextUpdatePhoneType(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_oListCtrl.GetSelectedCount() > 0);
}

void CPhoneTypesView::OnContextDeletePhoneType(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_oListCtrl.GetSelectedCount() > 0);
}


void CPhoneTypesView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    bool bUpToDate(true);
    switch (nChar) {
    case VK_RETURN:
        bUpToDate = SelectPhoneType();
        break;
    case VK_DELETE:
        bUpToDate = DeletePhoneType();
        break;
    case VK_INSERT:
        bUpToDate = InsertPhoneType();
        break;
    case VK_BACK:
        bUpToDate = UpdatePhoneType();
        break;
    default:
        break;
    }
    //If actions in the switch fail update the view to most recent version
    if (!bUpToDate) {
        OnRefresh();
    }
    CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPhoneTypesView::OnInsertPhoneType()
{
    InsertPhoneType();
}

void CPhoneTypesView::OnUpdatePhoneType()
{
    UpdatePhoneType();
}
void CPhoneTypesView::OnDeletePhoneType()
{
    DeletePhoneType();
}

void CPhoneTypesView::OnRefresh() {
    CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();
    pPhoneTypesDocument->LoadPhoneTypes();
    DisplayData();
}


// Methods
// ----------------

CPhoneTypesDocument* CPhoneTypesView::GetDocument() const
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhoneTypesDocument)));
    return (CPhoneTypesDocument*)m_pDocument;
}

bool CPhoneTypesView::InsertPhoneType()
{
    CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();

    if (!pPhoneTypesDocument) {
        AfxMessageBox(ÅRROR_FETCHING_PHONE_TYPE);
        return FALSE;
    }

    CPhoneTypesDlg oPhoneTypesDialog;

    if (oPhoneTypesDialog.DoModal() == IDCANCEL)
        return FALSE;

    PHONE_TYPES& oPhoneTypes = *oPhoneTypesDialog.GetPhoneType();

    //Copy the data

    if (!pPhoneTypesDocument->InsertPhoneType(oPhoneTypes))
        return FALSE;

    return TRUE;
}

bool CPhoneTypesView::SelectPhoneType()
{
    CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();

    long lIndexer = GetRowIndex();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

    if (!pPhoneTypesDocument) {
        AfxMessageBox(ÅRROR_FETCHING_PHONE_TYPE);
        return FALSE;
    }
    //Get ID from the selected row

    PHONE_TYPES oPhoneTypes;

    long lPhoneTypeID = (long)m_oListCtrl.GetItemData(lIndexer);

    if (!lPhoneTypeID) {
        AfxMessageBox(PHONE_TYPE_CANNOT_BE_SELECTED);
        return FALSE;
    }
    if (!pPhoneTypesDocument->SelectPhoneType(lPhoneTypeID, oPhoneTypes)) {
        AfxMessageBox(PHONE_TYPE_CANNOT_BE_SELECTED);
        return FALSE;
    }
    CString strPhoneType;

    CPhoneTypesDlg oPhoneTypeDlg(oPhoneTypes,FALSE);

    oPhoneTypeDlg.DoModal();

    return TRUE;
}

bool CPhoneTypesView::DeletePhoneType()
{
    CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();

    long lIndexer = GetRowIndex();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

    if (!pPhoneTypesDocument) {
        AfxMessageBox(ÅRROR_FETCHING_PHONE_TYPE);
        return FALSE;
    }
    //Get ID from the selected row
    long lPhoneTypeID = (long)m_oListCtrl.GetItemData(lIndexer);

    if (!lPhoneTypeID) {
        AfxMessageBox(PHONE_TYPE_CANNOT_BE_SELECTED);
        return FALSE;
    }
    if (AfxMessageBox(L"Ïîòâúðäåòå èçòðèâàíåòî", MB_OKCANCEL) == IDCANCEL)
        return FALSE;

    if (!pPhoneTypesDocument->DeletePhoneType(lPhoneTypeID, lIndexer)) {
        AfxMessageBox(PHONE_TYPE_CANNOT_BE_DELETED);
        return FALSE;
    }

    return TRUE;
}

bool CPhoneTypesView::UpdatePhoneType()
{
    CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();

    long lIndexer = GetRowIndex();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

    if (!pPhoneTypesDocument) {
        AfxMessageBox(ÅRROR_FETCHING_PHONE_TYPE);
        return FALSE;
    }
    long lPhoneTypeID = (long)m_oListCtrl.GetItemData(lIndexer);

    //Dummy reference ->It is later used as logical link to update PhoneTypes
    PHONE_TYPES& oPhoneTypes = *pPhoneTypesDocument->GetPhoneTypeArray().GetAt(lIndexer);

    //If PhoneType is still in view but no longer in table
    if (!pPhoneTypesDocument->SelectPhoneType(lPhoneTypeID, oPhoneTypes)) {
        AfxMessageBox(PHONE_TYPE_NOT_IN_TABLE);
        return FALSE;
    }

    //Initialize the dialog edit controls with values from the selected PhoneType
    CPhoneTypesDlg oPhoneTypesDialog(oPhoneTypes,TRUE);

    if (oPhoneTypesDialog.DoModal() == IDCANCEL)
        return FALSE;

    oPhoneTypes = *oPhoneTypesDialog.GetPhoneType();

    if (!pPhoneTypesDocument->UpdatePhoneType(lPhoneTypeID, oPhoneTypes))
        return FALSE;

    return TRUE;
}

void CPhoneTypesView::DisplayData()
{
    CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();

    if (!pPhoneTypesDocument) {
        AfxMessageBox(ÅRROR_FETCHING_PHONE_TYPE);
        return;
    }

    m_oListCtrl.DeleteAllItems();

    for (long lIndexer(0); (INT_PTR)lIndexer < pPhoneTypesDocument->GetPhoneTypeArray().GetCount(); ++lIndexer)
    {
        PHONE_TYPES* pPhoneTypes = pPhoneTypesDocument->GetPhoneTypeArray().GetAt(lIndexer);
        if (!pPhoneTypes)
            continue;
        m_oListCtrl.InsertItem(lIndexer, pPhoneTypes->szPhoneType);
        m_oListCtrl.SetItemData(lIndexer, pPhoneTypes->lID);
    }
}

long CPhoneTypesView::GetRowIndex()
{
    POSITION pos = m_oListCtrl.GetFirstSelectedItemPosition();
    if (!pos)
        return INDEX_NOT_FOUND;

    int lIndexer = m_oListCtrl.GetNextSelectedItem(pos);
    if (lIndexer == INDEX_NOT_FOUND)
        return INDEX_NOT_FOUND;

    return lIndexer;
}


// Implementaion
// ----------------

void CPhoneTypesView::AssertValid() const
{
    CListView::AssertValid();
}

void CPhoneTypesView::Dump(CDumpContext& dc) const
{
    CListView::Dump(dc);
}


