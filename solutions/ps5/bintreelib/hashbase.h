#ifndef HASHBASE_IS_INCLUDED
#define HASHBASE_IS_INCLUDED
/* { */

template <class KeyType>
class HashBase
{
public:
	typedef unsigned long long CodeType;

	class Handle
	{
	public:
		long long int row,column;
	};

	enum 
	{
		MINIMUM_TABLE_SIZE=7
	};

protected:
	long long int nElem;

public:
	// This function must be specialized for a key type.
	unsigned long long int HashCode(const KeyType &key) const;

	HashBase()
	{
		nElem=0;
	}
	Handle First(void) const
	{
		Handle h;
		if(0<nElem)
		{
			h.row=0;
			h.column=0;
		}
		else
		{
			h.row=-1;
			h.column=-1;
		}
		return h;
	}
	bool IsNotNull(Handle hd) const
	{
		if(0<=hd.row && 0<=hd.column)
		{
			return true;
		}
		return false;
	}
};

/* } */
#endif
