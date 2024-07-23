#include "pch.h"
#include "CitiesData.h"
BOOL CCitiesData::SelectAll(CAutoMemoryArray<CITIES>& oCitiesArray){
    return CCitiesTable::SelectAll(oCitiesArray);
}

BOOL CCitiesData::SelectWhereID(const long lID, CITIES& recCity) {
    return CCitiesTable::SelectWhereID(lID, recCity);
}


BOOL CCitiesData::UpdateWhereID(const long lID, CITIES& recCity){
    return CCitiesTable::UpdateWhereID(lID, recCity);
}


BOOL CCitiesData::InsertCity(CITIES& recCity) {
    return CCitiesTable::InsertCity(recCity);
}

BOOL CCitiesData::DeleteWhereID(const long lID) {
    return CCitiesTable::DeleteWhereID(lID);
}