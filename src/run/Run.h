#ifndef RUN_H
#define RUN_H

class Run 
{
public:
	Run();
	int initialize();		//	initialize Objy
	int shutdown();			//	shutdown Objy
	int testcppquery();		//	run queries
	int testcppcreate();	//	create data
	int testcppschema();	//	define schema

private:

};
#endif
