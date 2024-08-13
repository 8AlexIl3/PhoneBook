#pragma once
#include <atldbcli.h>
#include <atlstr.h> 
#include "Structures.h"
#include "PhoneNumbersAccessor.h"
#include "DBconnectionSingleton.h"
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable

class CPhoneNumbersTable : public CBaseTable<PHONE_NUMBERS, CPhoneNumbersAccessor>
{

    // Constructor / Destructor
    // ----------------
public:

    CPhoneNumbersTable();
    CPhoneNumbersTable(CString& strColumnName);
    virtual ~CPhoneNumbersTable();


    // Methods
    // ----------------
public:
    /// <summary>Loads up all Phone numbers from the table </summary>
    /// <param name="oCitiesArray">Cities that will be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool SelectAll(CPhoneNumbersArray& oPhoneNumbersArray);

    /// <summary>Get a phone number structure by its' id </summary>
    /// <param name="lID">ID to be searched for</param>
    /// <param name="recPhoneNumber">Reference to the phone number that is searched (if not found
    /// remains empty)</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumber);

    /// <summary>Update a row from the database with new values from recPhoneNumber</summary>
    /// <param name="lID">ID to be matched from recPhoneNumber to ensure it is the correct one</param>
    /// <param name="recPhoneNumber">Cities will get its update counter incremented</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool UpdateWhereID(const long lID, PHONE_NUMBERS& recPhoneNumber);

    /// <summary>Insert a new row into the table</summary>
    /// <param name="recPhoneNumber">Phone number to be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool InsertRecord(PHONE_NUMBERS& recPhoneNumber);

    /// <summary>Delete a phone number by ID from table</summary>
    /// <param name="lID">Id to delete from table</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool DeleteWhereID(const long lID);

    /// <summary>Get a phone number structure by its' id </summary>
    /// <param name="lID">ID to be searched for</param>
    /// <param name="recPhoneNumber">Reference to the phone number that is searched (if not found
    /// remains empty)</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool SelectMultipleWhereID(const long lID, CPhoneNumbersArray& oPhoneNumbersArray);

};
