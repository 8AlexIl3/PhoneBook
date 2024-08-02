#include "pch.h"
#include "PhoneTypesData.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesData

// Constructor / Destructor
// ----------------

CPhoneTypesData::CPhoneTypesData()
{
}

CPhoneTypesData::~CPhoneTypesData()
{
}


// Methods
// ----------------

bool CPhoneTypesData::SelectAll(CPhoneTypesArray& oPhoneTypesArray)
{
    CPhoneTypesTable oPhoneTypesTable;

    oPhoneTypesTable.SelectAll(oPhoneTypesArray);

    return !oPhoneTypesArray.IsEmpty();
}

bool CPhoneTypesData::SelectWhereID(const long lID, PHONE_TYPES& recCity)
{
    CPhoneTypesTable oPhoneTypesTable;

    oPhoneTypesTable.SelectWhereID(lID, recCity);

    return recCity.lID;
}

bool CPhoneTypesData::UpdateWhereID(const long lID, PHONE_TYPES& recCity)
{
    CPhoneTypesTable oPhoneTypesTable;

    return oPhoneTypesTable.UpdateWhereID(lID, recCity);
}

bool CPhoneTypesData::InsertCity(PHONE_TYPES& recCity)
{
    CPhoneTypesTable oPhoneTypesTable;

    return  oPhoneTypesTable.InsertRecord(recCity);
}

bool CPhoneTypesData::DeleteWhereID(const long lID)
{
    CPhoneTypesTable oPhoneTypesTable;

    return oPhoneTypesTable.DeleteWhereID(lID);
}
