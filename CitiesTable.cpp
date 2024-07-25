#include "pch.h"
#include "CitiesTable.h"
#include "DBconnectionSingleton.h"

BOOL CCitiesTable::SelectAll(CAutoMemoryArray<CITIES>& oCitiesArray)
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
        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }
    oHresult = MoveFirst();
    //If there is no data in the table
    if (!m_oConnection.IsActionSuccessful(oHresult))
    {
        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }
    //add all cities to the array
    do
    {
        AddRecord(oCitiesArray);
    } while (MoveNext()==S_OK);
    
    Close();
    m_oConnection.CloseSessionAndDataSource();
    return TRUE;
}

BOOL CCitiesTable::SelectWhereID(const long lID, CITIES& recCity) {
    if (!m_oConnection.ViewSessionResult()){
        return FALSE;
    }
    CString strQuery;
    strQuery.Format( _T("SELECT * FROM CITIES WHERE ID = %d"), lID);
    HRESULT oHresult;

    oHresult = Open(m_oConnection.GetSession(), strQuery);

    //If query is NOT sucessful 
    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }
    //If record is NOT present in the table
    if (!GetRecord(lID)) {
        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }
    recCity = m_recCity;
    Close();
    m_oConnection.CloseSessionAndDataSource();

    return TRUE;
}


BOOL CCitiesTable::UpdateWhereID(const long lID,CITIES& recCity)
{
    if (!m_oConnection.ViewSessionResult()) {
        return FALSE;
    }
    HRESULT oHresult;
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM CITIES WITH (UPDLOCK) WHERE ID = %d"), lID);

    oHresult = Open(m_oConnection.GetSession(), strQuery, &m_oConnection.GetUpdatePropSet());

    //If query is successful
    if (!m_oConnection.IsActionSuccessful(oHresult) ) {
        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }
    //if record exists in table
    if (!GetRecord(lID)) {
        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }

    //record is NOT up to date
    if (recCity.lUpdateCounter != m_recCity.lUpdateCounter) {
        AfxMessageBox(_T("Update counter mismatch"));
        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }
    //ensure this record is up to date in the future
    ++recCity.lUpdateCounter;
    m_recCity = recCity;

   //Set new data
    oHresult = SetData(ACCESSOR_1);
    if (!m_oConnection.UpdateData(oHresult,lID)) {
        Close();
        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }
    Close();
    m_oConnection.CloseSessionAndDataSource();

    return TRUE;
}


BOOL CCitiesTable::InsertCity(CITIES& recCity) {
    // Connect to server -> database -> open session
    if (!m_oConnection.ViewSessionResult()) {
        return FALSE;
    }
    HRESULT oHresult;
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM CITIES WHERE 1=0"));

    oHresult = Open(m_oConnection.GetSession(), strQuery, &m_oConnection.GetUpdatePropSet());
    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }

    // Initialize record with the provided data
    m_recCity = recCity;
    // Insert new record
    oHresult = Insert(ACCESSOR_1);
    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        Close();
        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }
    
    Close();
    m_oConnection.CloseSessionAndDataSource();

    return TRUE;
}

BOOL CCitiesTable::DeleteWhereID(const long lID) {
    
    //Connect to server->database->open session
    if (!m_oConnection.ViewSessionResult()) {
        return FALSE;
    }
    HRESULT oHresult;
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM CITIES WHERE ID = %d"), lID);

    oHresult = Open(m_oConnection.GetSession(), strQuery,&m_oConnection.GetUpdatePropSet());

    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }

    oHresult = MoveFirst();

    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        Close();
        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }

    oHresult = Delete();

    if (!m_oConnection.IsActionSuccessful(oHresult)) {
        Close();
        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }

    Close();
    m_oConnection.CloseSessionAndDataSource();

    return TRUE;
}


BOOL CCitiesTable::GetRecord(const long lID) {
    HRESULT oHresult=MoveFirst();
    if (oHresult == S_OK)
        return TRUE;

    CString oStrError;

    switch (oHresult) {

    case DB_S_ENDOFROWSET:
        oStrError.Format(_T("ID: %d, was NOT found"), lID);
        break;

    default:
        oStrError.Format(_T("Unexpected Error"));
        break;

    }
    AfxMessageBox(oStrError);

    return FALSE;

}
BOOL CCitiesTable::AddRecord(CAutoMemoryArray<CITIES>& oCitiesArray) {
    CITIES* pCity = new CITIES(m_recCity);

    if (pCity) {//If memory is allocated
        oCitiesArray.Add(pCity);
        return TRUE;
    }
    //If memory is NOT allocated
    CString strError;
    strError.Format(_T("ID: %d, City: %s, Town Residence: %s was NOT added"),
        m_recCity.lID,
        m_recCity.szCityName,
        m_recCity.szTownResidence);
    AfxMessageBox(strError);
    return FALSE;
}