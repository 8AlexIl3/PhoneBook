#include "pch.h"
#include "PhoneTypesTable.h"
#include "DBconnectionSingleton.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable

// Constructor / Destructor
// ----------------

CPhoneTypesTable::CPhoneTypesTable()
{
    m_strTableName.Format(L"PHONE_TYPES");
}

CPhoneTypesTable::~CPhoneTypesTable()
{
}


//Overrides
// ----------------

bool CPhoneTypesTable::SelectAll(CPhoneTypesArray& oPhonetypesArray)
{
    CBaseTable oTable(m_strTableName);
    return oTable.SelectAll(oPhonetypesArray);
}

bool CPhoneTypesTable::SelectWhereID(const long lID, PHONE_TYPES& recPhoneType) {

    CBaseTable oTable(m_strTableName);
    return oTable.SelectWhereID(lID, recPhoneType);
}

bool CPhoneTypesTable::UpdateWhereID(const long lID, PHONE_TYPES& recPhoneType)
{
    CBaseTable oTable(m_strTableName);
    return oTable.UpdateWhereID(lID, recPhoneType);
}

bool CPhoneTypesTable::InsertRecord(PHONE_TYPES& recPhoneType) {
    CBaseTable oTable(m_strTableName);
    return oTable.InsertRecord(recPhoneType);
}

bool CPhoneTypesTable::DeleteWhereID(const long lID) {
    CBaseTable oTable(m_strTableName);
    return oTable.DeleteWhereID(lID);
}
