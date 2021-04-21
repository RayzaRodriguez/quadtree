#include <vector>
#include "point.h"
using namespace std;
class node
{	
public:
	node  *regions[4];
	point *topLeftPoint;
	point *botRightPoint;
	bool isLeaf = 1;
	int level = 0;
	vector<point *> points;
	node(point *topLeftPoint, point *botRightPoint);
	~node();
};

