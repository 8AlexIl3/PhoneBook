#pragma once
#include "Structures.h"
#include <atldbcli.h>
#define ACCESSOR_COUNT              2

#define ACCESSOR_IDENTITY           0
#define ACCESSOR_DATA               1

#define REC_ID                      1

#define PHONE_TYPE_UPDATE_COUNTER   2
#define PHONE_TYPE                  3

class CPhoneTypesAccessor
{
protected:
    PHONE_TYPES m_rec;

    BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, ACCESSOR_COUNT)
        BEGIN_ACCESSOR(ACCESSOR_IDENTITY, true)
        COLUMN_ENTRY(REC_ID, m_rec.lID)
        END_ACCESSOR()

        BEGIN_ACCESSOR(ACCESSOR_DATA, true)
        COLUMN_ENTRY(PHONE_TYPE_UPDATE_COUNTER, m_rec.lUpdateCounter)
        COLUMN_ENTRY(PHONE_TYPE, m_rec.szPhoneType)
        END_ACCESSOR()
    END_ACCESSOR_MAP()
};