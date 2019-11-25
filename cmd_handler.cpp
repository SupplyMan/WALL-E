#include "cmd_handler.h"

SerialCommandHandler::SerialCommandHandler()
{
	baudrate = 9600;
	token_count = 0;
	cmd_count = 0;
}

SerialCommandHandler::SerialCommandHandler(uint32_t baudrate)
{
	this->baudrate = baudrate;
	token_count = 0;
	cmd_count = 0;
}

void SerialCommandHandler::registerCommand(char* id, CMDFunc func)
{
	if (cmd_count >= SERIAL_MAX_CMD) return;

	cmd_ids[cmd_count] = id;
	cmd_funcs[cmd_count] = func;
	cmd_count++;
}

void SerialCommandHandler::init()
{
	Serial.begin(baudrate);
}

void SerialCommandHandler::readCommand()
{
	size_t size = Serial.readBytesUntil('\n', serial_buffer, SERIAL_BUFFER_SIZE);
	serial_buffer[size] = '\0';

	size_t count = 0;
	char* temp = strtok(serial_buffer, " ");
	
	while(temp != nullptr && count < SERIAL_MAX_TOKENS)
	{
		tokens[count] = temp;
		count++;

		temp = strtok(nullptr, " ");
	}

	token_count = count;
}

void SerialCommandHandler::handleCommand()
{
	size_t count;

	readCommand();

	for (count = 0; count < cmd_count; count++)
	{
		if (strcmp(tokens[0], cmd_ids[count]) == 0)
		{
			(*(cmd_funcs[count]))(tokens, token_count);
		}
	}
}

char* SerialCommandHandler::getToken(size_t i)
{
	if (i >= token_count) return nullptr;
	return tokens[i];
}

size_t SerialCommandHandler::getTokenCount()
{
	return token_count;
}