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
    virtual ~ITable();


// Methods
// ----------------
protected:
    virtual bool SelectAll(CAutoMemoryArray<RecordType>& oArray) = 0;
    virtual bool SelectWhereID(const long lID, RecordType& rec) = 0;
    virtual bool UpdateWhereID(const long lID, RecordType& rec) = 0;
    virtual bool InsertRecord(RecordType& rec) = 0;
    virtual bool DeleteWhereID(const long lID) = 0;
};
template<typename RecordType>
inline ITable<RecordType>::ITable()
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
