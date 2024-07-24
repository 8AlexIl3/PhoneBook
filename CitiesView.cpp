#include "pch.h"
#include "CitiesDocument.h"
#include "CitiesView.h"
#include "PhoneBook.h"
#include "CCitiesDlg.h"
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
END_MESSAGE_MAP()

CCitiesView::CCitiesView() noexcept
    : m_oListCtrl(GetListCtrl())
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

void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    m_oListCtrl.DeleteAllItems();
    DisplayData();
}
void CCitiesView::DisplayData() {

    CCitiesDocument* pDoc = GetDocument();


    for (int indexer(0); indexer < pDoc->m_oCitiesArray.GetSize(); ++indexer)
    {
        CITIES* pCity = pDoc->m_oCitiesArray.GetAt(indexer);
        CString strID;
        strID.Format(_T("%ld"), pCity->lID);
        m_oListCtrl.InsertItem(indexer, strID);
        m_oListCtrl.SetItemText(indexer, CITY_COLUMN, pCity->szCityName);
        m_oListCtrl.SetItemText(indexer, RESIDENCE_COLUMN, pCity->szTownResidence);
    }
}
void CCitiesView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar) {
    case VK_RETURN:
        CitySelector();
        break;
    case VK_DELETE:
        DeleteCity();
        break;
    case VK_INSERT:
        InsertCity();
        break;
    case VK_BACK:
        UpdateCity();
        break;
    default:
        break;
    }
    CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}

long CCitiesView::GetCurselView() {
    POSITION pos = m_oListCtrl.GetFirstSelectedItemPosition();
    if (!pos)
        return INDEX_NOT_FOUND;

    int lIndexer = m_oListCtrl.GetNextSelectedItem(pos);
    if (lIndexer == INDEX_NOT_FOUND)
        return INDEX_NOT_FOUND;

    return lIndexer;
}
BOOL CCitiesView::DeleteCity(){

    long lIndexer = GetCurselView();

    if (lIndexer==INDEX_NOT_FOUND)
        return FALSE;
    
    CCitiesDocument* pDoc = GetDocument();

    if (!pDoc) {
        AfxMessageBox(L"Не може да бъде извлечен документ");
        return FALSE;
    }
    //Get ID from the selected row
    CITIES oCity = pDoc->GetCity(lIndexer);

    if (!oCity.lID) {//ID is equal to 0
        AfxMessageBox(L"Грешка: Градът с ID не трябва да съществува");
        return FALSE;
    }
    else if (!pDoc->DeleteCityByID(oCity.lID, lIndexer)) {
        AfxMessageBox(L"Грешка: Градът не може да бъде изтрит");
        return FALSE;
    }

    return TRUE;
}
//Display additionial info
BOOL CCitiesView::CitySelector() {
    long lIndexer = GetCurselView();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

    CCitiesDocument* pDoc = GetDocument();

    if (!pDoc) {
        AfxMessageBox(L"Не може да бъде извлечен документ");
        return FALSE;
    }
    CITIES oCitySelector;

    //Get ID from the selected row
    CITIES oCity = pDoc->GetCity(lIndexer);

    if (!oCity.lID) {
        AfxMessageBox(L"Грешка: Невалидно избиране на град");
        return FALSE;
    }
    if (!pDoc->SelectCityByID(oCity.lID, oCitySelector)) {
        AfxMessageBox(L"Грешка: Не може да бъде избран град");
        return FALSE;
    }
    CString strCity;

    //Print City
        strCity.Format(L"Населено място: %s,Област: %s, ID: %d, Брояч: %d",
        oCitySelector.szCityName,
        oCitySelector.szTownResidence,
        oCitySelector.lID,
        oCitySelector.lUpdateCounter);
        AfxMessageBox(strCity);

    return TRUE;
}
BOOL CCitiesView::UpdateCity()
{
    long lIndexer = GetCurselView();

    if (lIndexer == INDEX_NOT_FOUND)
        return FALSE;

    CCitiesDocument* pDoc = GetDocument();

    if (!pDoc) {
        AfxMessageBox(L"Не може да бъде извлечен документ");
        return FALSE;
    }

    CITIES* pCityUpdater = &pDoc->GetCity(lIndexer);

    //Initialize the dialog edit controls with values from the selected city
    CCitiesDlg oCityUpdateDialog(nullptr, pCityUpdater->szCityName, pCityUpdater->szTownResidence);

    if (oCityUpdateDialog.DoModal() == IDCANCEL) {
        return FALSE;
    }

    //Copy the data
    _tcscpy_s(pCityUpdater->szCityName, oCityUpdateDialog.m_szCityName);
    _tcscpy_s(pCityUpdater->szTownResidence, oCityUpdateDialog.m_szTownResidence);
    if (!pDoc->UpdateCityByID(pCityUpdater->lID, *pCityUpdater)) {
        return FALSE;
    }

    return TRUE;
}
BOOL CCitiesView::InsertCity() {
    CCitiesDocument* pDoc = GetDocument();

    if (!pDoc) {
        AfxMessageBox(L"Unable to fetch data.\n");
        return FALSE;
    }

    CCitiesDlg oCityInsertDialog;

    if (oCityInsertDialog.DoModal() == IDCANCEL) {
        return FALSE;
    }

    CITIES oInsertCity;
    //Copy the data
    _tcscpy_s(oInsertCity.szCityName, oCityInsertDialog.m_szCityName);
    _tcscpy_s(oInsertCity.szTownResidence, oCityInsertDialog.m_szTownResidence);

    if (!pDoc->InsertCity(oInsertCity))
        return FALSE;

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
