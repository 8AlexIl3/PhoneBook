#include "pch.h"
#include "PersonsTable.h"
#include "DBconnectionSingleton.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsTable


// Constructor / Destructor
// ----------------

CPersonsTable::CPersonsTable(): CBaseTable(CString(L"PERSONS"))
{
}

CPersonsTable::~CPersonsTable()
{
}


//Methods
// ----------------

bool CPersonsTable::SelectAll(CPersonsArray& oPersonsArray)
{
    return CBaseTable::SelectAll(oPersonsArray);
}

bool CPersonsTable::SelectWhereID(const long lID, PERSONS& recPerson)
{
    return CBaseTable::SelectWhereID(lID,recPerson);
}

bool CPersonsTable::UpdateWhereID(const long lID, PERSONS& recPerson)
{
    return CBaseTable::UpdateWhereID(lID, recPerson);
}

bool CPersonsTable::InsertRecord(PERSONS& recPerson)
{
    return CBaseTable::InsertRecord(recPerson);
}

bool CPersonsTable::DeleteWhereID(const long lID)
{
    return CBaseTable::DeleteWhereID(lID);
}
