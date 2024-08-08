#pragma once


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesData

#include "PhoneTypesTable.h"
class CPhoneTypesData
{

    // Constructor / Destructor
    // ----------------
public:
    CPhoneTypesData();
    virtual ~CPhoneTypesData();


    // Methods
    // ----------------
public:
    /// <summary>Loads up all PhoneTypes from the table </summary>
    /// <param name="oPhoneTypesArray">PhoneTypes that will be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool SelectAll(CPhoneTypesArray& oPhoneTypesArray);

    /// <summary>Get a phoneNumber structure by its' id </summary>
    /// <param name="lID">ID to be searched for</param>
    /// <param name="recPhoneNumber">Reference to the phoneNumber that is searched (if not found
    /// remains empty)</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool SelectWhereID(const long lID, PHONE_TYPES& recPhoneNumber);

    /// <summary>Update a row from the database with new values from recPhoneNumber</summary>
    /// <param name="lID">ID to be matched from recPhoneNumber to ensure it is the correct one</param>
    /// <param name="recPhoneNumber">PhoneTypes will get its update counter incremented</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool UpdateWhereID(const long lID, PHONE_TYPES& recPhoneNumber);

    /// <summary>Insert a new row into the table</summary>
    /// <param name="recPhoneNumber">phoneNumber to be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool InsertPhoneType(PHONE_TYPES& recPhoneNumber);

    /// <summary>Delete a phoneNumber by ID from table</summary>
    /// <param name="lID">Id to delete from table</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool DeleteWhereID(const long lID);
};

