#include <iostream>
#include <string>
#include "graph.h"
#include <limits.h>


using namespace std;

// Part 1: Find tickets for an airline passenger
void P5_part1()
{
	string cty1,cty2;
	int arp_n, rts_n;
	cin >> arp_n >> rts_n;
	Graph *g = new Graph(arp_n, rts_n); //constr. reads in the paths
	//g->printGraph();
	cin >> cty1;
	while(cty1 != "END") // Find tickets until END appears
	{
		cin >> cty2;
		g->find_ticket(cty1, cty2);
		cin >> cty1;
	}
}

// Part 2: Perform an eulerian tour of the graph.
void P5_part2()
{
	string cty1,cty2;
	int arp_n, rts_n;
	cin >> arp_n >> rts_n;
	Graph *g = new Graph(arp_n, rts_n); //constr. reads in the paths
	//g->printGraph();

	string MST_rt;
	cin >> MST_rt;
	string* mst = g->prims(MST_rt);
	/*cout << "MST for root " << MST_rt << ": ";
	for(int i = 0; i < arp_n; i++)
		cout << parent[i] << " " ;
	cout << endl << endl;
	cout << "tour with same root: "<< endl;*/
	g->eulerian_tour(MST_rt, mst);

}

int main()
{
	int cmd;
	cin >> cmd;
	if(cmd == 1) 
		P5_part1();
	else if(cmd == 2) 
		P5_part2();
	return 0;
}
