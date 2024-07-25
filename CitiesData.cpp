#include "pch.h"
#include "CitiesData.h"
BOOL CCitiesData::SelectAll(CAutoMemoryArray<CITIES>& oCitiesArray){
    return  oCityTable.SelectAll(oCitiesArray);
}

BOOL CCitiesData::SelectWhereID(const long lID, CITIES& recCity) {
    return oCityTable.SelectWhereID(lID, recCity);
}

BOOL CCitiesData::UpdateWhereID(const long lID, CITIES& recCity){
    return  oCityTable.UpdateWhereID(lID, recCity);
}

BOOL CCitiesData::InsertCity(CITIES& recCity) {
    return  oCityTable.InsertCity(recCity);
}

BOOL CCitiesData::DeleteWhereID(const long lID) {
    return  oCityTable.DeleteWhereID(lID);
}