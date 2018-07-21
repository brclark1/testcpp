/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ObjyAccess.cpp
 * Author: Brian
 * 
 * Created on March 22, 2018
 */

#include <iostream>

#include <objy/data/Data.h>

#include "objyMeta.h"
#include "objyAccess.h"


ObjyAccess::ObjyAccess() {
	_stringVariable = objy::data::createUtf8String();
}

ObjyAccess::~ObjyAccess() {
}

/**
 * 
 * @return 
 */
bool ObjyAccess::setupCache()
{
	// cache classes. although we don't need to do this ahead of using class proxies
	this->getClassProxy(AddressClassName);
	this->getClassProxy(PersonClassName);
	this->getClassProxy(PhoneClassName);
	this->getClassProxy(PhoneCallClassName);
	this->getClassProxy(LocationClassName);

	return true;
}

/**
 * 
 * @param id
 * @param street_number
 * @param street_name
 * @param city
 * @param state
 * @param zip
 * @param geo_location
 * @param owner
 * @return 
 */

objy::data::Reference ObjyAccess::createAddress(
		uint64_t id,
		const char* street_number,
		const char* street_name,
		const char* city,
		const char* state,
		uint64_t zip,
		objy::data::Reference& geo_location,
		objy::data::Reference& owner)
{

	ClassAccessor* classAccessor = this->getClassProxy(AddressClassName);

	objy::data::Object object = classAccessor->createInstance();
	objy::data::Variable value;

	value.set(id);
	classAccessor->setAttributeValue(object, AddressIdAttr, value);

	value.set(street_number);
	classAccessor->setAttributeValue(object, AddressStreetNumberAttr, value);

	value.set(street_name);
	classAccessor->setAttributeValue(object, AddressStreetNameAttr, value);

	value.set(city);
	classAccessor->setAttributeValue(object, AddressCityAttr, value);

	value.set(state);
	classAccessor->setAttributeValue(object, AddressStateAttr, value);

	value.set(zip);
	classAccessor->setAttributeValue(object, AddressZipAttr, value);

	classAccessor->setReference(object,AddressGeoLocationAttr,geo_location);

	objy::data::Reference objectRef = objy::data::createReference(object);

	return objectRef;
}

/**
 * 
 * @param id
 * @param first_name
 * @param middle_name
 * @param last_name
 * @param date_of_birth
 * @param sex
 * @param lives_at
 * @param owns
 * @return 
 */
objy::data::Reference ObjyAccess::createPerson(
		uint64_t id,
		const char* first_name,
		const char* middle_name,
		const char* last_name,
		objy::data::Date date_of_birth,
		const char* sex,
		objy::data::Reference& lives_at,
		objy::data::Reference& owns)
{

	ClassAccessor* classAccessor = this->getClassProxy(PersonClassName);
	objy::data::Object object = classAccessor->createInstance();

	objy::data::Variable value;

	value.set(id);
	classAccessor->setAttributeValue(object, PersonIdAttr, value);

	value.set(first_name);
	classAccessor->setAttributeValue(object, PersonFirstNameAttr, value);

	value.set(middle_name);
	classAccessor->setAttributeValue(object, PersonMiddleNameAttr, value);

	value.set(last_name);
	classAccessor->setAttributeValue(object, PersonLastNameAttr, value);

	value.set(objy::data::Date(date_of_birth));
	classAccessor->setAttributeValue(object, PersonDateOfBirthAttr, value);

	value.set(sex);
	classAccessor->setAttributeValue(object, PersonSexAttr, value);

	classAccessor->setReference(object, PersonLivesAtAttr, lives_at);

	classAccessor->setReference(object, PersonOwnsAttr, owns);

	return objy::data::createReference(object);
}

/**
 * 
 * @param id
 * @param phone_number
 * @param owner
 * @param calls_from
 * @param calls_to
 * @return 
 */
objy::data::Reference ObjyAccess::createPhone(
		uint64_t id,
		const char* phone_number,
		objy::data::Reference& owner,
		objy::data::Reference& calls_from,
		objy::data::Reference& calls_to)
{
	ClassAccessor* classAccessor = this->getClassProxy(PhoneClassName);
	objy::data::Object object = classAccessor->createInstance();

	objy::data::Variable value;

	value.set(id);
	classAccessor->setAttributeValue(object, PhoneIdAttr, value);

	value.set(phone_number);
	classAccessor->setAttributeValue(object, PhonePhoneNumberAttr, value);
/*
	classAccessor->setReference(object,
			PhoneOwnerAttr,
			owner);

	classAccessor->setReference(object,
			PhoneCallsFromAttr,
			calls_from);

	classAccessor->setReference(object,
			PhoneCallsToAttr,
			calls_to);
*/
	return objy::data::createReference(object);
}

/**
 * 
 * @param id
 * @param address
 * @param addressRef
 * @param trxValue
 * @return 
 */
objy::data::Reference ObjyAccess::createPhoneCall(
		const char* from_number,
		const char* to_number,
		objy::data::DateTime call_time,
		uint64_t call_duration,
		objy::data::Reference& from_phone,
		objy::data::Reference& to_phone,
		objy::data::Reference& from_location,
		objy::data::Reference& to_location)
{
	ClassAccessor* classAccessor = this->getClassProxy(PhoneCallClassName);
	objy::data::Object object = classAccessor->createInstance();

	objy::data::Variable value;

	value.set(from_number);
	classAccessor->setAttributeValue(object, PhoneCallFromNumberAttr, value);

	value.set(to_number);
	classAccessor->setAttributeValue(object, PhoneCallToNumberAttr, value);

	value.set(call_time);
	classAccessor->setAttributeValue(object, PhoneCallCallTimeAttr, value);

	value.set(call_duration);
	classAccessor->setAttributeValue(object, PhoneCallCallDurationAttr, value);

	classAccessor->setReference(object, PhoneCallFromPhoneAttr, from_phone);

	classAccessor->setReference(object, PhoneCallToPhoneAttr, to_phone);
/*
	classAccessor->setReference(object, PhoneCallFromLocationAttr, from_location);

	classAccessor->setReference(object, PhoneCallToLocationAttr, to_location);
*/
	objy::data::Reference objectRef = objy::data::createReference(object);

	return objectRef;
}
/**
 * 
 * @param latitude
 * @param longitude
 * @return 
 */
objy::data::Reference ObjyAccess::createLocation(
		float64 latitude,
		float64 longitude)
{
	ClassAccessor* classAccessor = this->getClassProxy(LocationClassName);
	objy::data::Object object = classAccessor->createInstance();

	objy::data::Variable value;

	value.set(latitude);
	classAccessor->setAttributeValue(object, LocationLatitudeAttr, value);

	value.set(longitude);
	classAccessor->setAttributeValue(object, LocationLongitudeAttr, value);

	return objy::data::createReference(object);
}

bool ObjyAccess::addPhoneToPerson(objy::data::Reference& phone, objy::data::Reference& person)
{
	ClassAccessor* classAccessor = this->getClassProxy(PersonClassName);
	classAccessor->addReference(person.referencedObject(), PersonOwnsAttr,phone);
	return true;
}

