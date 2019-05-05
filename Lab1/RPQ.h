#pragma once
#include <algorithm>
class RPQ
{
public:
	RPQ() = default;
	RPQ(unsigned int r, unsigned int p, unsigned int q);
	unsigned int R, P, Q;
	virtual ~RPQ();

};

class RpqComparatorByR
{
public:
	bool operator() (RPQ a, RPQ b) /*For priority Queue */
	{
		return a.R > b.R;
	}
};

class RpqComparatorByQ
{
public:
	bool operator() (RPQ a, RPQ b) /*For priority Queue */
	{
		return a.Q < b.Q;
	}
};
