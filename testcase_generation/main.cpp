#include "ArrayList.cpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

static const char alphanum[] = "ABCDEFGHIJKLMOPQRSTUVWXYZ";

int stringLength = sizeof(alphanum) - 1;

char genRandom()  // Random string generator function.
{

    return alphanum[rand() % stringLength];
}
void printList(ArrayList<string> list)
{
	std::cout<<"Size: "<<list.size()<<std::endl;
	std::cout<<"{";
	for (int x = 0; x < list.size(); ++x) {
		if (x && !(x % 5))
			std::cout<<std::endl;
		std::cout<<list[x]<<((x == list.size() - 1) ? "" : ", ");
	} std::cout<<"}"<<std::endl;
}

int main()
{
	cout << fixed;
    cout << setprecision(2);
	int i = 0;
	string line = "";
	string cty1 = "";
	string cty2 = "";
	ArrayList<string> list;
	ArrayList<string> cities;
	int name_size = 3;
	while(cities.size() < 2000) 
	{
		double price = ((double) rand()*(999)/(double)RAND_MAX-1);
	    for(int z=0; z < name_size; z++)
	    	cty1 += genRandom();
	    line += cty1;	        
	    if(!cities.contains(cty1))
	    	cities.add(cty1);
	    line += " ";
	    for(int z=0; z < name_size; z++)
	    	cty2 += genRandom();
	    line += cty2;
	    if(!cities.contains(cty2))
		    cities.add(cty2);

	    if(!list.contains(line) && cty1 != cty2)
	    {
	    	list.add(line);
	    	cout << line << " " << price << endl;
	    }	
	    cty1 = "";
	    cty2 = "";    	
	    line = "";
	}
	cout << endl << "# Cities : "<< cities.size() << " # Routes: "<< list.size() << endl;
	//printList(cities);
    return 0;
}