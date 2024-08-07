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

    oPersonsTable.SelectWhereID(lID, oPersons);

    CPerson oPerson(oPersons);

    oPhoneNumbersTable.SelectMultipleWhereID
    (oPerson.m_oRecPerson.lID, oPerson.m_oPhoneNumbersArray);

    recPerson = oPerson;

    return true;
}

bool CPersonsData::UpdateWhereID(const long lID, CPerson& recPerson)
{
    CPersonsTable oPersonsTable;
    CPhoneNumbersTable oPhoneNumbersTable;

    if (m_oConnection.GetSession().StartTransaction() != S_OK) {
        return FALSE;
    }
    
    if (!oPersonsTable.UpdateWhereID(lID, recPerson.m_oRecPerson)) {
        m_oConnection.GetSession().Abort();
        return FALSE;
    }
    
    for (INT_PTR nIndexer(0); nIndexer < recPerson.m_oPhoneNumbersArray.GetCount(); nIndexer++) {

        if (recPerson.m_oPhoneNumbersArray.GetAt(nIndexer)->lID == 0) {

            recPerson.m_oPhoneNumbersArray.GetAt(nIndexer)->lPersonID = recPerson.m_oRecPerson.lID;

            if (!oPhoneNumbersTable.InsertRecord(*recPerson.m_oPhoneNumbersArray.GetAt(nIndexer))) {
                m_oConnection.GetSession().Abort();
                return FALSE;
            }
        }

        if (!oPhoneNumbersTable.UpdateWhereID(recPerson.m_oPhoneNumbersArray.GetAt(nIndexer)->lID,
            *recPerson.m_oPhoneNumbersArray.GetAt(nIndexer))) {
            m_oConnection.GetSession().Abort();
            return FALSE;
        }

        if (!_tcscmp(recPerson.m_oPhoneNumbersArray.GetAt(nIndexer)->szPhone,EMPTY_NUMBER)) {
            if (!oPhoneNumbersTable.DeleteWhereID(recPerson.m_oPhoneNumbersArray.GetAt(nIndexer)->lID)) {

                m_oConnection.GetSession().Abort();
                return FALSE;
            }
        }
        
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
bool CPersonsData::InsertPerson(CPerson& recPerson)
{
    if (m_oConnection.GetSession().StartTransaction() != S_OK) {
        return FALSE;
    }
    CPersonsTable oPersonsTable;
    CPhoneNumbersTable oPhoneNumbersTable;

    if (!oPersonsTable.InsertRecord(recPerson.m_oRecPerson)) {
        m_oConnection.GetSession().Abort();
        return FALSE;
    }

    for (INT_PTR nIndexer(0); nIndexer < recPerson.m_oPhoneNumbersArray.GetCount(); nIndexer++) {
        recPerson.m_oPhoneNumbersArray.GetAt(nIndexer)->lPersonID = recPerson.m_oRecPerson.lID;
        //phoneNumber is about to be inserted
        if (recPerson.m_oPhoneNumbersArray.GetAt(nIndexer)->lID == 0) {

            if (!oPhoneNumbersTable.InsertRecord(*recPerson.m_oPhoneNumbersArray.GetAt(nIndexer))) {
                m_oConnection.GetSession().Abort();
                return FALSE;
            }
        }
    }
    if (m_oConnection.GetSession().Commit() != S_OK) {
        return FALSE;
    }

    return TRUE;
}


