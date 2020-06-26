#pragma once
#ifndef BIWABOT_INLINE_KEYBOARD
#define BIWABOT_INLINE_KEYBOARD

#define ARDUINOJSON_USE_LONG_LONG 1 // for using int_64 data
#include <ArduinoJson.h>
#include <Arduino.h>


enum InlineKeyboardButtonType {
	KeyboardButtonURL    = 1,
	KeyboardButtonQuery  = 2
};

class InlineKeyboard
{
private:
#pragma message  "ArduinoJson - DA CONVERTIRE"
	DynamicJsonBuffer m_jsonBuffer;
	JsonObject *m_root;
	JsonArray  *m_rows;
	JsonArray  *m_buttons;
	bool m_isRowEmpty;

	void initialize(void);

public:
	InlineKeyboard();
	~InlineKeyboard();

	// flush the buffer and initialize the data structure
	void flushData(void);

	// add a new empty row of buttons
	// return:
	//    true if no error occurred
	bool addRow(void);

	// add a button in the current row
	// params:
	//   text   : the text displayed as button label
	//   command: URL (if buttonType is KeyboardButtonURL)
	//            callback query data (if buttonType is KeyboardButtonQuery)
	// return:
	//    true if no error occurred
	bool addButton(String text, String command, InlineKeyboardButtonType buttonType);

	// generate a string that contains the inline keyboard formatted in a JSON structure. 
	// Useful for Biwabot::sendMessage()
	// returns:
	//   the JSON of the inline keyboard 
	String getJSON(void);
};



#endif
