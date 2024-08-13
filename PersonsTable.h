#pragma once
#include <atldbcli.h>
#include <atlstr.h> 
#include "Structures.h"
#include "PersonsAccessor.h"
#include "DBconnectionSingleton.h"
#include "BaseTable.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

class CPersonsTable : public CBaseTable<PERSONS, CPersonsAccessor>
{

    // Constructor / Destructor
    // ----------------
public:

    CPersonsTable();
    virtual ~CPersonsTable();


    // Methods
    // ----------------
public:
    /// <summary>Loads up all persons from the table </summary>
    /// <param name="oPersonsArray">Persons that will be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool SelectAll(CPersonsArray& oPersonsArray);

    /// <summary>Get a person structure by its' id </summary>
    /// <param name="lID">ID to be searched for</param>
    /// <param name="recPerson">Reference to the person that is searched (if not found
    /// remains empty)</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool SelectWhereID(const long lID, PERSONS& recPerson);

    /// <summary>Update a row from the database with new values from recPerson</summary>
    /// <param name="lID">ID to be matched from recPerson to ensure it is the correct one</param>
    /// <param name="recPerson">Persons will get its update counter incremented</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool UpdateWhereID(const long lID, PERSONS& recPerson);

    /// <summary>Insert a new row into the table</summary>
    /// <param name="recPerson">Person to be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool InsertRecord(PERSONS& recPerson);

    /// <summary>Delete a person by ID from table</summary>
    /// <param name="lID">Id to delete from table</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool DeleteWhereID(const long lID);

};



