/* 
 * File:   objyAccess.h
 * Author: Brian
 *
 * Created on March 19, 2018
 */

#ifndef OBJYACCESS_H
#define OBJYACCESS_H

#include <string>
#include <map>

#include <ooObjy.h>
#include <objy/data/Data.h>
#include <objy/data/List.h>
#include <objy/data/DataSpecificationBuilder.h>

#include <iostream>
using namespace std;

class ClassAccessor;

typedef std::map<string, ClassAccessor*> ClassAccessorMap;
typedef map<string, objy::data::Attribute> AttributeMap;


class ClassAccessor {
public:
	ClassAccessor(const ClassAccessor& orig) = delete;

	virtual ~ClassAccessor() {
	}

	ClassAccessor(const std::string& name) :
		_className(name) { }

	ClassAccessor(ClassAccessor&& other) :
		_className(std::move(other._className)),
		_classRef(std::move(other._classRef)),
		_attributeMap(std::move(other._attributeMap))
	{ }

	void init() {
		//cout << "locating class: " << _className.c_str() << endl;
		objy::data::Class clazz = objy::data::lookupClass(_className.c_str());
		_classRef = clazz;
		for (unsigned i = 0; i < _classRef.numberOfAttributes(); i++) {
			objy::data::Attribute attr = _classRef.attribute(i);
			_attributeMap[attr.name()] = attr;
		}
	}

	const objy::data::Attribute& getAttribute(const string& attrName) const
	{
		AttributeMap::const_iterator itr = _attributeMap.find(attrName);
		if (itr == _attributeMap.end()) {
			cerr << "Failed to get attribute: '" << attrName
					<< "' for class: '" << _className << "'" << endl;
			throw std::invalid_argument("Failed to get attribute: " + attrName);
		}

		return itr->second;
	}

	string getClassName() const {
		return _className;
	}

	objy::data::Class getObjyClass() const {
		return _classRef;
	}

	objy::data::Object createInstance() const {
		//objectCreatedCounter++;
		return objy::data::createPersistentObject(_classRef);
	}

	void setAttributeValue(objy::data::Object instance,
			const string& attributeName, const objy::data::Variable& value) const
	{
		const objy::data::Attribute& attribute = this->getAttribute(attributeName);
		if (!attribute.isNull())
			setAttributeValue(instance, attribute, value);
	}

	void setReference(objy::data::Object instance,
			const string& attributeName, const objy::data::Reference value) const
	{
		const objy::data::Attribute& attribute = this->getAttribute(attributeName);
		if (instance.isNull() || value.isNull() || attribute.isNull()) {
			std::cerr << "For attr: " << attributeName
					<< " - instance/attribute/value: " << objy::data::oidFor(instance).sprint()
					<< " / " << attribute.name() << " / " << objy::data::oidFor(value).sprint()
					<< std::endl;
		}
		setReference(instance, attribute, value);
	}

	void addReference(objy::data::Object instance,
			const string& attributeName, const objy::data::Reference value) const
	{
		const objy::data::Attribute& attribute = this->getAttribute(attributeName);
		setReference(instance, attribute, value);
	}

	void incUInt64AttributeValue(objy::data::Object instance, const string& attributeName) const
	{
		const objy::data::Attribute& attribute = this->getAttribute(attributeName);
		if (!attribute.isNull())
			incUInt64AttributeValue(instance, attribute);
	}

	void addToUInt64AttributeValue(objy::data::Object instance,
			const string& attributeName, uint64_t value) const
	{
		const objy::data::Attribute& attribute = this->getAttribute(attributeName);
		if (!attribute.isNull())
			addToUInt64AttributeValue(instance, attribute, value);
	}



private:
	void setAttributeValue(objy::data::Object instance,
			const objy::data::Attribute& attribute, const objy::data::Variable& value) const
	{
		objy::data::Variable varValue;
		instance.attributeValue(attribute, varValue);
		//varValue.set(value);
		varValue = value;
	}

