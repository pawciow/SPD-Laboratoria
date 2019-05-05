#pragma once
#include <algorithm>
class RPQ
{
public:
	RPQ(int r, int p, int q);
	int R, P, Q;
	virtual ~RPQ();
	bool operator() (RPQ a, RPQ b)
	{
		return a.Q > b.Q;
	}
};

