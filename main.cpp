#include <iostream>
#include "qtree.h"

int main(int, char**) {
    point *topLeftPoint = new point(0.0, 101);
	point *botRightPoint = new point(101, 0.0);
	node *root = new node(topLeftPoint, botRightPoint);
	qtree q(root, 2);
	q.insert(20, 90);
	q.insert(100, 90);
	q.insert(30, 20);
	q.insert(90, 10);
    
}
