#include"FighterDataLoader.h"
#include "DxLib.h"
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>


static BodyData LoadBody(int id)
{
	int bodyFileHandle = FileRead_open("Body.csv");

	if (bodyFileHandle == 0)
	{
		// ì«Ç›çûÇ›é∏îs
		return;
	}

	char bodyBuffer[256];
	char* bodyContext = nullptr;

	while (FileRead_eof(bodyFileHandle) == 0)
	{
		FileRead_gets(bodyBuffer, sizeof(bodyBuffer), bodyFileHandle);

		std::string line = bodyBuffer;
		std::stringstream ss(line);
		std::string token;

		BodyData data;

		// id
		std::getline(ss, token, ',');
		int csvId = std::stoi(token);

	}

	FileRead_close(bodyFileHandle);
}