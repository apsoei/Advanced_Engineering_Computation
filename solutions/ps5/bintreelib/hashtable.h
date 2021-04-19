#ifndef HASHTABLE_IS_INCLUDED
#define HASHTABLE_IS_INCLUDED
/* { */

#include <vector>
#include <stdio.h>

#include "hashbase.h"

template <class KeyType,class ValueType>
class HashTable : public HashBase <KeyType>
{
private:
	class Entry
	{
	public:
		KeyType hashKey;
		CodeType hashCode;
		ValueType value;
	};

	std::vector <std::vector <Entry> > table;

public:
	HashTable();
	~HashTable();
	void CleanUp(void);

	void Update(const KeyType &key,const ValueType &value);
	bool IsIncluded(const KeyType &key) const;
	void Resize(long long int tableSize);
	void Delete(const KeyType &key);

	ValueType *operator[](const KeyType key);
	const ValueType *operator[](const KeyType key) const;

	Handle Next(Handle hd) const;
	ValueType *operator[](Handle hd);
	const ValueType *operator[](Handle hd) const;
	const KeyType &GetKey(Handle hd) const;
};

template <class KeyType,class ValueType>
HashTable<KeyType,ValueType>::HashTable()
{
	table.resize(MINIMUM_TABLE_SIZE);
}
template <class KeyType,class ValueType>
HashTable<KeyType,ValueType>::~HashTable()
{
}
template <class KeyType,class ValueType>
void HashTable<KeyType,ValueType>::CleanUp(void)
{
	table.resize(MINIMUM_TABLE_SIZE);
	for(auto &t : table)
	{
		t.clear();
	}
	nElem=0;
}
template <class KeyType,class ValueType>
void HashTable<KeyType,ValueType>::Update(const KeyType &key,const ValueType &value)
{
	auto hashCode=HashCode(key);
	auto idx=hashCode%table.size();
	for(auto &e : table[idx])
	{
		if(e.hashCode==hashCode && e.hashKey==key)
		{
			e.value=value;
			return;
		}
	}
	Entry entry;
	entry.hashKey=key;
	entry.hashCode=hashCode;
	entry.value=value;
	table[idx].push_back(entry);
	++nElem;

	if(table.size()*4<nElem)
	{
		Resize(table.size()*2);
	}
}
template <class KeyType,class ValueType>
bool HashTable<KeyType,ValueType>::IsIncluded(const KeyType &key) const
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
template <class KeyType,class ValueType>
void HashTable<KeyType,ValueType>::Resize(long long int tableSize)
{
	std::vector <Entry> buffer;
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
		Update(b.hashKey,b.value);
	}
}
template <class KeyType,class ValueType>
void HashTable<KeyType,ValueType>::Delete(const KeyType &key)
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
			if(table.size()<MINIMUM_TABLE_SIZE*2 && nElem<table.size()/4)
			{
				Resize(table.size()/2);
			}
			break;
		}
	}
}

template <class KeyType,class ValueType>
ValueType *HashTable<KeyType,ValueType>::operator[](const KeyType key)
{
	auto hashCode=HashCode(key);
	auto idx=hashCode%table.size();
	for(auto &e : table[idx])
	{
		if(e.hashCode==hashCode && e.hashKey==key)
		{
			return &e.value;
		}
	}
	return nullptr;
}

template <class KeyType,class ValueType>
const ValueType *HashTable<KeyType,ValueType>::operator[](const KeyType key) const
{
	auto hashCode=HashCode(key);
	auto idx=hashCode%table.size();
	for(auto &e : table[idx])
	{
		if(e.hashCode==hashCode && e.hashKey==key)
		{
			return &e.value;
		}
	}
	return nullptr;
}

template <class KeyType,class ValueType>
typename HashTable<KeyType,ValueType>::Handle HashTable<KeyType,ValueType>::Next(Handle hd) const
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

template <class KeyType,class ValueType>
ValueType *HashTable<KeyType,ValueType>::operator[](Handle hd)
{
	return &table[hd.row][hd.column].value;
}
template <class KeyType,class ValueType>
const ValueType *HashTable<KeyType,ValueType>::operator[](Handle hd) const
{
	return &table[hd.row][hd.column].value;
}

template <class KeyType,class ValueType>
const KeyType &HashTable<KeyType,ValueType>::GetKey(Handle hd) const
{
	return table[hd.row][hd.column].hashKey;
}

/* } */
#endif
