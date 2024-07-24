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
    ON_COMMAND(IDM_INSERT_CITY, &CCitiesView::InsertCity)
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

void CCitiesView::DeleteCity(){
    POSITION pos = m_oListCtrl.GetFirstSelectedItemPosition();
    if (pos != NULL)
    {
        CCitiesDocument* pDoc = GetDocument();
        int lIndexer = m_oListCtrl.GetNextSelectedItem(pos);
        if (lIndexer != INDEX_NOT_FOUND)
        {
            
            //Get ID from the selected row
            long lItemID = _wtoi(m_oListCtrl.GetItemText(lIndexer, ID_COLUMN));

            if (!lItemID)//ID is equal to 0
                AfxMessageBox(L"Грешка: Градът не може да бъде избран");
            else if (!pDoc->DeleteCityByID(lItemID, lIndexer)) {
                AfxMessageBox(L"Грешка: Градът не може да бъде изтрит");
            }
        }
    }
}
//Display additionial info
void CCitiesView::CitySelector() {
    POSITION pos = m_oListCtrl.GetFirstSelectedItemPosition();
    if (pos != NULL)
    {
        int lIndexer = m_oListCtrl.GetNextSelectedItem(pos);
        CCitiesDocument* pDoc = GetDocument();
        if (lIndexer != INDEX_NOT_FOUND)
        {
            CITIES oCitySelector;

            //Get ID from the selected row
            long lItemID = _wtoi(m_oListCtrl.GetItemText(lIndexer, ID_COLUMN));

            CString strCity;
            if (!lItemID) {
                AfxMessageBox(L"Грешка: Невалидно избиране на град");
            }
            else if (pDoc->SelectCityByID(lItemID, oCitySelector)) {
                strCity.Format(L"Населено място: %s,Област: %s, ID: %d, Брояч: %d",
                    oCitySelector.szCityName,
                    oCitySelector.szTownResidence,
                    oCitySelector.lID,
                    oCitySelector.lUpdateCounter);
                AfxMessageBox(strCity);
            }
        }
    }
}
void CCitiesView::UpdateCity()
{
    POSITION pos = m_oListCtrl.GetFirstSelectedItemPosition();
    if (pos != NULL)
    {
        CCitiesDocument* pDoc = GetDocument();
        int lIndexer = m_oListCtrl.GetNextSelectedItem(pos);
        if (lIndexer != INDEX_NOT_FOUND)
        {
            //Convert the selected rows' ID to integer
            CITIES* pCityUpdater = pDoc->m_oCitiesArray.GetAt(lIndexer);

            //Get ID from the selected row
            long lItemID = _wtoi(m_oListCtrl.GetItemText(lIndexer, ID_COLUMN));
            
            //Initialize the dialog edit controls with values from the selected city
            CCitiesDlg oCityUpdateDialog(nullptr, pCityUpdater->szCityName, pCityUpdater->szTownResidence);

            //Set the updated values upon pressing confirm 
            if (oCityUpdateDialog.DoModal() == IDOK) {
                _tcscpy_s(pCityUpdater->szCityName, oCityUpdateDialog.m_szCityName);
                _tcscpy_s(pCityUpdater->szTownResidence, oCityUpdateDialog.m_szTownResidence);
                pDoc->UpdateCityByID(lItemID, *pCityUpdater);
            }
        }
    }
}
void CCitiesView::InsertCity() {
    CCitiesDocument* pDoc = GetDocument();

    if (!pDoc) {
        AfxMessageBox(L"Unable to fetch data.\n");
        return;
    }
    CCitiesDlg oCityInsertDialog;
    //Set the updated values upon pressing confirm 
    if (oCityInsertDialog.DoModal() == IDOK) {
        CITIES oInsertCity;
        _tcscpy_s(oInsertCity.szCityName, oCityInsertDialog.m_szCityName);
        _tcscpy_s(oInsertCity.szTownResidence, oCityInsertDialog.m_szTownResidence);
        bool bRresult=pDoc->InsertCity(oInsertCity);
    }
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
