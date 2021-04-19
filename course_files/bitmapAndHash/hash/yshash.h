#ifndef YSHASH_IS_INCLUDED
#define YSHASH_IS_INCLUDED
/* { */

#include <vector>

// Template for hash functions.
template <class KeyType>
struct ysHash
{
	std::size_t operator()(const KeyType &key) const;
};



class ysHashBase
{
protected:
	enum
	{
		MINIMUM_HASH_SIZE=7
	};
	std::size_t len=0;

public:
	std::size_t size(void) const
	{
		return len;
	}

protected:
	template <class IteratorType,class KeyType,class EntryType>
	IteratorType find_base(const KeyType &key,std::size_t code,const std::vector <std::vector <EntryType> > &table) const
	{
		IteratorType iter;
		auto r=code%table.size();
		for(unsigned int c=0; c<table[r].size(); ++c)
		{
			if(code==table[r][c].code && key==table[r][c].first) // Check for code first, then key.
			{
				iter.row=r;
				iter.column=c;
				return iter;
			}
		}
		return end_base<IteratorType>();
	}

	template <class IteratorType,class EntryType>
	IteratorType begin_base(const std::vector <std::vector <EntryType> > &table) const
	{
		IteratorType iter;
		iter.column=0;
		for(iter.row=0; 0==table[iter.row].size() && iter.row<table.size(); ++iter.row)
		{
		}
		if(iter.row==table.size())
		{
			return end_base<IteratorType>();
		}
		return iter;
	}

	template <class IteratorType>
	IteratorType end_base(void) const
	{
		IteratorType iter;
		iter.row=~0;
		iter.column=~0;
		iter.owner=nullptr;
		return iter;
	}
};

template <class KeyType>
class ysHashSet : public ysHashBase // <-> Comparable to std::unordered_set
{
private:
	class Entry
	{
	public:
		std::size_t code;
		KeyType first;
	};
	std::vector <std::vector <Entry> > table;
	ysHash<KeyType> func; // <-> just like std::hash<KeyType>

	friend class iterator;

public:
	class iterator
	{
	public:
		std::size_t row,column;
		const ysHashSet <KeyType> *owner;

		bool operator==(const iterator &incoming) const
		{
			return row==incoming.row && column==incoming.column;
		}
		bool operator!=(const iterator &incoming) const
		{
			return row!=incoming.row || column!=incoming.column;
		}

		iterator operator++(void) // ++iter;
		{
			++column;
			if(owner->table[row].size()<=column)
			{
				++row;
				column=0;
				while(row<owner->table.size())
				{
					if(0<owner->table[row].size())
					{
						return *this;
					}
					++row;
				}
				*this=owner->end();
			}
			return *this;
		}
		iterator operator++(int) // iter++;
		{
			auto copy=*this;
			++column;
			if(owner->table[row].size()<=column)
			{
				++row;
				column=0;
				while(row<owner->table.size())
				{
					if(0<owner->table[row].size())
					{
						return *this;
					}
					++row;
				}
				*this=owner->end();
			}
			return copy;
		}

		const KeyType &operator*(void) const
		{
			return owner->table[row][column].first;
		}
		const KeyType *operator->(void) const
		{
			return &owner->table[row][column].first;
		}
	};

	ysHashSet()
	{
		table.resize(MINIMUM_HASH_SIZE);
	}
	~ysHashSet()
	{
		clear();
	}
	void clear(void)
	{
		table.resize(MINIMUM_HASH_SIZE);
		for(auto &row : table)
		{
			row.clear();
		}
		len=0;
	}
	void insert(const KeyType &key)
	{
		if(find(key)==end()) // if key is not in the set yet,
		{
			auto code=func(key);
			auto row=code%table.size(); // table.size() is number of rows.
			Entry ent;
			table[row].push_back(ent);
			table[row].back().code=code;
			table[row].back().first=key;
			++len;
			autoResize();
		}
	}
	void erase(const KeyType &key)
	{
		erase(find(key));
	}
	void erase(iterator iter)
	{
		if(iter!=end())
		{
			std::swap(table[iter.row][iter.column],table[iter.row].back());  // Swap rather than copy.  Swapping is faster in general.
			table[iter.row].pop_back();  // Shrink by one.
			--len;
			autoResize();
		}
	}
	iterator find(const KeyType &key) const
	{
		auto iter=find_base<iterator,KeyType,Entry>(key,func(key),table);
		iter.owner=this;
		return iter;
	}

	iterator begin(void) const  // Find the first element in the set/table.  Not necessarily row,columne=0,0.
	{
		auto iter=begin_base<iterator,Entry>(table);
		iter.owner=this;
		return iter;
	}

	// Standard Template Library very often uses end() as NULL.
	iterator end(void) const
	{
		iterator iter;
		iter.row=~0;
		iter.column=~0;
		iter.owner=this;
		return iter;
	}

	void resize(std::size_t nRows)
	{
		nRow=std::max<unsigned int>(MINIMUM_HASH_SIZE,nRow);
		decltype(table) newTable;
		newTable.resize(nRow);  // newTable.size will be number of rows.
		for(auto &row : table)
		{
			for(auto &c : row)
			{
				auto newRow=c%newTable.size();
				newTable[newRow].push_back(c);
			}
		}
		std::swap(table,newTable);
	}

