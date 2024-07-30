#include "pch.h"
#include "CitiesTable.h"
#include "DBconnectionSingleton.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

// Constructor / Destructor
// ----------------

CCitiesTable::CCitiesTable():
    m_oConnection(CDBConnectionSingleton::GetInstance())
{
}

CCitiesTable::~CCitiesTable()
{
}


//Overrides
// ----------------

bool CCitiesTable::SelectAll(CCitiesArray& oCitiesArray)
{
    //Connect to server->database->open session
    if (!m_oConnection.ViewSessionResult()) {
        return FALSE;
    }

    //Set query
    CString oStrQuery(_T("SELECT * FROM CITIES"));
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
    //add all cities to the array
    do
    {
        CITIES* pCities = new CITIES(m_recCity);

        if (!pCities) {//If memory is NOT allocated
            CString strError;
            strError.Format(_T("ID: %d, City: %s, Town Residence: %s was NOT added"),
                m_recCity.lID,
                m_recCity.szCityName,
                m_recCity.szTownResidence);
            AfxMessageBox(strError);

            continue;

        }
        oCitiesArray.Add(pCities);

    } while (MoveNext()==S_OK);

    Close();

    return TRUE;
}

bool CCitiesTable::SelectWhereID(const long lID, CITIES& recCity) {

    if (!m_oConnection.ViewSessionResult()){
        return FALSE;
    }
    CString strQuery;
    strQuery.Format( _T("SELECT * FROM CITIES WHERE ID = %d"), lID);
    HRESULT oHresult;

    oHresult = Open(m_oConnection.GetSession(), strQuery);

    //If query is NOT sucessful 
    if (!m_oConnection.IsActionSuccessful(oHresult)) {

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
    recCity = m_recCity;

    Close();

    return TRUE;
}

bool CCitiesTable::UpdateWhereID(const long lID,CITIES& recCity)
{
    if (!m_oConnection.ViewSessionResult()) {
        return FALSE;
    }
    HRESULT oHresult;

    oHresult=m_oConnection.GetSession().StartTransaction();
    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        return FALSE;
    }
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM CITIES WITH (UPDLOCK) WHERE ID = %d"), lID);

    oHresult = Open(m_oConnection.GetSession(), strQuery, &m_oConnection.GetUpdatePropSet());

    //If query is successful
    if (!m_oConnection.IsActionSuccessful(oHresult) ) {
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
    if (recCity.lUpdateCounter != m_recCity.lUpdateCounter) {
        m_oConnection.GetSession().Abort();
        UPDATE_COUNTER_MISMATCH;
        Close();

        return FALSE;
    }
    //ensure this record is up to date in the future
    ++recCity.lUpdateCounter;
    m_recCity = recCity;

   //Set new data
    oHresult = SetData(ACCESSOR_1);
    if (FAILED(oHresult)) {
        m_oConnection.GetSession().Abort();

        CString strError;
        if (oHresult == DB_E_CONCURRENCYVIOLATION)
            CONCURRENCY_VIOLATION;
        else
            DATA_UPDATE_FAIL;
        AfxMessageBox(strError);
        return FALSE;
    }
    m_oConnection.GetSession().Commit();
    Close();

    return TRUE;
}

bool CCitiesTable::InsertRecord(CITIES& recCity) {
    // Connect to server -> database -> open session
    if (!m_oConnection.ViewSessionResult()) {
        return FALSE;
    }
    HRESULT oHresult;
    CString strQuery;
    strQuery.Format(_T("SELECT TOP(0) * FROM CITIES"));
    oHresult = Open(m_oConnection.GetSession(), strQuery, &m_oConnection.GetUpdatePropSet());
    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        Close();
        return FALSE;
    }
   
    // Initialize record with the provided data
    m_recCity = recCity;
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
    //To get The insert city's ID
    recCity = m_recCity;
    Close();

    return TRUE;
}

bool CCitiesTable::DeleteWhereID(const long lID) {
    
    //Connect to server->database->open session
    if (!m_oConnection.ViewSessionResult()) {
        return FALSE;
    }
    HRESULT oHresult;
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM CITIES WHERE ID = %d"), lID);

    oHresult = Open(m_oConnection.GetSession(), strQuery,&m_oConnection.GetUpdatePropSet());

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
