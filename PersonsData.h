#pragma once


/////////////////////////////////////////////////////////////////////////////
// CPersonsData
#include "Person.h"
#include "PersonsTable.h"

class CPersonsData
{

// Constructor / Destructor
// ----------------
public:
    CPersonsData();
    virtual ~CPersonsData();


// Methods
// ----------------
public:
    /// <summary>Loads up all cities from the table </summary>
    /// <param name="oCitiesArray">Cities that will be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool SelectAll(CPersonsArray& oPersonsArray);

    /// <summary>Get a person structure by its' id </summary>
    /// <param name="lID">ID to be searched for</param>
    /// <param name="recperson">Reference to the person that is searched (if not found
    /// remains empty)</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool SelectWhereID(const long lID, PERSONS& recPerson);

    /// <summary>Update a row from the database with new values from recperson</summary>
    /// <param name="lID">ID to be matched from recperson to ensure it is the correct one</param>
    /// <param name="recperson">Cities will get its update counter incremented</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool UpdateWhereID(const long lID, PERSONS& recPerson);

    /// <summary>Insert a new row into the table</summary>
    /// <param name="recperson">person to be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool InsertPerson(PERSONS& recPerson);

    /// <summary>Delete a person by ID from table</summary>
    /// <param name="lID">Id to delete from table</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    bool DeleteWhereID(const long lID);


// Members
// ----------------
private:
    CDBConnection& m_oConnection;

};

