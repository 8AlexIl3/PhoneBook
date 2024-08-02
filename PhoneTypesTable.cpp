#include "pch.h"
#include "PhoneTypesTable.h"
#include "DBconnectionSingleton.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable

// Constructor / Destructor
// ----------------

CPhoneTypesTable::CPhoneTypesTable() :
    m_oConnection(CDBConnectionSingleton::GetInstance())
{
}

CPhoneTypesTable::~CPhoneTypesTable()
{
}


//Overrides
// ----------------

bool CPhoneTypesTable::SelectAll(CPhoneTypesArray& oPhonetypesArray)
{
    //Connect to server->database->open session
    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }

    //Set query
    CString oStrQuery(_T("SELECT * FROM PHONE_TYPES WTIH (NOLOCK)"));
    HRESULT oHresult;

    oHresult = Open(m_oConnection.GetSession(), oStrQuery);
    //If query is not successful
    if (!m_oConnection.IsActionSuccessful(oHresult))
    {

        return FALSE;
    }
    oHresult = MoveFirst();
    //If there is no data in the table
    if (!m_oConnection.IsActionSuccessful(oHresult))
    {
        return FALSE;
    }
    //add all phone Types to the array
    do
    {
        PHONE_TYPES* pPhoneTypes = new PHONE_TYPES(m_recPhoneType);

        if (!pPhoneTypes) {//If memory is NOT allocated
            CString strError;
            strError.Format(_T("Неуспешно добавяне на тип телефон"));
            AfxMessageBox(strError);

            continue;

        }
        oPhonetypesArray.Add(pPhoneTypes);

    } while (MoveNext() == S_OK);

    Close();

    return TRUE;
}

bool CPhoneTypesTable::SelectWhereID(const long lID, PHONE_TYPES& recPhoneType) {

    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM PHONE_TYPES  WTIH (NOLOCK) WHERE ID = %d"), lID);
    HRESULT oHresult;

    oHresult = Open(m_oConnection.GetSession(), strQuery);

    //If query is NOT sucessful 
    if (!m_oConnection.IsActionSuccessful(oHresult)) {

        return FALSE;
    }
    oHresult = MoveFirst();

    if (FAILED(oHresult)) {
        CString oStrError;
        oStrError.Format((SELECT_ID_FAIL), lID);

        AfxMessageBox(oStrError);

        m_oConnection.GetSession().Abort();
        Close();

        return FALSE;
    }
    recPhoneType = m_recPhoneType;

    Close();

    return TRUE;
}

bool CPhoneTypesTable::UpdateWhereID(const long lID, PHONE_TYPES& recPhoneType)
{
    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }
    HRESULT oHresult;

    oHresult = m_oConnection.GetSession().StartTransaction();
    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        return FALSE;
    }
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM PHONE_TYPES WITH (UPDLOCK) WHERE ID = %d"), lID);

    oHresult = Open(m_oConnection.GetSession(), strQuery, &m_oConnection.GetUpdatePropSet());

    //If query is successful
    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        m_oConnection.GetSession().Abort();

        return FALSE;
    }
    oHresult = MoveFirst();

    if (FAILED(oHresult)) {
        CString oStrError;
        oStrError.Format((SELECT_ID_FAIL),lID);
        AfxMessageBox(oStrError);

        m_oConnection.GetSession().Abort();
        Close();

        return FALSE;
    }

    //record is NOT up to date
    if (recPhoneType.lUpdateCounter != m_recPhoneType.lUpdateCounter) {
        m_oConnection.GetSession().Abort();
        AfxMessageBox(UPDATE_COUNTER_MISMATCH);
        Close();

        return FALSE;
    }
    //ensure this record is up to date in the future
    ++recPhoneType.lUpdateCounter;
    m_recPhoneType = recPhoneType;

    //Set new data
    oHresult = SetData(ACCESSOR_1);
    if (FAILED(oHresult)) {
        m_oConnection.GetSession().Abort();

        CString strError;
        if (oHresult == DB_E_CONCURRENCYVIOLATION)
            strError=CONCURRENCY_VIOLATION;
        else
            strError=DATA_UPDATE_FAIL;
        AfxMessageBox(strError);
        return FALSE;
    }
    m_oConnection.GetSession().Commit();
    Close();

    return TRUE;
}

bool CPhoneTypesTable::InsertRecord(PHONE_TYPES& recPhoneType) {
    // Connect to server -> database -> open session
    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }
    HRESULT oHresult;
    CString strQuery;
    strQuery.Format(_T("SELECT TOP(0) * FROM PHONE_TYPES"));
    oHresult = Open(m_oConnection.GetSession(), strQuery, &m_oConnection.GetUpdatePropSet());
    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        Close();
        return FALSE;
    }

    // Initialize record with the provided data
    m_recPhoneType = recPhoneType;
    // Insert new record
    oHresult = Insert(ACCESSOR_1);
    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        Close();
        return FALSE;
    }
    oHresult = MoveFirst();
    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        Close();
        return FALSE;
    }
    //To get The inserted phone type's ID
    recPhoneType = m_recPhoneType;
    Close();

    return TRUE;
}

bool CPhoneTypesTable::DeleteWhereID(const long lID) {

    //Connect to server->database->open session
    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }
    HRESULT oHresult;
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM PHONE_TYPES WHERE ID = %d"), lID);

    oHresult = Open(m_oConnection.GetSession(), strQuery, &m_oConnection.GetUpdatePropSet());

    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        Close();

        return FALSE;
    }

    oHresult = MoveFirst();

    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        Close();

        return FALSE;
    }

    oHresult = Delete();

    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        Close();

        return FALSE;
    }

    Close();

    return TRUE;
}
