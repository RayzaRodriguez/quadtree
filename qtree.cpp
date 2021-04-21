#include "qtree.h"


qtree::qtree(node *root, int maxPointPerRegion)
{
	this->root = root;
	this->maxPointPerRegion = maxPointPerRegion;
}

bool qtree::isInBox(float x, float y, node * r) {
	return (x >= r->topLeftPoint->x && x <= r->botRightPoint->x && y <= r->topLeftPoint->y && y >= r->botRightPoint->y);
}

node * qtree::search(float x, float y) {
	if (!isInBox(x, y, this->root)) {
		return nullptr;
	}
	queue<node *>path;
	node * guide = this->root;
	path.push(guide);
	while (!path.empty() && !guide->isLeaf) {
		for (auto &r : guide->regions) {
			if (isInBox(x, y, r)) {
				path.push(r);
				break;
			}
		}
		path.pop();
		guide = path.front();
	}
	cout << "Cuadrante donde cae el punto: xtl:" << guide->topLeftPoint->x << " ytl:" << guide->topLeftPoint->y << " xbr:" << guide->botRightPoint->x << " ybr:" << guide->botRightPoint->y << endl;
	return guide;
}

void qtree::insert(float x, float y) {
	node *n = this->search(x, y);
	point *newPoint = new point(x, y);
	n->points.push_back(newPoint);
    //cout << "Box Found: " << n->topLeftPoint->x << " " << n->topLeftPoint->y << " " << n->botRightPoint->x << " " << n->botRightPoint->y << endl;
	while (n->points.size() > this->maxPointPerRegion) {
        cout<<"La altura del arbol aumenta"<<endl;
		point *topLeftPoint;
		point *botLeftPoint;
		point *centerPoint = new point((n->topLeftPoint->x + n->botRightPoint->x) / 2, (n->topLeftPoint->y + n->botRightPoint->y) / 2);
		topLeftPoint = n->topLeftPoint;
		botLeftPoint = centerPoint;
		int actualLevel = n->level + 1;
		n->regions[0] = new node(topLeftPoint, botLeftPoint);
		n->regions[0]->level = actualLevel;
		n->regions[0]->isLeaf = true;
		topLeftPoint = new point(centerPoint->x, n->topLeftPoint->y);
		botLeftPoint = new point(n->botRightPoint->x, centerPoint->y);
		n->regions[1] = new node(topLeftPoint, botLeftPoint);
		n->regions[1]->level = actualLevel;
		n->regions[1]->isLeaf = true;
		topLeftPoint = new point(n->topLeftPoint->x, centerPoint->y);
		botLeftPoint = new point(centerPoint->x, n->botRightPoint->y);
		n->regions[2] = new node(topLeftPoint, botLeftPoint);
		n->regions[2]->level = actualLevel;
		n->regions[2]->isLeaf = true;
		n->regions[3] = new node(centerPoint, n->botRightPoint);
		n->regions[3]->level = actualLevel;
		n->regions[3]->isLeaf = true;
        n->isLeaf = 0;
        cout<<"Altura del arbol: "<<actualLevel+1<<endl;
		for (auto &p: n->points)
		{
			if (this->isInBox(p->x, p->y, n->regions[0])) {
				n->regions[0]->points.push_back(p);
			}
			else if (this->isInBox(p->x, p->y, n->regions[1])) {
				n->regions[1]->points.push_back(p);
				
			}
			else if (this->isInBox(p->x, p->y, n->regions[2]))
			{
				n->regions[2]->points.push_back(p);
			
			}
			else {
				n->regions[3]->points.push_back(p);
				
			}
		}
        n->points.clear();
        for(int i  = 0; i< 4;i++){
            if (n->regions[i]->points.size() > this->maxPointPerRegion)
            {
                n = n->regions[i];
                break;
            }
        }
		
	}
}

qtree::~qtree()
{
}
