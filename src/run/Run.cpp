using namespace std;
#include <iostream>
#include <time.h>

#include <ooObjy.h>
#include <objy/db/Connection.h>			//	for Connection

#include "Run.h"

Run::Run()
{

}

int Run::initialize()
{
	try
	{
		cout << "Run::initialize(): initialize Objy" << endl;
		//  initialize Objy
		int logOption = oocLogNone;				//oocLogAll;
		ooObjy::setLoggingOptions(logOption,	// Enable all logging options
			oocTrue,							// Write to log files
			oocFalse,							// Append to existing files
			".",								// Log directory
			"MainLog.txt");						// Name of main log file);

		ooObjy::startup();
		cout << "ooObjy::startup()" <<  endl;

		string _connectionString("data/testfd.boot");
		objy::db::Connection* _connection;

		_connection = objy::db::Connection::connect(_connectionString.c_str(), true, 0, false);
		cout << "objy::db::Connection::connect(_connectionString.c_str(), true, 0, false)" << endl;

		cout << "_connection->getBootFile() = " << _connection->getBootFile() << endl;
	}
	catch (ooKernelException& e) {
			cerr << "error2.1: " << e.what() << endl;
		} catch (ooBaseException& e) {
			cerr << "error2.2: " << e.what() << endl;
		}
	return 0;
}

int Run::shutdown()
{
	try
	{
		//  shutdown Objy
		ooObjy::shutdown();
		cout << "ooObjy::shutdown()" << endl;
	}
	catch (ooKernelException& e) {
		cerr << "error2.1: " << e.what() << endl;
	} catch (ooBaseException& e) {
		cerr << "error2.2: " << e.what() << endl;
	}
	return 0;
}





