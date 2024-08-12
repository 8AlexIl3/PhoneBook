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

bool CPersonsData::SelectAllPersonsExtended(CPersonArray& oPersonArray)
{
    CPersonsTable oPersonsTable;
    CPhoneNumbersTable oPhoneNumbersTable;

    CPersonsArray oPersonsArray;

    CPersonExtend* pPerson;

    if (!oPersonsTable.SelectAll(oPersonsArray))
        return FALSE;
    

   
    for (INT_PTR nIndexer(0); nIndexer < oPersonsArray.GetCount(); nIndexer++) {

        pPerson = new CPersonExtend (*oPersonsArray.GetAt(nIndexer));
        if (!pPerson) 
            continue;
        oPhoneNumbersTable.SelectMultipleWhereID
        (pPerson->m_oRecPerson.lID, pPerson->m_oPhoneNumbersArray);

        oPersonArray.Add(pPerson);
    }

    return TRUE;
}

bool CPersonsData::SelectPersonExtendedWhereID(const long lID, CPersonExtend& recPerson)
{
    CPersonsTable oPersonsTable;
    CPhoneNumbersTable oPhoneNumbersTable;
    PERSONS oPersons;

    if (!oPersonsTable.SelectWhereID(lID, recPerson.m_oRecPerson)) 
        return FALSE;

    if (!oPhoneNumbersTable.SelectMultipleWhereID
    (recPerson.m_oRecPerson.lID, recPerson.m_oPhoneNumbersArray))
        return FALSE;

    return TRUE;
}

bool CPersonsData::UpdatePersonExtendedWhereID(const long lID, CPersonExtend& recPerson)
{
    CPersonsTable oPersonsTable;

    if (!m_oConnection.StartTransaction()) 
        return FALSE;

    if (!UpdatePersonExtendedData(recPerson)) {
        m_oConnection.RollbackTransaction();
        return FALSE;
    }
    if (!oPersonsTable.UpdateWhereID(lID, recPerson.m_oRecPerson)) {
        m_oConnection.RollbackTransaction();
        return FALSE;
    }
    m_oConnection.CommitTransaction();
   
    return TRUE;
}


bool CPersonsData::DeletePersonExtended(CPersonExtend& recPerson)
{
    if (!m_oConnection.StartTransaction())
        return FALSE;
    
    CPersonsTable oPersonsTable;
    CPhoneNumbersTable oPhoneNumbersTable;
    
    for (INT_PTR nIndexer(0); nIndexer < recPerson.m_oPhoneNumbersArray.GetCount(); nIndexer++) {

        PHONE_NUMBERS* pPhoneNumber= recPerson.m_oPhoneNumbersArray.GetAt(nIndexer);
        if (!pPhoneNumber) {
            m_oConnection.RollbackTransaction();
            return FALSE;
        }

        long lPhoneNumberID = pPhoneNumber->lID;
         if (!oPhoneNumbersTable.DeleteWhereID(lPhoneNumberID)) {
             m_oConnection.RollbackTransaction();
             return FALSE;
         }
    }

    if (!oPersonsTable.DeleteWhereID(recPerson.m_oRecPerson.lID)) {
        m_oConnection.RollbackTransaction();
        return FALSE;
    }

    m_oConnection.CommitTransaction();

    return TRUE;
}
bool CPersonsData::UpdatePersonExtendedData(CPersonExtend& recPerson)
{
    CPhoneNumbersTable oPhoneNumbersTable;

    CPhoneNumbersArray oPhoneNumbersDeleter;

    for (INT_PTR nIndexer(0); nIndexer < recPerson.m_oPhoneNumbersArray.GetCount(); nIndexer++) {

        PHONE_NUMBERS* pPhoneNumbers = recPerson.m_oPhoneNumbersArray.GetAt(nIndexer);
        if (!pPhoneNumbers)
            continue;
        if (pPhoneNumbers->lID == 0) {

            pPhoneNumbers->lPersonID = recPerson.m_oRecPerson.lID;

            if (!oPhoneNumbersTable.InsertRecord(*pPhoneNumbers))
                return FALSE;

        }

        else if (!oPhoneNumbersTable.UpdateWhereID(pPhoneNumbers->lID, *pPhoneNumbers))
            return FALSE;

        if (!_tcscmp(pPhoneNumbers->szPhone, EMPTY_NUMBER))
            if (!oPhoneNumbersTable.DeleteWhereID(pPhoneNumbers->lID))
                return FALSE;

    }
    for (int nIndexer(0); nIndexer < recPerson.m_oPhoneNumbersArray.GetCount(); nIndexer++) {
        PHONE_NUMBERS* pPhoneNumber = recPerson.m_oPhoneNumbersArray.GetAt(nIndexer);
        if (!pPhoneNumber)
            continue;

        if (!_tcscmp(pPhoneNumber->szPhone, EMPTY_NUMBER)) {
            recPerson.m_oPhoneNumbersArray.RemoveAt(nIndexer--);
            delete pPhoneNumber;
            pPhoneNumber = nullptr;
        }
    }

    return TRUE;

}
bool CPersonsData::InsertPersonExtended(CPersonExtend& recPerson)
{
    if (!m_oConnection.StartTransaction())
        return FALSE;
    
    CPersonsTable oPersonsTable;

    if (!oPersonsTable.InsertRecord(recPerson.m_oRecPerson)) {
        m_oConnection.RollbackTransaction();
        return FALSE;
    }

    if (!UpdatePersonExtendedData(recPerson)) {
        m_oConnection.RollbackTransaction();
        return FALSE;
    }
    
    m_oConnection.CommitTransaction();

    return TRUE;
}


