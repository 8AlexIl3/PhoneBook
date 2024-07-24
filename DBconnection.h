#pragma once
#include <atldbcli.h>
#include <atlstr.h> 
class CDBConnection {

public:
    /// Methods -----------------------------------------------------------------


    BOOL InitializeConnection();
    /// <summary>Determine if query is successful</summary>
    /// <returns>TRUE if succesful/FALSE if not</returns>
    BOOL IsActionSuccessful(const HRESULT& hResult);

    void CloseSessionAndDataSource();

    /// <summary>Update Data in the table</summary>
    /// <returns>TRUE if succesful/FALSE if not</returns>
    BOOL UpdateData(const HRESULT& hResult, const long& lID);

private:
    /// <returns>Database connection to the server</returns>
    CDBPropSet ConnectToSQLServer();

    /// <returns>Rowset properties</returns>
    CDBPropSet UpdateDbPropSet();

    /// <param name="hResult">hresult code to determine action </param>
    /// <returns>TRUE if successful/FALSE if not</returns>
    BOOL ConnectToSQLDB(const HRESULT& hResult);

    /// <param name="hResult">hresult code to determine action </param>
    /// <returns>TRUE if successful/FALSE if not</returns>
    BOOL OpenSession(const HRESULT& hResult);


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


