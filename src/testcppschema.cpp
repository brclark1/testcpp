//============================================================================
// Name        : testcppschema.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Run query C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdint>
using namespace std;


#include <objy/db/Transaction.h>		//	for Transaction
#include <objy/Exception.h>				//	for exceptions
#include <objy/data/Data.h>
#include <objy/data/ClassBuilder.h>
#include <objy/schema_provider/SchemaProvider.h>

using namespace objy;
using namespace objy::db;
using namespace objy::data;
using namespace objy::schema_provider;

#include "objy/objyMeta.h"
#include "run/Run.h"

//	needs the following Objectivity libraries - oo, SessionManager, Configuration, Data, Util, Statement, Error, Policy

int Run::testcppschema() {

	cout << ">>>> Enter Run::testcppschema()" << endl;

	try {
		Transaction* transaction = new Transaction(OpenMode::Update,"Update");
		cout << "Transaction* transaction = new Transaction(OpenMode::Update, \"update\")" << endl;

		try {

			const char* superClassName = "ooObj";

			SchemaProvider* provider = SchemaProvider::defaultPersistentProvider();
			cout << "SchemaProvider* provider = SchemaProvider::defaultPersistentProvider()" << endl;
			//
			//		Address Class
			//
			Class addressClass;
			ClassBuilder addressClassBuilder (AddressClassName);
			cout << "ClassBuilder addressClassBuilder (AddressClassName);" << endl;

			addressClassBuilder.setSuperclass(superClassName);
			addressClassBuilder.addAttribute<std::int32_t>(AddressIdAttr);
			addressClassBuilder.addAttribute<objy::data::Utf8String>(AddressStreetNumberAttr);
			addressClassBuilder.addAttribute<objy::data::Utf8String>(AddressStreetNameAttr);
			addressClassBuilder.addAttribute<objy::data::Utf8String>(AddressCityAttr);
			addressClassBuilder.addAttribute<objy::data::Utf8String>(AddressStateAttr);
			addressClassBuilder.addAttribute<std::int32_t>(AddressZipAttr);

			DataSpecificationHandle geo_locationRef = DataSpecificationBuilder<LogicalType::Reference>()
								.setReferencedClass(LocationClassName)
								.setIdentifierSpecification(SpecificationFor<std::uint64_t>::get())
								.build();
			addressClassBuilder.addAttribute(AddressGeoLocationAttr, geo_locationRef);

			DataSpecificationHandle ownerRef = DataSpecificationBuilder<LogicalType::Reference>()
								.setReferencedClass(PersonClassName)
								.setIdentifierSpecification(SpecificationFor<std::uint64_t>::get())
								.setInverseAttribute(PersonLivesAtAttr)
								.build();
			addressClassBuilder.addAttribute(AddressOwnerAttr, ownerRef);

			addressClass = addressClassBuilder.build();
			cout << "addressClass = addressClassBuilder.build()" << endl;

			provider->represent(addressClass);
			cout << "provider->represent(addressClass)" << endl;
			//
			//		Location Class
			//
			Class locationClass;
			ClassBuilder locationClassBuilder (LocationClassName);
			cout << "ClassBuilder locationClassBuilder (LocationClassName);" << endl;

			locationClassBuilder.setSuperclass(superClassName);

			locationClassBuilder.addAttribute<std::float64_t>(LocationLatitudeAttr);
			locationClassBuilder.addAttribute<std::float64_t>(LocationLongitudeAttr);

			locationClass = locationClassBuilder.build();
			cout << "locationClass = locationClassBuilder.build()" << endl;

			provider->represent(locationClass);
			cout << "provider->represent(locationClass)" << endl;
			//
			//		Person Class
			//
			Class personClass;
			ClassBuilder personClassBuilder (PersonClassName);
			cout << "ClassBuilder personClassBuilder (PersonClassName);" << endl;

			personClassBuilder.setSuperclass(superClassName);
			personClassBuilder.addAttribute<std::int32_t>(PersonIdAttr);
			personClassBuilder.addAttribute<objy::data::Utf8String>(PersonFirstNameAttr);
			personClassBuilder.addAttribute<objy::data::Utf8String>(PersonMiddleNameAttr);
			personClassBuilder.addAttribute<objy::data::Utf8String>(PersonLastNameAttr);
			personClassBuilder.addAttribute<objy::data::Date>(PersonDateOfBirthAttr);
			personClassBuilder.addAttribute<objy::data::Utf8String>(PersonSexAttr);

			DataSpecificationHandle lives_atRef = DataSpecificationBuilder<LogicalType::Reference>()
								.setReferencedClass(AddressClassName)
								.setIdentifierSpecification(SpecificationFor<std::uint64_t>::get())
								.setInverseAttribute(AddressOwnerAttr)
								.build();
			personClassBuilder.addAttribute(PersonLivesAtAttr, lives_atRef);
			cout << "personClassBuilder.addAttribute(PersonLivesAtAttr, lives_atRef)" << endl;

			DataSpecificationHandle ownsRef = DataSpecificationBuilder<LogicalType::Reference>()
								.setReferencedClass(PhoneClassName)
								.setIdentifierSpecification(SpecificationFor<std::uint64_t>::get())
								.setInverseAttribute(PhoneOwnerAttr)
								.build();
			DataSpecificationHandle ownsRefList = DataSpecificationBuilder<LogicalType::List>()
									.setElementSpecification(ownsRef)
									.build();
			personClassBuilder.addAttribute(PersonOwnsAttr, ownsRefList);
			cout << "personClassBuilder.addAttribute(PersonOwnsAttr, ownsRefList)" << endl;

			personClass = personClassBuilder.build();
			cout << "personClass = personClassBuilder.build()" << endl;

			provider->represent(personClass);
			cout << "provider->represent(personClass)" << endl;
			//
			//		Phone Class
			//
			Class phoneClass;
			ClassBuilder phoneClassBuilder (PhoneClassName);
			cout << "ClassBuilder phoneClassBuilder (PhoneClassName);" << endl;

			phoneClassBuilder.setSuperclass(superClassName);
			phoneClassBuilder.addAttribute<std::int32_t>(PhoneIdAttr);
			phoneClassBuilder.addAttribute<objy::data::Utf8String>(PhonePhoneNumberAttr);

			DataSpecificationHandle phoneOwnerRef = DataSpecificationBuilder<LogicalType::Reference>()
										.setReferencedClass(PersonClassName)
										.setIdentifierSpecification(SpecificationFor<std::uint64_t>::get())
										.setInverseAttribute(PersonOwnsAttr)
										.build();
			phoneClassBuilder.addAttribute(PhoneOwnerAttr, phoneOwnerRef);

			DataSpecificationHandle callsFromRef = DataSpecificationBuilder<LogicalType::Reference>()
								.setReferencedClass(PhoneCallClassName)
								.setIdentifierSpecification(SpecificationFor<std::uint64_t>::get())
								.setInverseAttribute(PhoneCallFromPhoneAttr)
								.build();
			DataSpecificationHandle callsFromRefList = DataSpecificationBuilder<LogicalType::List>()
									.setElementSpecification(callsFromRef)
									.build();
			phoneClassBuilder.addAttribute(PhoneCallsFromAttr, callsFromRefList);

			DataSpecificationHandle callsToRef = DataSpecificationBuilder<LogicalType::Reference>()
								.setReferencedClass(PhoneCallClassName)
								.setIdentifierSpecification(SpecificationFor<std::uint64_t>::get())
								.setInverseAttribute(PhoneCallToPhoneAttr)
								.build();
			DataSpecificationHandle callsToRefList = DataSpecificationBuilder<LogicalType::List>()
									.setElementSpecification(callsToRef)
									.build();
			phoneClassBuilder.addAttribute(PhoneCallsToAttr, callsToRefList);

			phoneClass = phoneClassBuilder.build();
			cout << "phoneClass = phoneClassBuilder.build()" << endl;

			provider->represent(phoneClass);
			cout << "provider->represent(phoneClass)" << endl;

			//
			//		PhoneCall Class
			//
			Class phoneCallClass;
			ClassBuilder phoneCallClassBuilder (PhoneCallClassName);
			cout << "ClassBuilder phoneCallClassBuilder (PhoneCallClassName);" << endl;

			phoneCallClassBuilder.setSuperclass(superClassName);
			phoneCallClassBuilder.addAttribute<objy::data::Utf8String>(PhoneCallFromNumberAttr);
			phoneCallClassBuilder.addAttribute<objy::data::Utf8String>(PhoneCallToNumberAttr);
			phoneCallClassBuilder.addAttribute<objy::data::Date>(PhoneCallCallTimeAttr);
			phoneCallClassBuilder.addAttribute<std::int32_t>(PhoneCallCallDurationAttr);

			DataSpecificationHandle fromPhoneRef = DataSpecificationBuilder<LogicalType::Reference>()
							.setReferencedClass(PhoneClassName)
							.setIdentifierSpecification(SpecificationFor<std::uint64_t>::get())
							.setInverseAttribute(PhoneCallsFromAttr)
							.build();
			phoneCallClassBuilder.addAttribute(PhoneCallFromPhoneAttr, fromPhoneRef);

			DataSpecificationHandle toPhoneRef = DataSpecificationBuilder<LogicalType::Reference>()
							.setReferencedClass(PhoneClassName)
							.setIdentifierSpecification(SpecificationFor<std::uint64_t>::get())
							.setInverseAttribute(PhoneCallsToAttr)
							.build();
			phoneCallClassBuilder.addAttribute(PhoneCallToPhoneAttr, toPhoneRef);

			DataSpecificationHandle fromLocationRef = DataSpecificationBuilder<LogicalType::Reference>()
													.setReferencedClass(LocationClassName)
													.setIdentifierSpecification(SpecificationFor<std::uint64_t>::get())
													.build();
			phoneCallClassBuilder.addAttribute(PhoneCallFromLocationAttr, fromLocationRef);

			DataSpecificationHandle toLocationRef = DataSpecificationBuilder<LogicalType::Reference>()
																.setReferencedClass(LocationClassName)
																.setIdentifierSpecification(SpecificationFor<std::uint64_t>::get())
																.build();
			phoneCallClassBuilder.addAttribute(PhoneCallToLocationAttr, toLocationRef);

			phoneCallClass = phoneCallClassBuilder.build();
			cout << "phoneCallClass = phoneCallClassBuilder.build()" << endl;

			provider->represent(phoneCallClass);
			cout << "provider->represent(phoneCallClass)" << endl;

		} catch (Exception& e) {
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

	cout << "<<<< Exit Run::testcppcschema()" << endl;

	return 0;
}
