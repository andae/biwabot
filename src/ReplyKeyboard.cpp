#include "ReplyKeyboard.h"
#include "Utilities.h"

void ReplyKeyboard::initialize(void)
{
#pragma message  "ArduinoJson - DA CONVERTIRE"
	JsonObject& root = m_jsonBuffer.createObject();
	JsonArray&  rows = root.createNestedArray("keyboard");
	JsonArray&  buttons = rows.createNestedArray();
	
	m_root = &root;
	m_rows = &rows;
	m_buttons = &buttons;
	m_isRowEmpty = true;
}

ReplyKeyboard::ReplyKeyboard()
{
	initialize();
}

ReplyKeyboard::~ReplyKeyboard()
{
}

void ReplyKeyboard::flushData(void)
{
#pragma message  "ArduinoJson - DA CONVERTIRE"
	m_jsonBuffer.clear();
	initialize();
}

bool ReplyKeyboard::addRow(void)
{
#pragma message  "ArduinoJson - DA CONVERTIRE"
	if (m_isRowEmpty)
		return(false);
	JsonArray&  buttons = m_rows->createNestedArray();
	m_buttons = &buttons;
	m_isRowEmpty = true;
	return(true);
}

bool ReplyKeyboard::addButton(String text, ReplyKeyboardButtonType buttonType)
{
#pragma message  "ArduinoJson - DA CONVERTIRE"
	JsonObject& button = m_buttons->createNestedObject();
	text = URLEncodeMessage(text);
	button["text"] = text;

	if (KeyboardButtonContact == buttonType)
		button["request_contact"] = true;
	else if (KeyboardButtonLocation == buttonType)
		button["request_location"] = true;

	if (m_isRowEmpty)
		m_isRowEmpty = false;
	return(true);
}

void ReplyKeyboard::enableResize(void) {
#pragma message  "ArduinoJson - DA CONVERTIRE"
	(*m_root)["resize_keyboard"] = true;
}

void ReplyKeyboard::enableOneTime(void) {
#pragma message  "ArduinoJson - DA CONVERTIRE"
	(*m_root)["one_time_keyboard"] = true;
}

void ReplyKeyboard::enableSelective(void) {
#pragma message  "ArduinoJson - DA CONVERTIRE"
	(*m_root)["selective"] = true;
}

String ReplyKeyboard::getJSON(void)
{
#pragma message  "ArduinoJson - DA CONVERTIRE"
	String serialized;
	m_root->printTo(serialized);
	return(serialized);
}