	// Memo to myself: autoResize should be implemented in the assignment.
	//                 Don't write during the lecture.
	void autoResize(void)
	{
		// Part of the next assignment.
	}
	// Hint:  If you increase size when the length exceeds table_size*4, and
	//        reduce size when the length is below table_size/4, 
	//        it could increase/decrease table size too often when
	//        keys are inserted and deleted frequently.
	//        There should be a buffer.
};



template <class KeyType,class ValueType>
class ysHashTable : public ysHashBase  // <-> Comparable to std::unordered_map
{
private:
	class Entry
	{
	public:
		std::size_t code;
		KeyType first;
		ValueType second;
	};
	std::vector <std::vector <Entry> > table;
	ysHash<KeyType> func; // <-> just like std::hash<KeyType>

	friend class iterator;

public:
	class iterator
	{
	public:
		const ysHashTable <KeyType,ValueType> *owner;
		std::size_t row,column;
		bool operator==(const iterator &incoming) const
		{
			return row==incoming.row && column==incoming.column;
		}
		bool operator!=(const iterator &incoming) const
		{
			return row!=incoming.row || column!=incoming.column;
		}
	
		/*
		   auto iter=hashTable.find(key);
		   (*iter).first key
		   (*iter).second second
		*/
		const Entry &operator*(void) const
		{
			return owner->table[row][column];
		}

		const Entry *operator->(void) const
		{
			return &owner->table[row][column];
		}

		iterator operator++(void) // ++iter;
		{
			++column;
			if(owner->table[row].size()<=column)
			{
				++row;
				column=0;
				while(row<owner->table.size())
				{
					if(0<owner->table[row].size())
					{
						return *this;
					}
					++row;
				}
				*this=owner->end();
			}
			return *this;
		}
		iterator operator++(int) // iter++;
		{
			auto copy=*this;
			++column;
			if(owner->table[row].size()<=column)
			{
				++row;
				column=0;
				while(row<owner->table.size())
				{
					if(0<owner->table[row].size())
					{
						return *this;
					}
					++row;
				}
				*this=owner->end();
			}
			return copy;
		}
	};

	ysHashTable()
	{
		table.resize(MINIMUM_HASH_SIZE);
	}
	~ysHashTable()
	{
		clear();
	}
	void clear(void)
	{
		table.resize(MINIMUM_HASH_SIZE);
		for(auto &row : table)
		{
			row.clear();
		}
		len=0;
	}
	void insert(const KeyType &key,const ValueType &value)
	{
		if(find(key)==end()) // if key is not in the set yet,
		{
			auto code=func(key);
			auto row=code%table.size(); // table.size() is number of rows.
			Entry ent;
			table[row].push_back(ent);
			table[row].back().code=code;
			table[row].back().first=key;
			table[row].back().second=value;
			++len;
			autoResize();
		}
	}
	void erase(const KeyType &key)
	{
		erase(find(key));
	}
	void erase(iterator iter)
	{
		if(iter!=end())
		{
			std::swap(table[iter.row][iter.column],table[iter.row].back());  // Swap rather than copy.  Swapping is faster in general.
			table[iter.row].pop_back();  // Shrink by one.
			--len;
			autoResize();
		}
	}
	iterator find(const KeyType &key) const
	{
		auto iter=find_base<iterator,KeyType,Entry>(key,func(key),table);
		iter.owner=this;
		return iter;
	}

	iterator begin(void) const
	{
		auto iter=begin_base<iterator,Entry>(table);
		iter.owner=this;
		return iter;
	}

	// Standard Template Library very often uses end() as NULL.
	iterator end(void) const
	{
		iterator iter;
		iter.row=~0;
		iter.column=~0;
		iter.owner=this;
		return iter;
	}

	void resize(std::size_t nRows)
	{
		nRow=std::max<unsigned int>(MINIMUM_HASH_SIZE,nRow);
		decltype(table) newTable;
		newTable.resize(nRow);  // newTable.size will be number of rows.
		for(auto &row : table)
		{
			for(auto &c : row)
			{
				auto newRow=c%newTable.size();
				newTable[newRow].push_back(c);
			}
		}
		std::swap(table,newTable);
	}

	// Memo to myself: autoResize should be implemented in the assignment.
	//                 Don't write during the lecture.
	void autoResize(void)
	{
		// Part of the next assignment.
	}
	// Hint:  If you increase size when the length exceeds table_size*4, and
	//        reduce size when the length is below table_size/4, 
	//        it could increase/decrease table size too often when
	//        keys are inserted and deleted frequently.
	//        There should be a buffer.
};

template <class KeyType,class ValueType>
typename ysHashTable <KeyType,ValueType>::iterator begin(const ysHashTable <KeyType,ValueType> &table)
{
	return table.begin();
}

template <class KeyType,class ValueType>
typename ysHashTable <KeyType,ValueType>::iterator end(const ysHashTable <KeyType,ValueType> &table)
{
	return table.end();
}



/* } */
#endif
