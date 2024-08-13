#include "pch.h"
#include "PhoneTypesTable.h"
#include "DBconnectionSingleton.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable

// Constructor / Destructor
// ----------------

CPhoneTypesTable::CPhoneTypesTable():CBaseTable(CString(L"PHONE_TYPES"))
{
}

CPhoneTypesTable::~CPhoneTypesTable()
{
}


//Methods
// ----------------

bool CPhoneTypesTable::SelectAll(CPhoneTypesArray& oPhonetypesArray)
{
    return CBaseTable::SelectAll(oPhonetypesArray);
}

bool CPhoneTypesTable::SelectWhereID(const long lID, PHONE_TYPES& recPhoneType)
{
    return CBaseTable::SelectWhereID(lID, recPhoneType);
}

bool CPhoneTypesTable::UpdateWhereID(const long lID, PHONE_TYPES& recPhoneType)
{
    return CBaseTable::UpdateWhereID(lID, recPhoneType);
}

bool CPhoneTypesTable::InsertRecord(PHONE_TYPES& recPhoneType)
{
    return CBaseTable::InsertRecord(recPhoneType);
}

bool CPhoneTypesTable::DeleteWhereID(const long lID)
{
    return CBaseTable::DeleteWhereID(lID);
}
