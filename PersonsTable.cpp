#include "pch.h"
#include "PersonsTable.h"
#include "DBconnectionSingleton.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

// Constructor / Destructor
// ----------------

CPersonsTable::CPersonsTable() 
{
    m_strTableName.Format(L"PERSONS");
}

CPersonsTable::~CPersonsTable()
{
}


//Overrides
// ----------------

bool CPersonsTable::SelectAll(CPersonsArray& oPersonsArray)
{
    CBaseTable oTable(m_strTableName);
    return oTable.SelectAll(oPersonsArray);
}

bool CPersonsTable::SelectWhereID(const long lID, PERSONS& recPerson)
{
    CBaseTable oTable(m_strTableName);
    return oTable.SelectWhereID(lID,recPerson);
}

bool CPersonsTable::UpdateWhereID(const long lID, PERSONS& recPerson)
{
    CBaseTable oTable(m_strTableName);
    return oTable.UpdateWhereID(lID, recPerson);
}

bool CPersonsTable::InsertRecord(PERSONS& recPerson)
{
    CBaseTable oTable(m_strTableName);
    return oTable.InsertRecord(recPerson);
}

bool CPersonsTable::DeleteWhereID(const long lID)
{
    CBaseTable oTable(m_strTableName);
    return oTable.DeleteWhereID(lID);
}
