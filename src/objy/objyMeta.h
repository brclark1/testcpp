/* 
 * File:   objyMeta.h
 * Author: Brian
 *
 * Created on March 19, 2018
 */

#ifndef OBJYMETA_H
#define OBJYMETA_H

#include <objy/data/Data.h>

// class names
static const char* AddressClassName        = "Address";
static const char* PersonClassName  		= "Person";
static const char* PhoneClassName        	= "Phone";
static const char* PhoneCallClassName      = "PhoneCall";
static const char* LocationClassName      	= "Location";

//	attributes by class names
static const char* AddressIdAttr 			= "id";
static const char* AddressStreetNumberAttr	= "street_number";
static const char* AddressStreetNameAttr	= "street_name";
static const char* AddressCityAttr			= "city";
static const char* AddressStateAttr		= "state";
static const char* AddressZipAttr 			= "zip";
static const char* AddressGeoLocationAttr	= "geo_location";
static const char* AddressOwnerAttr 		= "owner";

static const char* PersonIdAttr 			= "id";
static const char* PersonFirstNameAttr		= "first_name";
static const char* PersonMiddleNameAttr	= "middle_name";
static const char* PersonLastNameAttr		= "last_name";
static const char* PersonDateOfBirthAttr 	= "date_of_birth";
static const char* PersonSexAttr			= "sex";
static const char* PersonLivesAtAttr		= "lives_at";
static const char* PersonOwnsAttr			= "owns";

static const char* PhoneIdAttr				= "id";
static const char* PhonePhoneNumberAttr	= "phone_number";
static const char* PhoneOwnerAttr			= "owner";
static const char* PhoneCallsFromAttr		= "calls_from";
static const char* PhoneCallsToAttr		= "calls_to";

static const char* PhoneCallFromNumberAttr		= "from_number";
static const char* PhoneCallToNumberAttr 		= "to_number";
static const char* PhoneCallCallTimeAttr		= "call_time";
static const char* PhoneCallCallDurationAttr 	= "call_duration";
static const char* PhoneCallFromPhoneAttr		= "from_phone";
static const char* PhoneCallToPhoneAttr		= "to_phone";
static const char* PhoneCallFromLocationAttr	= "from_location";
static const char* PhoneCallToLocationAttr		= "to_location";

static const char* LocationLatitudeAttr 	= "latitude";
static const char* LocationLongitudeAttr	= "longitude";

#endif /* OBJYMETA_H */

