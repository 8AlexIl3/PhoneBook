#include "pch.h"
#include "CitiesTable.h"
#include "DBconnectionSingleton.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

// Constructor / Destructor
// ----------------

CCitiesTable::CCitiesTable()
{
    m_strTableName.Format(L"CITIES");
}

CCitiesTable::~CCitiesTable()
{
}


//Overrides
// ----------------

bool CCitiesTable::SelectAll(CCitiesArray& oCitiesArray)
{
    CBaseTable oTable(m_strTableName);
    return oTable.SelectAll(oCitiesArray);
}
bool CCitiesTable::SelectWhereID(const long lID, CITIES& recCity)
{
    CBaseTable oTable(m_strTableName);
    return oTable.SelectWhereID(lID, recCity);
}

bool CCitiesTable::UpdateWhereID(const long lID,CITIES& recCity)
{
    CBaseTable oTable(m_strTableName);
    return oTable.UpdateWhereID(lID,recCity);
}

bool CCitiesTable::InsertRecord(CITIES& recCity)
{
    CBaseTable oTable(m_strTableName);
    return oTable.InsertRecord(recCity);
}

bool CCitiesTable::DeleteWhereID(const long lID)
{
    CBaseTable oTable(m_strTableName);
    return oTable.DeleteWhereID(lID);
}
