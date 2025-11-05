#pragma once
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <graphviz/cdt.h>
#include <filesystem>
#include <string>
#include<queue>
#include<list>
#include<vector>
#include<fstream>
#include <cstring>


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Diagnostics;
using namespace System::Runtime::InteropServices;
using namespace std;



void DeletePngFiles(String^ directoryPath) // sterge png urile
{
	DirectoryInfo^ di = gcnew DirectoryInfo(directoryPath);
	cli::array<FileInfo^>^ files = di->GetFiles("*.png");
	for each (FileInfo ^ file in files)
	{
		File::Delete(file->FullName);
	}
}

void creare_Grafic(graph_t* graph, GVC_t* gvc,string curDir,const char *file) // construieste graficul pentru a afisat in format png
{
	//PARAMETRUL curDir reprezinta fiseierul unde se vor gasi datele de intrare

	String^ inputFilePath = gcnew String(curDir.c_str());
	
	if (System::IO::File::Exists(inputFilePath))
	{

		ifstream fin(curDir.c_str());
	
		ofstream fout(file);

		int numNodes;
		fin >> numNodes;
		for (int i = 0; i < numNodes; i++) {
			// Create a node with a label equal to its ID
			char* nodeId = (char*)(void*)Marshal::StringToHGlobalAnsi(i.ToString());
			agnode(graph, nodeId, true);
		}
		int node1, node2, label;
		while (!fin.eof())
		{

			fin >> node1 >> node2 >> label;
			fout << node1 << " " << node2<<" "<<label << endl;

				char* nodeId1 = (char*)(void*)Marshal::StringToHGlobalAnsi(node1.ToString());
				char* nodeId2 = (char*)(void*)Marshal::StringToHGlobalAnsi(node2.ToString());
				Agnode_t* agNode1 = agnode(graph, nodeId1, true);
				Agnode_t* agNode2 = agnode(graph, nodeId2, true);
				if (agnnodes(graph) > numNodes)
				{
					String^ message = String::Format("Nodurile trebuie sa fie intre 0 si {0}", numNodes - 1);
					MessageBox::Show(message, "Error");
					return;
				}
					Agedge_t* agEdge = agedge(graph, agNode1, agNode2, NULL, true);
					char* labelStr = (char*)(void*)Marshal::StringToHGlobalAnsi(label.ToString());
					if (agEdge)
						agsafeset(agEdge, (char*)"label", labelStr, (char*)"");
		}
	}

	else
	{
		MessageBox::Show("Nu a fost introdus niciun fisier txt", "error");
	}
}




class Graph
{
	int V; // numar de varfuri
	int E; // nr muchii
	list<pair<int, int>>* adjList;
	vector<vector<int>> adjMat;
	vector<vector<int>> incMat;
	vector<int> deg_min;
	vector<int> deg_plus;
public:
	Graph(const char* fis)
	{
		ifstream ifs(fis);
		E = 0;
		int u; //nodul sursa
		int v; //nodul destinatie
		int w; // greutatea muchiei
		ifs >> V; //citim din fisier numarul de varfuri
		// alocam memorie pentru adjList
		adjList = new list<pair<int, int>>[V];
		while (!ifs.eof()) {
			ifs >> u >> v >> w;
			adjList[u].push_back(make_pair(v, w));
			E++;
		}
		//initializam cu 0 matricea de adiacenta
		for (int i = 0; i < V; i++) {
			vector<int> v1;
			for (int j = 0; j < V; j++)
				v1.push_back(0);
			adjMat.push_back(v1);
		}
		// initializam cu 0 matricea de incidenta
		for (int i = 0; i < V; i++) {
			vector<int> v1;
			for (int j = 0; j < E; j++)
				v1.push_back(0);
			incMat.push_back(v1);
		}


	}
	

	void adjList_to_adjMat()
	{
		list<pair<int, int>>::iterator it;
		for (int v = 0; v < V; v++)
			for (it = adjList[v].begin(); it != adjList[v].end(); ++it)
				adjMat[v][(*it).first] = (*it).second;
	}

	void calculate_degrees()
	{
		for (int i = 0; i < V; i++) {
			deg_plus.push_back(adjList[i].size());
			deg_min.push_back(0); //initializam cu 0  gradele de intrare
		}

		list<pair<int, int>>::iterator it;
		for (int v = 0; v < V; v++)
		{
			for (it = adjList[v].begin(); it != adjList[v].end(); ++it)
				deg_min[(*it).first]++;

		}
	}

	void adjList_to_incMat()
	{
		list<pair<int, int>>::iterator it;
		int k = 0;
		for (int v = 0; v < V; v++)

			for (it = adjList[v].begin(); it != adjList[v].end(); ++it)
			{
				incMat[v][k] = 1;
				incMat[(*it).first][k] = -1;
				k++;
			}

	}

	 
	int isHamiltonCycle() // TEOREMA LUI DIRAC
	{
		calculate_degrees();
		list<pair<int, int>>::iterator it;
		for (int i = 0; i < V; i++)
			if (deg_min[i] + deg_plus[i] < V / 2)
				return 0;
		return 1;
	}


