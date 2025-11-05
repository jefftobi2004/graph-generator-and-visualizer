#pragma once


#include<fstream>
#include<list>
#include<stack>
#include<vector>
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

using namespace std;

class Crosssing // vom folosi aceasta clasa pentru cicluri hamiltoniene si euleriene
{
	int V;
	list<pair<int, int>>* adj;
	int* inDeg;
public:
	Crosssing(const char* file) // compiem datele de intrare in clasa
	{
		ifstream ifs(file);
		ifs >> V; //citesc din fisier numarul de varfuri
		adj = new list<pair<int, int>>[V];
		while (!ifs.eof()) {
			int u, v, w;
			ifs >> u >> v >> w;
			adj[u].push_back(make_pair(v, w));
		}
		inDeg = new int[V];
		for (int i = 0; i < V; i++)
			inDeg[i] = 0;

	}
	Crosssing(int v) //constructor 
	{
		V = v;
		adj = new list<pair<int, int>>[V];
		inDeg = new int[V];
	}
	//functia care determina daca graful este tare conex(strong connected)
	bool isSC()
	{
		bool* visited = new bool[V];
		for (int i = 0; i < V; i++)
			visited[i] = false;

		// Se parcurge graful prin metoda DFS incepand cu nodul 0.
		DFSUtil(0, visited);

		// Daca DFS nu viziteaza toate nodurile graful nu este tare conex.
		for (int i = 0; i < V; i++)
			if (visited[i] == false)
				return false;

		// PAsul 3: Se creaza graful transpus
		Crosssing gt = getTranspose();

		// Pasul 4: Se marcheaza toate nodurile nevizitate (pentru al doilea  DFS)

		for (int i = 0; i < V; i++)
			visited[i] = false;

		// Pasul 5: Se parcurege  graful transpus prin metoda DFS.
		// Nodul de start trebuie sa fie acelasi ca si la prima parcurgere
		gt.DFSUtil(0, visited);

		// Daca nu au fost vizitate toate nodurile atunci
		// return false
		for (int i = 0; i < V; i++)
			if (visited[i] == false)
				return false;

		return true;
	}
	// functia care verifica daca graful este eurlerian
	bool isEulerianCycle()
	{
		if (!isSC())
			return false;
		list<int>::iterator j;
		for (int i = 0; i < V; i++) {
			if (inDeg[i] != adj[i].size())
				return false;

			return true;
		}

	}
	// functia care parcurege graful in adancime
	void DFSUtil(int src, bool* visited)
	{
		visited[src] = true;

		// Recur for all the vertices adjacent to this vertex
		list<pair<int, int>> ::iterator i;
		for (i = adj[src].begin(); i != adj[src].end(); ++i)
			if (!visited[(*i).first])
				DFSUtil((*i).first, visited);
	}

	Crosssing getTranspose()
	{
		Crosssing tg = Crosssing(V);
		list<pair<int, int>> ::iterator j;
		for (int i = 0; i < V; i++)
			for (j = this->adj[i].begin(); j != this->adj[i].end(); ++j)
			{
				tg.adj[(*j).first].push_back(make_pair(i, (*j).second));
				inDeg[i]++;
			}
		return tg;
	}


	void HierHolzer(const char* file, graph_t* graph)
	{
		ofstream fout(file);
		// edge_count reprezinta numarul de arce care pleaca din fiecare varf
		int* edge_count = new int[V];

		for (int i = 0; i < V; i++)
		{

			edge_count[i] = adj[i].size();
		}


		// cream o stiva care va contine calea curenta



		// vectorul care memoreaza circuitul final
		vector<int> circuit;

		stack<int> curr_path;

		// incepem cu oricare varf
		curr_path.push(0);
		int curr_v = 0;

		while (!curr_path.empty())
		{

			if (edge_count[curr_v])
			{
				// Push the vertex
				curr_path.push(curr_v);

				// Find the next vertex using an edge
				int next_v = (adj[curr_v].back()).first;
				// and remove that edge
				edge_count[curr_v]--;
				adj[curr_v].pop_back();

				// Move to next vertex
				curr_v = next_v;
			}

			// back-track to find remaining circuit
			else
			{
				circuit.push_back(curr_v);

				// Back-tracking
				curr_v = curr_path.top();
				curr_path.pop();
			}
		}
		// we've got the circuit, now print it in reverse
		for (int i = circuit.size() - 1; i >= 1; i--) // VOM AFISA PATH EULERIAN SI VOM CONSTRUI UN NOU GRAF PENTRU A AFISAT IN PNG
		{
			char* nodename1 = (char*)(void*)Marshal::StringToHGlobalAnsi(circuit[i].ToString());
			char* nodename2 = (char*)(void*)Marshal::StringToHGlobalAnsi(circuit[i - 1].ToString());
			Agnode_t* Idnode1 = agnode(graph, nodename1, false);
			Agnode_t* Idnode2 = agnode(graph, nodename2, false);
			Agedge_t* agEdge = agedge(graph, Idnode1, Idnode2, NULL, false);
			char* f = (char*)(void*)Marshal::StringToHGlobalAnsi((circuit.size() - i).ToString());
			if(agEdge)
			agsafeset(agEdge, "label", f, "");
			fout << circuit[i];
			fout << " -> ";
		}
		fout << circuit[0];;
	}


