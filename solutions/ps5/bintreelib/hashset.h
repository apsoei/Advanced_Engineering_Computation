#ifndef HASHSET_IS_INCLUDED
#define HASHSET_IS_INCLUDED
/* { */

#include <vector>
#include <stdio.h>

#include "hashbase.h"

template <class KeyType>
class SimpleHashSet
{
private:
	enum 
	{
		MINIMUM_TABLE_SIZE=7
	};
	std::vector <std::vector <KeyType> > table;
	long long int nElem;

public:
	SimpleHashSet();
	~SimpleHashSet();
	void CleanUp(void);

	void Add(KeyType key);
	bool IsIncluded(KeyType key) const;
	void Resize(long long int tableSize);
	void Print(void) const;
	void Delete(KeyType key);
};

template <class KeyType>
SimpleHashSet<KeyType>::SimpleHashSet()
{
	table.resize(MINIMUM_TABLE_SIZE);
	nElem=0;
}
template <class KeyType>
SimpleHashSet<KeyType>::~SimpleHashSet()
{
}
template <class KeyType>
void SimpleHashSet<KeyType>::CleanUp(void)
{
	table.resize(MINIMUM_HASH_SIZE);
	for(auto &t : table)
	{
		t.clear();
	}
	nElem=0;
}
template <class KeyType>
void SimpleHashSet<KeyType>::Add(KeyType key)
{
	auto idx=key%table.size();
	for(auto e : table[idx])
	{
		if(e==key)
		{
			return;
		}
	}
	table[idx].push_back(key);
	++nElem;
}
template <class KeyType>
bool SimpleHashSet<KeyType>::IsIncluded(KeyType key) const
{
	auto idx=key%table.size();
	for(auto e : table[idx])
	{
		if(e==key)
		{
			return true;
		}
	}
	return false;
}

template <class KeyType>
void SimpleHashSet<KeyType>::Delete(KeyType key)
{
	auto idx=key%table.size();
	for(auto &e : table[idx])
	{
		if(e==key)
		{
			e=table[idx].back();
			table[idx].pop_back();
			--nElem;
			break;
		}
	}
}

template <class KeyType>
void SimpleHashSet<KeyType>::Print(void) const
{
	int idx=0;
	for(auto &t : table)
	{
		printf("[%3d]",idx);
		for(auto e : t)
		{
			printf(" %d",(int)e);
		}
		printf("\n");
		++idx;
	}
}

template <class KeyType>
void SimpleHashSet<KeyType>::Resize(long long int tableSize)
{
	std::vector <KeyType> buffer;
	for(auto &t : table)
	{
		for(auto e : t)
		{
			buffer.push_back(e);
		}
		t.clear();
	}
	table.resize(tableSize);
	for(auto b : buffer)
	{
		Add(b);
	}
}



////////////////////////////////////////////////////////////

template <class KeyType>
class HashSet : public HashBase <KeyType>
{
private:
	class Entry
	{
	public:
		KeyType hashKey;
		CodeType hashCode;
	};

	std::vector <std::vector <Entry> > table;

public:
	HashSet();
	~HashSet();
	void CleanUp(void);

	void Add(const KeyType &key);
	bool IsIncluded(const KeyType &key) const;
	void Resize(long long int tableSize);
	void Delete(const KeyType &key);

	Handle Next(Handle hd) const;
	const KeyType *operator[](Handle hd) const;
};

template <class KeyType>
HashSet<KeyType>::HashSet()
{
	table.resize(MINIMUM_TABLE_SIZE);
}
template <class KeyType>
HashSet<KeyType>::~HashSet()
{
}
template <class KeyType>
void HashSet<KeyType>::CleanUp(void)
{
	table.resize(MINIMUM_HASH_SIZE);
	for(auto &t : table)
	{
		t.clear();
	}
	nElem=0;
}
template <class KeyType>
void HashSet<KeyType>::Add(const KeyType &key)
{
	auto hashCode=HashCode(key);
	auto idx=hashCode%table.size();
	for(auto e : table[idx])
	{
		if(e.hashCode==hashCode && e.hashKey==key)
		{
			return;
		}
	}
	Entry entry;
	entry.hashKey=key;
	entry.hashCode=hashCode;
	table[idx].push_back(entry);
	++nElem;
}
template <class KeyType>
bool HashSet<KeyType>::IsIncluded(const KeyType &key) const
{
	auto hashCode=HashCode(key);
	auto idx=hashCode%table.size();
	for(auto e : table[idx])
	{
		if(e.hashCode==hashCode && e.hashKey==key)
		{
			return true;
		}
	}
	return false;
}
template <class KeyType>
void HashSet<KeyType>::Resize(long long int tableSize)
{
	std::vector <KeyType> buffer;
	for(auto &t : table)
	{
		for(auto e : t)
		{
			buffer.push_back(e.hashKey);
		}
		t.clear();
	}
	table.resize(tableSize);
	for(auto b : buffer)
	{
		Add(b);
	}
}
template <class KeyType>
void HashSet<KeyType>::Delete(const KeyType &key)
{
	auto hashCode=HashCode(key);
	auto idx=hashCode%table.size();
	for(auto &e : table[idx])
	{
		if(e.hashCode==hashCode && e.hashKey==key)
		{
			e=table[idx].back();
			table[idx].pop_back();
			--nElem;
			break;
		}
	}
}

template <class KeyType>
typename HashSet<KeyType>::Handle HashSet<KeyType>::Next(Handle hd) const
{
	if(true!=IsNotNull(hd))
	{
		return First();
	}

	++hd.column;
	if(hd.column<table[hd.row].size())
	{
		return hd;
	}

	hd.column=0;
	++hd.row;
	while(hd.row<table.size())
	{
		if(0<table[hd.row].size())
		{
			return hd;
		}
		++hd.row;
	}

	hd.row=-1;
	hd.column=-1;
	return hd;
}

template <class KeyType>
const KeyType *HashSet<KeyType>::operator[](Handle hd) const
{
	return &table[hd.row][hd.column].hashKey;
}

/* } */
#endif
