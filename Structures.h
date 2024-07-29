#pragma once
#define NAME_SIZE 32
#define ADDRESS_SIZE 64
#define PHONE_SIZE 16

struct PERSONS
{	
	//Members
public:
	long lID;
	long lCityID;
	long lUpdateCounter;
	
	TCHAR szFirstName[NAME_SIZE];
	TCHAR szSurname[NAME_SIZE];
	TCHAR szLastName[NAME_SIZE];
	TCHAR szEGN[NAME_SIZE];
	TCHAR szAddress[ADDRESS_SIZE];

	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
	
};
typedef CTypedPtrArray<CPtrArray, PERSONS*> CPtrPersonsArray;

struct PHONE_NUMBERS
{
	long lID;
	long lUpdateCounter;
	long lPersonID;
	long lPhoneTypeID;
	TCHAR szPhone[PHONE_SIZE];

	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
	
};
typedef CTypedPtrArray<CPtrArray, PHONE_NUMBERS*> CPtrPhoneNumbersArray;

struct PHONE_TYPES
{
	long lID;
	long lUpdateCounter;
	TCHAR szPhoneType[PHONE_SIZE];

	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};
typedef CTypedPtrArray<CPtrArray, PHONE_TYPES*> CPtrPhoneTypesArray;

struct CITIES
{
	long lID;
	long lUpdateCounter;
	TCHAR szTownResidence[NAME_SIZE];
	TCHAR szCityName[NAME_SIZE];

	CITIES()

	{
		SecureZeroMemory(this, sizeof(*this));
	}
	
};
typedef CTypedPtrArray<CPtrArray, CITIES*> CPtrCitiesArray;

/// <summary>Array that frees the memory upon destruction</summary>
/// <typeparam name="TYPE">Type of pointer the array will be</typeparam>
template<class TYPE>
class CAutoMemoryArray : public CTypedPtrArray<CPtrArray, TYPE*>
{
public:
    CAutoMemoryArray() = default;

    CAutoMemoryArray(const CAutoMemoryArray& other)
    {
        CopyFrom(other);
    }

    virtual ~CAutoMemoryArray()
    {
        ClearArray();
    }

private:
    void ClearArray()
    {
        for (int i = 0; i < this->GetCount(); ++i)
        {
            delete this->GetAt(i);
        }
        this->RemoveAll();
    }

    void CopyFrom(const CAutoMemoryArray& other)
    {
        for (int i = 0; i < other.GetCount(); ++i)
        {
            TYPE* pNewElem = other.GetAt(i);
            this->Add(pNewElem);
        }
    }
};

typedef CAutoMemoryArray<CITIES> CCitiesArray;
