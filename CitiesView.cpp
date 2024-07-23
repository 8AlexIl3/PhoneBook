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
    ON_WM_LBUTTONDOWN()
    ON_COMMAND(IDM_INSERT_CITY, &CCitiesView::OnInsertCity)
END_MESSAGE_MAP()

CCitiesView::CCitiesView() noexcept
{
    // TODO: add construction code here
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
   
    CListCtrl& oListCtrl = GetListCtrl();
    oListCtrl.DeleteAllItems();
    CCitiesDocument* pDoc = GetDocument();

    oListCtrl.ModifyStyle(0, LVS_REPORT| LVS_SINGLESEL);
    oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    oListCtrl.InsertColumn(ID_COLUMN, _T("ID"), LVCFMT_CENTER, 100);
    oListCtrl.InsertColumn(CITY_COLUMN, _T("Град"), LVCFMT_CENTER, 100);
    oListCtrl.InsertColumn(RESIDENCE_COLUMN, _T("Област"), LVCFMT_CENTER, 100);
    
    ASSERT(pDoc != nullptr);
    
    for (int indexer(0); indexer < pDoc->m_oCitiesArray.GetSize(); ++indexer)
    {
        CITIES* pCity = pDoc->m_oCitiesArray.GetAt(indexer);
        CString strID;
        strID.Format(_T("%ld"), pCity->lID);
        oListCtrl.InsertItem(indexer, strID);
        oListCtrl.SetItemText(indexer, CITY_COLUMN, pCity->szCityName);
        oListCtrl.SetItemText(indexer, RESIDENCE_COLUMN, pCity->szTownResidence);
    }

}
void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    CListCtrl& oListCtrl = GetListCtrl();
    oListCtrl.DeleteAllItems();
    CCitiesDocument* pDoc = GetDocument();
    ASSERT(pDoc != nullptr);

    for (int indexer(0); indexer < pDoc->m_oCitiesArray.GetSize(); ++indexer)
    {
        CITIES* pCity = pDoc->m_oCitiesArray.GetAt(indexer);
        CString strID;
        strID.Format(_T("%ld"), pCity->lID);
        oListCtrl.InsertItem(indexer, strID);
        oListCtrl.SetItemText(indexer, CITY_COLUMN, pCity->szCityName);
        oListCtrl.SetItemText(indexer, RESIDENCE_COLUMN, pCity->szTownResidence);
    }
}
//Display additionial info
void CCitiesView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CCitiesDocument* pDoc = GetDocument();
    CListCtrl& oListCtrl = GetListCtrl();
    long nItem = oListCtrl.HitTest(point);
    if (nItem != -1)
    {
        CString Tempbox;
        CITIES tempCity;
        Tempbox= oListCtrl.GetItemText(nItem, 0);
        long nItem = _wtoi(Tempbox);
        if(!nItem)//ID is equal to 0
        Tempbox.Format(L"Refresh document to select this city");
        else if(pDoc->SelectCityByID(nItem, tempCity)){
            Tempbox.Format(L"Selected a SINGLECITY ID: %d city: %s\n\
                Residence :%s Update counter:%d",
                tempCity.lID,tempCity.szCityName,
                tempCity.szTownResidence,tempCity.lUpdateCounter);
        }
        AfxMessageBox(Tempbox);
    }
    CListView::OnLButtonDown(nFlags, point);
}
void CCitiesView::OnRButtonDown(UINT nFlags, CPoint point){
    CCitiesDocument* pDoc = GetDocument();
    CListCtrl& oListCtrl = GetListCtrl();
    long lIndexer = oListCtrl.HitTest(point);
    if (lIndexer != -1)
    {
        long lItem;
        CString Tempbox;
        CITIES tempCity;
        Tempbox = oListCtrl.GetItemText(lIndexer, 0);
        lItem = _wtoi(Tempbox);
        if (!lItem)//ID is equal to 0
            Tempbox.Format(L"Refresh document to select this city");

        else if (pDoc->DeleteCityByID(lItem, lIndexer)) {
            Tempbox.Format(L"Selected a SINGLECITY ID: %d city: %s\n\
                Residence :%s Update counter:%d",
                tempCity.lID, tempCity.szCityName,
                tempCity.szTownResidence, tempCity.lUpdateCounter);
        }
    }
    CListView::OnRButtonDown(nFlags, point);
}
//Double click -> update a city info
void CCitiesView::OnLButtonDblClk(UINT nFlags, CPoint point)
{   
    CCitiesDocument* pDoc = GetDocument();
    CListCtrl& oListCtrl = GetListCtrl();
    long nItem = oListCtrl.HitTest(point);

    //If an item is pressed
    if (nItem != -1)
    {
        CString Tempbox;
        CITIES* tempCity= pDoc->m_oCitiesArray.GetAt(nItem);
        Tempbox = oListCtrl.GetItemText(nItem, 0);
        long nItem = _wtoi(Tempbox);
        CCitiesDlg CityInserter(NULL);
        if (CityInserter.DoModal() == IDOK) {
            _tcscpy_s(tempCity->szCityName, CityInserter.m_szCityName);
            _tcscpy_s(tempCity->szTownResidence, CityInserter.m_szTownResidence);
            pDoc->UpdateCityByID(nItem, *tempCity);

        }
    }
    CListView::OnLButtonDblClk(nFlags, point);
}
void CCitiesView::OnInsertCity() {
    CCitiesDocument* pDoc = GetDocument();

    if (!pDoc) {
        AfxMessageBox(L"Unable to fetch data.\n");
        return;
    }
    CCitiesDlg CityInserter(NULL);
    if (CityInserter.DoModal() == IDOK) {
        
        CITIES oCity;
        _tcscpy_s(oCity.szCityName, CityInserter.m_szCityName);
        _tcscpy_s(oCity.szTownResidence, CityInserter.m_szTownResidence);
        pDoc->InsertCity(oCity);
        
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
