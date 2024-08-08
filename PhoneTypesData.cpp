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

bool CPhoneTypesData::SelectWhereID(const long lID, PHONE_TYPES& recPhoneNumber)
{
    CPhoneTypesTable oPhoneTypesTable;

    oPhoneTypesTable.SelectWhereID(lID, recPhoneNumber);

    return recPhoneNumber.lID;
}

bool CPhoneTypesData::UpdateWhereID(const long lID, PHONE_TYPES& recPhoneNumber)
{
    CPhoneTypesTable oPhoneTypesTable;

    return oPhoneTypesTable.UpdateWhereID(lID, recPhoneNumber);
}

bool CPhoneTypesData::InsertPhoneType(PHONE_TYPES& recPhoneNumber)
{
    CPhoneTypesTable oPhoneTypesTable;

    return  oPhoneTypesTable.InsertRecord(recPhoneNumber);
}

bool CPhoneTypesData::DeleteWhereID(const long lID)
{
    CPhoneTypesTable oPhoneTypesTable;

    return oPhoneTypesTable.DeleteWhereID(lID);
}
