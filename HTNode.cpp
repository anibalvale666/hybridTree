#include "HTNode.h"



HTNode::HTNode(Point<double> esq1, Point<double> esq2)
{
	htn_sons[0] = htn_sons[1] = NULL;
	htn_leaf = 1;
	htn_esq1 = esq1;
	htn_esq2 = esq2;

}

