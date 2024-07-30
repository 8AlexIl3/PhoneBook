#pragma once


/////////////////////////////////////////////////////////////////////////////
// ITable.h

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
#include "ITable.inl"

