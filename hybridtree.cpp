#include "hybridtree.h"
#include <stdlib.h>
#include <algorithm> 
#include <math.h>

hybridTree::hybridTree(int n_dimensions,int n_max, Point<double> e1, Point<double> e2)
{
	ht_dimensions = n_dimensions;
	ht_M = n_max;

	Point<double> esq1, esq2;

	for (int i = 0; i < e1.p_coords.size(); i++)
	{
		if (e1.p_coords[i] < e2.p_coords[i])
		{
			esq1.p_coords.push_back(e1.p_coords[i]);
			esq2.p_coords.push_back(e2.p_coords[i]);
		}
		else
		{
			esq1.p_coords.push_back(e2.p_coords[i]);
			esq2.p_coords.push_back(e1.p_coords[i]);
		}
	}

	ht_root = new HTNode(esq1,esq2);
}


bool hybridTree::find(Point<double> x, HTNode * &p)
{
	for (p = ht_root; p->htn_leaf == false; p = p->htn_sons[x.p_coords[p->htn_split_dimension] > p->htn_rsp]);

	for (int i = 0; i < p->htn_entries.size(); i++)
	{
		if (p->htn_entries[i].p_coords == x.p_coords)
			return 1;
	}
	return 0;

}

bool hybridTree::insert(Point<double> x)
{
	HTNode *p;
	
	if(find(x, p)) return 0;
	
	p->htn_entries.push_back(x);

	if (p->htn_entries.size() >= ht_M)
	{
		leaf_split(p);
	}
	return 1;
}


//-----------------------leaf split and functions-----------------------------//
int hybridTree::leaf_split_dimension(HTNode *p)
{
	//calculamo el lado mas extenso
	int index_return_max=0;
	double max_extend_segment= abs(p->htn_esq1.p_coords[0] - p->htn_esq2.p_coords[0]);
	double aux_extend_segment;
	for (int i = 1; i < ht_dimensions; i++)
	{
		aux_extend_segment = abs(p->htn_esq2.p_coords[i] - p->htn_esq1.p_coords[i]);
		if (aux_extend_segment > max_extend_segment)
		{
			max_extend_segment = aux_extend_segment;
			index_return_max = i;
		}
	}
	return index_return_max;
}


//me devuelve la posicion de la media y el vector ordenado lsito pa partir
vector<Point<double> > hybridTree::leaf_split_position(HTNode *p, int split_dimension)
{
	//calculamo la media
	vector<Point<double >> vector_points_sorted = p->htn_entries;


	sort(vector_points_sorted.begin(), vector_points_sorted.end(), [split_dimension](Point<double> a, Point<double> b) 
	{return (a.p_coords[split_dimension] < b.p_coords[split_dimension]); });
	return vector_points_sorted;
}


bool hybridTree::leaf_split(HTNode *p)
{

	
	int split_dimension;
	Point<double> esq1, esq2;
	vector<Point<double >> vector_entries_sorted;

	//inicializamos
	split_dimension = leaf_split_dimension(p);
	vector_entries_sorted = p->htn_entries;
	vector_entries_sorted = leaf_split_position(p, split_dimension);
	

	//volvemos al nodo hoja padre
	p->htn_entries.clear();
	p->htn_leaf = false;
	//inicializamos valores del padre
	p->htn_split_dimension = split_dimension;
	p->htn_lsp = p->htn_rsp = vector_entries_sorted[vector_entries_sorted.size() / 2].p_coords[split_dimension];
	//creamos los dos hijos

	esq1 = p->htn_esq1;
	esq2 = p->htn_esq2;
	esq2.p_coords[split_dimension] = p->htn_lsp;
	HTNode *l = new HTNode(esq1,esq2);
	
	esq1 = p->htn_esq1;
	esq2 = p->htn_esq2;
	esq1.p_coords[split_dimension] = p->htn_lsp;
	HTNode *r = new HTNode(esq1,esq2);

	l->htn_entries = vector<Point<double>> (vector_entries_sorted.begin(), vector_entries_sorted.begin() + (vector_entries_sorted.size() / 2));
	r->htn_entries = vector<Point<double>> (vector_entries_sorted.begin() + (vector_entries_sorted.size() / 2)+1, vector_entries_sorted.end() );
	
	p->htn_sons[0] = l;
	p->htn_sons[1] = r;
	return true;
}



