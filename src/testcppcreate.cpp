//============================================================================
// Name        : testcppquery.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Run query C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;


#include <objy/db/Transaction.h>		//	for Transaction
#include <objy/Exception.h>				//	for exceptions
#include <objy/data/Data.h>

#include "Run.h"

//	needs the following Objectivity libraries - oo, SessionManager, Configuration, Data, Util, Statement, Error, Policy

int Run::testcppcreate() {

	cout << ">>>> Enter Run::testcppcreate()" << endl;

	try {
		objy::db::Transaction* transaction = new objy::db::Transaction(objy::db::OpenMode::Update,"Update");
		cout << "objy::db::Transaction* transaction = new objy::db::Transaction(objy::db::OpenMode::Update, \"update\")" << endl;

		try {

		} catch (objy::UserException& e) {
			cerr << "error1.1: %s\n" << e.what() << endl;
		}

		transaction->commit();
		cout << "transaction->commit()" << endl;

		transaction->release();
		cout << "transaction->release()" << endl;

	} catch (ooKernelException& e) {
		cerr << "error2.1: " << e.what() << endl;
	} catch (ooBaseException& e) {
		cerr << "error2.2: " << e.what() << endl;
	}

	cout << "<<<< Exit Run::testcppcreate()" << endl;

	return 0;
}
