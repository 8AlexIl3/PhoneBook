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

    if (!LoadPersons())
        return FALSE;

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
#if 0
bool CPersonsDocument::InsertPerson(PERSONS& oPersons)
{
    CPersonsData oPersonsData;

    if (!oPersonsData.InsertPerson(oPersons))
        return FALSE;

    PERSONS* pPersons = new PERSONS(oPersons);
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

bool CPersonsDocument::UpdatePerson(const long lID, CPerson& oPersons)
{
    CPersonsData oPersonsData;

    if (!oPersonsData.UpdateWhereID(lID, oPersons))
        return FALSE;

    UpdateAllViews(NULL);

    return TRUE;
}
#endif

bool CPersonsDocument::SelectPerson(const long lID, CPerson& oPersons)
{
    CPersonsData oPersonsData;

    if (!oPersonsData.SelectWhereID(lID, oPersons))
        return FALSE;

    return TRUE;
}

bool CPersonsDocument::LoadPersons()
{
    CPersonsData oPersonsData;

    ClearArray();
    if (!oPersonsData.SelectAll(m_oPersonsArray))
        return FALSE;

    return TRUE;
}

const CPersonArray& CPersonsDocument::GetPersonArray()
{
    return m_oPersonsArray;
}

void CPersonsDocument::ClearArray()
{
    for (long lIndexer = 0; (INT_PTR)lIndexer < m_oPersonsArray.GetCount(); lIndexer++) {
        delete m_oPersonsArray.GetAt(lIndexer);
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
