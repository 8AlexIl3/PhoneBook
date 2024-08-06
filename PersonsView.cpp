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
    ON_COMMAND(IDM_INSERT_CITY, &CPersonsView::OnInsertPerson)
    ON_COMMAND(IDM_REFRESH_VIEW, &CPersonsView::OnRefresh)
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
    m_oListCtrl.InsertColumn(FIRST_NAME_COLUMN, _T("���"), LVCFMT_CENTER, DEFAULT_COLUMN_WIDTH);
    m_oListCtrl.InsertColumn(LAST_NAME_COLUMN, _T("�������"), LVCFMT_CENTER, DEFAULT_COLUMN_WIDTH);
    m_oListCtrl.InsertColumn(CITY_ID_COLUMN, _T("����(ID)"), LVCFMT_CENTER, DEFAULT_COLUMN_WIDTH);
    m_oListCtrl.InsertColumn(ADDRESS_COLUMN, _T("�����"), LVCFMT_CENTER, DEFAULT_COLUMN_WIDTH);

    DisplayData();

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
    OnRefresh();
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
    //If actions in the switch fail update the view to most recent version
    if (!bUpToDate) {
        OnRefresh();
    }
    CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPersonsView::OnInsertPerson()
{
    InsertPerson();
}

void CPersonsView::OnRefresh() {
    CPersonsDocument* pPersonsDocument = GetDocument();
    pPersonsDocument->LoadCities();
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

    if (!pPersonsDocument) {
        return FALSE;
    }

    
    pPersonsDocument->LoadCities();
    pPersonsDocument->LoadPhoneTypes();

    CPersonsDlg oPersonsDialog(pPersonsDocument->GetCitiesArray(),
        &pPersonsDocument->GetPhoneTypesArray());

    if (oPersonsDialog.DoModal() == IDCANCEL) {
        return FALSE;
    }

    //Copy the data

    if (!pPersonsDocument->InsertPerson(oPersonsDialog.GetPerson())) {
        return FALSE;
    }
   
    return TRUE;
}

bool CPersonsView::SelectPerson()
{
    CPersonsDocument* pPersonsDocument = GetDocument();

    long lIndexer = GetRowIndex();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

    if (!pPersonsDocument) {
        AfxMessageBox(ERROR_FETCHING_PERSON);
        return FALSE;
    }
    //Get ID from the selected row

    CPerson oPersons;

    long lPersonID = (long)m_oListCtrl.GetItemData(lIndexer);

    if (!lPersonID) {
        AfxMessageBox(PERSON_CANNOT_BE_SELECTED);
        return FALSE;
    }
    if (!pPersonsDocument->SelectPerson(lPersonID, oPersons)) {
        AfxMessageBox(PERSON_CANNOT_BE_SELECTED);
        return FALSE;
    }
    CString strPerson;

    //Print Person
    strPerson.Format(L" ID: % d, ����� : % d",
        oPersons.m_oRecPerson.lID,
        oPersons.m_oRecPerson.lUpdateCounter);
    AfxMessageBox(strPerson);

    return TRUE;
}
bool CPersonsView::DeletePerson()
{
    CPersonsDocument* pPersonsDocument = GetDocument();

    long lIndexer = GetRowIndex();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

    if (!pPersonsDocument) {
        AfxMessageBox(ERROR_FETCHING_PERSON);
        return FALSE;
    }
    //Get ID from the selected row
    long lPersonID = (long)m_oListCtrl.GetItemData(lIndexer);

    if (!lPersonID) {
        AfxMessageBox(PERSON_CANNOT_BE_SELECTED);
        return FALSE;
    }
    if (AfxMessageBox(L"���������� �����������", MB_OKCANCEL)==IDCANCEL) {
        return FALSE;
    }
    if (!pPersonsDocument->DeletePerson(lPersonID, lIndexer)) {
        AfxMessageBox(PERSON_CANNOT_BE_DELETED);
        return FALSE;
    }

    return TRUE;
}

bool CPersonsView::UpdatePerson()
{
    CPersonsDocument* pPersonsDocument = GetDocument();

    long lIndexer = GetRowIndex();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

    if (!pPersonsDocument) {
        return FALSE;
    }
    long lCityID = (long)m_oListCtrl.GetItemData(lIndexer);

    CPerson& pPerson =  *pPersonsDocument->GetPersonArray().GetAt(lIndexer);
   
    if (!pPersonsDocument->SelectPerson(lCityID, pPerson)) {
        return FALSE;
    }

    pPersonsDocument->LoadCities();
    pPersonsDocument->LoadPhoneTypes();

    CPersonsDlg oPersonsDialog(pPersonsDocument->GetCitiesArray(),
        &pPersonsDocument->GetPhoneTypesArray(), &pPerson);

    if (oPersonsDialog.DoModal() == IDCANCEL) {
        return FALSE;
    }

    //Copy the data

    if (!pPersonsDocument->UpdatePerson(pPerson.m_oRecPerson.lID, oPersonsDialog.GetPerson())) {
        return FALSE;
    }
    
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

    for (long lIndexer(0); (INT_PTR)lIndexer < pPersonsDocument->GetPersonArray().GetCount(); ++lIndexer)
    {
        CPerson* pPersons = pPersonsDocument->GetPersonArray().GetAt(lIndexer);
        if (pPersons != nullptr) {
            m_oListCtrl.InsertItem(lIndexer, pPersons->GetPerson().szFirstName);
            m_oListCtrl.SetItemText(lIndexer, LAST_NAME_COLUMN, pPersons->GetPerson().szLastName);
            CString TEMP;
            pPersonsDocument->cityIDtoString.Lookup(pPersons->GetPerson().lCityID,TEMP);
            m_oListCtrl.SetItemText(lIndexer, CITY_ID_COLUMN, TEMP);
            m_oListCtrl.SetItemText(lIndexer, ADDRESS_COLUMN, pPersons->GetPerson().szAddress);
            m_oListCtrl.SetItemData(lIndexer, pPersons->GetPerson().lID);
        }
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


