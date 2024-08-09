#include "pch.h"
#include "CitiesDocument.h"
#include "CitiesView.h"
#include "PhoneBook.h"
#include "CitiesDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesView

IMPLEMENT_DYNCREATE(CCitiesView, CListView)

BEGIN_MESSAGE_MAP(CCitiesView, CListView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_RBUTTONDOWN()
    ON_WM_UPDATEUISTATE()
    ON_WM_KEYDOWN()
    ON_COMMAND(IDM_INSERT_RECORD, &CCitiesView::OnInsertCity)
    ON_COMMAND(IDM_REFRESH_VIEW, &CCitiesView::OnRefresh)
    ON_COMMAND(IDM_EDIT_RECORD, &CCitiesView::OnUpdateCity)
    ON_COMMAND(IDM_DELETE_RECORD, &CCitiesView::OnDeleteCity)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CCitiesView::CCitiesView() noexcept
    : m_oListCtrl(GetListCtrl())
{
}

CCitiesView::~CCitiesView()
{
}


// MFC Overrides
// ----------------

BOOL CCitiesView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CListView::PreCreateWindow(cs);
}

void CCitiesView::OnInitialUpdate()
{
    CListView::OnInitialUpdate();

    m_oListCtrl.ModifyStyle(0, LVS_REPORT| LVS_SINGLESEL);
    m_oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    m_oListCtrl.InsertColumn(ID_COLUMN, _T("ID"), LVCFMT_CENTER, DEFAULT_COLUMN_WIDTH);
    m_oListCtrl.InsertColumn(CITY_COLUMN, _T("Ãðàä"), LVCFMT_CENTER, DEFAULT_COLUMN_WIDTH);
    m_oListCtrl.InsertColumn(RESIDENCE_COLUMN, _T("Îáëàñò"), LVCFMT_CENTER, DEFAULT_COLUMN_WIDTH);
    
    DisplayData();

}


// MFC message handlers
// ----------------

void CCitiesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CCitiesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    OnRefresh();
}

void CCitiesView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    bool bUpToDate(true);
    switch (nChar) {
    case VK_RETURN:
        bUpToDate = SelectCity();
        break;
    case VK_DELETE:
        bUpToDate = DeleteCity();
        break;
    case VK_INSERT:
        bUpToDate = InsertCity();
        break;
    case VK_BACK:
        bUpToDate = UpdateCity();
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

void CCitiesView::OnInsertCity()
{
    InsertCity();
}

void CCitiesView::OnUpdateCity()
{
    UpdateCity();
}
void CCitiesView::OnDeleteCity()
{
    DeleteCity();
}

void CCitiesView::OnRefresh() {
    CCitiesDocument* pCitiesDocument = GetDocument();
    pCitiesDocument->LoadCities();
    DisplayData();
}


// Methods
// ----------------

CCitiesDocument* CCitiesView::GetDocument() const
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDocument)));
    return (CCitiesDocument*)m_pDocument;
}

bool CCitiesView::InsertCity()
{
    CCitiesDocument* pCitiesDocument = GetDocument();

    if (!pCitiesDocument) {
        AfxMessageBox(ÅRROR_FETCHING_CITY);
        return FALSE;
    }

    CCitiesDlg oCitiesDialog;

    if (oCitiesDialog.DoModal() == IDCANCEL) 
        return FALSE;

    CITIES& oCities=*oCitiesDialog.GetCity();

    //Copy the data

    if (!pCitiesDocument->InsertCity(oCities))
        return FALSE;

    return TRUE;
}

