// Name: Derek Hackman
// Partner Name: Ben Abbott
// Class: Network Security
// Assignment: Project 2 - RSA Key Generation
// Description: Using a provided list of prime numbers user will choose
// two large primes, this will calculate n and then and then find totient of
// n. After it will calculate 
//--------------------------------------------------------------------------------------------------------------------------


#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <string.h>
using namespace std;

int main()
{
	
	fstream myfile;
	myfile.open("..\..\primes.txt", ios::in);
	string prime[200];
	cout << "Opening file" << endl;

	if (myfile.is_open()) 
	{ 
		/* ok, proceed with reading */ 
		int i = 0;
		while (getline(myfile, prime[i]))
		{
			cout << prime[i] << endl;
		}
	}
	else
	{
		cout << "Did not open";
	}



	myfile.close();
	return 0;

}