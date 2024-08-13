#pragma once
#include <atldbcli.h>
#include <atlstr.h> 


/////////////////////////////////////////////////////////////////////////////
// CDBConnection

class CDBConnection
{

// Constructor / Destructor
// ----------------
public:
    CDBConnection();
    virtual ~CDBConnection();


// Methods
// ----------------
public:
    CDBPropSet GetPropSet();

    CDBPropSet GetUpdatePropSet();

    CDataSource GetDataSource();

    CSession GetSession();

    /// <summary>Determine if query is successful</summary>
    /// <returns>TRUE if succesful/FALSE if not</returns>
    bool IsActionSuccessful(const HRESULT& hResult);

    /// <summary>Update Data in the table</summary>
    /// <returns>TRUE if succesful/FALSE if not</returns>
    bool CheckValidSession();

    bool StartTransaction();

    bool RollbackTransaction();

    bool CommitTransaction();

private:
    /// <returns>Database connection to the server</returns>
    CDBPropSet SetDBProperties();

    /// <returns>Rowset properties</returns>
    CDBPropSet UpdateDBPropSet();
    
    /// <summary>Initilizes Session</summary>
    /// <returns>TRUE if succesful/FALSE if not</returns>
    bool OpenSession();

    /// <summary>Initilizes Connection</summary>
    /// <returns>TRUE if succesful/FALSE if not</returns>
    bool OpenConnection();

// Members
// ----------------
private:
    CDBPropSet m_oUpdatePropSet;
    CDBPropSet m_oDBPropSet;
    CDataSource m_oDataSource;
    CSession m_oSession;
};
#define SERVER_CONNECTION_ERROR L"Не може да се създаде връзка към сървър"
#define SESSION_CREATE_ERROR L"Не може да се създаде сесия"
#define TRANSACTION_STARTED 4096l
#define TRANSACTION_NOT_STARTED 0l
