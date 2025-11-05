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


namespace GRAPHS {

	


	#include "classes.h"
	#include "second_classes.h"
	


	/// <summary>
	/// Summary for Grafuri
	/// </summary>
	public ref class Grafuri : public System::Windows::Forms::Form
	{
	public:
		Grafuri(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Grafuri()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ input_data;
	protected:
	private: System::Windows::Forms::Button^ output_data;
	private: System::Windows::Forms::Button^ output_graph;
	private: System::Windows::Forms::Button^ dijkstra;
	private: System::Windows::Forms::TextBox^ write_node;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ start_node;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ end_node;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ maximum_flow;
	private: System::Windows::Forms::Button^ connectivity;
	private: System::Windows::Forms::Button^ hamiltomian;
	private: System::Windows::Forms::Button^ eulerian;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->input_data = (gcnew System::Windows::Forms::Button());
			this->output_data = (gcnew System::Windows::Forms::Button());
			this->output_graph = (gcnew System::Windows::Forms::Button());
			this->dijkstra = (gcnew System::Windows::Forms::Button());
			this->write_node = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->start_node = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->end_node = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->maximum_flow = (gcnew System::Windows::Forms::Button());
			this->connectivity = (gcnew System::Windows::Forms::Button());
			this->hamiltomian = (gcnew System::Windows::Forms::Button());
			this->eulerian = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// input_data
			// 
			this->input_data->Location = System::Drawing::Point(12, 37);
			this->input_data->Name = L"input_data";
			this->input_data->Size = System::Drawing::Size(174, 71);
			this->input_data->TabIndex = 0;
			this->input_data->Text = L"Chose a txt file";
			this->input_data->UseVisualStyleBackColor = true;
			this->input_data->Click += gcnew System::EventHandler(this, &Grafuri::input_data_Click);
			// 
			// output_data
			// 
			this->output_data->Location = System::Drawing::Point(192, 37);
			this->output_data->Name = L"output_data";
			this->output_data->Size = System::Drawing::Size(174, 71);
			this->output_data->TabIndex = 1;
			this->output_data->Text = L"Representation of the graph";
			this->output_data->UseVisualStyleBackColor = true;
			this->output_data->Click += gcnew System::EventHandler(this, &Grafuri::output_data_Click);
			// 
			// output_graph
			// 
			this->output_graph->Location = System::Drawing::Point(98, 114);
			this->output_graph->Name = L"output_graph";
			this->output_graph->Size = System::Drawing::Size(174, 71);
			this->output_graph->TabIndex = 2;
			this->output_graph->Text = L"Display Graph";
			this->output_graph->UseVisualStyleBackColor = true;
			this->output_graph->Click += gcnew System::EventHandler(this, &Grafuri::output_graph_Click);
			// 
			// dijkstra
			// 
			this->dijkstra->Location = System::Drawing::Point(12, 289);
			this->dijkstra->Name = L"dijkstra";
			this->dijkstra->Size = System::Drawing::Size(174, 71);
			this->dijkstra->TabIndex = 3;
			this->dijkstra->Text = L"Apply Dijkstra\'s algorithm for a given node";
			this->dijkstra->UseVisualStyleBackColor = true;
			this->dijkstra->Click += gcnew System::EventHandler(this, &Grafuri::dijkstra_Click);
			// 
			// write_node
			// 
			this->write_node->Font = (gcnew System::Drawing::Font(L"Arial", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->write_node->Location = System::Drawing::Point(220, 318);
			this->write_node->Name = L"write_node";
			this->write_node->Size = System::Drawing::Size(137, 42);
			this->write_node->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(216, 291);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(137, 24);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Write a node:";
			// 
			// start_node
			// 
			this->start_node->Font = (gcnew System::Drawing::Font(L"Arial", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->start_node->Location = System::Drawing::Point(220, 397);
			this->start_node->Name = L"start_node";
			this->start_node->Size = System::Drawing::Size(137, 42);
			this->start_node->TabIndex = 6;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(216, 373);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(118, 24);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Start Node:";
			// 
			// end_node
			// 
			this->end_node->Font = (gcnew System::Drawing::Font(L"Arial", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->end_node->Location = System::Drawing::Point(220, 478);
			this->end_node->Name = L"end_node";
			this->end_node->Size = System::Drawing::Size(137, 42);
			this->end_node->TabIndex = 8;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(216, 451);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(109, 24);
			this->label3->TabIndex = 9;
			this->label3->Text = L"End Node:";
			// 
			// maximum_flow
			// 
			this->maximum_flow->Location = System::Drawing::Point(12, 373);
			this->maximum_flow->Name = L"maximum_flow";
			this->maximum_flow->Size = System::Drawing::Size(174, 71);
			this->maximum_flow->TabIndex = 10;
			this->maximum_flow->Text = L"Maximum Flow between the Start Node and End Node";
			this->maximum_flow->UseVisualStyleBackColor = true;
			this->maximum_flow->Click += gcnew System::EventHandler(this, &Grafuri::maximum_flow_Click);
			// 
			// connectivity
			// 
			this->connectivity->Location = System::Drawing::Point(12, 451);
			this->connectivity->Name = L"connectivity";
			this->connectivity->Size = System::Drawing::Size(174, 71);
			this->connectivity->TabIndex = 11;
			this->connectivity->Text = L"Is Start Node connected to End Node\?";
			this->connectivity->UseVisualStyleBackColor = true;
			this->connectivity->Click += gcnew System::EventHandler(this, &Grafuri::connectivity_Click);
			// 
			// hamiltomian
			// 
			this->hamiltomian->Location = System::Drawing::Point(12, 200);
			this->hamiltomian->Name = L"hamiltomian";
			this->hamiltomian->Size = System::Drawing::Size(174, 71);
			this->hamiltomian->TabIndex = 12;
			this->hamiltomian->Text = L"Show if the given graph has a Hamiltonian path";
			this->hamiltomian->UseVisualStyleBackColor = true;
			this->hamiltomian->Click += gcnew System::EventHandler(this, &Grafuri::hamiltomian_Click);
			// 
			// eulerian
			// 
			this->eulerian->Location = System::Drawing::Point(192, 200);
			this->eulerian->Name = L"eulerian";
			this->eulerian->Size = System::Drawing::Size(174, 71);
			this->eulerian->TabIndex = 13;
			this->eulerian->Text = L"Show if the given graph has a Eulerian path";
			this->eulerian->UseVisualStyleBackColor = true;
			this->eulerian->Click += gcnew System::EventHandler(this, &Grafuri::eulerian_Click);
			// 
			// Grafuri
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(375, 536);
			this->Controls->Add(this->eulerian);
			this->Controls->Add(this->hamiltomian);
			this->Controls->Add(this->connectivity);
			this->Controls->Add(this->maximum_flow);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->end_node);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->start_node);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->write_node);
			this->Controls->Add(this->dijkstra);
			this->Controls->Add(this->output_graph);
			this->Controls->Add(this->output_data);
			this->Controls->Add(this->input_data);
			this->Name = L"Grafuri";
			this->Text = L"Grafuri";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void input_data_Click(System::Object^ sender, System::EventArgs^ e) {
	string dataDir(__FILE__);
		dataDir = dataDir.substr(0, dataDir.find_last_of("\\/")) + "\\data_set";
		
		String^ dataDirString = gcnew String(dataDir.c_str());


		// Check if data_set directory exists, and create it if it doesn't
		if (!System::IO::Directory::Exists(dataDirString))
		{
			System::IO::Directory::CreateDirectory(dataDirString);
		}



		// Check if input.txt exists in data_set directory, and delete it if it does
		String^ inputFilePath = dataDirString + "\\input.txt";
		if (System::IO::File::Exists(inputFilePath))
		{
			try {
				System::IO::File::Delete(inputFilePath);
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message);
				return;
			}
		}

		// Open file dialog to select text file
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		openFileDialog1->Filter = "Text Files|*.txt";
		openFileDialog1->Title = "Select a text file";

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ filePath = openFileDialog1->FileName;
			String^ fileName = Path::GetFileName(filePath);

			try {
				// Copy the selected file to the data_set directory as input.txt
				System::IO::File::Copy(filePath, inputFilePath);
				MessageBox::Show("File copied successfully!");
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message);
			}
		}

		string Dir(__FILE__);
		Dir = Dir.substr(0, Dir.find_last_of("\\/")) + "\\data_set\\vef.txt";
		String^ inputFile = gcnew String(Dir.c_str());
		if (!System::IO::File::Exists(inputFile))
		{
			try {
				System::IO::File::Create(inputFile);
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message);
				return;
			}
		}
	}



private: System::Void output_data_Click(System::Object^ sender, System::EventArgs^ e) {

	string curDir(__FILE__);
	curDir = curDir.substr(0, curDir.find_last_of("\\/")) + "\\data_set\\input.txt";

	const char* file = curDir.c_str();
	GRAPHS::Graph obiect(file);

	string dataDir(__FILE__);
	dataDir = dataDir.substr(0, dataDir.find_last_of("\\/")) + "\\data_set\\output.txt";

	String^ inputFilePath = gcnew String(dataDir.c_str());
	if (!System::IO::File::Exists(inputFilePath))
	{
		try {
			System::IO::File::Create(inputFilePath);
		}
		catch (Exception^ ex) {
			MessageBox::Show(ex->Message);
			return;
		}
	}
	const char* fil = dataDir.c_str();
	obiect.printGraph(fil);
	//System::Diagnostics::Process::Start("data_set\\output.txt");

}



private: System::Void hamiltomian_Click(System::Object^ sender, System::EventArgs^ e) {
	string curDir(__FILE__);
	curDir = curDir.substr(0, curDir.find_last_of("\\/")) + "\\data_set\\input.txt";
	const char* fisier = curDir.c_str();
	GRAPHS::Graph obiect(fisier);
	 
	if (obiect.isHamiltonCycle())
	{
		graph_t* graph;
		GVC_t* gvc;
		Agdesc_t desc;
		desc.directed = true;
		graph = agopen("graph", desc, NULL);
		gvc = gvContext();

		string vef(__FILE__);
		vef = vef.substr(0, vef.find_last_of("\\/")) + "\\data_set\\vef.txt";
		const char* fil = vef.c_str();

		GRAPHS::creare_Grafic(graph, gvc, curDir,fil);
		GRAPHS::Crosssing obj(fisier);
		string dataDir(__FILE__);
		dataDir = dataDir.substr(0, dataDir.find_last_of("\\/")) + "\\data_set\\Hamiltonian";

		String^ dataDirString = gcnew String(dataDir.c_str());


		if (!System::IO::Directory::Exists(dataDirString))
		{
			System::IO::Directory::CreateDirectory(dataDirString);
		}

		string Dir(__FILE__);
		Dir = Dir.substr(0, Dir.find_last_of("\\/")) + "\\data_set\\Hamiltonian\\Hamiltonian.txt";
		const char* file = Dir.c_str();
		int V;
		ifstream fin(fisier);
		fin >> V;
		
	    
	     int *cross=new int[V];
		 
		obj.hamilton(cross);
	          
		obj.hamiltonian(file, graph,cross);

		for (Agnode_t* node = agfstnode(graph); node != nullptr; node = agnxtnode(graph, node))
		{
			for (Agedge_t* edge = agfstout(graph, node); edge != nullptr; edge = agnxtout(graph, edge))
			{
				if (strcmp(agget(edge, "color"), "blue") != 0)
				{
					agsafeset(edge, "label", "-", "");
				}
			}
		}
			gvLayout(gvc, graph, "dot");
			gvRenderFilename(gvc, graph, "png", "data_set\\Hamiltonian\\Hamiltonian.png");
			gvFreeContext(gvc);
			agclose(graph);
			System::Diagnostics::Process::Start("data_set\\Hamiltonian\\Hamiltonian.png");

	}
	else
		MessageBox::Show("The graph given doesn't have an Hamiltonian path!", "Warning!");
}




private: System::Void eulerian_Click(System::Object^ sender, System::EventArgs^ e) {

	string curDir(__FILE__);
	curDir = curDir.substr(0, curDir.find_last_of("\\/")) + "\\data_set\\input.txt";
	const char* file = curDir.c_str();
	GRAPHS::Crosssing obj(file);

	if (obj.isEulerianCycle())
	{
	string dataDir(__FILE__);
	dataDir = dataDir.substr(0, dataDir.find_last_of("\\/")) + "\\data_set\\Eulerian";

	String^ dataDirString = gcnew String(dataDir.c_str());


	if (!System::IO::Directory::Exists(dataDirString))
	{
		System::IO::Directory::CreateDirectory(dataDirString);
	}

	string Dir(__FILE__);
	Dir = Dir.substr(0, Dir.find_last_of("\\/")) + "\\data_set\\Eulerian\\Eulerian.txt";
	const char* fisier = Dir.c_str();

	string vef(__FILE__);
	vef = vef.substr(0, vef.find_last_of("\\/")) + "\\data_set\\vef.txt";
	const char* fil = vef.c_str();

		graph_t* graph;
		GVC_t* gvc;
		Agdesc_t desc;
		desc.directed = true;
		graph = agopen("graph", desc, NULL);
		gvc = gvContext();
		GRAPHS::creare_Grafic(graph, gvc,curDir,fil);
		obj.HierHolzer(fisier,graph);
		gvLayout(gvc, graph, "dot");
		gvRenderFilename(gvc, graph, "png", "data_set\\Eulerian\\Eulerian.png");
		gvFreeContext(gvc);
		agclose(graph);
		System::Diagnostics::Process::Start("data_set\\Eulerian\\Eulerian.png");
	}
	else
	{
		MessageBox::Show("The graph given doesn't have an Eulerian path!", "Warning");
	}

}



private: System::Void dijkstra_Click(System::Object^ sender, System::EventArgs^ e) {
	int src = 0;
	Int32::TryParse(write_node->Text, src);

	string curDir(__FILE__);
	curDir = curDir.substr(0, curDir.find_last_of("\\/")) + "\\data_set\\input.txt";
	const char* file = curDir.c_str();
	GRAPHS::Dijsktra obj(file);

	string dataDir(__FILE__);
	dataDir = dataDir.substr(0, dataDir.find_last_of("\\/")) + "\\data_set\\Dijkstra";

	String^ dataDirString = gcnew String(dataDir.c_str());

	

	if (!System::IO::Directory::Exists(dataDirString))
	{
		System::IO::Directory::CreateDirectory(dataDirString);
	}
	DeletePngFiles(dataDirString);
	string Dir(__FILE__);
	Dir = Dir.substr(0, Dir.find_last_of("\\/")) + "\\data_set\\Dijkstra\\Dijsktra.txt";
	const char* fisier = Dir.c_str();
	obj.shortestPath(src, fisier);
	System::Diagnostics::Process::Start("data_set\\Dijkstra\\Dijsktra.txt");

}



private: System::Void maximum_flow_Click(System::Object^ sender, System::EventArgs^ e) {

	string curDir(__FILE__);
	curDir = curDir.substr(0, curDir.find_last_of("\\/")) + "\\data_set\\input.txt";
	const char* fisier = curDir.c_str();
	GRAPHS::Graph obiect(fisier);

	int node_start = 0;
	Int32::TryParse(start_node->Text, node_start);

	int node_end = 0;
	Int32::TryParse(end_node->Text, node_end);

	string dataDir(__FILE__);
	dataDir = dataDir.substr(0, dataDir.find_last_of("\\/")) + "\\data_set\\Max_Flow";

	String^ dataDirString = gcnew String(dataDir.c_str());
	if (!System::IO::Directory::Exists(dataDirString))
	{
		System::IO::Directory::CreateDirectory(dataDirString);
	}
	DeletePngFiles(dataDirString);


	string Dir(__FILE__);
	Dir = Dir.substr(0, Dir.find_last_of("\\/")) + "\\data_set\\Max_Flow\\input.txt";

	String^ dataD = gcnew String(Dir.c_str());
	if (!System::IO::File::Exists(dataD))
	{
		System::IO::File::Create(dataD);
	}

	string Directory(__FILE__);
	Directory = Directory.substr(0, Directory.find_last_of("\\/")) + "\\data_set\\Max_Flow\\output_mat.txt";

	String^ dataDirectory = gcnew String(Directory.c_str());
	if (!System::IO::File::Exists(dataDirectory))
	{
		System::IO::File::Create(dataDirectory);
	}
	
	string Director(__FILE__);
 Director = Director.substr(0, Director.find_last_of("\\/")) + "\\data_set\\Max_Flow\\output_list.txt";

	String^ dataDirector = gcnew String(Director.c_str());
	if (!System::IO::File::Exists(dataDirector))
	{
		System::IO::File::Create(dataDirector);
	}

	const char* file=Dir.c_str();
	obiect.printGraph_adjmat(file);

    GRAPHS::Max_Flow obj(file);
	const char* file_mat = Directory.c_str();
	const char* file_list = Director.c_str();
	obj.FordFuckerson(node_start, node_end,file_mat);
	obj.print_transform_adjMat_to_adjList(file,file_mat,file_list);
	graph_t* graph;
	GVC_t* gvc;
	Agdesc_t desc;
	desc.directed = true;
	graph = agopen("graph", desc, NULL);
	gvc = gvContext();
	string tor(__FILE__);
	string vef(__FILE__);
	vef = vef.substr(0, vef.find_last_of("\\/")) + "\\data_set\\vef.txt";
	const char* ret = vef.c_str();
	GRAPHS::creare_Grafic(graph, gvc, Director,ret);

	for (Agnode_t* node = agfstnode(graph); node != nullptr; node = agnxtnode(graph, node))
	{
		for (Agedge_t* edge = agfstout(graph, node); edge != nullptr; edge = agnxtout(graph, edge))
		{
			if (edge)
				if (strcmp(agget(edge, "label"), "0") == 0)
				{
					agsafeset(edge, "color", "red", "");
				}
		}
	}
	gvLayout(gvc, graph, "dot");
	gvRenderFilename(gvc, graph, "png", ("data_set\\Max_Flow\\Max_Flow_" + to_string(node_start) + "-" + to_string(node_end) + ".png").c_str());
	String^ open_file = gcnew String(("data_set\\Max_Flow\\Max_Flow_" + to_string(node_start) + "-" + to_string(node_end) + ".png").c_str());
	System::Diagnostics::Process::Start(open_file);
	gvFreeContext(gvc);
	agclose(graph);


}
private: System::Void connectivity_Click(System::Object^ sender, System::EventArgs^ e) {

	string curDir(__FILE__);
	curDir = curDir.substr(0, curDir.find_last_of("\\/")) + "\\data_set\\input.txt";
	
	const char* fisier = curDir.c_str();

	int node_start = 0;
	Int32::TryParse(start_node->Text, node_start);

	int node_end = 0;
	Int32::TryParse(end_node->Text, node_end);

	GRAPHS::Crosssing obiect(fisier);
	if (obiect.conectare(node_start, node_end))
	{
		String^ message = String::Format("CONNECTION FOUND:between node {0} and node {1}", node_start, node_end);
		MessageBox::Show(message, "Warning!");
	}
	else
	{
		String^ message = String::Format("There is no conection between node {0} and node {1}", node_start, node_end);
		MessageBox::Show(message, "Warning!");
	}
}


private: System::Void output_graph_Click(System::Object^ sender, System::EventArgs^ e) {

	string curDir(__FILE__);
curDir = curDir.substr(0, curDir.find_last_of("\\/")) + "\\data_set\\input.txt";
	String^ appDir = System::IO::Path::GetDirectoryName(Application::ExecutablePath);
	String^ Dir = System::IO::Path::Combine(appDir, "data_set\\input.txt");

	graph_t* graph;     
	GVC_t* gvc;
	Agdesc_t desc;
	desc.directed = true;
	graph = agopen("graph", desc, NULL);
	gvc = gvContext(); 

	string vef(__FILE__);
	vef = vef.substr(0, vef.find_last_of("\\/")) + "\\data_set\\vef.txt";
	const char* file = vef.c_str();
	GRAPHS::creare_Grafic(graph, gvc, curDir,file);


	// Layout the graph using Graphviz
	gvLayout(gvc, graph, "dot");

	if (gvc != nullptr)
	{
		if (graph != nullptr)
		{
			gvRenderFilename(gvc, graph, "png", "data_set\\afisare.png");
			// Display the PNG file
			System::Diagnostics::Process::Start("data_set\\afisare.png");
			gvFreeContext(gvc);
			agclose(graph);
		}
		else
		{
			MessageBox::Show("graph's fault", "error");
		}
	}
	else
	{
		MessageBox::Show("gvc's fault", "error");
	}

}
};
}
