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

			objy::data::Reference from_phone	= nullptr;
			objy::data::Reference to_phone		= nullptr;
			objy::data::Reference person		= nullptr;
			objy::data::Reference phone[12]		= nullptr;
			objy::data::Reference address		= nullptr;
			objy::data::Reference location		= nullptr;
			objy::data::Reference phoneCall		= nullptr;

			objyAccess.setupCache(); // cache schema and attributes for later.
			cout << "objyAccess.setupCache(); " << endl;

			location = objyAccess.createLocation(+43.288601,-91.209399);
			cout << "location = objyAccess.createLocation(+43.288601,-91.209399);" << endl;

			address = objyAccess.createAddress(1,"93","Lincoln Avenue","Harpers Ferry","IA", 52146,location, person);
			cout << "address = objyAccess.createAddress(1,\"93\",\"Lincoln Avenue\",\"Harpers Ferry\",\"IA\", 52146,location, person);" << endl;

			phone[0] = objyAccess.createPhone(1,"6516417325", person, from_phone, to_phone);
			cout << "phone[0] = objyAccess.createPhone(1,\"6516417325\", person, from_phone, to_phone);" << endl;

			person = objyAccess.createPerson(1,"Thomas", "David","Vongsamphanh",objy::data::Date(2017-3-3),"M",address,phone[0]);
			cout << "person = objyAccess.createPerson(1,\"Thomas\", \"David\",\"Vongsamphanh\",objy::data::Date(2017-3-3),\"M\",address,phone[0]);" << endl;

			location = objyAccess.createLocation(+37.773962,-85.201068);
			address = objyAccess.createAddress(2,"41","Walnut Street","Saint Catharine","KY", 40061,location, person);
			phone[1] = objyAccess.createPhone(2,"2242190650", person, from_phone, to_phone);
			person = objyAccess.createPerson(2,"Charles", "Neil","Gallinger",objy::data::Date(2017-3-3),"M",address,phone[1]);

			location = objyAccess.createLocation(+27.777000,-97.463213);
			address = objyAccess.createAddress(3,"110","Oak Street","Corpus Christi","TX", 78427,location, person);
			phone[2] = objyAccess.createPhone(3,"5078878884", person, from_phone, to_phone);
			person = objyAccess.createPerson(3,"Daniel", "Juan","Hauben",objy::data::Date(2017-3-3),"M",address,phone[2]);
			phone[3] = objyAccess.createPhone(4,"4196672956", person, from_phone, to_phone);
			//	add phone to person
			objyAccess.addPhoneToPerson(phone[3], person);

			location = objyAccess.createLocation(+41.800617,-85.866011);
			address = objyAccess.createAddress(4,"140","Willow Avenue","Union","MI", 49130,location, person);
			phone[4] = objyAccess.createPhone(5,"2704575128", person, from_phone, to_phone);
			person = objyAccess.createPerson(4,"Benjamin", "Robert","Loe",objy::data::Date(1997-3-3),"M",address,phone[4]);

			location = objyAccess.createLocation(+35.662957,-95.197780);
			address = objyAccess.createAddress(5,"160","Highland Place","Braggs","OK", 74423,location, person);
			phone[5] = objyAccess.createPhone(6,"5708072704", person, from_phone, to_phone);
			person = objyAccess.createPerson(5,"Willie", "James","Silva",objy::data::Date(1998-3-3),"M",address,phone[5]);
			phone[6] = objyAccess.createPhone(7,"2096550524", person, from_phone, to_phone);
			//	add phone to person
			objyAccess.addPhoneToPerson(phone[6], person);

			location = objyAccess.createLocation(+43.562030,-119.078609);
			address = objyAccess.createAddress(6,"160","Park Place","Braggs","OR", 97736,location, person);
			phone[7] = objyAccess.createPhone(8,"7082641995", person, from_phone, to_phone);
			person = objyAccess.createPerson(6,"Eugene", "Michael","Hernandez",objy::data::Date(1998-3-3),"M",address,phone[7]);


			location = objyAccess.createLocation(+39.743934,-104.987577);
			address = objyAccess.createAddress(7,"22","Madison Place","Denver","CO", 80274,location, person);
			phone[8] = objyAccess.createPhone(9,"6605868262", person, from_phone, to_phone);
			person = objyAccess.createPerson(7,"Rodney", "Laurence","Johnson",objy::data::Date(1995-3-3),"M",address,phone[8]);

			location = objyAccess.createLocation(+48.216068,-106.320808);
			address = objyAccess.createAddress(8,"180","Davis Court","Nashua","MT", 59248,location, person);
			phone[9] = objyAccess.createPhone(10,"7704579542", person, from_phone, to_phone);
			person = objyAccess.createPerson(8,"Dorian", "Manuel","Stych",objy::data::Date(1994-3-3),"M",address,phone[9]);
			phone[10] = objyAccess.createPhone(11,"3129904832", person, from_phone, to_phone);
			//	add phone to person
			objyAccess.addPhoneToPerson(phone[10], person);

			location = objyAccess.createLocation(+27.777000,-97.463213);
			address = objyAccess.createAddress(9,"120","Birch Place","Corpus Christia","TX", 78465,location, person);
			phone[11] = objyAccess.createPhone(12,"5401931120", person, from_phone, to_phone);
			person = objyAccess.createPerson(9,"Joseph", "Timothy","Lueckenbach",objy::data::Date(1993-3-3),"M",address,phone[11]);
			phone[12] = objyAccess.createPhone(13,"2606996491", person, from_phone, to_phone);
			//	add phone to person
			objyAccess.addPhoneToPerson(phone[12], person);

			//	create phone calls
			objyAccess.createPhoneCall("6516417325", "2242190650", objy::data::DateTime(2017-5-5), 100, phone[0], phone[1], location, location);
			objyAccess.createPhoneCall("2242190650", "6516417325", objy::data::DateTime(2017-5-5), 100, phone[1], phone[0], location, location);
			objyAccess.createPhoneCall("5078878884", "6516417325", objy::data::DateTime(2017-5-5), 100, phone[2], phone[0], location, location);
			objyAccess.createPhoneCall("2242190650", "5078878884", objy::data::DateTime(2017-5-5), 100, phone[1], phone[2], location, location);
			objyAccess.createPhoneCall("5078878884", "4196672956", objy::data::DateTime(2017-5-5), 100, phone[2], phone[3], location, location);
			objyAccess.createPhoneCall("4196672956", "2704575128", objy::data::DateTime(2017-5-5), 100, phone[3], phone[4], location, location);
			objyAccess.createPhoneCall("2704575128", "5708072704", objy::data::DateTime(2017-5-5), 100, phone[4], phone[5], location, location);
			objyAccess.createPhoneCall("5708072704", "2096550524", objy::data::DateTime(2017-5-5), 100, phone[5], phone[6], location, location);
			objyAccess.createPhoneCall("2096550524", "7082641995", objy::data::DateTime(2017-5-5), 100, phone[6], phone[7], location, location);
			objyAccess.createPhoneCall("7082641995", "6605868262", objy::data::DateTime(2017-5-5), 100, phone[7], phone[8], location, location);
			objyAccess.createPhoneCall("6605868262", "7704579542", objy::data::DateTime(2017-5-5), 100, phone[8], phone[9], location, location);
			objyAccess.createPhoneCall("7704579542", "3129904832", objy::data::DateTime(2017-5-5), 100, phone[9], phone[10], location, location);
			objyAccess.createPhoneCall("3129904832", "5401931120", objy::data::DateTime(2017-5-5), 100, phone[10], phone[11], location, location);
			objyAccess.createPhoneCall("5401931120", "2606996491", objy::data::DateTime(2017-5-5), 100, phone[11], phone[12], location, location);

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
