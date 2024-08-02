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
#define UPDATE_COUNTER_MISMATCH L"�������������� ���������, �������� ��-�����"
#define CONCURRENCY_VIOLATION L"������� �� ��������� �� ����� �����, �������� ��-�����"
#define DATA_UPDATE_FAIL L"������� �� ����� �� ����� ���������, �������� ��-�����"
#define SELECT_ID_FAIL L"ID: %d �� ���� �� ���� ���������"
