#include "pch.h"
#include "CitiesDocument.h"
#include "CitiesView.h"
#include "PhoneBook.h"
#include "CitiesDlg.h"
//CitiesView.cpp
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CCitiesView, CListView)

BEGIN_MESSAGE_MAP(CCitiesView, CListView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_RBUTTONDOWN()
    ON_WM_UPDATEUISTATE()
    ON_WM_KEYDOWN()
    ON_COMMAND(IDM_INSERT_CITY, &CCitiesView::OnInsertCity)
    ON_COMMAND(IDM_REFRESH_VIEW, &CCitiesView::OnRefresh)
END_MESSAGE_MAP()

CCitiesView::CCitiesView() noexcept
    : m_oListCtrl(GetListCtrl()),m_pDoc(nullptr)
{
}

CCitiesView::~CCitiesView()
{
}

BOOL CCitiesView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CListView::PreCreateWindow(cs);
}

void CCitiesView::OnInitialUpdate()
{

    CListView::OnInitialUpdate();

    m_oListCtrl.DeleteAllItems();

    m_oListCtrl.ModifyStyle(0, LVS_REPORT| LVS_SINGLESEL);
    m_oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    m_oListCtrl.InsertColumn(ID_COLUMN, _T("ID"), LVCFMT_CENTER, DEFAULT_COLUMN_WIDTH);
    m_oListCtrl.InsertColumn(CITY_COLUMN, _T("Град"), LVCFMT_CENTER, DEFAULT_COLUMN_WIDTH);
    m_oListCtrl.InsertColumn(RESIDENCE_COLUMN, _T("Област"), LVCFMT_CENTER, DEFAULT_COLUMN_WIDTH);
    
    DisplayData();

}
void CCitiesView::OnRefresh() {
    m_oListCtrl.DeleteAllItems();
    DisplayData();
}
void CCitiesView::OnInsertCity()
{
    InsertCity();
}

void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    m_pDoc = GetDocument();
    m_oListCtrl.DeleteAllItems();
    DisplayData();
}

void CCitiesView::DisplayData() {

    for (long lIndexer(0); lIndexer < m_pDoc->GetCityArray().GetCount(); ++lIndexer)
    {
        CITIES* pCity = m_pDoc->GetCityArray().GetAt(lIndexer);
        CString strID;
        strID.Format(_T("%ld"), pCity->lID);
        m_oListCtrl.InsertItem(lIndexer, strID);
        m_oListCtrl.SetItemText(lIndexer, CITY_COLUMN, pCity->szCityName);
        m_oListCtrl.SetItemText(lIndexer, RESIDENCE_COLUMN, pCity->szTownResidence);
    }
}
void CCitiesView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    bool bUpToDate(true);
    switch (nChar) {
    case VK_RETURN:
        bUpToDate=SelectCity();
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
        bUpToDate = false;
        break;
    }
    //If actions in the switch fail update the view to most recent version
    if (!bUpToDate) {
        OnRefresh();
    }
    CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}

long CCitiesView::GetTableRowIndex() {
    POSITION pos = m_oListCtrl.GetFirstSelectedItemPosition();
    if (!pos)
        return INDEX_NOT_FOUND;

    int lIndexer = m_oListCtrl.GetNextSelectedItem(pos);
    if (lIndexer == INDEX_NOT_FOUND)
        return INDEX_NOT_FOUND;

    return lIndexer;
}
BOOL CCitiesView::DeleteCity(){

    long lIndexer = GetTableRowIndex();

    if (lIndexer==INDEX_NOT_FOUND)
        return FALSE;
    
    if (!m_pDoc) {
        AfxMessageBox(L"Не може да бъде извлечен документ");
        return FALSE;
    }
    //Get ID from the selected row
    long lCityID = m_pDoc->GetCity(lIndexer).lID;

    if (!lCityID) {
        AfxMessageBox(L"Грешка: Градът с ID не трябва да съществува");
        return FALSE;
    }
    else if (!m_pDoc->DeleteCity(lCityID, lIndexer)) {
        AfxMessageBox(L"Грешка: Градът не може да бъде изтрит");
        return FALSE;
    }

    return TRUE;
}
BOOL CCitiesView::SelectCity() {
    long lIndexer = GetTableRowIndex();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

    if (!m_pDoc) {
        AfxMessageBox(L"Не може да бъде извлечен документ");
        return FALSE;
    }
    //Get ID from the selected row

    CITIES oSelectedCity;

    long lCityID = m_pDoc->GetCity(lIndexer).lID;

    if (!lCityID) {
        AfxMessageBox(L"Грешка: Невалидно избиране на град");
        return FALSE;
    }
    if (!m_pDoc->SelectCity(lCityID, oSelectedCity)) {
        AfxMessageBox(L"Грешка: Не може да бъде избран град");
        return FALSE;
    }
    CString strCity;

    //Print City
        strCity.Format(L"Населено място: %s,Област: %s, ID: %d, Брояч: %d",
        oSelectedCity.szCityName,
        oSelectedCity.szTownResidence,
        oSelectedCity.lID,
        oSelectedCity.lUpdateCounter);
        AfxMessageBox(strCity);

    return TRUE;
}
BOOL CCitiesView::UpdateCity()
{
    long lIndexer = GetTableRowIndex();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

    if (!m_pDoc) {
        AfxMessageBox(L"Не може да бъде извлечен документ");
        return FALSE;
    }

    CITIES& oCityUpdater = m_pDoc->GetCity(lIndexer);


    //Initialize the dialog edit controls with values from the selected city
    CCitiesDlg oCityDialog(oCityUpdater);

    if (oCityDialog.DoModal() == IDCANCEL) {
        return FALSE;
    }

    //Copy the data
    _tcscpy_s(oCityUpdater.szCityName, oCityDialog.GetCityName());
    _tcscpy_s(oCityUpdater.szTownResidence, oCityDialog.GetTownResidence());

    if (!m_pDoc->UpdateCity(oCityUpdater)) {
        return FALSE;
    }

    return TRUE;
}
BOOL CCitiesView::InsertCity() {

    if (!m_pDoc) {
        AfxMessageBox(L"Unable to fetch data.\n");
        return FALSE;
    }

    CCitiesDlg oCityDialog;

    if (oCityDialog.DoModal() == IDCANCEL) {
        return FALSE;
    }

    CITIES oInsertCity;

    //Copy the data

    _tcscpy_s(oInsertCity.szCityName, oCityDialog.GetCityName());
    _tcscpy_s(oInsertCity.szTownResidence, oCityDialog.GetTownResidence());

    if (!m_pDoc->InsertCity(oInsertCity)) {
        return FALSE;
    }
    
    return TRUE;
}


void CCitiesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CCitiesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
   theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

#ifdef _DEBUG
void CCitiesView::AssertValid() const
{
    CListView::AssertValid();
}

void CCitiesView::Dump(CDumpContext& dc) const
{
    CListView::Dump(dc);
}

CCitiesDocument* CCitiesView::GetDocument() const
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDocument)));
    return (CCitiesDocument*)m_pDocument;
}
#endif //_DEBUG
