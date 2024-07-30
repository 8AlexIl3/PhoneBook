#pragma once
#pragma once
#include "Structures.h"
#include <atldbcli.h>
#define ACCESSOR_COUNT  2

#define ACCESSOR_0      0
#define ACCESSOR_1      1

#define REC_ID          1

#define CITY_ID         2
#define UPDATE_COUNTER  3
#define FIRST_NAME      4
#define SURNAME         5
#define LAST_NAME       6
#define EGN             7
#define ADDRESS         8

class CPersonsAccessor
{
protected:
    PERSONS m_recPerson;

    BEGIN_ACCESSOR_MAP(CPersonsAccessor, ACCESSOR_COUNT)
        BEGIN_ACCESSOR(ACCESSOR_0, true)
        COLUMN_ENTRY(REC_ID, m_recPerson.lID)
        END_ACCESSOR()

        BEGIN_ACCESSOR(ACCESSOR_1, true)
        COLUMN_ENTRY(REC_ID, m_recPerson.lCityID)
        COLUMN_ENTRY(UPDATE_COUNTER, m_recPerson.lUpdateCounter)
        COLUMN_ENTRY(FIRST_NAME, m_recPerson.szFirstName)
        COLUMN_ENTRY(SURNAME, m_recPerson.szSurname)
        COLUMN_ENTRY(LAST_NAME, m_recPerson.szLastName)
        COLUMN_ENTRY(EGN, m_recPerson.szEGN)
        COLUMN_ENTRY(ADDRESS, m_recPerson.szAddress)
        END_ACCESSOR()

    END_ACCESSOR_MAP()
};