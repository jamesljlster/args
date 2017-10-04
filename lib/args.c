#include <stdio.h>
#include <string.h>

#include "args_private.h"
#include "debug.h"

int args_strcmp(const char* src1, const char* src2)
{
	int ret = 0;
	int cmpLen;

	LOG("enter");

	// Find compare length
	cmpLen = strlen(src1);
	if(cmpLen != strlen(src2))
	{
		ret = -1;
		goto RET;
	}

	// Compare string
	ret = strncmp(src1, src2, cmpLen);

RET:
	LOG("exit");
	return ret;
}

int args_parse(const args_t* list, int argc, const char* argv[], const char* versionMsg)
{
	int i;
	int ret = ARGS_NO_ERROR;

	LOG("enter");

	// Processing argument
	for(i = 1; i < argc; i++)
	{
	}

	LOG("exit");
	return ret;
}

int args_find_type(const char* src, const char** strPtr)
{
	int i;
	int ret = ARGS_TYPE_ARG;
	int srcLen;

	LOG("enter");

	// Find string length
	srcLen = strlen(src);

	// Parse string
	for(i = 0; i < srcLen; i++)
	{
		if(src[i] == '-')
		{
			ret++;
		}
		else
		{
			*strPtr = &src[i];
			break;
		}
	}

	LOG("exit");
	return ret;
}

int args_find_id(const args_t* list, const char* name, char shortTag)
{
	int i;
	int ret = -1;

	LOG("enter");

	// Find argument id
	i = 0;
	while(list[i].enable >= 0)
	{
		// Compare name
		if(args_strcmp(name, list[i].name) == 0)
		{
			ret = i;
			break;
		}

		// Compare tag
		if(list[i].shortTag > ' ' || shortTag == list[i].shortTag)
		{
			ret = i;
			break;
		}
	}

	LOG("exit");
	return ret;
}
