#include "pch.h"
#include "PersonsData.h"
#include "PhoneNumbersTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData

// Constructor / Destructor
// ----------------

CPersonsData::CPersonsData():
    m_oConnection(CDBConnectionSingleton::GetInstance())
{
}

CPersonsData::~CPersonsData()
{
}


// Methods
// ----------------

bool CPersonsData::SelectAll(CPersonArray& oPersonArray)
{
    CPersonsTable oPersonsTable;
    CPhoneNumbersTable oPhoneNumbersTable;

    CPersonsArray oPersonsArray;

    CPerson* pPerson;
    oPersonsTable.SelectAll(oPersonsArray);

    for (INT_PTR nIndexer(0); nIndexer < oPersonsArray.GetCount(); nIndexer++) {

        pPerson = new CPerson(*oPersonsArray.GetAt(nIndexer));
        if (!pPerson) {
            continue;
        }
        oPhoneNumbersTable.SelectMultipleWhereID
        (pPerson->m_oRecPerson.lID, pPerson->m_oPhoneNumbersArray);

        oPersonArray.Add(pPerson);
    }

    return true;
}

bool CPersonsData::SelectWhereID(const long lID, CPerson& recPerson)
{
    CPersonsTable oPersonsTable;
    CPhoneNumbersTable oPhoneNumbersTable;
    PERSONS oPersons;

    oPersonsTable.SelectWhereID(lID, recPerson.m_oRecPerson);

    oPhoneNumbersTable.SelectMultipleWhereID
    (recPerson.m_oRecPerson.lID, recPerson.m_oPhoneNumbersArray);

    return true;
}

bool CPersonsData::UpdateWhereID(const long lID, CPerson& recPerson)
{
    CPersonsTable oPersonsTable;

    if (m_oConnection.GetSession().StartTransaction() != S_OK) {
        return FALSE;
    }
    
    if (!UpdatePersonData(recPerson)) {
        m_oConnection.GetSession().Abort();
        return FALSE;
    }
    if (!oPersonsTable.UpdateWhereID(lID, recPerson.m_oRecPerson)) {
        m_oConnection.GetSession().Abort();
        return FALSE;
    }
    if (m_oConnection.GetSession().Commit() != S_OK) {
        return FALSE;
    }

    return TRUE;
}


bool CPersonsData::DeleteWhereID(const long lID)
{
    if (m_oConnection.GetSession().StartTransaction() != S_OK) {
        return FALSE;
    }
    CPersonsTable oPersonsTable;
    CPhoneNumbersTable oPhoneNumbersTable;
    CPhoneNumbersArray oPhoneNubmersArray;
    PERSONS oPersons;

    if (!oPersonsTable.SelectWhereID(lID, oPersons)) {
        m_oConnection.GetSession().Abort();
        return FALSE;
    }

    if (!oPhoneNumbersTable.SelectMultipleWhereID(oPersons.lID, oPhoneNubmersArray)) {
        m_oConnection.GetSession().Abort();
        return FALSE;
    }

    for (INT_PTR nIndexer(0); nIndexer < oPhoneNubmersArray.GetCount(); nIndexer++) {

        long lID = oPhoneNubmersArray.GetAt(nIndexer)->lID;

         if (!oPhoneNumbersTable.DeleteWhereID(lID)) {
             m_oConnection.GetSession().Abort();
             return FALSE;
         }
    }

    if (!oPersonsTable.DeleteWhereID(lID)) {
        m_oConnection.GetSession().Abort();
        return FALSE;
    }

    if (m_oConnection.GetSession().Commit() != S_OK) {
        return FALSE;
    }
    return TRUE;
}
bool CPersonsData::UpdatePersonData(CPerson& recPerson)
{
    CPhoneNumbersTable oPhoneNumbersTable;

    for (INT_PTR nIndexer(0); nIndexer < recPerson.m_oPhoneNumbersArray.GetCount(); nIndexer++) {

        PHONE_NUMBERS oPhoneNumbers= *recPerson.m_oPhoneNumbersArray.GetAt(nIndexer);
        if (oPhoneNumbers.lID == 0) {

            oPhoneNumbers.lPersonID = recPerson.m_oRecPerson.lID;

            if (!oPhoneNumbersTable.InsertRecord(oPhoneNumbers)) {
                return FALSE;
            }
        }

        else if (!oPhoneNumbersTable.UpdateWhereID(oPhoneNumbers.lID,
            oPhoneNumbers)) {
            return FALSE;
        }

        if (!_tcscmp(oPhoneNumbers.szPhone, EMPTY_NUMBER)) {
            if (!oPhoneNumbersTable.DeleteWhereID(oPhoneNumbers.lID)) {

                return FALSE;
            }
        }

    }
    return TRUE;
}
bool CPersonsData::InsertPerson(CPerson& recPerson)
{
    if (m_oConnection.GetSession().StartTransaction() != S_OK) {
        return FALSE;
    }
    CPersonsTable oPersonsTable;

    if (!oPersonsTable.InsertRecord(recPerson.m_oRecPerson)) {
        m_oConnection.GetSession().Abort();
        return FALSE;
    }

    if (!UpdatePersonData(recPerson)) {
        m_oConnection.GetSession().Abort();
        return FALSE;
    }
    
    if (m_oConnection.GetSession().Commit() != S_OK) {
        return FALSE;
    }

    return TRUE;
}


