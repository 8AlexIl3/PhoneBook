#pragma once
#pragma once

#include <atldbcli.h>
#include <atlstr.h>
#include "Structures.h"
#include "CitiesAccessor.h"
#include "DBconnectionSingleton.h"

/// <summary>Клас за работа с таблица CITIES</summary>
template <class TAccessor, class TRecord>
class CTable : private CCommand<CAccessor<TAccessor>>
{
public:
    /// Constructors and destructors ------------------------------------------------------
    CTable();
    virtual ~CTable();

protected:
    /// Methods ----------------------------------------------------------------------------

    /// <summary>Loads up all cities from the table </summary>
    /// <param name="oArray">Cities that will be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    virtual BOOL SelectAll(CAutoMemoryArray<CITIES>& oArray)=0;

    /// <summary>Get a city structure by its' id </summary>
    /// <param name="lID">ID to be searched for</param>
    /// <param name="oRec">Reference to the city that is searched (if not found
    /// remains empty)</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    virtual BOOL SelectWhereID(const long lID, TRecord& oRec)=0;

    /// <summary>Update a row from the database with new values from oRec</summary>
    /// <param name="lID">ID to be matched from oRec to ensure it is the correct one</param>
    /// <param name="oRec">Cities will get its update counter incremented</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    virtual BOOL UpdateWhereID(const long lID, TRecord& oRec)=0;

    /// <summary>Insert a new row into the table</summary>
    /// <param name="oRec">City to be added</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    virtual BOOL InsertRecord(TRecord& oRec)=0;

    /// <summary>Delete a city by ID from table</summary>
    /// <param name="lID">Id to delete from table</param>
    /// <returns>TRUE if successful/FALSE if NOT</returns>
    virtual BOOL DeleteWhereID(const long lID)=0;

private:
    /// <param name="lID">ID to search for </param>
    /// <returns>TRUE if successful/FALSE if not</returns>
    virtual BOOL GetRecord(const long lID)=0;

    /// <param name="oArray">array to add cities to</param>
    /// <returns>TRUE if successful/FALSE if not</returns>
    virtual BOOL AddRecord(CAutoMemoryArray<TRecord>& oArray)=0;

    /// Members ----------------------------------------------------------------------------
private:
    CDBConnection& m_oConnection = CDBConnectionSingleton::GetInstance();
};


