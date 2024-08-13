#include "pch.h"
#include "PhoneNumbersTable.h"
#include "DBconnectionSingleton.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable

// Constructor / Destructor
// ----------------

CPhoneNumbersTable::CPhoneNumbersTable():CBaseTable(CString(L"PHONE_NUMBERS"))
{
}

CPhoneNumbersTable::CPhoneNumbersTable(CString& strColumnName) :
    CBaseTable(CString(L"PHONE_NUMBERS"),strColumnName)
{
}

CPhoneNumbersTable::~CPhoneNumbersTable()
{
}


//Methods
// ----------------

bool CPhoneNumbersTable::SelectAll(CPhoneNumbersArray& oPhoneNumbersArray)
{
    return CBaseTable::SelectAll(oPhoneNumbersArray);
}

bool CPhoneNumbersTable::SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumber)
{
    return CBaseTable::SelectWhereID(lID,recPhoneNumber);
}

bool CPhoneNumbersTable::SelectMultipleWhereID(const long lID, CPhoneNumbersArray& oPhoneNumbersArray)
{
    return CBaseTable::SelectMultipleWhereID(lID, oPhoneNumbersArray);
}

bool CPhoneNumbersTable::UpdateWhereID(const long lID, PHONE_NUMBERS& recPhoneNumber)
{
    return CBaseTable::UpdateWhereID(lID,recPhoneNumber);
}

bool CPhoneNumbersTable::InsertRecord(PHONE_NUMBERS& recPhoneNumber)
{    
    return CBaseTable::InsertRecord(recPhoneNumber);
}

bool CPhoneNumbersTable::DeleteWhereID(const long lID)
{
    return CBaseTable::DeleteWhereID(lID);
   
}
