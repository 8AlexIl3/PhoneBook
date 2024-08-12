#pragma once
#include "DBconnectionSingleton.h"

#define UPDATE_COUNTER_MISMATCH L"Презаписването неуспешно, опитайте по-късно"
#define CONCURRENCY_VIOLATION L"Данните се използват от друго място, опитайте по-късно"
#define DATA_UPDATE_FAIL L"Данните не могат да бъдат обновенни, опитайте по-късно"
#define SELECT_ID_FAIL L"ID: %d не може да бъде извлечено"

/////////////////////////////////////////////////////////////////////////////
// CBaseTable

template <typename RecordType,typename Accessor>
class CBaseTable : public CCommand<CAccessor<Accessor>>
{

// Constructor / Destructor
// ----------------
public:
    CBaseTable();

    CBaseTable(CString& strTableName, CString strColumnName);

    CBaseTable(CString& strTableName);
    virtual ~CBaseTable();


// Methods
// ----------------
public:
    virtual bool SelectAll(CAutoMemoryArray<RecordType>& oArray) {
        //Connect to server->database->open session
        if (!m_oConnection.CheckValidSession()) 
            return FALSE;
  
        //Set query
        CString oStrQuery;
        oStrQuery.Format(_T("SELECT * FROM %s WTIH (NOLOCK)"), static_cast<const wchar_t*>(m_strTableName));
        HRESULT oHresult;

        oHresult = Open(m_oConnection.GetSession(), oStrQuery);
        //If query is not successful
        if (!m_oConnection.IsActionSuccessful(oHresult))
            return FALSE;
        
        oHresult = MoveFirst();
        //If there is no data in the table
        if (!m_oConnection.IsActionSuccessful(oHresult))
            return FALSE;

        //add all phone numbers to the array
        do
        {
            RecordType* pPhoneNumbers = new RecordType(m_rec);

            if (!pPhoneNumbers) {//If memory is NOT allocated
                CString strError;
                strError.Format(_T("Неуспешно добавяне на телефонен номер"));
                AfxMessageBox(strError);

                continue;

            }
            oArray.Add(pPhoneNumbers);

        } while (MoveNext() == S_OK);

        Close();

        return TRUE;
    }

