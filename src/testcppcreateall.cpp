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

int Run::testcppcreateall() {

	cout << ">>>> Enter Run::testcppcreateall()" << endl;

	try {
		objy::db::Transaction* transaction = new objy::db::Transaction(objy::db::OpenMode::Update,"Update");
		cout << "objy::db::Transaction* transaction = new objy::db::Transaction(objy::db::OpenMode::Update, \"update\")" << endl;

		try {
			ObjyAccess objyAccess;
			cout << "ObjyAccess objyAccess;" << endl;

			objy::data::Reference person		= nullptr;
			objy::data::Reference location		= nullptr;
			objy::data::Reference from_phone	= nullptr;
			objy::data::Reference to_phone		= nullptr;
			objy::data::Reference phone1		= nullptr;
			objy::data::Reference phone2		= nullptr;
			objy::data::Reference phoneCall		= nullptr;

			objyAccess.setupCache(); // cache schema and attributes for later.
			cout << "objyAccess.setupCache(); " << endl;

			phone1 = objyAccess.createPhone(0,"6516417325", person, from_phone, to_phone);
			for (int i = 1; i < 1000000; i++) {
				phone2 = objyAccess.createPhone(0,"6516417325", person, from_phone, to_phone);
				objyAccess.createPhoneCall("6516417325", "2242190650", objy::data::DateTime(2017-5-5), 100, phone1, phone2, location, location);
				phone1 = phone2;
			}

		} catch (objy::Exception& e) {
			cerr << "error1.1: " << e.what() << endl;
		}

		transaction->commit();
		cout << "transaction->commit()" << endl;

		transaction->removeRef();
		cout << "transaction->release()" << endl;

	} catch (ooKernelException& e) {
		cerr << "error2.1: " << e.what() << endl;
	} catch (ooBaseException& e) {
		cerr << "error2.2: " << e.what() << endl;
	}

	cout << "<<<< Exit Run::testcppcreateall()" << endl;

	return 0;
}
