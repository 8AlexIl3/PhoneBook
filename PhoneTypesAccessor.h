#pragma once
#include "Structures.h"
#include <atldbcli.h>
#define ACCESSOR_COUNT  2

#define ACCESSOR_0      0
#define ACCESSOR_1      1

#define REC_ID          1

#define UPDATE_COUNTER  2
#define PHONE_TYPE      3

class CPhoneTypesAccessor
{
protected:
    PHONE_TYPES m_recPhoneType;

    BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, ACCESSOR_COUNT)
        BEGIN_ACCESSOR(ACCESSOR_0, true)
        COLUMN_ENTRY(REC_ID, m_recPhoneType.lID)
        END_ACCESSOR()

        BEGIN_ACCESSOR(ACCESSOR_1, true)
        COLUMN_ENTRY(UPDATE_COUNTER, m_recPhoneType.lUpdateCounter)
        COLUMN_ENTRY(PHONE_TYPE, m_recPhoneType.szPhoneType)
        END_ACCESSOR()
    END_ACCESSOR_MAP()
};