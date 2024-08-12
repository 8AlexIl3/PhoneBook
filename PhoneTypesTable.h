#pragma once


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable

#include "Structures.h"
#include "PhoneTypesAccessor.h"
#include "DBconnectionSingleton.h"
#include "BaseTable.h"


class CPhoneTypesTable :  public CBaseTable<PHONE_TYPES,CPhoneTypesAccessor>
{

    // Constructor / Destructor
    // ----------------
public:

    CPhoneTypesTable();
    virtual ~CPhoneTypesTable();


    // Overrides
    // ----------------
public:
    /// <summary>Loads up all phoneNumbers from the table </summary>
    /// <param name="ophoneNumbersArray">phoneNumbers that will be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool SelectAll(CPhoneTypesArray& oPhoneTypesArray);

    /// <summary>Get a phoneNumber structure by its' id </summary>
    /// <param name="lID">ID to be searched for</param>
    /// <param name="recphoneNumber">Reference to the phoneNumber that is searched (if not found
    /// remains empty)</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool SelectWhereID(const long lID, PHONE_TYPES& recPhoneType);

    /// <summary>Update a row from the database with new values from recphoneNumber</summary>
    /// <param name="lID">ID to be matched from recphoneNumber to ensure it is the correct one</param>
    /// <param name="recphoneNumber">phoneNumbers will get its update counter incremented</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool UpdateWhereID(const long lID, PHONE_TYPES& recPhoneType);

    /// <summary>Insert a new row into the table</summary>
    /// <param name="recphoneNumber">phoneNumber to be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool InsertRecord(PHONE_TYPES& recPhoneType);

    /// <summary>Delete a phoneNumber by ID from table</summary>
    /// <param name="lID">Id to delete from table</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool DeleteWhereID(const long lID);


    // Members
    // ----------------
private:
    CString m_strTableName;
};
