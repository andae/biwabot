#pragma once
#ifndef BIWABOT_DATA_STRUCTURES
#define BIWABOT_DATA_STRUCTURES

#include <Arduino.h>

enum MessageType {
	MessageNoData   = 0,
	MessageText     = 1,
	MessageQuery    = 2,
	MessageLocation = 3,
	MessageContact  = 4
};

typedef struct TBUser {
	int32_t  id;
	bool     isBot;
	String   firstName;
	String   lastName;
	String   username;
	String   languageCode;
};

typedef struct TBGroup {
	int64_t id;
	String  title;
};

typedef struct TBLocation{
	float longitude;
	float latitude;
};

typedef struct TBContact {
	String  phoneNumber;
	String  firstName;
	String  lastName;
	int32_t id;
	String  vCard;
};


typedef struct TBMessage {
	int32_t          messageID;
	TBUser           sender;
	TBGroup          group;
	int32_t          date;
	String           text;
	String           chatInstance;
	String           callbackQueryData;
	String           callbackQueryID;
	TBLocation       location;
	TBContact        contact;
	MessageType messageType;
};

#endif