	void printGraph(const char* file)
	{
		
			ofstream fout(file);
			adjList_to_adjMat();
			calculate_degrees();
			adjList_to_incMat();
			list<pair<int, int>>::iterator it;
			for (int v = 0; v < V; v++)
			{
				fout << v << " : ";
				for (it = adjList[v].begin(); it != adjList[v].end(); ++it)
					fout << "(" << (*it).first << "," << (*it).second << ")";
				fout << "\n";
			}
			fout << "\n";

			fout << "matricea de adiacenta:" << "\n";
			for (int i = 0; i < adjMat.size(); i++) {
				for (int j = 0; j < adjMat[i].size(); j++)
					fout << adjMat[i][j] << "  ";
				fout << "\n";
			}
			fout << "\n";

			fout << "Degree minus:" << "\n";
			for (int i = 0; i < deg_min.size() - 1; i++)
				fout << deg_min[i] << ", ";

			fout << deg_min[deg_min.size() - 1];
			fout << "\n";


			fout << "Degree plus:" << "\n";
			for (int i = 0; i < deg_plus.size() - 1; i++)
				fout << deg_plus[i] << ", ";

			fout << deg_plus[deg_plus.size() - 1];
			fout << "\n";

			fout << "\n" << "matricea de incidenta" << "\n";
			for (int v = 0; v < V; v++) {
				for (int e = 0; e < V; e++)
					fout << incMat[v][e] << "    ";
				fout << "\n";
			}

		
	}

	void printGraph_adjmat(const char* fil)
	{
		ofstream f(fil);
		adjList_to_adjMat();
		f << V << "\n";
		list<pair<int, int>>::iterator it;

		for (int i = 0; i < adjMat.size() - 1; i++) {
			for (int j = 0; j < adjMat[i].size(); j++)
				f << adjMat[i][j] << "  ";
			f << "\n";
		}
		int i = adjMat.size() - 1;
		for (int j = 0; j < adjMat[i].size(); j++)
			f << adjMat[i][j] << "  ";
	}
};

class Dijsktra {
	int V; // nr de varfuri
	list<pair<int, int>>* adj;
public:
	Dijsktra(const char* file) {
		ifstream ifs(file);
		ifs >> V; //citesc din fisier numarul de varfuri
		adj = new list<pair<int, int>>[V];
		while (!ifs.eof()) {
			int u, v, w;
			ifs >> u >> v >> w;
			adj[u].push_back(make_pair(v, w));
		}
	}

	//O metoda prin care cu ajutorul parcurgerii BFS (in latime) verificam daca doua noduri sunt adiacente
	int conectare(int start, int catched)
	{
		vector<bool> visited(V, false);
		queue<int> q;

		q.push(start);
		while (!q.empty()) {
			int u = q.front();
		
			list<pair<int, int>> ::iterator it;
			if (!visited[u]) {
				for (it = adj[u].begin(); it != adj[u].end(); ++it)
					q.push((*it).first);
				if (catched == u)
					return 1;
				visited[u] = 1;
			}
			q.pop();
		}
		return 0;
	}

	//Afiseaza intr-un fisier lista de adiacenta a fiecarui nod
	void print(const char* file) {
		ofstream fout(file);
		for (int i = 0; i < V; i++)
		{
			fout << i << "->";
			list<pair<int, int>> ::iterator j;
			for (j = adj[i].begin(); j != adj[i].end(); ++j)
				fout << "(" << (*j).first << "," << (*j).second << ")";
			fout << "\n";
		}
	}

