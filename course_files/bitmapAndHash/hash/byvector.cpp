#include <algorithm>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>



template <class IntClass>
class SimpleSet
{
public:
    enum
    {
        MINIMUM_HASH_SIZE=7
    };
private:
    std::vector <std::vector <IntClass> > table;
public:
	class iterator
	{
	public:
		unsigned int row,column;

		bool operator==(iterator from) const
		{
			return row==from.row && column==from.column;
		}
		bool operator!=(iterator from) const
		{
			return row!=from.row || column!=from.column;
		}
	};

    SimpleSet()
    {
		table.resize(MINIMUM_HASH_SIZE);
	}
    ~SimpleSet()
    {
		clear();
	}
    void clear(void)
    {
		table.resize(MINIMUM_HASH_SIZE);
		for(auto &row : table)	 // table is an array of rows.
		{
			row.clear();
		}
	}
    void insert(const IntClass i)
    {
		if(find(i)==end()) // If the number is not in the set yet.
		{
			auto row=i%table.size(); // table.size=number of rows.  table.size() is non-zero from the constructor.
			table[row].push_back(i);
		}
	}
	void erase(const IntClass i)
	{
		auto iter=find(i);
		if(end()!=iter)
		{
			table[iter.row][iter.column]=table[iter.row].back();
			table[iter.row].pop_back();
		}
	}
	void resize(unsigned int nRow)
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
	iterator find(IntClass i) const
	{
		auto row=i%table.size();
		for(unsigned int c=0; c<table[row].size(); ++c) // table[row] is a row, and table[row].size() is number of columns for the row.
		{
			if(table[row][c]==i)
			{
				iterator iter;
				iter.row=row;
				iter.column=c;
				return iter;
			}
		}
		return end();
	}
	iterator end(void) const
	{
		iterator iter;
		iter.row=~0;    // 0xffffffff
		iter.column=~0; // 0xffffffff
		return iter;
	}
    // How can we implement find() and end()?
};



int main(void)
{
	srand((int)time(NULL));
	SimpleSet <int> used;

	int numbers[20];
	for(int i=0; i<20; ++i)
	{
	RETRY:
		int r=rand()%20;
		if(used.end()!=used.find(r))
		{
			goto RETRY;
		}
		numbers[i]=r;
		used.insert(r);
	}

	used.resize(11);

	for(auto n : numbers)
	{
		std::cout << n << std::endl;
	}

	for(int i=0; i<20; i+=2)
	{
		used.erase(i);
	}

	return 0;
}
