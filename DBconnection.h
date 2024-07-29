#pragma once
#include <atldbcli.h>
#include <atlstr.h> 
class CDBConnection {

public:
    // Constructor / Destructor
    // ------------------------------------------------------------------------------------------------------
    CDBConnection();
    virtual ~CDBConnection();

    // Methods ----------------------------------------------------------------------------------------------
public:
    /// <summary>Determine if query is successful</summary>
    /// <returns>TRUE if succesful/FALSE if not</returns>
    BOOL IsActionSuccessful(const HRESULT& hResult);

    /// <summary>Update Data in the table</summary>
    /// <returns>TRUE if succesful/FALSE if not</returns>
    BOOL ViewSessionResult();


 
private:
    /// <returns>Database connection to the server</returns>
    CDBPropSet SetDBProperties();

    /// <returns>Rowset properties</returns>
    CDBPropSet UpdateDbPropSet();

    /// <param name="hResult">hresult code to determine action </param>
    /// <returns>TRUE if successful/FALSE if not</returns>
    BOOL OpenSession();
    BOOL OpenConnection();


    /// Getters & Setters
public:
    CDBPropSet GetPropSet() {
        return m_oDBPropSet;
    }
    CDBPropSet GetUpdatePropSet() {
        return m_oUpdatePropSet;
    }
    CDataSource GetDataSource() {
        return m_oDataSource;
    }
    CSession GetSession() {
        return m_oSession;
    }

private:
    /// Members -----------------------------------------------------------------
    CDBPropSet m_oUpdatePropSet;
    CDBPropSet m_oDBPropSet;
    CDataSource m_oDataSource;
    CSession m_oSession;
};


