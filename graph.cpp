#include <iostream>
#include <string>
#include "graph.h"
#include <iomanip>


using namespace std;

Graph::Graph(int arp, int rts)
{
	array = (struct AL*) malloc(arp* sizeof(struct AL));
	for (int i = 0; i < arp; ++i)
        array[i].head = NULL;
	//# of airports = no. of adj lists
	vertices = arp;
	routes = rts;

	int n = rts;
	string cty1,cty2;
	double price;
	while(n--)
	{
		cin >> cty1 >> cty2 >> price;
		addEdge(cty1, cty2, price);
	}
}
void Graph::addEdge(string start, string dest, double price)
{
	struct ALNode* newNode = newALNode(start, dest, price);
	struct ALNode* stNode =  getV(start);
	if(stNode == NULL)
	{
		for(int i = 0; i < vertices; i++)
			if( array[i].head == NULL)
			{
				array[i].head = newNode;
				break;
			}				
	}
	else
	{
		newNode->next = stNode->next;
		stNode->next = newNode; //start -> dest
	}
	//add path from dest to start
	newNode = newALNode(dest, start, price);
	stNode =  getV(dest);
	if(stNode == NULL)
	{
		for(int i = 0; i < vertices; i++)
			if( array[i].head == NULL)
			{
				array[i].head = newNode;
				break;
			}
	}
	else
	{
		newNode->next = stNode->next;
		stNode->next = newNode;
	}
   
}
void Graph::printGraph()
{
	cout << "-----Graph-----" << endl;
	for(int i = 0; i < vertices; i++)
	{
		if( array[i].head )
		{		
			cout << "Routes for: [" << array[i].head->name << "]: ";		
			for(struct ALNode* newNode = array[i].head; newNode != NULL; newNode = newNode->next)
				cout << "FROM: " << newNode->name << " TO [" <<newNode->dest  << "] " << newNode->price << ",";
			cout << endl;
		}
	}	
	cout << "-----END-----" << endl;			
}
string Graph::getIntmd(string src, string end, string prev_arr[])
{
	string res[vertices];
	int i = 0;
	string curr = end;
	string intmd = "";
	while( curr != src)
	{
		int ci = getVI(curr);
		if(ci == -1)
			return intmd;		
		curr = prev_arr[ci];
		res[i++] = curr + " ";
	}
	int n = i;
	for(int k = i; k > -1; k--)
		intmd += res[k];
	//cout << "res = " << intmd << endl;	
	return intmd;
}
double Graph::dijkstra_alg(string src, string dest)
{
	double cost[vertices];
	string previous[vertices];
	bool known[vertices];
	for(int i = 0; i < vertices; i++)
	{
		cost[i] = infinity;
		previous[i] = "---";
		known[i] = false;
	}
	int src_i = getVI(src);
	cost[src_i] = 0; //getVI gets the index of the node in the array of lists
	//int t = 1000;
	while(1)
	{
		int i = -1;
		struct ALNode* v = getMinUnknown(cost, known);
		if (v == NULL)
			break;
		//cout << v->name << " added to done" << endl;
		int vi = getVI(v->name);
		known[vi] = true;
		//visit all children of that node
		double alt;
		int wi;
		for(struct ALNode* w = v; w != NULL; w = w->next )
		{
			wi = getVI(w->dest);
			if(!known[wi])
			{
				alt = cost[vi] + w->price;				
				if(alt < cost[wi])
				{
					cost[wi] = alt;
					previous[wi] = v->name;
				}
			}							
		}
	}
	int res = getVI(dest);
	if(cost[res] < infinity)
		cout << getIntmd(src, dest, previous) << dest;	
	return cost[res];  
}

// Code for part 1. Print out the sequence of airports and price
// of the trip.
void Graph::find_ticket(const string &source, const string &destination)
{
	double res = dijkstra_alg(source, destination);
	cout << fixed;
    cout << setprecision(2);
	if(res >= infinity) 
		cout << "not possible" <<endl;
	else
		cout << " " << res <<endl;
}
// Code for part 2. Print out the tour sequence or "not possible"
// if not all cities can be visited.
string* Graph::prims(string root)
{
	double dist[vertices];
	string *parent = new string[vertices];
	bool known[vertices];
	for(int i = 0; i < vertices; i++)
	{
		dist[i] = infinity;
		parent[i] = "---";
		known[i] = true;
	}
	int src_i = getVI(root);
	//cout << "src_i= " << src_i<< endl;
	dist[src_i] = 0;
	known[src_i] = false;
	while(1)
	{
		struct ALNode* v = getMinUnknown(dist, known);
		if (v == NULL)
			break;
		int vi = getVI(v->name);
		known[vi] = true;
		dist[vi] = -1*dist[vi];
		int ui;
		for(struct ALNode* u = v; u != NULL; u = u->next )
		{
			ui = getVI(u->dest);
			if(dist[ui] > u->price)
			{
				dist[ui] = u->price;
				parent[ui] = v->name;
				if(known[ui])
					known[ui] = false;					
			}							
		}
	}	
	return parent;	
}
void Graph::eulerian_tour(string root, string * tree)
{
	//string * mst = prims(root);
	int not_mst = 0;
	for(int i = 0; i < vertices; i++)
	{
		if(tree[i] == "---")
			not_mst++;
	}
	if(not_mst > 1)
		cout << "not possible" << endl;
	else
		print_tour(root, tree);
}

void Graph::print_tour(string root, string* tree)
{
	cout << root << endl;
	BinaryHeap *children = new BinaryHeap(false); //new min heap to keep children sorted
	for(int i = 0; i < vertices; i++)
		if(tree[i] == root)
			children->insert(new TreeNode(array[i].head->name, 0) );
	while(children->size() > 0)
	{
		string minChild = (children->extract())->key;
		print_tour(minChild, tree);
	}
	//print_tour(array[i].head->name, tree);
	return;
}









































