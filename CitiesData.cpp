#include "pch.h"
#include "CitiesData.h"
BOOL CCitiesData::SelectAll(CCitiesArray& oCitiesArray){
    CCitiesTable oCityTable;

    oCityTable.SelectAll(oCitiesArray);

    return !oCitiesArray.IsEmpty();
}

BOOL CCitiesData::SelectWhereID(const long lID, CITIES& recCity) {
    CCitiesTable oCityTable;

    oCityTable.SelectWhereID(lID, recCity);

    return recCity.lID;
}

BOOL CCitiesData::UpdateWhereID(const long lID, CITIES& recCity){
    CCitiesTable oCityTable;

    CITIES oInitalCity=recCity;

    oCityTable.UpdateWhereID(lID, recCity);
    //If recCity is updated to something else that we did NOT set
    BOOL bCmpResult = _tcscmp(recCity.szCityName, oInitalCity.szCityName)
        || _tcscmp(recCity.szTownResidence, oInitalCity.szTownResidence);

    return !bCmpResult;
}

BOOL CCitiesData::InsertCity(CITIES& recCity) {
    CCitiesTable oCityTable;
    return  oCityTable.InsertRecord(recCity);
}

BOOL CCitiesData::DeleteWhereID(const long lID) {
    CCitiesTable oCityTable;
    return oCityTable.DeleteWhereID(lID);
}
