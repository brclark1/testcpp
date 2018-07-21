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
#include <objy/statement/Statement.h>

#include "run/Run.h"

//	needs the following Objectivity libraries - oo, SessionManager, Configuration, Data, Util, Statement, Error, Policy

int Run::testcppquery() {

	cout << ">>>> Enter Run::testcppquery()" << endl;

	try {
		objy::db::Transaction* transaction = new objy::db::Transaction(objy::db::OpenMode::ReadOnly, "read");
		cout << "objy::db::Transaction* transaction = new objy::db::Transaction(objy::db::OpenMode::ReadOnly, \"read\")" << endl;

		try {
			//	string qString("SELECT * from Person TAKE 5;");
			//	string qString("MATCH path = (p1:Person{id=3})-->() RETURN path;");
			//	string qString("MATCH path = (p3:Person{id=3})-[*1..3]->() RETURN path;");
			//	string qString("MATCH path = (p3:Person{id=3})-[*1..4]->() RETURN path;");
			//	string qString("SELECT * FROM Person WHERE first_name == 'Daniel';");
			//	string qString("FROM Person WHERE first_name == 'Daniel' RETURN *;");
			//	string qString("FROM Person WHERE lives_at.city == 'Corpus Christi' RETURN *;");
			//	string qString("MATCH path=(:Person {first_name == 'Daniel'})-[:lives_at]->() RETURN path;");
			string qString("MATCH path=(:Person {first_name == 'Daniel'})-[owns]->(:Phone)-->(:PhoneCall)-[:to_phone]->(:Phone {phone_number='2704575128'}) RETURN path;");
			//	string qString("MATCH path = (p3:Person{id=3})-[*1..4]->(p2:Person{id=2}) RETURN path;");	//**	 still crashes

			cout << "executing query = " << qString.c_str() << endl;
			objy::statement::Statement doStatement(qString.c_str());
			cout << "objy::statement::Statement doStatement(qString.c_str())" << endl;

			// Add the identifier to the results projection.
			objy::policy::Policies policies;
			policies.add("AddIdentifier.enable", true);
			cout << "policies.add(\"AddIdentifier.enable\", true)" << endl;

			policies.add("Navigator.enableParallelNavigation", false);
			cout << "policies.add(\"Navigator.enableParallelNavigation\", true)" << endl;

			objy::data::Variable results = doStatement.execute(nullptr, policies);
			cout << "objy::data::Variable results = doStatement.execute(nullptr, policies)" << endl;

			objy::data::LogicalType::type logicalType = results.specification()->logicalType();
			cout << "objy::data::LogicalType::type logicalType = results.specification()->logicalType()" << endl;
			cout << "results specification: " << objy::data::LogicalType::toString(logicalType) << endl;

			if (logicalType == objy::data::LogicalType::Sequence) {
				objy::data::Sequence sequence = results.get<objy::data::Sequence>();
				cout << "objy::data::Sequence sequence = results.get<objy::data::Sequence>()" << endl;
				objy::data::Variable sequenceItem;
				int count = 0;
				cout << "process sequence" << endl;
				while (sequence.next()) {
					sequence.current(sequenceItem);
		            stringstream os;
		            sequenceItem.toJSON(os);
		            cout << "sequence result: " << count++ << " : " << os.str() << endl;
				}
			}
			else {
				stringstream os;
				results.toJSON(os);
				cout << "Query results: " << os.str() << endl;
			}
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

	cout << "<<<< Exit Run::testcppquery()" << endl;

	return 0;
}
