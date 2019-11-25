#include "cmd_handler.h"

SerialCommandHandler::SerialCommandHandler()
{
	this->baudrate = 9600;
	this->token_count = 0;
	this->cmd_count = 0;
}

SerialCommandHandler::SerialCommandHandler(uint32_t baudrate)
{
	this->baudrate = baudrate;
	this->token_count = 0;
	this->cmd_count = 0;
}

void SerialCommandHandler::registerCommand(char* id, CMDFunc func)
{
	if (this->cmd_count >= SERIAL_MAX_CMD) return;

	this->cmd_ids[this->cmd_count] = id;
	this->cmd_funcs[this->cmd_count] = func;
	this->cmd_count++;
}

void SerialCommandHandler::init()
{
	Serial.begin(this->baudrate);
}

void SerialCommandHandler::readCommand()
{
	size_t size = Serial.readBytesUntil('\n', this->serial_buffer, SERIAL_BUFFER_SIZE);
	this->serial_buffer[size] = 0;

	size_t count = 0;
	char* temp = strtok(this->serial_buffer, " ");
	
	while(temp != nullptr && count < SERIAL_MAX_TOKENS)
	{
		this->tokens[count] = temp;
		count++;

		temp = strtok(nullptr, " ");
	}

	this->token_count = count;
}

void SerialCommandHandler::handleCommand()
{
	size_t count;

	this->readCommand();

	for (count = 0; count < cmd_count; count++)
	{
		if (strcmp(this->tokens[0], this->cmd_ids[count]) == 0)
		{
			(*(this->cmd_funcs[count]))(this->tokens, this->token_count);
		}
	}
}

char* SerialCommandHandler::getToken(size_t i)
{
	if (i >= this->token_count) return nullptr;
	return this->tokens[i];
}

size_t SerialCommandHandler::getTokenCount()
{
	return this->token_count;
}