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

CITIES& CCitiesDocument::GetCity(long lIndexer)
{
     return *m_oCitiesArray.GetAt(lIndexer);
    
}

const CCitiesArray& CCitiesDocument::GetCityArray()
{
    return m_oCitiesArray;
}

BOOL CCitiesDocument::OnNewDocument()
{
    static int numberDoc=1;
    if (!CDocument::OnNewDocument())
        return FALSE;
    CString strName;
    strName.Format(L"Cities Document %d", numberDoc++);
    SetTitle(strName);

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
    for (int lIndexer = 0; lIndexer < m_oCitiesArray.GetCount(); lIndexer++) {
        delete m_oCitiesArray.GetAt(lIndexer);
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
BOOL CCitiesDocument::DeleteCity(const long lID, const long lrowIndexer)
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
BOOL CCitiesDocument::UpdateCity(CITIES& oCity)
{
    if (!oCitiesData.UpdateWhereID(oCity.lID, oCity))
        return FALSE;

    LoadCities();

    return TRUE;
}
BOOL CCitiesDocument::SelectCity(const long lID, CITIES& oCity)
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
