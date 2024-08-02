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
#if 0
bool CPersonsData::UpdateWhereID(const long lID, CPerson& recPerson)
{
    CPersonsTable oPersonsTable;
    CPhoneNumbersTable oPhoneNumbersTable;

    if (m_oConnection.GetSession().StartTransaction() != S_OK) {
        return FALSE;
    }
    if (oPersonsTable.UpdateWhereID(lID, recPerson)) {
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
    CPersonsTable oPersonsTable;

    return oPersonsTable.DeleteWhereID(lID);
}
bool CPersonsData::InsertPerson(CPerson& recPerson)
{
    CPersonsTable oPersonsTable;

    return  oPersonsTable.InsertRecord(recPerson);
}


#endif
