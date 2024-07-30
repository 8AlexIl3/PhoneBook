#pragma once


/////////////////////////////////////////////////////////////////////////////
// CDBConnection

#include <atldbcli.h>
#include <atlstr.h> 

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
    bool ViewSessionResult();

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


#define OBJECT_CURRENTLY_IN_USE strError.Format(_T("������� �� ���� �� ���� ������,������ �� �������� ��������"))
#define OBJECT_NOT_FOUND strError.Format(_T("������� �� ���� �������"))
#define QUERY_UNSUCCESSFUL strError.Format(_T("�������� � ���������"))
#define SERVER_CONNECTION_ERROR strError.Format(_T("�� ���� �� �� ������� ������ ��� �������"))
#define SESSION_CREATE_ERROR strError.Format(_T("�� ���� �� �� ������� �����"))

