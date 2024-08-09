#include "pch.h"
#include "DBconnection.h"


/////////////////////////////////////////////////////////////////////////////
// CDBConnection


// Constructor / Destructor
// ----------------

CDBConnection::CDBConnection() 
{
    m_oDBPropSet = SetDBProperties();
    m_oUpdatePropSet = UpdateDBPropSet();
    OpenConnection();
    OpenSession();
}

CDBConnection::~CDBConnection()
{
    m_oSession.Close();
    m_oDataSource.Close();
}

// Methods
// ----------------

CDBPropSet CDBConnection::GetPropSet()
{
    return m_oDBPropSet;
}

CDBPropSet CDBConnection::GetUpdatePropSet()
{
    return m_oUpdatePropSet;
}

CDataSource CDBConnection::GetDataSource()
{
    return m_oDataSource;
}

CSession CDBConnection::GetSession()
{
    return m_oSession;
}

bool CDBConnection::IsActionSuccessful(const HRESULT& hResult)
{

    if (hResult == S_OK)
        return TRUE;
 
    return FALSE;
}

bool CDBConnection::CheckValidSession()
{

    bool bResultConnection(true);
    //if connection is not up
    if (!m_oDataSource.m_spInit) 
        bResultConnection = OpenConnection();

    if (!bResultConnection) {
        CString strError;
        strError=SERVER_CONNECTION_ERROR;
        AfxMessageBox(strError);
        return FALSE;
    }
    //if session is not up
    if (!m_oSession.m_spOpenRowset) 
        bResultConnection = OpenSession();
    

    if (!bResultConnection) {
        CStringW strError;
        strError=SESSION_CREATE_ERROR;
        AfxMessageBox(strError);

        return FALSE;
    }

    return TRUE;
}

CDBPropSet CDBConnection::SetDBProperties()
{

    CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
    oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("USER-28684S1KFL\\MSSQLSERVER01")); // SQL Server instance name
    oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, ("SSPI"));
    oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("SQL_PHONEBOOK")); // Database name
    oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
    oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
    oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));
    return oDBPropSet;
}

CDBPropSet CDBConnection::UpdateDBPropSet()
{
    CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
    oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
    oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
    oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
    oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
    return oUpdateDBPropSet;
}

bool CDBConnection::OpenSession()
{
    HRESULT oHresult = m_oSession.Open(m_oDataSource);
    if (FAILED(oHresult))
        return FALSE;
    return TRUE;

}

bool CDBConnection::OpenConnection()
{
    HRESULT oHresult = m_oDataSource.Open(_T("SQLOLEDB.1"), &m_oDBPropSet);
    if (FAILED(oHresult))
    {
        return FALSE;
    }
    return TRUE;
}


