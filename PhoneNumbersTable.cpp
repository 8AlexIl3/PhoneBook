#include "pch.h"
#include "PhoneNumbersTable.h"
#include "DBconnectionSingleton.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable

// Constructor / Destructor
// ----------------

CPhoneNumbersTable::CPhoneNumbersTable() :
    m_oConnection(CDBConnectionSingleton::GetInstance())
{
}

CPhoneNumbersTable::~CPhoneNumbersTable()
{
}


//Overrides
// ----------------

bool CPhoneNumbersTable::SelectAll(CPhoneNumbersArray& oPhoneNumbersArray)
{
    //Connect to server->database->open session
    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }

    //Set query
    CString oStrQuery(_T("SELECT * FROM PHONE_NUMBERS  WTIH (NOLOCK)"));
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
    //add all phone numbers to the array
    do
    {
        PHONE_NUMBERS* pPhoneNumbers = new PHONE_NUMBERS(m_recPhoneNumber);

        if (!pPhoneNumbers) {//If memory is NOT allocated
            CString strError;
            strError.Format(_T("Неуспешно добавяне на телефонен номер"));
            AfxMessageBox(strError);

            continue;

        }
        oPhoneNumbersArray.Add(pPhoneNumbers);

    } while (MoveNext() == S_OK);

    Close();

    return TRUE;
}

bool CPhoneNumbersTable::SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumber) {

    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM PHONE_NUMBERS  WTIH (NOLOCK) WHERE ID = %d"), lID);
    HRESULT oHresult;

    oHresult = Open(m_oConnection.GetSession(), strQuery);

    //If query is NOT sucessful 
    if (!m_oConnection.IsActionSuccessful(oHresult)) {

        return FALSE;
    }
    oHresult = MoveFirst();

    if (FAILED(oHresult)) {
        CString oStrError;
        oStrError.Format(SELECT_ID_FAIL);

        AfxMessageBox(oStrError);

        m_oConnection.GetSession().Abort();
        Close();

        return FALSE;
    }
    recPhoneNumber = m_recPhoneNumber;

    Close();

    return TRUE;
}

bool CPhoneNumbersTable::SelectMultipleWhereID(const long lID, CPhoneNumbersArray& oPhoneNumbersArray)
{
    //Connect to server->database->open session
    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }

    //Set query
    CString oStrQuery;
    HRESULT oHresult;
    oStrQuery.Format(_T("SELECT * FROM PHONE_NUMBERS WTIH (NOLOCK) WHERE PERSON_ID = %d"), lID);
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
    //add all phone numbers to the array
    do
    {
        PHONE_NUMBERS* pPhoneNumbers = new PHONE_NUMBERS(m_recPhoneNumber);

        if (!pPhoneNumbers) {//If memory is NOT allocated
            CString strError;
            strError.Format(_T("Неуспешно добавяне на телефонен номер"));
            AfxMessageBox(strError);

            continue;

        }
        oPhoneNumbersArray.Add(pPhoneNumbers);

    } while (MoveNext() == S_OK);

    Close();

    return TRUE;
}

bool CPhoneNumbersTable::UpdateWhereID(const long lID, PHONE_NUMBERS& recPhoneNumber)
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
    strQuery.Format(_T("SELECT * FROM PHONE_NUMBERS WITH (UPDLOCK) WHERE ID = %d"), lID);

    oHresult = Open(m_oConnection.GetSession(), strQuery, &m_oConnection.GetUpdatePropSet());

    //If query is successful
    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        m_oConnection.GetSession().Abort();

        return FALSE;
    }
    oHresult = MoveFirst();

    if (FAILED(oHresult)) {
        CString oStrError;
        SELECT_ID_FAIL;
        AfxMessageBox(oStrError);

        m_oConnection.GetSession().Abort();
        Close();

        return FALSE;
    }

    //record is NOT up to date
    if (recPhoneNumber.lUpdateCounter != m_recPhoneNumber.lUpdateCounter) {
        m_oConnection.GetSession().Abort();
        AfxMessageBox(UPDATE_COUNTER_MISMATCH);
        Close();

        return FALSE;
    }
    //ensure this record is up to date in the future
    ++recPhoneNumber.lUpdateCounter;
    m_recPhoneNumber = recPhoneNumber;

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

bool CPhoneNumbersTable::InsertRecord(PHONE_NUMBERS& recPhoneNumber) {
    // Connect to server -> database -> open session
    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }
    HRESULT oHresult;
    CString strQuery;
    strQuery.Format(_T("SELECT TOP(0) * FROM PHONE_NUMBERS"));
    oHresult = Open(m_oConnection.GetSession(), strQuery, &m_oConnection.GetUpdatePropSet());
    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        Close();
        return FALSE;
    }

    // Initialize record with the provided data
    m_recPhoneNumber = recPhoneNumber;
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
    //To get The inserted phone number's ID
    recPhoneNumber = m_recPhoneNumber;
    Close();

    return TRUE;
}

bool CPhoneNumbersTable::DeleteWhereID(const long lID) {

    //Connect to server->database->open session
    if (!m_oConnection.CheckValidSession()) {
        return FALSE;
    }
    HRESULT oHresult;
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM PHONE_NUMBERS  WHERE ID = %d"), lID);

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
