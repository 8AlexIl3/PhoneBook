// CTable.h
#pragma once

template <typename RecordType>
class ITable {
public:
    virtual ~ITable() {}

    virtual BOOL SelectAll(CAutoMemoryArray<RecordType>& oArray) = 0;
    virtual BOOL SelectWhereID(const long lID, RecordType& rec) = 0;
    virtual BOOL UpdateWhereID(const long lID, RecordType& rec) = 0;
    virtual BOOL InsertRecord(RecordType& rec) = 0;
    virtual BOOL DeleteWhereID(const long lID) = 0;

protected:
    virtual BOOL GetRecord(const long lID) = 0;
    virtual BOOL AddRecord(CAutoMemoryArray<RecordType>& oArray) = 0;
};
