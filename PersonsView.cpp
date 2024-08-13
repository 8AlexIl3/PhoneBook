#include "pch.h"
#include "PersonsDocument.h"
#include "PersonsView.h"
#include "PhoneBook.h"
#include "PersonsDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsView

IMPLEMENT_DYNCREATE(CPersonsView, CListView)

BEGIN_MESSAGE_MAP(CPersonsView, CListView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_RBUTTONDOWN()
    ON_WM_UPDATEUISTATE()
    ON_WM_KEYDOWN()
    ON_COMMAND(IDM_INSERT_RECORD, &CPersonsView::OnInsertPerson)
    ON_COMMAND(IDM_REFRESH_VIEW, &CPersonsView::OnRefresh)
    ON_COMMAND(IDM_EDIT_RECORD, &CPersonsView::OnUpdatePerson)
    ON_COMMAND(IDM_DELETE_RECORD, &CPersonsView::OnDeletePerson)
    ON_UPDATE_COMMAND_UI(IDM_EDIT_RECORD, &CPersonsView::OnContextUpdatePerson)
    ON_UPDATE_COMMAND_UI(IDM_DELETE_RECORD, &CPersonsView::OnContextDeletePerson)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CPersonsView::CPersonsView() noexcept
    : m_oListCtrl(GetListCtrl())
{
}

CPersonsView::~CPersonsView()
{
}


// MFC Overrides
// ----------------

BOOL CPersonsView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CListView::PreCreateWindow(cs);
}

void CPersonsView::OnInitialUpdate()
{
    CListView::OnInitialUpdate();

    m_oListCtrl.ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL);
    m_oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    m_oListCtrl.InsertColumn(FIRST_NAME_COLUMN, _T("Име"), LVCFMT_LEFT, DEFAULT_COLUMN_WIDTH);
    m_oListCtrl.InsertColumn(LAST_NAME_COLUMN, _T("Фамилия"), LVCFMT_LEFT, DEFAULT_COLUMN_WIDTH);
    m_oListCtrl.InsertColumn(CITY_ID_COLUMN, _T("Град"), LVCFMT_LEFT, DEFAULT_COLUMN_WIDTH);
    m_oListCtrl.InsertColumn(ADDRESS_COLUMN, _T("Адрес"), LVCFMT_LEFT, 2*DEFAULT_COLUMN_WIDTH);
    m_oListCtrl.InsertColumn(PRIMARY_PHONE_COLUMN, _T("Главен телефон"), LVCFMT_LEFT, DEFAULT_COLUMN_WIDTH);

    OnRefresh();
}


// MFC message handlers
// ----------------

void CPersonsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CPersonsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

void CPersonsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    DisplayData();
}
void CPersonsView::OnContextUpdatePerson(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_oListCtrl.GetSelectedCount() > 0);
}

void CPersonsView::OnContextDeletePerson(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_oListCtrl.GetSelectedCount() > 0);
}

void CPersonsView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    bool bUpToDate(true);
    switch (nChar) {
    case VK_RETURN:
        bUpToDate = SelectPerson();
        break;
    case VK_DELETE:
        bUpToDate = DeletePerson();
        break;
    case VK_INSERT:
        bUpToDate = InsertPerson();
        break;
    case VK_BACK:
        bUpToDate = UpdatePerson();
        break;
    default:
        break;
    }
    //If action in the switch fail update the view to most recent version
    if (!bUpToDate)
        OnRefresh();
    
    CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPersonsView::OnInsertPerson()
{
    InsertPerson();
}
void CPersonsView::OnUpdatePerson()
{
    UpdatePerson();
}
void CPersonsView::OnDeletePerson()
{
    DeletePerson();
}

void CPersonsView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    UpdatePerson();
}

void CPersonsView::OnRefresh() {
    CPersonsDocument* pPersonsDocument = GetDocument();
    pPersonsDocument->GetCredentials().RefreshData();
    pPersonsDocument->LoadPersons();
    DisplayData();
}


// Methods
// ----------------

CPersonsDocument* CPersonsView::GetDocument() const
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonsDocument)));
    return (CPersonsDocument*)m_pDocument;
}

bool CPersonsView::InsertPerson()
{
    CPersonsDocument* pPersonsDocument = GetDocument();

    if (!pPersonsDocument)
        return FALSE;

    pPersonsDocument->GetCredentials().RefreshData();

    CPersonExtend oPerson;

    CPersonsDlg oPersonsDialog(pPersonsDocument->GetCredentials(), oPerson,true);

    if (oPersonsDialog.DoModal() == IDCANCEL)
        return FALSE;

    //Copy the data

    if (!pPersonsDocument->InsertPerson(oPersonsDialog.GetPerson()))
        return FALSE;
   
    return TRUE;
}

