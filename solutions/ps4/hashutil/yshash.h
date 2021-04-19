#ifndef YSHASH_IS_INCLUDED
#define YSHASH_IS_INCLUDED
/* { */

#include <vector>
#include <algorithm>  // To use std::swap

// Template for hash functions.
template <class KeyType>
struct ysHash
{
	std::size_t operator()(const KeyType &key) const;
};


// Make a base class for hash set and hash table to reduce code duplicate.
// Since clang and g++ started a harsh interpretation of C++ specification,
// you can expect errors that should not be there.
// The errors pops up when you write what they call ambiguous, even when
// there is no ambiguity.  Majority of the cases are when you write a template
// within template.  To avoid it, let's use double inheritance.
template <class KeyType>
class ysHashTemplate
{
protected:
	ysHash <KeyType> func;
};

class ysHashBase
{
protected:
	enum
	{
		MINIMUM_HASH_SIZE=7
	};
	std::size_t len=0;

	template <class OwnerClass,class KeyType>
	class iterator_base
	{
	public:
		std::size_t row,column;
		const OwnerClass *owner;  // This iterator only works for const owner.
		bool operator==(const iterator_base<OwnerClass,KeyType> &incoming) const
		{
			return row==incoming.row && column==incoming.column;
		}
		bool operator!=(const iterator_base<OwnerClass,KeyType> &incoming) const
		{
			return row!=incoming.row || column!=incoming.column;
		}
	};


	template <class TableClass>
	void resize_base(TableClass &table,unsigned int nRows)
	{
		TableClass newTable;
		newTable.resize(nRows);
		for(auto &row : table)
		{
			for(auto &column : row)
			{
				auto newRow=column.code%nRows;
				newTable[newRow].push_back(column);
			}
		}
		std::swap(table,newTable);
	}

	template <class TableClass>
	void autoResize_base(TableClass &table)
	{
		if(table.size()*4<len)
		{
			resize_base<TableClass>(table,table.size()*2);
		}
		else if(len<table.size()/8 && MINIMUM_HASH_SIZE<table.size())
		{
			resize_base<TableClass>(table,table.size()/2);
		}
	}

	template <class TableClass,class iterClass>
	void moveToNext_base(const TableClass &table,iterClass &iter,iterClass end) const
	{
		if(iter.row<table.size())
		{
			++iter.column;
			if(iter.column<table[iter.row].size())
			{
				return;
			}
			else
			{
				iter.column=0;
				++iter.row;
				while(iter.row<table.size())
				{
					if(0<table[iter.row].size())
					{
						return;
					}
					++iter.row;
				}
			}
		}
		iter=end;
	}

	template <class KeyType,class TableClass,class iterator>
	iterator find_base(const KeyType &key,const TableClass &table,iterator end,std::size_t code) const
	{
		auto row=code%table.size(); // Make sure table.size() won't become zero.
		for(int column=0; column<table[row].size(); ++column)
		{
			if(code==table[row][column].code && // First compare code.  Comparison of code is less costly than of key.
			   key==table[row][column].key)
			{
				iterator iter;
				iter.row=row;
				iter.column=column;
				return iter;
			}
		}
		return end;
	}

	template <class KeyType,class TableClass,class iterator>
	iterator begin_base(const TableClass &table,iterator end) const
	{
		// Return an iterator for the first element.
		for(int row=0; row<table.size(); ++row)
		{
			if(0<table[row].size())
			{
				iterator iter;
				iter.row=row;
				iter.column=0;
				return iter;
			}
		}
		return end;
	}

	template <class iterator>
	iterator end_base(void) const
	{
		iterator iter;
		iter.row=~0;    // ~0 is 0xffffffffffffffff (a very big number)
		iter.column=~0;
		return iter;
	}
};

template <class KeyType>
class ysHashSet : public ysHashBase, ysHashTemplate <KeyType>
{
private:
	class Entry
	{
	public:
		std::size_t code;
		KeyType key;
	};
	std::vector <std::vector <Entry> > table;

public:
	// For a production code, you need to make iterator and const_iterator 
	// to make it const correct.
	class iterator : public iterator_base<ysHashSet<KeyType>,KeyType>
	{
	public:
		const KeyType &operator*() const
		{
			return this->owner->getKey(*this);
		}
		iterator operator++()
		{
			this->owner->moveToNext(*this);
			return *this;
		}
		iterator operator++(int) // Dummy int is for post-incrementation, as defined by C++ rule.
		{
			auto copy=*this;
			this->owner->moveToNext(*this);
			return copy;
		}
	};