	//Aplica algoritmul lui Djikstra
	void shortestPath(int src, const char* file) {
		ofstream fout(file);
		//initializam vectorul distantelor cu infinit
		vector<int> dist(V, INT_MAX);
		//initializam vectorul de parintii (nodul precedent al altui nod)
		vector<int> parent(V);
		for (int i = 0; i < V; i++)
			parent[i] = i;
		//cream coada de prioritati unde se vor aduga nodurile neprocesate 
		priority_queue< pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>>> pq;

		pq.push(make_pair(0, src));
		dist[src] = 0;
		while (!pq.empty()) {
			int u, v;// nodul sursa, nodul destinatie 
			int w; //ponderea muchiei [uv]
			u = pq.top().second;
			w = pq.top().first;
			pq.pop();
			list<pair<int, int>> ::iterator i;
			for (i = adj[u].begin(); i != adj[u].end(); ++i) {
				v = (*i).first;
				w = (*i).second;
				if (dist[u] + w < dist[v])
				{
					dist[v] = dist[u] + w;
					pq.push(make_pair(dist[v], v));
					parent[v] = u;
				}

			}


		}
		
		for (int i = 0; i < V-1; i++)
			if(dist[i]!=INT_MAX)
			fout << dist[i] << ",";
		if (dist[V-1] != INT_MAX)
		fout << dist[V - 1] << "\n";


		string curDir(__FILE__);
		curDir = curDir.substr(0, curDir.find_last_of("\\/")) + "\\data_set\\input.txt";

		string vef(__FILE__);
		vef = vef.substr(0, vef.find_last_of("\\/")) + "\\data_set\\vef.txt";
		const char* ret = vef.c_str();
		int* t = new int[V];

		fout << "\n" << "PATHS:" << "\n"; 
		for (int i = 0; i < V; i++) {
			int k = 0;
			if(conectare(src,i)) // AFISAM PATH-URILE DOAR DACA STIM CA EXISTA O CONEXIUNE INTRE NODUL SURSA SI NODUL CURENT I
			{
				showPath(parent, i, fout, t, k);
				graph_t* g;
				GVC_t* gvc;
				Agdesc_t desc;
				desc.directed = true;
				g = agopen("graph", desc, NULL);
				gvc = gvContext();
				creare_Grafic(g, gvc, curDir,ret);
				if (k != 0)
				for (int j = 0; j < k - 1; j++) // COLORAM PATH-UL CU ALBASTRU PENTRU A IESI IN EVIDENTA
				{
					char* nodename1 = (char*)(void*)Marshal::StringToHGlobalAnsi(t[j].ToString());
					char* nodename2 = (char*)(void*)Marshal::StringToHGlobalAnsi(t[j + 1].ToString());
					Agnode_t* Idnode1 = agnode(g, nodename1, false);
					Agnode_t* Idnode2 = agnode(g, nodename2, false);
					Agedge_t* agEdge = agedge(g, Idnode1, Idnode2, NULL, false);
					agsafeset(agEdge, "color", "blue", "");
				}

				gvLayout(gvc, g, "dot");
				gvRenderFilename(gvc, g, "png", ("data_set\\Dijkstra\\Djikstra-" + to_string(i) + ".png").c_str());
				gvFreeContext(gvc);
				agclose(g);
				fout << "\n";
			}
		}

	}

	void showPath(vector<int> parent, int v, ofstream& fout, int t[], int& k) {

		if (v != parent[v])
		{
			showPath(parent, parent[v], fout, t, k);
		}
		t[k] = v;
		k++;
		fout << v << "->";
	}
};



class Max_Flow {
	int V;
	int** graph;
	int counter;
public:
	Max_Flow(const char* fis) {
		ifstream is(fis);
		counter = 0;
		is >> V;
		graph = new int* [V];
		for (int i = 0; i < V; i++)
			graph[i] = new int[V];
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
			{
				is >> graph[i][j];
				if (graph[i][j])
					counter++;
			}
	}
	

	bool BFS(int** rGraph, int s, int t, int* parent) {
		bool* visited = new bool[V];
		for (int i = 0; i < V; i++)
			visited[i] = false;
		queue<int> q;

		q.push(s);
		visited[s] = true;
		parent[s] = -1;

		while (!q.empty()) {
			int u = q.front();
			q.pop();

			for (int v = 0; v < V; v++)
				if (!visited[v] && rGraph[u][v] > 0) {
					if (v == t) {
						parent[v] = u;
						return true;
					}
					q.push(v);
					visited[v] = true;
					parent[v] = u;

				}
		}
		return false;

	}

	void print(const char* file)
	{
		ofstream fout(file);
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++)
				fout << graph[i][j] << "  ";
			fout << "\n";
		}
	}

	void FordFuckerson(int s, int t, const char* file)
	{
		ofstream fout(file);
		int u, v;
		int** rGraph = new int* [V];
		for (int i = 0; i < V; i++)
			rGraph[i] = new int[V];
		int** fGraph = new int* [V];
		for (int i = 0; i < V; i++)
			fGraph[i] = new int[V];

		int maxFlow = 0;
		int* parent = new int[V];


		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++) {
				rGraph[i][j] = graph[i][j];
				fGraph[i][j] = 0;
			}

		while (BFS(rGraph, s, t, parent)) {
			int pathFlow = INT_MAX;

			for (v = t; v != s; v = parent[v]) {
				u = parent[v];
				pathFlow = min(pathFlow, rGraph[u][v]);
			}
			for (v = t; v != s; v = parent[v]) {
				u = parent[v];
				rGraph[u][v] -= pathFlow;
				rGraph[v][u] += pathFlow;
				fGraph[u][v] += pathFlow;
			}
			maxFlow += pathFlow;
		}
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++)
				fout << fGraph[i][j] << "  ";
			fout << "\n";
		}
		fout<<"Fluxul maxim este: " << maxFlow;

	}

	void print_transform_adjMat_to_adjList(const char* file_mat_init,const char*file_mat_ford,const char* destination) 
	{
		int x, y, z = 0;
		ifstream fin(file_mat_init);
		ifstream f(file_mat_ford);
		ofstream fout(destination);
		fin >> x;
		fout << V << "\n";
		for (int i = 0; i < V ; i++)
			for (int j = 0; j < V; j++)
			{
				fin >> x;
				f >> y;
				if (x)
					if (z <= counter - 2)
						if (y)
						{
							fout << i << " " << j << " " << y << "\n";
							z++;
						}
						else
						{
							fout << i << " " << j << " " << 0 << "\n";
							z++;
						}
					else
						if (y)
						{
							fout << i << " " << j << " " << y;
							z++;
						}
						else
						{
							fout << i << " " << j << " " << 0;
							z++;
						}
					
			}
	}
};

