	int conectare(int start, int catched) //DFS care verifica daca 2 noduri pot fi conectate
	{
		vector<bool> visited(V, false);
		stack<int> q;
	
		q.push(start);
		while (!q.empty()) {
			int u = q.top();
			q.pop();
			list<pair<int, int>> ::iterator it;
			if (!visited[u]) {
				for (it = adj[u].begin(); it != adj[u].end(); ++it)
					q.push((*it).first);
				if (catched == u)
					return 1;
				visited[u] = 1;
			}
		}
		return 0;
	}

	void maxineighbor(int start, int& count, int cross[]) // Numaram cate noduri sunt legate de nodul start direct sau indirect
	{
		// IN VECTORUL VOM PUNE TOTI VECINI DIRECTI SI INDIRECTI AI NOUDULUI START
		int c = 0;
		vector<bool> visited(V, false);
		stack<int> q;

		q.push(start);
		while (!q.empty()) {
			int u = q.top();
			q.pop();
			list<pair<int, int>>::iterator it;
			if (!visited[u]) {
				for (it = adj[u].begin(); it != adj[u].end(); ++it)
					q.push((*it).first);
				cross[c] = u;
				c++;
				visited[u] = true;
			}
		}
		count = c;
	}


	void hamiltonian(const char* file, graph_t* graph,int cross[]) // AFISAM PATH UL CARE TRECE PRIN TOATE NODURILE
	{
		ofstream fout(file);
		
		if (V == 1)
		{
			char* nodename = (char*)(void*)Marshal::StringToHGlobalAnsi(cross[0].ToString());
			Agnode_t* Idnode = agnode(graph, nodename, false);
			Agedge_t* agEdge = agedge(graph, Idnode, Idnode, NULL, false);
			char* f = (char*)(void*)Marshal::StringToHGlobalAnsi(V.ToString());
			agsafeset(agEdge, "label", f, "");
			agsafeset(agEdge, "color", "blue", "");
		}
		else
		{
			for (int i = 0; i < V - 1; i++)
			{
				char* nodename1 = (char*)(void*)Marshal::StringToHGlobalAnsi(cross[i].ToString());
				char* nodename2 = (char*)(void*)Marshal::StringToHGlobalAnsi(cross[i + 1].ToString());
				Agnode_t* Idnode1 = agnode(graph, nodename1, false);
				Agnode_t* Idnode2 = agnode(graph, nodename2, false);
				Agedge_t* agEdge = agedge(graph, Idnode1, Idnode2, NULL, false);
				char* f = (char*)(void*)Marshal::StringToHGlobalAnsi((i + 1).ToString());
				agsafeset(agEdge, "label", f, "");
				agsafeset(agEdge, "color", "blue", "");
				fout << cross[i];
				fout << " -> ";
			}
			fout << cross[V - 1];
		}
	}

	int verify(int cross[]) // VERIFICAM VECTORUL CROSS  DIN FUNCTIA maxineighbor PENTRU A VEDEA DACA IN PATH-UL EXISTA O
		// MUCHIE INTRE 2 VALORI CONSECUTIVE ALE PATH-ULUI
	{
	
		list<pair<int, int>> ::iterator j;
		for (int i = V-1; i >=1; i++)
			for (j = this->adj[cross[i-1]].begin(); j != this->adj[cross[i-1]].end(); ++j)
			{
				if ((*j).first != cross[i])
					return 0;
			}
		return 1;
	}

	void hamilton(int cross[]) // VOM EXTRAGE PRIMUL PATH CORECT(ADICA EXISTA O MUCHIE INTRE ORICARE 2 VALORI CONSECUTIVE ALE VECTORULUI CROSS)
	{

		int i, count;
		if (V == 1)
		{
			cross[0] = 0;
		}
		else
		for (i = 0; i < V; i++)
		{
			maxineighbor(i, count,cross);
			if (count == V)
				if (verify(cross))
					return;
		}
	}
};