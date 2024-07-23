#include "pch.h"
#include "DBconnection.h"
CDBPropSet CDBConnection::ConnectToSQLServer() {

    CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
    oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("USER-28684S1KFL\\MSSQLSERVER01")); // SQL Server instance name
    oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, ("SSPI"));
    oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("SQL_PHONEBOOK")); // Database name
    oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
    oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
    oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));
    return oDBPropSet;
}
CDBPropSet CDBConnection::UpdateDbPropSet() {
    CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
    oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
    oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
    oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
    oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
    return oUpdateDBPropSet;
}


BOOL CDBConnection::InitializeConnection()
{
    m_oDBPropSet = ConnectToSQLServer();

    if (!ConnectToSQLDB(m_oDataSource.Open(_T("SQLOLEDB.1"), &m_oDBPropSet))) {
        return FALSE;
    }
    if (!OpenSession(m_oSession.Open(m_oDataSource))) {

        m_oDataSource.Close();

        return FALSE;
    }
    m_oUpdatePropSet = UpdateDbPropSet();

    return TRUE;
}
BOOL CDBConnection::QuerySuccessful(const HRESULT& hResult) {

    if (hResult == S_OK)
        return TRUE;

    //Return more accurate error info
    CString strError;
    switch (hResult) {

    case DB_E_INTEGRITYVIOLATION:
        strError.Format(_T("City cannot be deleted as there are people assigned to it"));
        break;

    case DB_E_ERRORSOCCURRED:
        strError.Format(_T("Object is currently used by other instances"));
        break;

    case DB_S_ENDOFROWSET:
        strError.Format(_T("City was not found"));
        break;

    default:
        strError.Format(_T("Unable to execute query"));
        break;
    }
    AfxMessageBox(strError);

    return FALSE;
}
BOOL CDBConnection::UpdateData(const HRESULT& hResult, const long& lID) {

    if (hResult == S_OK)
        return TRUE;

    //Return more accurate error info
    CString strError;
    switch (hResult) {

    case DB_E_CONCURRENCYVIOLATION:
        strError.Format(_T("Someone is working with this rowset currently"));
        break;

    default:
        strError.Format(_T("Unable to update data"));
        break;
    }
    AfxMessageBox(strError);
    return FALSE;
}
BOOL CDBConnection::ConnectToSQLDB(const HRESULT& hResult) {

    if (FAILED(hResult))
    {
        CString strError;
        strError.Format(_T("Unable to connect to SQL Server database"));
        AfxMessageBox(strError);

        return FALSE;
    }

    return TRUE;
}
BOOL CDBConnection::OpenSession(const HRESULT& hResult) {

    if (FAILED(hResult))
    {
        CStringW strError;
        strError.Format(_T("Unable to open session."));
        AfxMessageBox(strError);

        return FALSE;
    }

    return TRUE;
}
void CDBConnection::CloseSessionAndDataSource() {
    m_oSession.Close();
    m_oDataSource.Close();
}