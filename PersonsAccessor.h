#pragma once
#include "Structures.h"
#include <atldbcli.h>
#define ACCESSOR_COUNT          2

#define ACCESSOR_IDENTITY       0
#define ACCESSOR_DATA           1

#define REC_ID                  1

#define CITY_ID                 2
#define PERSON_UPDATE_COUNTER   3
#define FIRST_NAME              4
#define SURNAME                 5
#define LAST_NAME               6
#define EGN                     7
#define ADDRESS                 8

class CPersonsAccessor
{
protected:
    PERSONS m_rec;

    BEGIN_ACCESSOR_MAP(CPersonsAccessor, ACCESSOR_COUNT)
        BEGIN_ACCESSOR(ACCESSOR_IDENTITY, true)
        COLUMN_ENTRY(REC_ID, m_rec.lID)
        END_ACCESSOR()

        BEGIN_ACCESSOR(ACCESSOR_DATA, true)
        COLUMN_ENTRY(CITY_ID, m_rec.lCityID)
        COLUMN_ENTRY(PERSON_UPDATE_COUNTER, m_rec.lUpdateCounter)
        COLUMN_ENTRY(FIRST_NAME, m_rec.szFirstName)
        COLUMN_ENTRY(SURNAME, m_rec.szSurname)
        COLUMN_ENTRY(LAST_NAME, m_rec.szLastName)
        COLUMN_ENTRY(EGN, m_rec.szEGN)
        COLUMN_ENTRY(ADDRESS, m_rec.szAddress)
        END_ACCESSOR()

    END_ACCESSOR_MAP()
};