	ysHashSet()
	{
		table.resize(MINIMUM_HASH_SIZE);
		len=0;
	}
	void insert(const KeyType &key)
	{
		if(find(key)==end())  // If it is not in the set yet,
		{
			auto code=this->func(key); // You may have to type this->func(key) in clang and g++
			auto row=code%table.size();
			Entry ent;
			table[row].push_back(ent);
			table[row].back().code=code;
			table[row].back().key=key;
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
		if(iter.row<table.size() && iter.column<table[iter.row].size())
		{
			std::swap(table[iter.row][iter.column],table[iter.row].back());
			table[iter.row].pop_back();
			--len;
			autoResize();
		}
	}
	iterator find(const KeyType &key) const
	{
		auto iter=find_base<KeyType,decltype(table),iterator>(key,table,end(),this->func(key));
		iter.owner=this;
		return iter;
	}

	iterator begin(void) const
	{
		auto iter=begin_base<KeyType,decltype(table),iterator>(table,end());
		iter.owner=this;
		return iter;
	}

	// Standard Template Library very often uses end() as NULL.
	iterator end(void) const
	{
		auto iter=end_base<iterator>();
		iter.owner=this;
		return iter;
	}

	void resize(std::size_t nRows)
	{
		resize_base<decltype(table)>(table,nRows);
	}

	const KeyType &getKey(iterator iter) const
	{
		// You cannot do too much if iter is invalid.
		// Most likely the program will crash.
		// You need to make sure not to give an invalid iterator to this function.
		return table[iter.row][iter.column].key;
	}

	void moveToNext(iterator &iter) const
	{
		moveToNext_base<decltype(table),iterator>(table,iter,end());
	}

	void autoResize(void)
	{
		autoResize_base<decltype(table)>(table);
	}
};

template <class KeyType>
typename ysHashSet<KeyType>::iterator begin(const ysHashSet<KeyType> &set)
{
	return set.begin();
}
template <class KeyType>
typename ysHashSet<KeyType>::iterator end(const ysHashSet<KeyType> &set)
{
	return set.end();
}

////////////////////////////////////////////////////////////////////////////////

template <class KeyType,class ValueType>
class ysHashTable : public ysHashBase, ysHashTemplate <KeyType>
{
private:
	enum
	{
		MINIMUM_HASH_SIZE=7
	};
	class Entry
	{
	public:
		std::size_t code;
		KeyType key;
		ValueType value;

		#define first key
		#define second value
	};
	std::vector <std::vector <Entry> > table;

public:
	// For a production code, you need to make iterator and const_iterator 
	// to make it const correct.
	class iterator : public iterator_base<ysHashTable<KeyType,ValueType>,KeyType>
	{
	public:
		const Entry &operator*() const
		{
			return this->owner->getElem(*this);
		}
		const Entry *operator->() const
		{
			return &this->owner->getElem(*this);
		}
		iterator operator++()
		{
			this->owner->moveToNext(*this);
			return *this;
		}
		iterator operator++(int) // Dummy int is for post-incrementation, as defined by C++ rule.
		{
			auto copy=*this;
			this->owner->moveToNext(*this);
			return copy;
		}
	};

	ysHashTable()
	{
		table.resize(MINIMUM_HASH_SIZE);
		len=0;
	}
	void insert(const KeyType &key,const ValueType &value)
	{
		if(find(key)==end())  // If it is not in the set yet,
		{
			auto code=this->func(key);
			auto row=code%table.size();
			Entry ent;
			table[row].push_back(ent);
			table[row].back().code=code;
			table[row].back().key=key;
			table[row].back().value=value;
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
		if(iter.row<table.size() && iter.column<table[iter.row].size())
		{
			std::swap(table[iter.row][iter.column],table[iter.row].back());
			table[iter.row].pop_back();
			--len;
			autoResize();
		}
	}
	iterator find(const KeyType &key) const
	{
		auto iter=find_base<KeyType,decltype(table),iterator>(key,table,end(),this->func(key));
		iter.owner=this;
		return iter;
	}

	iterator begin(void) const
	{
		auto iter=begin_base<KeyType,decltype(table),iterator>(table,end());
		iter.owner=this;
		return iter;
	}

	// Standard Template Library very often uses end() as NULL.
	iterator end(void) const
	{
		auto iter=end_base<iterator>();
		iter.owner=this;
		return iter;
	}

	void resize(std::size_t nRows)
	{
		resize_base<decltype(table)>(table,nRows);
	}

	const Entry &getElem(iterator iter) const
	{
		// You cannot do too much if iter is invalid.
		// Most likely the program will crash.
		// You need to make sure not to give an invalid iterator to this function.
		return table[iter.row][iter.column];
	}

	void moveToNext(iterator &iter) const
	{
		moveToNext_base<decltype(table),iterator>(table,iter,end());
	}

	void autoResize(void)
	{
		autoResize_base<decltype(table)>(table);
	}
};

template <class KeyType,class ValueType>
typename ysHashTable<KeyType,ValueType>::iterator begin(const ysHashTable<KeyType,ValueType> &set)
{
	return set.begin();
}
template <class KeyType,class ValueType>
typename ysHashTable<KeyType,ValueType>::iterator end(const ysHashTable<KeyType,ValueType> &set)
{
	return set.end();
}

/* } */
#endif
