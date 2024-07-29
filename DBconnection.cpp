#include "pch.h"
#include "DBconnection.h"
CDBConnection::CDBConnection() {
    m_oDBPropSet = SetDBProperties();
    m_oUpdatePropSet = UpdateDbPropSet();
    OpenConnection();
    OpenSession();
}

CDBConnection::~CDBConnection() {
    m_oSession.Close();
    m_oDataSource.Close();
}
CDBPropSet CDBConnection::SetDBProperties() {

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
BOOL CDBConnection::OpenConnection() {
    HRESULT oHresult=m_oDataSource.Open(_T("SQLOLEDB.1"), &m_oDBPropSet);
    if (FAILED(oHresult))
    {
        return FALSE;
    }
    return TRUE;
}
BOOL CDBConnection::OpenSession() {
    HRESULT oHresult= m_oSession.Open(m_oDataSource);
    if (FAILED(oHresult))
    {
        return FALSE;
    }
    return TRUE;

}
BOOL CDBConnection::ViewSessionResult() {

    BOOL bResultConnection=true;
    if (!m_oDataSource.m_spInit) {
        bResultConnection = OpenConnection();
    }
  
    if (!bResultConnection) {
        CString strError;
        strError.Format(_T("Unable to connect to SQL Server database"));
        AfxMessageBox(strError);

        return FALSE;
    }
    if (!m_oSession.m_spOpenRowset) {
            bResultConnection = OpenSession();
        }

    if (!bResultConnection) {
        CStringW strError;
        strError.Format(_T("Unable to open session."));
        AfxMessageBox(strError);

        return FALSE;
    }

    return TRUE;
}

BOOL CDBConnection::IsActionSuccessful(const HRESULT& hResult) {

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



