#ifndef HTNODE_H
#define HTNODE_H
#include "rect.h"
#include "rect.cpp"
#include <vector>

using namespace std;

class HTNode
{
public:
	int htn_split_dimension; //split dimension
	double htn_lsp, htn_rsp; // left and right values 
	
	Point<double> htn_esq1, htn_esq2; // BR of node

	bool htn_leaf; // 1 = is leaf

	HTNode *htn_sons[2]; //0 left 1 right
	vector<Point<double>> htn_entries; // save the points if the node is leaf

	inline HTNode(Point<double>, Point<double>);

};


	 //to lo menore estan en esq1 y to lo mayore en esq2
#endif 
