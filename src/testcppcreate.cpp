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
#include "objy/objyAccess.h"
#include "run/Run.h"

//	needs the following Objectivity libraries - oo, SessionManager, Configuration, Data, Util, Statement, Error, Policy

int Run::testcppcreate() {

	cout << ">>>> Enter Run::testcppcreate()" << endl;

	try {
		objy::db::Transaction* transaction = new objy::db::Transaction(objy::db::OpenMode::Update,"Update");
		cout << "objy::db::Transaction* transaction = new objy::db::Transaction(objy::db::OpenMode::Update, \"update\")" << endl;

		try {
			ObjyAccess objyAccess;
			cout << "ObjyAccess objyAccess;" << endl;

			objyAccess.setupCache(); // cache schema and attributes for later.
			cout << "objyAccess.setupCache(); " << endl;

			objy::data::Reference geo_location = objyAccess.createLocation(+43.288601,-91.209399);
			cout << "objy::data::Reference geo_location = objyAccess.createLocation(+43.288601,-91.209399);" << endl;

			objy::data::Reference owner = nullptr;
			objy::data::Reference calls_from = nullptr;
			objy::data::Reference calls_to = nullptr;

			objy::data::Reference owns = objyAccess.createPhone(2,"2242190650");
			cout << "objy::data::Reference owns = objyAccess.createPhone(2,\"2242190650\");" << endl;

			objy::data::Reference address = objyAccess.createAddress(1234,"street number","street name","san jose","CA",95134,geo_location, owner);
			cout << "objy::data::Reference address = objyAccess.createAddress(1234,\"street number\",\"street name\",\"san jose\",\"CA\",95134,);" << endl;

			objy::data::Reference person = objyAccess.createPerson(9,"brian","richard","clark",objy::data::Date(2017-3-3),"M",address,owns);
			cout << "objy::data::Reference person = objyAccess.createPerson(9,\"brian\",\"richard\",\"clark\",objy::data::Date(2017-3-3),\"M\",address,owns);" << endl;


		} catch (objy::UserException& e) {
			cerr << "error1.1: " << e.what() << endl;
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
