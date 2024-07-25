#pragma once

#include <atldbcli.h>
#include <atlstr.h> 
#include "Structures.h"
#include "CitiesAccessor.h"
#include "DBconnection.h"
/// <summary>Клас за работа с таблица CITIES</summary>
class CCitiesTable : private CCommand<CAccessor<CCitiesAccessor>>
{
public:
    /// Constructors and destructors ------------------------------------------------------
    CCitiesTable() {
        SecureZeroMemory(this, sizeof(this));
    }
    virtual ~CCitiesTable() {};

public:
    /// Methods ----------------------------------------------------------------------------
   
    /// <summary>Loads up all cities from the table </summary>
    /// <param name="oCitiesArray">Cities that will be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    BOOL SelectAll(CAutoMemoryArray<CITIES>& oCitiesArray);

    /// <summary>Get a city structure by its' id </summary>
    /// <param name="lID">ID to be searched for</param>
    /// <param name="recCity">Reference to the city that is searched (if not found
    /// remains empty)</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    BOOL SelectWhereID(const long lID, CITIES& recCity);

    /// <summary>Update a row from the database with new values from recCity</summary>
    /// <param name="lID">ID to be matched from recCity to ensure it is the correct one</param>
    /// <param name="recCity">Cities will get its update counter incremented</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    BOOL UpdateWhereID(const long lID,CITIES& recCity);

    /// <summary>Insert a new row into the table</summary>
    /// <param name="recCity">City to be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    BOOL InsertCity(CITIES& recCity);

    /// <summary>Delete a city by ID from table</summary>
    /// <param name="lID">Id to delete from table</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    BOOL DeleteWhereID(const long lID);


private:
    /// <param name="lID">ID to search for </param>
    /// <returns>TRUE if succesful/FALSE if not</returns>
    BOOL GetRecord(const long lID);

    /// <param name="oCitiesArray">array to add cities to</param>
    /// <returns>TRUE if succesful/FALSE if not</returns>
    BOOL AddRecord(CAutoMemoryArray<CITIES>& oCitiesArray);
    /// Members ----------------------------------------------------------------------------
private:
    CDBConnection m_oConnection; 
};