bool CCitiesView::SelectCity()
{
    CCitiesDocument* pCitiesDocument = GetDocument();

    long lIndexer = GetRowIndex();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

    if (!pCitiesDocument) {
        AfxMessageBox(ÅRROR_FETCHING_CITY);
        return FALSE;
    }
    //Get ID from the selected row

    CITIES oCities;

    long lCityID = (long)m_oListCtrl.GetItemData(lIndexer);

    if (!lCityID) {
        AfxMessageBox(CITY_CANNOT_BE_SELECTED);
        return FALSE;
    }
    if (!pCitiesDocument->SelectCity(lCityID, oCities)) {
        AfxMessageBox(CITY_CANNOT_BE_SELECTED);
        return FALSE;
    }
    CString strCity;

    //Print City
    strCity.Format(L"Íàñåëåíî ìÿñòî: %s,Îáëàñò: %s, ID: %d, Áðîÿ÷: %d",
        oCities.szCityName,
        oCities.szTownResidence,
        oCities.lID,
        oCities.lUpdateCounter);
    AfxMessageBox(strCity);

    return TRUE;
}

bool CCitiesView::DeleteCity()
{
    CCitiesDocument* pCitiesDocument = GetDocument();

    long lIndexer = GetRowIndex();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

    if (!pCitiesDocument) {
        AfxMessageBox(ÅRROR_FETCHING_CITY);
        return FALSE;
    }
    //Get ID from the selected row
    long lCityID = (long)m_oListCtrl.GetItemData(lIndexer);

    if (!lCityID) {
        AfxMessageBox(CITY_CANNOT_BE_SELECTED);
        return FALSE;
    }
    if (!pCitiesDocument->DeleteCity(lCityID, lIndexer)) {
        AfxMessageBox(CITY_CANNOT_BE_DELETED);
        return FALSE;
    }

    return TRUE;
}

bool CCitiesView::UpdateCity()
{
    CCitiesDocument* pCitiesDocument = GetDocument();

    long lIndexer = GetRowIndex();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

    if (!pCitiesDocument) {
        AfxMessageBox(ÅRROR_FETCHING_CITY);
        return FALSE;
    }
    long lCityID = (long)m_oListCtrl.GetItemData(lIndexer);

    //Dummy reference ->It is later used as logical link to update cities
    CITIES& oCities = *pCitiesDocument->GetCityArray().GetAt(lIndexer);

    //If city is still in view but no longer in table
    if (!pCitiesDocument->SelectCity(lCityID, oCities)) {
        AfxMessageBox(CITY_NOT_IN_TABLE);
        return FALSE;
    }

    //Initialize the dialog edit controls with values from the selected city
    CCitiesDlg oCitiesDialog(oCities);

    if (oCitiesDialog.DoModal() == IDCANCEL) 
        return FALSE;

    oCities = *oCitiesDialog.GetCity();

    if (!pCitiesDocument->UpdateCity(lCityID,oCities))
        return FALSE;

    return TRUE;
}

void CCitiesView::DisplayData()
{
    CCitiesDocument* pCitiesDocument = GetDocument();

    if (!pCitiesDocument) {
        AfxMessageBox(ÅRROR_FETCHING_CITY);
        return;
    }

    m_oListCtrl.DeleteAllItems();

    for (long lIndexer(0);(INT_PTR)lIndexer < pCitiesDocument->GetCityArray().GetCount(); ++lIndexer)
    {
        CITIES* pCities = pCitiesDocument->GetCityArray().GetAt(lIndexer);
        if (!pCities)
            continue;
        CString strID;
        strID.Format(_T("%ld"), pCities->lID);
        m_oListCtrl.InsertItem(lIndexer, strID);
        m_oListCtrl.SetItemText(lIndexer, CITY_COLUMN, pCities->szCityName);
        m_oListCtrl.SetItemText(lIndexer, RESIDENCE_COLUMN, pCities->szTownResidence);
        m_oListCtrl.SetItemData(lIndexer, pCities->lID);
    }
}

long CCitiesView::GetRowIndex()
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

void CCitiesView::AssertValid() const
{
    CListView::AssertValid();
}

void CCitiesView::Dump(CDumpContext& dc) const
{
    CListView::Dump(dc);
}


