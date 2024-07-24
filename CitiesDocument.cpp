#include "pch.h"
#include "CitiesDocument.h"
IMPLEMENT_DYNCREATE(CCitiesDocument, CDocument)

BEGIN_MESSAGE_MAP(CCitiesDocument, CDocument)
END_MESSAGE_MAP()

CCitiesDocument::CCitiesDocument() noexcept
{
}

CCitiesDocument::~CCitiesDocument()
{
}

CITIES CCitiesDocument::GetCity(long lIndexer)
{
    CITIES oCity=*m_oCitiesArray.GetAt(lIndexer);
    return oCity;
}

BOOL CCitiesDocument::OnNewDocument()
{
    
    if (!CDocument::OnNewDocument())
        return FALSE;
        SetTitle(L"CitiesDocument");

   if (!LoadCities())
       return FALSE;
   
    return TRUE;
}


void CCitiesDocument::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // TODO: add storing code here
    }
    else
    {
        // TODO: add loading code here
    }
}

void CCitiesDocument::SetTitle(LPCTSTR lpszTitle)
{
    CDocument::SetTitle(lpszTitle);
}

BOOL CCitiesDocument::LoadCities()
{
    ClearArray();
    if (!oCitiesData.SelectAll(m_oCitiesArray))
        return FALSE;

    UpdateAllViews(NULL);

    return TRUE;
}
void CCitiesDocument::ClearArray()
{
    for (int indexer = 0; indexer < m_oCitiesArray.GetSize(); indexer++) {
        delete m_oCitiesArray.GetAt(indexer);
    }
    m_oCitiesArray.RemoveAll();
}
BOOL CCitiesDocument::InsertCity(CITIES& oCity)
{

    if (!oCitiesData.InsertCity(oCity))
        return FALSE;

    CITIES* pCity = new CITIES(oCity);
    if (!pCity) {
        return FALSE;
    }

    m_oCitiesArray.Add(pCity);

    LoadCities();

    return TRUE;
}
BOOL CCitiesDocument::DeleteCityByID(const long lID, const long lrowIndexer)
{
    if (!oCitiesData.DeleteWhereID(lID))
        return FALSE;

    CITIES* pCityElement = m_oCitiesArray.GetAt(lrowIndexer);
    if (!pCityElement) {
        return FALSE;
    }
    delete pCityElement;

    m_oCitiesArray.RemoveAt(lrowIndexer);

    LoadCities();

    return TRUE;
}
BOOL CCitiesDocument::UpdateCityByID(const long lID,CITIES& oCity)
{
    if (!oCitiesData.UpdateWhereID(lID, oCity))
        return FALSE;

    LoadCities();

    return TRUE;
}
BOOL CCitiesDocument::SelectCityByID(const long lID, CITIES& oCity)
{
    if (!oCitiesData.SelectWhereID(lID,oCity))
        return FALSE;

    return TRUE;
}
#ifdef _DEBUG
void CCitiesDocument::AssertValid() const
{
    CDocument::AssertValid();
}

void CCitiesDocument::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif
