#ifndef _CMD_HANDLER_H
#define _CMD_HANDLER_H

#include <Arduino.h>

typedef void (*CMDFunc)(char* tokens[], size_t token_count);

class SerialCommandHandler
{
private:
	static const size_t SERIAL_BUFFER_SIZE = 30;
	static const size_t SERIAL_MAX_TOKENS = 6;
	static const size_t SERIAL_MAX_CMD = 6;

	uint32_t baudrate;

	char serial_buffer[SERIAL_BUFFER_SIZE + 1];
	char* tokens[SERIAL_MAX_TOKENS];
	size_t token_count;

	char* cmd_ids[SERIAL_MAX_CMD];
	CMDFunc cmd_funcs[SERIAL_MAX_CMD];
	size_t cmd_count;

	void readCommand();

public:
	SerialCommandHandler();
	SerialCommandHandler(uint32_t baudrate);

	void registerCommand(char* id, CMDFunc func);
	void init();
	void handleCommand();
	char* getToken(size_t i);
	size_t getTokenCount();
};

#endif