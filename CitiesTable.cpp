#include "pch.h"
#include "CitiesTable.h"
#include "DBconnection.h"

BOOL CCitiesTable::SelectAll(CAutoArray<CITIES>& oCitiesArray)
{
    //Connect to server->database->open session
    if (!m_oConnection.InitializeConnection()) {
        return FALSE;
    }
    //Set query
    CString oStrQuery(_T("SELECT * FROM CITIES"));

    if (!m_oConnection.QuerySuccessful(Open(m_oConnection.GetSession(), oStrQuery)))
    {
        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }
    //If there is no data in the table
    if (!m_oConnection.QuerySuccessful(MoveFirst()))
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
    if (!m_oConnection.InitializeConnection()){
        return FALSE;
    }
    CString strQuery;
    strQuery.Format( _T("SELECT * FROM CITIES WHERE ID = %d"), lID);

    //If query is NOT sucessful or record is NOT found in db
    //first check if query is successful and then try to get reccord
    if (!m_oConnection.QuerySuccessful(Open(m_oConnection.GetSession(), strQuery)) || !GetRecord(lID)) {
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
    if (!m_oConnection.InitializeConnection()) {
        return FALSE;
    }
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM CITIES WITH (UPDLOCK) WHERE ID = %d"), lID);
    //If query is successful and record is in the table
    if (!m_oConnection.QuerySuccessful(Open(m_oConnection.GetSession(),
        strQuery, &m_oConnection.GetUpdatePropSet())) || !GetRecord(lID)) {
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
    if (!m_oConnection.UpdateData(SetData(ACCESSOR_1),lID)) {
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
    if (!m_oConnection.InitializeConnection()) {
        return FALSE;
    }

    CString strQuery;
    strQuery.Format(_T("SELECT * FROM CITIES WHERE 1=0"));

    if (!m_oConnection.QuerySuccessful(Open(m_oConnection.GetSession(),
        strQuery, &m_oConnection.GetUpdatePropSet()))) {
        m_oConnection.CloseSessionAndDataSource();
        return FALSE;
    }

    // Initialize record with the provided data
    m_recCity = recCity;
    // Insert new record
    if (!m_oConnection.QuerySuccessful(Insert(ACCESSOR_1))) {
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
    if (!m_oConnection.InitializeConnection()) {
        return FALSE;
    }
    CString strQuery;
    strQuery.Format(_T("SELECT * FROM CITIES WHERE ID = %d"), lID);

    if (!m_oConnection.QuerySuccessful(Open(m_oConnection.GetSession(), strQuery,
        &m_oConnection.GetUpdatePropSet()))) {

        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }

    if (!m_oConnection.QuerySuccessful(MoveFirst())) {

        Close();

        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }

    if (!m_oConnection.QuerySuccessful(Delete())) {

        Close();

        m_oConnection.CloseSessionAndDataSource();

        return FALSE;
    }

    Close();
    m_oConnection.CloseSessionAndDataSource();

    return TRUE;
}


BOOL CCitiesTable::GetRecord(const long lID) {
    switch (MoveFirst()) {
    case S_OK:
        return TRUE;
    case DB_S_ENDOFROWSET: {
        CString oStrCityData;
        oStrCityData.Format(_T("ID: %d, was NOT found"), lID);
        AfxMessageBox(oStrCityData);
        return FALSE;
    }
    default: {
        CString oStrCityData;
        oStrCityData.Format(_T("Unexpected Error"));
        AfxMessageBox(oStrCityData);
        return FALSE;
    }
    }
}
BOOL CCitiesTable::AddRecord(CPtrCitiesArray& oCitiesArray) {
    CITIES* pCity = new CITIES(m_recCity);

    if (pCity) {//If memory is allocated
        /*Message box (debug purposes) can be removed later
        CString StrCityData;
        StrCityData.Format(_T("ID: %d, City: %s, Town Residence: %s has been added"),
            pCity->lID,
            pCity->szCityName,
            pCity->szTownResidence);
        AfxMessageBox(StrCityData);
        Message box (debug purposes) can be removed later*/

        oCitiesArray.Add(pCity);
        return TRUE;
    }
    //In case of memory not being allocated
    CString strError;
    strError.Format(_T("ID: %d, City: %s, Town Residence: %s was NOT added"),
        m_recCity.lID,
        m_recCity.szCityName,
        m_recCity.szTownResidence);
    AfxMessageBox(strError);
    return FALSE;
}