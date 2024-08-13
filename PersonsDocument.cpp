#include "pch.h"
#include "PersonsDocument.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsDocument

// MFC Macros
// ----------------
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
bool CPersonsDocument::InsertPerson(CPersonExtend& oPersons)
{
    CPersonsData oPersonsData;

    if (!oPersonsData.InsertPersonExtended(oPersons))
        return FALSE;

    CPersonExtend* pPersons = new CPersonExtend(oPersons);
    if (!pPersons) 
        return FALSE;

    m_oPersonsArray.Add(pPersons);

    UpdateAllViews(NULL);

    return TRUE;
}

bool CPersonsDocument::UpdatePerson(const long lID, CPersonExtend& oPersons)
{
    CPersonsData oPersonsData;

    if (!oPersonsData.UpdatePersonExtendedWhereID(lID, oPersons))
        return FALSE;

    UpdateAllViews(NULL);

    return TRUE;
}

bool CPersonsDocument::DeletePerson(const long lID, const long lrowIndexer)
{
    CPersonsData oPersonsData;

    CPersonExtend* pPersons = m_oPersonsArray.GetAt(lrowIndexer);
    if (!pPersons)
        return FALSE;
    

    if (!oPersonsData.DeletePersonExtended(*pPersons))
        return FALSE;

    delete pPersons;

    m_oPersonsArray.RemoveAt(lrowIndexer);

    UpdateAllViews(NULL);

    return TRUE;
}


bool CPersonsDocument::LoadPersons()
{
    CPersonsData oPersonsData;

    ClearPersonsArray();
    if (!oPersonsData.SelectAllPersonsExtended(m_oPersonsArray))
        return FALSE;

    return TRUE;
}

CPersonsCredentials& CPersonsDocument::GetCredentials()
{
    return m_oCredentials;
}

bool CPersonsDocument::SelectPerson(const long lID, CPersonExtend& oPersons)
{
    CPersonsData oPersonsData;

    if (!oPersonsData.SelectPersonExtendedWhereID(lID, oPersons))
        return FALSE;

    return TRUE;
}


CPersonArray& CPersonsDocument::GetPersonArray()
{
    return m_oPersonsArray;
}


void CPersonsDocument::ClearPersonsArray()
{
    for (long lIndexer = 0; (INT_PTR)lIndexer < m_oPersonsArray.GetCount(); lIndexer++) {
        CPersonExtend* pPerson = m_oPersonsArray.GetAt(lIndexer);
        if (!pPerson)
            continue;
        delete pPerson;
    }
    m_oPersonsArray.RemoveAll();
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
