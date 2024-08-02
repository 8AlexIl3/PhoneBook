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

bool CPersonsData::SelectAll(CPersonsArray& oPersonsArray)
{
    CPersonsTable oPersonsTable;
    CPhoneNumbersTable oPhoneNumbersTable;


    return oPersonsTable.SelectAll(oPersonsArray);
}

bool CPersonsData::SelectWhereID(const long lID, PERSONS& recPerson)
{
    CPersonsTable oPersonsTable;

    return oPersonsTable.SelectWhereID(lID, recPerson);
}

bool CPersonsData::UpdateWhereID(const long lID, PERSONS& recPerson)
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

bool CPersonsData::InsertPerson(PERSONS& recPerson)
{
    CPersonsTable oPersonsTable;

    return  oPersonsTable.InsertRecord(recPerson);
}

bool CPersonsData::DeleteWhereID(const long lID)
{
    CPersonsTable oPersonsTable;

    return oPersonsTable.DeleteWhereID(lID);
}