    virtual bool SelectWhereID(const long lID, RecordType& rec) {

        if (!m_oConnection.CheckValidSession()) 
            return FALSE;

        CString strQuery;
        strQuery.Format(_T("SELECT * FROM %s WTIH (NOLOCK) WHERE ID = %d"), static_cast<const wchar_t*>(m_strTableName), lID);
        HRESULT oHresult;

        oHresult = Open(m_oConnection.GetSession(), strQuery);

        //If query is NOT sucessful 
        if (!m_oConnection.IsActionSuccessful(oHresult)) 
            return FALSE;
        
        oHresult = MoveFirst();

        if (FAILED(oHresult)) {
            CString oStrError;

            oStrError.Format((SELECT_ID_FAIL), lID);

            AfxMessageBox(oStrError);

            m_oConnection.GetSession().Abort();
            Close();

            return FALSE;
        }
        rec = m_rec;

        Close();

        return TRUE;
    }
    virtual bool SelectMultipleWhereID(const long lID, CAutoMemoryArray<RecordType>& oArray)
    {
        //Connect to server->database->open session
        if (!m_oConnection.CheckValidSession())
            return FALSE;
        

        //Set query
        CString oStrQuery;
        HRESULT oHresult;
        oStrQuery.Format(_T("SELECT * FROM %s WTIH (NOLOCK) WHERE %s = %d"),
            static_cast<const wchar_t*>(m_strTableName),
            static_cast<const wchar_t*>(m_strColumnName),
            lID);
        oHresult = Open(m_oConnection.GetSession(), oStrQuery);
        //If query is not successful
        if (!m_oConnection.IsActionSuccessful(oHresult))
            return FALSE;
        
        oHresult = MoveFirst();
        //If there is no data in the table
        if (!m_oConnection.IsActionSuccessful(oHresult))
        {
            Close();
            return FALSE;
        }
        
        //add all phone numbers to the array
        do
        {

            RecordType* pPhoneNumbers = new RecordType(m_rec);

            if (!pPhoneNumbers) {//If memory is NOT allocated
                CString strError;
                strError.Format(_T("Неуспешно добавяне на телефонен номер"));
                AfxMessageBox(strError);

                continue;

            }
            oArray.Add(pPhoneNumbers);

        } while (MoveNext() == S_OK);

        Close();

        return TRUE;
    }
    virtual bool UpdateWhereID(const long lID, RecordType& rec) {


        if (!m_oConnection.CheckValidSession()) 
            return FALSE;
        

        HRESULT oHresult;
        CString strQuery;
        strQuery.Format(_T("SELECT * FROM %s WITH (UPDLOCK) WHERE ID = %d"), static_cast<const wchar_t*>(m_strTableName), lID);

        bool bTransactionOccured = m_oConnection.StartTransaction();

        oHresult = Open(m_oConnection.GetSession(), strQuery, &m_oConnection.GetUpdatePropSet());

        //If query is successful
        if (!m_oConnection.IsActionSuccessful(oHresult)) {
            if (bTransactionOccured)
                m_oConnection.RollbackTransaction();
                
                Close();
            return FALSE;
        }
        
        oHresult = MoveFirst();

        if (FAILED(oHresult)) {
            if (bTransactionOccured)
                m_oConnection.RollbackTransaction();

                Close();

            CString oStrError;
            AfxMessageBox(SELECT_ID_FAIL);

            return FALSE;
        }

        //record is NOT up to date
        if (rec.lUpdateCounter != m_rec.lUpdateCounter) {
            if (bTransactionOccured)
                m_oConnection.RollbackTransaction();

                Close();

            AfxMessageBox(UPDATE_COUNTER_MISMATCH);

            return FALSE;
        }
        //No need to update to same value
        if (memcmp(&rec, &m_rec, sizeof(rec))) {
            ++rec.lUpdateCounter;
            m_rec = rec;
        }
        
        //Set new data
        oHresult = SetData(ACCESSOR_DATA);

        if (FAILED(oHresult)) {
            if (bTransactionOccured)
                m_oConnection.RollbackTransaction();

                Close();

            CString strError;

            if (oHresult == DB_E_CONCURRENCYVIOLATION)
                strError = CONCURRENCY_VIOLATION;

            else
                strError = DATA_UPDATE_FAIL;

            AfxMessageBox(strError);
            
            return FALSE;
        }
        
        if (bTransactionOccured) {
            m_oConnection.CommitTransaction();
            Close();
        }

        return TRUE;
    }
    virtual bool InsertRecord(RecordType& rec) {
        // Connect to server -> database -> open session
        if (!m_oConnection.CheckValidSession()) 
            return FALSE;
       
        HRESULT oHresult;
        CString strQuery;
        strQuery.Format(_T("SELECT TOP(0) * FROM %s"), static_cast<const wchar_t*>(m_strTableName));

        bool bTransactionOccured = m_oConnection.StartTransaction();

        oHresult = Open(m_oConnection.GetSession(), strQuery, &m_oConnection.GetUpdatePropSet());
        if (!m_oConnection.IsActionSuccessful(oHresult)) {
            if (bTransactionOccured)
                m_oConnection.RollbackTransaction();

                Close();
            return FALSE;
        }

        // Initialize record with the provided data
        m_rec = rec;
        // Insert new record
        oHresult = Insert(ACCESSOR_DATA);
        if (!m_oConnection.IsActionSuccessful(oHresult)) {
            if (bTransactionOccured)
                m_oConnection.RollbackTransaction();

                Close();
            return FALSE;
        }
        oHresult = MoveFirst();
        if (!m_oConnection.IsActionSuccessful(oHresult)) {
            if (bTransactionOccured)
                m_oConnection.RollbackTransaction();

                Close();
            return FALSE;
        }
        //Gets The records' ID
        rec = m_rec;

        if (bTransactionOccured) {
            m_oConnection.CommitTransaction();

                Close();
        }


        return TRUE;
    };
    virtual bool DeleteWhereID(const long lID) {
        //Connect to server->database->open session
        if (!m_oConnection.CheckValidSession()) 
            return FALSE;
        
        HRESULT oHresult;
        CString strQuery;
        strQuery.Format(_T("SELECT * FROM %s WHERE ID = %d"), static_cast<const wchar_t*>(m_strTableName), lID);

        bool bTransactionOccured = m_oConnection.StartTransaction();

        oHresult = Open(m_oConnection.GetSession(), strQuery, &m_oConnection.GetUpdatePropSet());

        if (!m_oConnection.IsActionSuccessful(oHresult)) {
            if (bTransactionOccured)
                m_oConnection.RollbackTransaction();

            Close();

            return FALSE;
        }

        oHresult = MoveFirst();

        if (!m_oConnection.IsActionSuccessful(oHresult)) {
            if (bTransactionOccured)
                m_oConnection.RollbackTransaction();

            Close();

            return FALSE;
        }

        oHresult = Delete();

        if (!m_oConnection.IsActionSuccessful(oHresult)) {
            if (bTransactionOccured)
                m_oConnection.RollbackTransaction();

            Close();

            return FALSE;
        }

        if (bTransactionOccured) {
            m_oConnection.CommitTransaction();

            Close();
        }

        return TRUE;
    }
private:
    CDBConnection& m_oConnection;
    CString m_strTableName;
    CString m_strColumnName;
};

template <typename RecordType, typename Accessor>
inline CBaseTable<RecordType, Accessor>::CBaseTable():
m_oConnection(CDBConnectionSingleton::GetInstance())
{
}

template <typename RecordType, typename Accessor>
inline CBaseTable<RecordType, Accessor>::CBaseTable(CString& strTableName, CString strColumnName) :
    m_strTableName(strTableName),
    m_strColumnName(strColumnName),
    m_oConnection(CDBConnectionSingleton::GetInstance())
{
}

template <typename RecordType, typename Accessor>
inline CBaseTable<RecordType, Accessor>::CBaseTable(CString& strTableName) :
    m_strTableName(strTableName),
    m_oConnection(CDBConnectionSingleton::GetInstance())
{
}

template <typename RecordType, typename Accessor>
inline CBaseTable<RecordType,Accessor>::~CBaseTable()
{
}
