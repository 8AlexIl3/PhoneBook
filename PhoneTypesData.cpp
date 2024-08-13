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

bool CPhoneTypesData::SelectAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray)
{
    CPhoneTypesTable oPhoneTypesTable;

    oPhoneTypesTable.SelectAll(oPhoneTypesArray);

    return !oPhoneTypesArray.IsEmpty();
}

bool CPhoneTypesData::SelectPhoneTypeWhereID(const long lID, PHONE_TYPES& recPhoneNumber)
{
    CPhoneTypesTable oPhoneTypesTable;

    oPhoneTypesTable.SelectWhereID(lID, recPhoneNumber);

    return recPhoneNumber.lID;
}

bool CPhoneTypesData::UpdatePhoneTypeWhereID(const long lID, PHONE_TYPES& recPhoneNumber)
{
    CPhoneTypesTable oPhoneTypesTable;

    return oPhoneTypesTable.UpdateWhereID(lID, recPhoneNumber);
}

bool CPhoneTypesData::InsertPhoneType(PHONE_TYPES& recPhoneNumber)
{
    CPhoneTypesTable oPhoneTypesTable;

    return  oPhoneTypesTable.InsertRecord(recPhoneNumber);
}

bool CPhoneTypesData::DeletePhoneTypeWhereID(const long lID)
{
    CPhoneTypesTable oPhoneTypesTable;

    return oPhoneTypesTable.DeleteWhereID(lID);
}
