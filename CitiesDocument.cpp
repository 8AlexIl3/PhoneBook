#include "pch.h"
#include "CitiesDocument.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesDlg

IMPLEMENT_DYNCREATE(CCitiesDocument, CDocument)

BEGIN_MESSAGE_MAP(CCitiesDocument, CDocument)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CCitiesDocument::CCitiesDocument()
{
}

CCitiesDocument::~CCitiesDocument()
{
}

// MFC Overrides
// ----------------

BOOL CCitiesDocument::OnNewDocument()
{
    static int numberDoc = 1;
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


//Methods
// ----------------

bool CCitiesDocument::InsertCity(CITIES& oCities)
{
    CCitiesData oCitiesData;

    if (!oCitiesData.InsertCity(oCities))
        return FALSE;

    CITIES* pCities = new CITIES(oCities);
    if (!pCities) {
        return FALSE;
    }

    m_oCitiesArray.Add(pCities);

    UpdateAllViews(NULL);

    return TRUE;
}

bool CCitiesDocument::DeleteCity(const long lID, const long lrowIndexer)
{
    CCitiesData oCitiesData;

    if (!oCitiesData.DeleteWhereID(lID))
        return FALSE;

    CITIES* pCities = m_oCitiesArray.GetAt(lrowIndexer);
    if (!pCities) {
        return FALSE;
    }
    delete pCities;

    m_oCitiesArray.RemoveAt(lrowIndexer);

    UpdateAllViews(NULL);

    return TRUE;
}

bool CCitiesDocument::UpdateCity(const long lID,CITIES& oCities)
{
    CCitiesData oCitiesData;

    if (!oCitiesData.UpdateWhereID(lID, oCities))
        return FALSE;

    UpdateAllViews(NULL);

    return TRUE;
}

bool CCitiesDocument::SelectCity(const long lID, CITIES& oCities)
{
    CCitiesData oCitiesData;

    if (!oCitiesData.SelectWhereID(lID,oCities))
        return FALSE;

    return TRUE;
}

bool CCitiesDocument::LoadCities()
{
    CCitiesData oCitiesData;

    ClearArray();
    if (!oCitiesData.SelectAll(m_oCitiesArray))
        return FALSE;

    return TRUE;
}

const CCitiesArray& CCitiesDocument::GetCityArray()
{
    return m_oCitiesArray;
}

void CCitiesDocument::ClearArray()
{
    for (long lIndexer = 0; (INT_PTR)lIndexer < m_oCitiesArray.GetCount(); lIndexer++) {
        delete m_oCitiesArray.GetAt(lIndexer);
    }
    m_oCitiesArray.RemoveAll();
}


// Implementation
// ----------------

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