	// NOTE: this version doesn't check if a reference exist in a list before
	//       adding it, but does that for the map since it's cheaper operation
	void setReference(objy::data::Object instance,
			const objy::data::Attribute& attribute, const objy::data::Reference value) const
	{
		objy::data::Variable varValue;
		instance.attributeValue(attribute, varValue);

		objy::data::LogicalType::type attrLogicalType =
				attribute.attributeValueSpecification()->logicalType();

		if (attrLogicalType == objy::data::LogicalType::List) {
			objy::data::List list = varValue.get<objy::data::List>();
			list.append(value);
		} else if (attrLogicalType == objy::data::LogicalType::Map) {
			objy::data::Map map = varValue.get<objy::data::Map>();
			addReferenceIfDoesnotExist(map, value);
		} else if (attrLogicalType == objy::data::LogicalType::Reference) {
			varValue.set(value);
		} else {
			std::cerr << "Illegal attribute type " << objy::data::LogicalType::toString(attrLogicalType)
			<< " for Instance value." << std::endl;
		}
	}

	void addReferenceIfDoesnotExist(objy::data::Map& map,
			const objy::data::Reference objRef) const {
		// set the key and value in the map from the call object....
		ooId oid = objy::data::oidFor(objRef);
		const char* key = oid.sprint();
		if (!map.containsKey(key)) {
			//objy::data::Variable value(objRef);
			map[key] = objRef;
		}
	}

	/*
	 * Note that the variable we are incrementing is of type 'uint64_t'
	 * Hence we named the function specifically to show that.
	 * A better generic impl should check the type and get the value accordingly.
	 */
	void incUInt64AttributeValue(objy::data::Object instance,
			const objy::data::Attribute& attribute) const
	{
		objy::data::Variable varValue;
		instance.attributeValue(attribute, varValue);
		varValue.set(varValue.get<uint64_t>() + 1);
	}

	/*
	 * Note that the variable we are adding is of type 'uint64_t'
	 * Hence we named the function specifically to show that.
	 * A better generic impl should check the type and get the value accordingly.
	 */
	void addToUInt64AttributeValue(objy::data::Object instance,
			const objy::data::Attribute& attribute, uint64_t value) const
	{
		objy::data::Variable varValue;
		instance.attributeValue(attribute, varValue);
		varValue.set(varValue.get<uint64_t>() + value);
	}

private:

	string            _className;
	objy::data::Class _classRef;
	AttributeMap      _attributeMap;

};


class ObjyAccess {
public:
	ObjyAccess();
	virtual ~ObjyAccess();
	bool setupCache();

	ClassAccessor* getClassProxy(const string& className) {

		auto itr = _classProxyMap.find(className);
		if (itr == _classProxyMap.end()) {
			ClassAccessor* classAccessor = new ClassAccessor(className);
			classAccessor->init();
			_classProxyMap[className] = classAccessor;
			return classAccessor;
		}
		return itr->second;
	}


	objy::data::Reference createAddress(
			uint64_t id,
			const char* street_number,
			const char* street_name,
			const char* city,
			const char* state,
			uint64_t zip,
			objy::data::Reference& geo_location,
			objy::data::Reference& owner);

	objy::data::Reference createPerson(
			uint64_t id,
			const char* first_name,
			const char* middle_name,
			const char* last_name,
			objy::data::Date date_of_birth,
			const char* sex,
			objy::data::Reference& lives_at,
			objy::data::Reference& owns);

	objy::data::Reference createPhone(
			uint64_t id,
			const char* phone_number,
			objy::data::Reference& owner,
			objy::data::Reference& calls_from,
			objy::data::Reference& calls_to);

	objy::data::Reference createPhoneCall(
			const char* from_number,
			const char* to_number,
			objy::data::DateTime call_time,
			uint64_t call_duration,
			objy::data::Reference& from_phone,
			objy::data::Reference& to_phone,
			objy::data::Reference& from_location,
			objy::data::Reference& to_location);

	objy::data::Reference createLocation(
			float64 latitude,
			float64 longitude);

	bool addPhoneToPerson(objy::data::Reference& phone, objy::data::Reference& person);

private:

	ClassAccessorMap      _classProxyMap;
	objy::data::Utf8String  _stringVariable;

};

#endif /* OBJYACCESS_H */

