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

    /// <summary>Get a city structure by its' id </summary>
    /// <param name="lID">ID to be searched for</param>
    /// <param name="recCity">Reference to the city that is searched (if not found
    /// remains empty)</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool SelectWhereID(const long lID, PHONE_TYPES& recCity);

    /// <summary>Update a row from the database with new values from recCity</summary>
    /// <param name="lID">ID to be matched from recCity to ensure it is the correct one</param>
    /// <param name="recCity">PhoneTypes will get its update counter incremented</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool UpdateWhereID(const long lID, PHONE_TYPES& recCity);

    /// <summary>Insert a new row into the table</summary>
    /// <param name="recCity">City to be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool InsertCity(PHONE_TYPES& recCity);

    /// <summary>Delete a city by ID from table</summary>
    /// <param name="lID">Id to delete from table</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool DeleteWhereID(const long lID);
};

