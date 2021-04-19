#ifndef SIMPLESET_IS_INCLUDED
#define SIMPLESET_IS_INCLUDED
/* { */



#include <vector>

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
	SimpleSet();
	~SimpleSet();
	void clear(void);
	void insert(const IntClass &incoming);

	// How can we implement find() and end()?
};



/* } */
#endif
