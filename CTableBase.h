#pragma once


/////////////////////////////////////////////////////////////////////////////
// ITable

template <typename RecordType>
class ITable
{

// Constructor / Destructor
// ----------------
public:
    ITable();
    ITable(CString strTableName);
    virtual ~ITable();


// Methods
// ----------------
protected:
    virtual bool SelectAll(CAutoMemoryArray<RecordType>& oArray) { return false; }
    virtual bool SelectWhereID(const long lID, RecordType& rec) { return false; }
    virtual bool UpdateWhereID(const long lID, RecordType& rec) { return false; }
    virtual bool InsertRecord(RecordType& rec){return false; }
    virtual bool DeleteWhereID(const long lID) { return false; }


// Members
// ----------------
protected:
    CString m_strTableName;
};
template<typename RecordType>
inline ITable<RecordType>::ITable()
{
}

template<typename RecordType>
inline ITable<RecordType>::ITable(CString strTableName) :
    m_strTableName(m_strTableName)
{
}

template<typename RecordType>
inline ITable<RecordType>::~ITable()
{
}
#define UPDATE_COUNTER_MISMATCH L"Презаписването неуспешно, опитайте по-късно"
#define CONCURRENCY_VIOLATION L"Данните се използват от друго място, опитайте по-късно"
#define DATA_UPDATE_FAIL L"Данните не могат да бъдат обновенни, опитайте по-късно"
#define SELECT_ID_FAIL L"ID: %d не може да бъде извлечено"
