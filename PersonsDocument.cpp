#include "pch.h"
#include "PersonsDocument.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsDocument

IMPLEMENT_DYNCREATE(CPersonsDocument, CDocument)

BEGIN_MESSAGE_MAP(CPersonsDocument, CDocument)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CPersonsDocument::CPersonsDocument()
{
}

CPersonsDocument::~CPersonsDocument()
{
    m_oCityIDtoString.RemoveAll();
}

// MFC Overrides
// ----------------

BOOL CPersonsDocument::OnNewDocument()
{
    static int numberDoc = 1;
    if (!CDocument::OnNewDocument())
        return FALSE;
    CString strName;
    strName.Format(L"Persons Document %d", numberDoc++);
    SetTitle(strName);

    return TRUE;
}

void CPersonsDocument::Serialize(CArchive& ar)
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



void CPersonsDocument::SetTitle(LPCTSTR lpszTitle)
{
    CDocument::SetTitle(lpszTitle);
}


//Methods
// ----------------
bool CPersonsDocument::InsertPerson(CPerson& oPersons)
{
    CPersonsData oPersonsData;

    if (!oPersonsData.InsertPerson(oPersons))
        return FALSE;

    CPerson* pPersons = new CPerson(oPersons);
    if (!pPersons) {
        return FALSE;
    }

    m_oPersonsArray.Add(pPersons);

    UpdateAllViews(NULL);

    return TRUE;
}

bool CPersonsDocument::DeletePerson(const long lID, const long lrowIndexer)
{
    CPersonsData oPersonsData;

    if (!oPersonsData.DeleteWhereID(lID))
        return FALSE;

    CPerson* pPersons = m_oPersonsArray.GetAt(lrowIndexer);
    if (!pPersons) {
        return FALSE;
    }
    delete pPersons;

    m_oPersonsArray.RemoveAt(lrowIndexer);

    UpdateAllViews(NULL);

    return TRUE;
}

bool CPersonsDocument::LoadCities()
{
    CCitiesData oCitiesData;
    ClearCitiesArray();

    if (!oCitiesData.SelectAll(m_oCitiesArray))
        return FALSE;

    for (INT_PTR nIndexer(0); nIndexer < m_oCitiesArray.GetCount(); nIndexer++) {

        m_oCityIDtoString.SetAt(m_oCitiesArray.GetAt(nIndexer)->lID,

        m_oCitiesArray.GetAt(nIndexer)->szCityName);
    }
    return TRUE;
}
bool CPersonsDocument::LoadPhoneTypes()
{
    CPhoneTypesData oPhoneTypesData;
    ClearPhoneTypesArray();

    if (!oPhoneTypesData.SelectAll(m_oPhoneTypesArray))
        return FALSE;

    return TRUE;
}
bool CPersonsDocument::LoadPersons()
{
    CPersonsData oPersonsData;

    ClearPersonsArray();
    if (!oPersonsData.SelectAll(m_oPersonsArray))
        return FALSE;

    return TRUE;
}

bool CPersonsDocument::UpdatePerson(const long lID, CPerson& oPersons)
{
    CPersonsData oPersonsData;

    if (!oPersonsData.UpdateWhereID(lID, oPersons))
        return FALSE;
    
    UpdateAllViews(NULL);

    return TRUE;
}

bool CPersonsDocument::SelectPerson(const long lID, CPerson& oPersons)
{
    CPersonsData oPersonsData;

    if (!oPersonsData.SelectWhereID(lID, oPersons))
        return FALSE;

    return TRUE;
}


CPersonArray& CPersonsDocument::GetPersonArray()
{
    return m_oPersonsArray;
}

CCitiesArray& CPersonsDocument::GetCitiesArray()
{
    return m_oCitiesArray;
}

CPhoneTypesArray& CPersonsDocument::GetPhoneTypesArray()
{
    return m_oPhoneTypesArray;
}

CMap<long, long, CString, CString>& CPersonsDocument::GetStringCity()
{
    return m_oCityIDtoString;
}

void CPersonsDocument::ClearPersonsArray()
{
    for (long lIndexer = 0; (INT_PTR)lIndexer < m_oPersonsArray.GetCount(); lIndexer++) {
        delete m_oPersonsArray.GetAt(lIndexer);
    }
    m_oPersonsArray.RemoveAll();
}

void CPersonsDocument::ClearCitiesArray()
{
    for (long lIndexer = 0; (INT_PTR)lIndexer < m_oCitiesArray.GetCount(); lIndexer++) {
        delete m_oCitiesArray.GetAt(lIndexer);
    }
    m_oCitiesArray.RemoveAll();
}
void CPersonsDocument::ClearPhoneTypesArray()
{
    for (long lIndexer = 0; (INT_PTR)lIndexer < m_oPhoneTypesArray.GetCount(); lIndexer++) {
        delete m_oPhoneTypesArray.GetAt(lIndexer);
    }
    m_oPhoneTypesArray.RemoveAll();
}

// Implementation
// ----------------

#ifdef _DEBUG
void CPersonsDocument::AssertValid() const
{
    CDocument::AssertValid();
}

void CPersonsDocument::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif
