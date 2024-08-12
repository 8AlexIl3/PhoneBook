#include "pch.h"
#include "PhoneTypesDocument.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDlg

IMPLEMENT_DYNCREATE(CPhoneTypesDocument, CDocument)

BEGIN_MESSAGE_MAP(CPhoneTypesDocument, CDocument)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CPhoneTypesDocument::CPhoneTypesDocument()
{
}

CPhoneTypesDocument::~CPhoneTypesDocument()
{
}

// MFC Overrides
// ----------------

BOOL CPhoneTypesDocument::OnNewDocument()
{
    static int numberDoc = 1;
    if (!CDocument::OnNewDocument())
        return FALSE;
    CString strName;
    strName.Format(L"PhoneTypes Document %d", numberDoc++);
    SetTitle(strName);

    if (!LoadPhoneTypes())
        return FALSE;

    return TRUE;
}

void CPhoneTypesDocument::Serialize(CArchive& ar)
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



void CPhoneTypesDocument::SetTitle(LPCTSTR lpszTitle)
{
    CDocument::SetTitle(lpszTitle);
}


//Methods
// ----------------

bool CPhoneTypesDocument::InsertPhoneType(PHONE_TYPES& oPhoneTypes)
{
    CPhoneTypesData oPhoneTypesData;

    if (!oPhoneTypesData.InsertPhoneType(oPhoneTypes))
        return FALSE;

    PHONE_TYPES* pPhoneTypes = new PHONE_TYPES(oPhoneTypes);
    if (!pPhoneTypes) {
        return FALSE;
    }

    m_oPhoneTypesArray.Add(pPhoneTypes);

    UpdateAllViews(NULL);

    return TRUE;
}

bool CPhoneTypesDocument::DeletePhoneType(const long lID, const long lrowIndexer)
{
    CPhoneTypesData oPhoneTypesData;

    if (!oPhoneTypesData.DeleteWhereID(lID))
        return FALSE;

    PHONE_TYPES* pPhoneTypes = m_oPhoneTypesArray.GetAt(lrowIndexer);
    if (!pPhoneTypes) {
        return FALSE;
    }
    delete pPhoneTypes;

    m_oPhoneTypesArray.RemoveAt(lrowIndexer);

    UpdateAllViews(NULL);

    return TRUE;
}

bool CPhoneTypesDocument::UpdatePhoneType(const long lID, PHONE_TYPES& oPhoneTypes)
{
    CPhoneTypesData oPhoneTypesData;

    if (!oPhoneTypesData.UpdateWhereID(lID, oPhoneTypes))
        return FALSE;

    UpdateAllViews(NULL);

    return TRUE;
}

bool CPhoneTypesDocument::SelectPhoneType(const long lID, PHONE_TYPES & oPhoneTypes)
{
    CPhoneTypesData oPhoneTypesData;

    if (!oPhoneTypesData.SelectWhereID(lID, oPhoneTypes))
        return FALSE;

    return TRUE;
}

bool CPhoneTypesDocument::LoadPhoneTypes()
{
    CPhoneTypesData oPhoneTypesData;

    ClearArray();
    if (!oPhoneTypesData.SelectAll(m_oPhoneTypesArray))
        return FALSE;

    return TRUE;
}

const CPhoneTypesArray& CPhoneTypesDocument::GetPhoneTypeArray()
{
    return m_oPhoneTypesArray;
}

void CPhoneTypesDocument::ClearArray()
{
    for (INT_PTR lIndexer = 0; lIndexer < m_oPhoneTypesArray.GetCount(); lIndexer++) {
        PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(lIndexer);
        if (!pPhoneType)
            continue;
        delete pPhoneType;
    }
    m_oPhoneTypesArray.RemoveAll();
}


// Implementation
// ----------------

#ifdef _DEBUG
void CPhoneTypesDocument::AssertValid() const
{
    CDocument::AssertValid();
}

void CPhoneTypesDocument::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif
