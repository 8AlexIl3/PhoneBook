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

    CPersonExtend* pPerson;

    if (!oPersonsTable.SelectAll(oPersonsArray)) {
        return FALSE;
    }

    for (INT_PTR nIndexer(0); nIndexer < oPersonsArray.GetCount(); nIndexer++) {

        pPerson = new CPersonExtend (*oPersonsArray.GetAt(nIndexer));
        if (!pPerson) {
            continue;
        }
        oPhoneNumbersTable.SelectMultipleWhereID
        (pPerson->m_oRecPerson.lID, pPerson->m_oPhoneNumbersArray);

        oPersonArray.Add(pPerson);
    }

    return TRUE;
}

bool CPersonsData::SelectWhereID(const long lID, CPersonExtend& recPerson)
{
    CPersonsTable oPersonsTable;
    CPhoneNumbersTable oPhoneNumbersTable;
    PERSONS oPersons;

    if (!oPersonsTable.SelectWhereID(lID, recPerson.m_oRecPerson)) {
        return FALSE;

    }

    if (!oPhoneNumbersTable.SelectMultipleWhereID
    (recPerson.m_oRecPerson.lID, recPerson.m_oPhoneNumbersArray))
        return FALSE;

    return TRUE;
}

bool CPersonsData::UpdateWhereID(const long lID, CPersonExtend& recPerson)
{
    CPersonsTable oPersonsTable;

    if (m_oConnection.GetSession().StartTransaction() != S_OK) {
        return FALSE;
    }
    
    if (!UpdatePersonExtendedData(recPerson)) {
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


bool CPersonsData::DeletePerson(CPersonExtend& recPerson)
{
    if (m_oConnection.GetSession().StartTransaction() != S_OK) {
        return FALSE;
    }
    CPersonsTable oPersonsTable;
    CPhoneNumbersTable oPhoneNumbersTable;
    CPhoneNumbersArray oPhoneNubmersArray;
    PERSONS oPersons;


    for (INT_PTR nIndexer(0); nIndexer < oPhoneNubmersArray.GetCount(); nIndexer++) {

        PHONE_NUMBERS* pPhoneNumber=oPhoneNubmersArray.GetAt(nIndexer);

        if (!pPhoneNumber) {
            m_oConnection.GetSession().Abort();
            return FALSE;
        }
        long lPhoneNumberID = pPhoneNumber->lID;

         if (!oPhoneNumbersTable.DeleteWhereID(lPhoneNumberID)) {
             m_oConnection.GetSession().Abort();
             return FALSE;
         }
    }

    if (!oPersonsTable.DeleteWhereID(recPerson.m_oRecPerson.lID)) {
        m_oConnection.GetSession().Abort();
        return FALSE;
    }

    if (m_oConnection.GetSession().Commit() != S_OK) 
        return FALSE;

    return TRUE;
}
bool CPersonsData::UpdatePersonExtendedData(CPersonExtend& recPerson)
{
    CPhoneNumbersTable oPhoneNumbersTable;

    for (INT_PTR nIndexer(0); nIndexer < recPerson.m_oPhoneNumbersArray.GetCount(); nIndexer++) {

        PHONE_NUMBERS* pPhoneNumbers= recPerson.m_oPhoneNumbersArray.GetAt(nIndexer);
        if (pPhoneNumbers->lID == 0) {

            pPhoneNumbers->lPersonID = recPerson.m_oRecPerson.lID;

            if (!oPhoneNumbersTable.InsertRecord(*pPhoneNumbers)) {
                return FALSE;
            }
        }

        else if (!oPhoneNumbersTable.UpdateWhereID(pPhoneNumbers->lID,
            *pPhoneNumbers)) {
            return FALSE;
        }

        if (!_tcscmp(pPhoneNumbers->szPhone, EMPTY_NUMBER)) {
            if (!oPhoneNumbersTable.DeleteWhereID(pPhoneNumbers->lID)) {

                return FALSE;
            }
        }

    }
    return TRUE;
}
bool CPersonsData::InsertPerson(CPersonExtend& recPerson)
{
    if (m_oConnection.GetSession().StartTransaction() != S_OK)
        return FALSE;
    
    CPersonsTable oPersonsTable;

    if (!oPersonsTable.InsertRecord(recPerson.m_oRecPerson)) {
        m_oConnection.GetSession().Abort();
        return FALSE;
    }

    if (!UpdatePersonExtendedData(recPerson)) {
        m_oConnection.GetSession().Abort();
        return FALSE;
    }
    
    if (m_oConnection.GetSession().Commit() != S_OK)
        return FALSE;
    
    return TRUE;
}


