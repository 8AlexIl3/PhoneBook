#pragma once


/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

#include <atldbcli.h>
#include <atlstr.h> 
#include "Structures.h"
#include "CitiesAccessor.h"
#include "DBconnectionSingleton.h"
#include "CBaseTable.h"


class CCitiesTable : public CBaseTable<CITIES, CCitiesAccessor>
{

// Constructor / Destructor
// ----------------
public:

    CCitiesTable();
    virtual ~CCitiesTable();


// Overrides
// ----------------
public:
    /// <summary>Loads up all cities from the table </summary>
    /// <param name="oCitiesArray">Cities that will be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool SelectAll(CCitiesArray& oCitiesArray) override;

    /// <summary>Get a city structure by its' id </summary>
    /// <param name="lID">ID to be searched for</param>
    /// <param name="recCity">Reference to the city that is searched (if not found
    /// remains empty)</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool SelectWhereID(const long lID, CITIES& recCity) override;

    /// <summary>Update a row from the database with new values from recCity</summary>
    /// <param name="lID">ID to be matched from recCity to ensure it is the correct one</param>
    /// <param name="recCity">Cities will get its update counter incremented</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool UpdateWhereID(const long lID,CITIES& recCity) override;

    /// <summary>Insert a new row into the table</summary>
    /// <param name="recCity">City to be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool InsertRecord(CITIES& recCity) override;

    /// <summary>Delete a city by ID from table</summary>
    /// <param name="lID">Id to delete from table</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool DeleteWhereID(const long lID);


// Members
// ----------------
private:
     CString m_strTableName;
};
