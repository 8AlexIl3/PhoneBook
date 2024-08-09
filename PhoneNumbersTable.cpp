#include "pch.h"
#include "PhoneNumbersTable.h"
#include "DBconnectionSingleton.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable

// Constructor / Destructor
// ----------------

CPhoneNumbersTable::CPhoneNumbersTable()
{
    m_strTable.Format(L"PHONE_NUMBERS");
}

CPhoneNumbersTable::~CPhoneNumbersTable()
{
}


//Overrides
// ----------------

bool CPhoneNumbersTable::SelectAll(CPhoneNumbersArray& oPhoneNumbersArray)
{
    CBaseTable oTable(m_strTable);
    return oTable.SelectAll(oPhoneNumbersArray);
}

bool CPhoneNumbersTable::SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumber)
{
    CBaseTable oTable(m_strTable);
    return oTable.SelectWhereID(lID,recPhoneNumber);
}

bool CPhoneNumbersTable::SelectMultipleWhereID(const long lID, CPhoneNumbersArray& oPhoneNumbersArray)
{
    CString strColumnName;
    strColumnName.Format(L"PERSON_ID");
    CBaseTable oTable(m_strTable,strColumnName);
    return oTable.SelectMultipleWhereID(lID, oPhoneNumbersArray);
}

bool CPhoneNumbersTable::UpdateWhereID(const long lID, PHONE_NUMBERS& recPhoneNumber)
{
    CBaseTable oTable(m_strTable);
    return oTable.UpdateWhereID(lID,recPhoneNumber);
}

bool CPhoneNumbersTable::InsertRecord(PHONE_NUMBERS& recPhoneNumber)
{    
    CBaseTable oTable(m_strTable);
    return oTable.InsertRecord(recPhoneNumber);
}

bool CPhoneNumbersTable::DeleteWhereID(const long lID) {

    CBaseTable oTable(m_strTable);
    return oTable.DeleteWhereID(lID);
   
}
