/*
	Things to consider in test:
	1. args: pagesize #pages
	2. args: pagesize #pages bootfile
	
*/

#include <ooObjy.h>

#include "Run.h"

using namespace std;

#include <iostream>

int main(int argc,char** argv)
{
	try
	{
		Run* run = new Run;

		if (argc == 2)
		{
		}
		else if (argc ==1)
		{	//	query
			cout << ">>>> Running query"  << endl;
		

			run->initialize();

			run->testcppquery();

			run->shutdown();
		}
		else
		{
			cerr << "Error: wrong number of arguemnts." << endl;
			cerr << "Params: <pagesize> <#pages>" << endl;
			cerr << "OR" << endl;
			cerr << "Params: <pagesize> <#pages> <bootfile>" << endl;
			return 99;
		}
	}
	catch (...)
	{
		cerr << "unknown exception in main" << endl;
	}
	return 0;
}
