#include "pch.h"
#include "PersonsTable.h"
#include "DBconnectionSingleton.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

// Constructor / Destructor
// ----------------

CPersonsTable::CPersonsTable() :
    m_oConnection(CDBConnectionSingleton::GetInstance())
{
}

CPersonsTable::~CPersonsTable()
{
}


//Overrides
// ----------------

bool CPersonsTable::SelectAll(CPersonsArray& oPersonsArray)
{
    //Connect to server->database->open session
    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }

    //Set query
    CString oStrQuery(_T("SELECT * FROM PERSONS  WTIH (NOLOCK)"));
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
    //add all Persons to the array
    do
    {
        PERSONS* pPersons = new PERSONS(m_recPerson);

        if (!pPersons) {//If memory is NOT allocated
            CString strError;
            strError.Format(_T("Неуспешно добавяне на човек"));
            AfxMessageBox(strError);

            continue;

        }
        oPersonsArray.Add(pPersons);

    } while (MoveNext() == S_OK);

    Close();

    return TRUE;
}

bool CPersonsTable::SelectWhereID(const long lID, PERSONS& recPerson) {

    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM PERSONS  WTIH (NOLOCK) WHERE ID = %d"), lID);
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
    recPerson = m_recPerson;

    Close();

    return TRUE;
}

bool CPersonsTable::UpdateWhereID(const long lID, PERSONS& recPerson)
{
    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }

    CString strQuery;

    strQuery.Format(_T("SELECT * FROM PERSONS WITH (UPDLOCK) WHERE ID = %d"), lID);

    HRESULT oHresult;

    oHresult = Open(m_oConnection.GetSession(), strQuery, &m_oConnection.GetUpdatePropSet());

    //If query is successful
    if (!m_oConnection.IsActionSuccessful(oHresult)) {

        return FALSE;
    }
    oHresult = MoveFirst();

    if (FAILED(oHresult)) {
        CString oStrError;
        oStrError.Format((SELECT_ID_FAIL),lID);
        AfxMessageBox(oStrError);

        Close();

        return FALSE;
    }

    //record is NOT up to date
    if (recPerson.lUpdateCounter != m_recPerson.lUpdateCounter) {
        AfxMessageBox(UPDATE_COUNTER_MISMATCH);
        Close();

        return FALSE;
    }
    //ensure this record is up to date in the future
    ++recPerson.lUpdateCounter;
    m_recPerson = recPerson;

    //Set new data
    oHresult = SetData(ACCESSOR_1);
    if (FAILED(oHresult)) {

        CString strError;
        if (oHresult == DB_E_CONCURRENCYVIOLATION)
            strError=CONCURRENCY_VIOLATION;
        else
            strError=DATA_UPDATE_FAIL;
        Close();
        AfxMessageBox(strError);
        return FALSE;
    }
    Close();

    return TRUE;
}

bool CPersonsTable::InsertRecord(PERSONS& recPerson) {
    // Connect to server -> database -> open session
    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }
    HRESULT oHresult;
    CString strQuery;
    strQuery.Format(_T("SELECT TOP(0) * FROM PERSONS"));
    oHresult = Open(m_oConnection.GetSession(), strQuery, &m_oConnection.GetUpdatePropSet());
    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        Close();
        return FALSE;
    }

    // Initialize record with the provided data
    m_recPerson = recPerson;
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
    //To get The inserted Person's ID
    recPerson = m_recPerson;

    Close();

    return TRUE;
}

bool CPersonsTable::DeleteWhereID(const long lID) {

    //Connect to server->database->open session
    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }
    HRESULT oHresult;
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM PERSONS WHERE ID = %d"), lID);

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
