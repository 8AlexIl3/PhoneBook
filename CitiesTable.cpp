#include "pch.h"
#include "CitiesTable.h"
#include "DBconnectionSingleton.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

// Constructor / Destructor
// ----------------

CCitiesTable::CCitiesTable():CBaseTable(CString(L"CITIES"))
{
}

CCitiesTable::~CCitiesTable()
{
}


//Methods
// ----------------

bool CCitiesTable::SelectAll(CCitiesArray& oCitiesArray)
{
    return CBaseTable::SelectAll(oCitiesArray);
}
bool CCitiesTable::SelectWhereID(const long lID, CITIES& recCity)
{
    return CBaseTable::SelectWhereID(lID, recCity);
}

bool CCitiesTable::UpdateWhereID(const long lID,CITIES& recCity)
{
    return CBaseTable::UpdateWhereID(lID,recCity);
}

bool CCitiesTable::InsertRecord(CITIES& recCity)
{
    return CBaseTable::InsertRecord(recCity);
}

bool CCitiesTable::DeleteWhereID(const long lID)
{
    return CBaseTable::DeleteWhereID(lID);
}
