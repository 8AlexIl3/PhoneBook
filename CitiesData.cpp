#include "pch.h"
#include "CitiesData.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesData

// Constructor / Destructor
// ----------------

CCitiesData::CCitiesData()
{
}

CCitiesData::~CCitiesData()
{
}


// Methods
// ----------------

bool CCitiesData::SelectAll(CCitiesArray& oCitiesArray)
{
    CCitiesTable oCitiesTable;

    oCitiesTable.SelectAll(oCitiesArray);

    return !oCitiesArray.IsEmpty();
}

bool CCitiesData::SelectWhereID(const long lID, CITIES& recCity)
{
    CCitiesTable oCitiesTable;

    oCitiesTable.SelectWhereID(lID, recCity);

    return recCity.lID;
}

bool CCitiesData::UpdateWhereID(const long lID, CITIES& recCity)
{
    CCitiesTable oCitiesTable;

    CITIES oCity=recCity;

    oCitiesTable.UpdateWhereID(lID, recCity);
    //If recCity is updated to something else that we did NOT set
    bool bCompareResult = _tcscmp(recCity.szCityName, oCity.szCityName)
        || _tcscmp(recCity.szTownResidence, oCity.szTownResidence);

    return !bCompareResult;
}

bool CCitiesData::InsertCity(CITIES& recCity)
{
    CCitiesTable oCitiesTable;

    return  oCitiesTable.InsertRecord(recCity);
}

bool CCitiesData::DeleteWhereID(const long lID)
{
    CCitiesTable oCitiesTable;

    return oCitiesTable.DeleteWhereID(lID);
}