bool CPersonsView::SelectPerson()
{
    CPersonsDocument* pPersonsDocument = GetDocument();

    if (!pPersonsDocument) {
        AfxMessageBox(ERROR_FETCHING_PERSON);
        return FALSE;
    }

    long lIndexer = GetRowIndex();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

    //Get ID from the selected row

    CPersonExtend oPerson;

    long lPersonID = (long)m_oListCtrl.GetItemData(lIndexer);

    if (!lPersonID) {
        AfxMessageBox(PERSON_CANNOT_BE_SELECTED);
        return FALSE;
    }
    if (!pPersonsDocument->SelectPerson(lPersonID, oPerson)) {
        AfxMessageBox(PERSON_CANNOT_BE_SELECTED);
        return FALSE;
    }
    
    pPersonsDocument->GetCredentials().RefreshData();


    CPersonsDlg oPersonsDialog(pPersonsDocument->GetCredentials(), oPerson,false);

    oPersonsDialog.DoModal();
      
    return TRUE;
}
bool CPersonsView::DeletePerson()
{
    CPersonsDocument* pPersonsDocument = GetDocument();

    if (!pPersonsDocument) {
        AfxMessageBox(ERROR_FETCHING_PERSON);
        return FALSE;
    }

    long lIndexer = GetRowIndex();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;
    
    //Get ID from the selected row
    long lPersonID = (long)m_oListCtrl.GetItemData(lIndexer);

    if (!lPersonID) {
        AfxMessageBox(PERSON_CANNOT_BE_SELECTED);
        return FALSE;
    }

    if (AfxMessageBox(L"Потвърдете изтриването", MB_OKCANCEL)==IDCANCEL)
        return FALSE;

    if (!pPersonsDocument->DeletePerson(lPersonID, lIndexer)) {
        AfxMessageBox(PERSON_CANNOT_BE_DELETED);
        return FALSE;
    }

    return TRUE;
}

bool CPersonsView::UpdatePerson()
{
    CPersonsDocument* pPersonsDocument = GetDocument();

    if (!pPersonsDocument) 
        return FALSE;

    long lIndexer = GetRowIndex();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

   
    long lCityID = (long)m_oListCtrl.GetItemData(lIndexer);

    //see if element pointer is null
    CPersonExtend* pPerson = pPersonsDocument->GetPersonArray().GetAt(lIndexer);
   
    if (!pPerson)
        return FALSE;

    CPersonExtend& oPerson = *pPerson;
      
    
    pPersonsDocument->GetCredentials().RefreshData();

    CPersonsDlg oPersonsDialog(pPersonsDocument->GetCredentials(),oPerson,true);

    if (oPersonsDialog.DoModal() == IDCANCEL) 
        return FALSE;
    

    //Copy the data

    if (!pPersonsDocument->UpdatePerson(oPerson.m_oRecPerson.lID, oPersonsDialog.GetPerson())) 
        return FALSE;
    
    return TRUE;
}

void CPersonsView::DisplayData()
{
    CPersonsDocument* pPersonsDocument = GetDocument();

    if (!pPersonsDocument) {
        AfxMessageBox(ERROR_FETCHING_PERSON);
        return;
    }

    m_oListCtrl.DeleteAllItems();

    for (long lIndexer(0),lCtrlListIndex(0); (INT_PTR)lIndexer < pPersonsDocument->GetPersonArray().GetCount(); ++lIndexer)
    {
        CPersonExtend* pPerson = pPersonsDocument->GetPersonArray().GetAt(lIndexer);
        if (!pPerson) 
            continue;

        PHONE_NUMBERS* pPhoneNumber = pPerson->m_oPhoneNumbersArray.GetAt(NULL);

        if (!pPhoneNumber)
            continue;

        m_oListCtrl.InsertItem(lCtrlListIndex, L"");
        m_oListCtrl.SetItemText(lCtrlListIndex, FIRST_NAME_COLUMN, pPerson->m_oRecPerson.szFirstName);
        m_oListCtrl.SetItemText(lCtrlListIndex, LAST_NAME_COLUMN, pPerson->m_oRecPerson.szLastName);

        CString strCityID;
        pPersonsDocument->GetCredentials().GetStringtoCityMap().Lookup(pPerson->m_oRecPerson.lCityID, strCityID);
        m_oListCtrl.SetItemText(lCtrlListIndex, CITY_ID_COLUMN, strCityID);

        m_oListCtrl.SetItemText(lCtrlListIndex, ADDRESS_COLUMN, pPerson->m_oRecPerson.szAddress);

        m_oListCtrl.SetItemData(lCtrlListIndex, pPerson->m_oRecPerson.lID);

        m_oListCtrl.SetItemText(lCtrlListIndex++, PRIMARY_PHONE_COLUMN, pPhoneNumber->szPhone);
        
    }
}

long CPersonsView::GetRowIndex()
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

void CPersonsView::AssertValid() const
{
    CListView::AssertValid();
}

void CPersonsView::Dump(CDumpContext& dc) const
{
    CListView::Dump(dc);
}