//-----------------------------------knn---------------------------------------------//
//-----------------------------------------------------------------------------------//

/*
inline double dot(Point<double> a, Point<double> b)
{
	double sum = 0;
	for (int i = 0; i < a.p_coords.size(); i++)
	{
		sum += a.p_coords[i] * b.p_coords[i];
	}
	return sum;
}


//point a and b is a points of line.
//the function dettermine the distance from p to line (a,b)
double hybridTree::min_dist(Point<double> p, Point<double> a, Point<double> b)
{
	Point<double> pa,ba,res;
	double t, d;

	d = 0;
	for (int i = 0; i < p.p_coords.size(); i++)
	{
		pa.p_coords.push_back(p.p_coords[i] - a.p_coords[i]);
		ba.p_coords.push_back(b.p_coords[i] - a.p_coords[i]);
	}

	t = dot(pa, ba) / dot(ba, ba);

	for (int i = 0; i < p.p_coords.size(); i++)
	{
		res.p_coords.push_back(pa.p_coords[i] - ba.p_coords[i]*t);
		d += pow(res.p_coords[i], 2);
	}

	
	return sqrt(d);
}*/


//euclidean distance
double hybridTree::distance(Point<double> a, Point<double> b) 
{
	double sum = 0;
	for (int i = 0; i < a.p_coords.size(); i++)
	{
		sum += pow(b.p_coords[i] - a.p_coords[i], 2);
	}
	return sqrt(sum);
}


priority_queue<pair<Point<double>, double>, vector<pair<Point<double>, double> >, mycomparison> hybridTree::k_nearest(int k, Point<double> query_object)
{
	priority_queue<pair<Point<double>, double>, vector<pair<Point<double>, double> >, mycomparison> nearest_list;
	//for (int i = 0; i < k; i++)q
		nearest_list.push(make_pair(Point<double>(), 10000000000));

	k_nearest_traversal(nearest_list,k,query_object,ht_root);
	return nearest_list;

}

void hybridTree::k_nearest_traversal(priority_queue<pair<Point<double>, double>, vector<pair<Point<double>, double> >, mycomparison> &nearest_list, int k, Point<double> query_object, HTNode *p)
{
	if (p->htn_leaf)
	{
		for (int i = 0; i < p->htn_entries.size(); i++)
		{
			double aux_dist = distance(query_object, p->htn_entries[i]); 
			if (aux_dist < nearest_list.top().second)
			{
				if (nearest_list.size() == k)
				{
					nearest_list.pop();
				}
				nearest_list.push(make_pair(p->htn_entries[i],aux_dist));
			}
		}
	}
	else
	{
		priority_queue<pair<HTNode *, double>, vector<pair<HTNode *, double> >, mycomparison2> active_branch_list;
		double dist_1 = distance(query_object, p->htn_sons[0]);
		double dist_2 = distance(query_object, p->htn_sons[1]);

		active_branch_list.push(make_pair(p->htn_sons[0], dist_1));
		active_branch_list.push(make_pair(p->htn_sons[1], dist_2));
		
		while(!active_branch_list.empty())
		{
			if (active_branch_list.top().second < nearest_list.top().second)
			{
				k_nearest_traversal(nearest_list, k, query_object, active_branch_list.top().first);
			}
			else
			{
				break;
			}
			active_branch_list.pop();
		}
	
	}
}


double hybridTree::distance(Point<double> q, HTNode *p)
{
	Point<double> center_point;
	for (int i = 0; i < ht_dimensions; i++)
	{
		center_point.p_coords.push_back((p->htn_esq2.p_coords[i] + p->htn_esq1.p_coords[i])/2);
	}
	return distance(q, center_point);
}