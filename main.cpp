#include <iostream>
#include <fstream>
#include <string>
#include <ctime> 
#include <chrono>

#include <stdlib.h>    
#include <time.h>

#include "hybridtree.h"
#include "hybridtree.cpp"
#define DATASET_DIM 91

using namespace std;

//global var
hybridTree *tree;
int cont;

void gg2(vector<Point<double>> &d1)
{
	ifstream fe("YearPredictionMSD2.txt");
	fe >> cont;
	vector<double> d91(DATASET_DIM, 0);
	for (int i = 0; i < cont; i++)
	{
		for (int k = 0; k < DATASET_DIM; k++)
		{
			fe >> d91[k];
			d91[k] /= 1000;

		}

		Point<double> point_insert;
		point_insert.p_coords = d91;
		d1.push_back(point_insert);
		//tree->insert(point_insert);
		//cout << i << endl;
		//cout << i << endl;
	}
		/*for (int k = 0; k < DATASET_DIM; k++)
		{
			cout << d91[k] << ", ";
			
		}
		cout << endl;*/
	fe.close();

}



void t1()
{
	ifstream fe("YearPredictionMSD.txt");
	ofstream fs("YearPredictionMSD2.txt");
	string cadena;
	int cont = 0;
	bool is_p = true;
	while (!fe.eof())
	{
		is_p = true;
		fe >> cadena;

		for (int i = 0; i < cadena.size(); i++)
		{
			if (cadena[i] == ',')
				cadena[i] = ' ';
		}
		fs << cadena << "\n" ;
	}
	fe.close();
	fs.close();
}

//clase utilizada en la cola de prioridad de dijkstra




int main()
{

	Point<double> esq1, esq2;
	double r = 100;
	for (int i = 0; i < DATASET_DIM; i++)
	{
		esq1.p_coords.push_back(r*(-1));
		esq2.p_coords.push_back(r);
	}


	tree = new hybridTree (DATASET_DIM, 100, esq1, esq2);
	

	vector<Point<double>> vec_points;
	gg2(vec_points);

	//tiempos para la construccion
	cout << "cantidad de puntos " << vec_points.size() << endl;
	auto start = std::chrono::system_clock::now();

	for(int i=0;i< vec_points.size();i++)
		tree->insert(vec_points[i]);

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << " segundos : " << diff.count() << " s\n";

	
	//tiempos para el knn
	Point<double> query_point = vec_points[rand()%500000];
	priority_queue<pair<Point<double>, double>, vector<pair<Point<double>, double> >, mycomparison> knn_resp;
	auto start1 = std::chrono::system_clock::now();

	knn_resp = tree->k_nearest(1000, query_point);

	auto end1 = std::chrono::system_clock::now();
	std::chrono::duration<double> diff1 = end1 - start1;
	cout << " segundos : " << diff1.count() << " s\n";
	cout << "tam " << knn_resp.size() << endl;

	//imprime los knn mas cercanos
	//cout << " query_point: " << query_point << "\n\n\n";
	/*while (!knn_resp.empty())
	{
		cout << knn_resp.top().first << "\n\n\n" << " with distance: " << knn_resp.top().second << endl;
		knn_resp.pop();
	}*/
	
	


	system("pause");

	return 0;
}