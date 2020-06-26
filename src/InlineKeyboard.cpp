#include "InlineKeyboard.h"
#include "Utilities.h"

void InlineKeyboard::initialize(void)
{
#pragma message  "ArduinoJson - DA CONVERTIRE"
	JsonObject& root = m_jsonBuffer.createObject();
	JsonArray&  rows = root.createNestedArray("inline_keyboard");
	JsonArray&  buttons = rows.createNestedArray();

	m_root = &root;
	m_rows = &rows;
	m_buttons = &buttons;
	m_isRowEmpty = true;
}

InlineKeyboard::InlineKeyboard()
{
	initialize();
}

InlineKeyboard::~InlineKeyboard()
{
}

void InlineKeyboard::flushData(void)
{
#pragma message  "ArduinoJson - DA CONVERTIRE"
	m_jsonBuffer.clear();
	initialize();
}

bool InlineKeyboard::addRow(void)
{
#pragma message  "ArduinoJson - DA CONVERTIRE"
	if (m_isRowEmpty)
		return(false);
	JsonArray&  buttons = m_rows->createNestedArray();
	m_buttons = &buttons;
	m_isRowEmpty = true;
	return(true);
}

bool InlineKeyboard::addButton(String text, String command, InlineKeyboardButtonType buttonType)
{
	if ((buttonType != KeyboardButtonURL) && (buttonType != KeyboardButtonQuery))
		return(false);

#pragma message  "ArduinoJson - DA CONVERTIRE"
	JsonObject& button = m_buttons->createNestedObject();
	text = URLEncodeMessage(text);
	button["text"] = text;

	if (KeyboardButtonURL == buttonType) 
		button["url"] = command;
	else if (KeyboardButtonQuery == buttonType) 
		button["callback_data"] = command;


	if (m_isRowEmpty)
		m_isRowEmpty = false;
	return(true);
}

String InlineKeyboard::getJSON(void)
{
#pragma message  "ArduinoJson - DA CONVERTIRE"
	String serialized;
	m_root->printTo(serialized);
	return(serialized);
}

