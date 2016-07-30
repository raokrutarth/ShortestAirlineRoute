#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <string>
#include <string.h>
#include <limits.h>
#include "heap.h"

using namespace std;

class Graph
{
	public:
		double infinity = LONG_MAX;
		Graph(int arp, int rts);
		int vertices;
		int routes;
		//double getMin(double arr[], int n, int &i);
		//struct ALNode* getMinUnknown(double * cost, bool * known);
		struct ALNode
		{
			string name;
    		string dest;
			double price;
    		struct ALNode* next;
		};
		struct AL {	struct ALNode *head; }; // pointer to head node of list		
		struct AL* array; //adjacency list of vertices
		
		// Part 1: Find a ticket using Dijkstra
		void find_ticket(const string &source,const string &destination); 
		
		// Part 2: Try to do a tour of all cities
		void eulerian_tour(string start_city, string * MST); 
		void addEdge(string start, string end, double weight);
		void printGraph();
		string getIntmd(string src, string dest, string prev_arr[]);
		double dijkstra_alg(string src, string dest);
		string* prims(string root);
		void print_tour(string root, string* tree);
		//string removeMin(ArrayList<string> list);
		
		struct ALNode* newALNode(string cityName, string dest, double price)
		{
			struct ALNode* newNode = new ALNode; //(struct ALNode*) malloc(sizeof(struct ALNode));
			newNode->name = cityName;
    		newNode->dest = dest;
			newNode->price = price;
    		newNode->next = NULL;
    		return newNode;
		}
		struct ALNode* getV(const string &cty)
		{
			struct ALNode * node = NULL;
			for(int i = 0; i < vertices; i++)
			{
				if( array[i].head && array[i].head->name == cty)
					node = array[i].head;
			}
			return node;			
		}
		double getVI(const string &cty)
		{
			for(int i = 0; i < vertices; i++)
			{
				if( array[i].head && array[i].head->name == cty)
					return i;
			}
			return -1;			
		}
		struct ALNode* getMinDist(ALNode* head, string dest)
		{
			struct ALNode* min = head;
			for(struct ALNode* curr = head; curr != NULL; curr = curr->next)
				if(curr->dest == dest && curr->price < min->price)
					min = curr;
			if(min == head && head->dest != dest)
				return NULL;
			return min;
		}
		struct ALNode* getMinUnknown(double * cost, bool * known)
		{
			//struct ALNode* result;
			double min = infinity;
			int min_i = -1;
			for( int i= 0; i < vertices; i++)
			{
				if(!known[i] && cost[i] < min)
				{
					min = cost[i];
					min_i = i;
				}
			}
			if(min_i > -1)
				return array[min_i].head; //ERROR: if queue is not empty and remaining vertices are inft.
			return NULL; //should return any child of last added node 
		}
};

#endif
