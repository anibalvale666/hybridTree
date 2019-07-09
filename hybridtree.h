#ifndef HYBRIDTREE_H
#define HYBRIDTREE_H

#include "HTNode.h"
#include "HTNode.cpp"

#include <queue>          // std::priority_queue


//top is greater
class mycomparison
{
public:
	inline bool operator() (pair<Point<double>, double>& lhs, pair<Point<double>, double>& rhs) const
	{
		return (lhs.second < rhs.second);
	}
};

//top is smaller
class mycomparison2
{
public:
	inline bool operator() (pair<HTNode *, double>& lhs, pair<HTNode *, double>& rhs) const
	{
		return (lhs.second > rhs.second);
	}
};

using namespace std;

class hybridTree
{
public:

	int ht_dimensions;	// total number of dimensions
	int ht_M;	//number max of points in the leaf
	HTNode *ht_root;


	inline hybridTree(int,int,Point<double> e1,Point<double> e2);

	//funciones
	inline bool find(Point<double>, HTNode *&);
	inline bool insert(Point<double> x);

	inline int leaf_split_dimension(HTNode *);
	inline vector<Point<double> > leaf_split_position(HTNode *,int );
	inline bool leaf_split(HTNode *);
	
	inline void knn(Point<double>, vector<Point<double>> &);

	

	//funciones KNN
	inline double min_dist(Point<double> q, Point<double> a, Point<double> b);
	inline double distance(Point<double>, Point<double>);

	inline priority_queue<pair<Point<double>, double>, vector<pair<Point<double>, double> >, mycomparison> k_nearest(int k, Point<double> query_object);
	inline void k_nearest_traversal(priority_queue<pair<Point<double>, double>, vector<pair<Point<double>, double> >, mycomparison> &nearest_list, int k, Point<double> query_object, HTNode *p);

	inline double distance(Point<double>, HTNode *);
};

#endif
