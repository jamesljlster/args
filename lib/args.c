#include <stdio.h>
#include <string.h>
#include <assert.h>

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

int args_parse(args_t* list, int argc, char* argv[], const char* versionMsg)
{
	int i, j;
	int ret = ARGS_NO_ERROR;
	int type;
	int tmpLen;
	int argCount, argId;
	const char* name = NULL;
	char** leadPtr;

	LOG("enter");

	// Processing argument
	argCount = 0;
	leadPtr = NULL;
	for(i = argc - 1; i > 0; i--)
	{
		// Find string type
		type = args_find_type(argv[i], &name);
		switch(type)
		{
			case ARGS_TYPE_NAME:
				// Find argument ID
				argId = args_find_id(list, name, 0);
				if(argId < 0)
				{
					ret = ARGS_PARSE_FAILED;
					printf("Invalid argument \'%s\'\n", argv[i]);
					goto RET;
				}

				// Checking leading argument
				if(list[argId].allowLeading != argCount)
				{
					if(list[argId].allowLeading > argCount)
					{
						printf("Too few arguments for \'%s\'\n", argv[i]);
					}
					else
					{
						printf("Too many arguments for \'%s\'\n", argv[i]);
					}

					ret = ARGS_PARSE_FAILED;
					goto RET;
				}
				else
				{
					// Set enable
					list[argId].enable = 1;

					// Set leading argument
					list[argId].leading = leadPtr;
				}

				// Reset leading
				argCount = 0;
				leadPtr = NULL;

				break;

			case ARGS_TYPE_TAG:
				// Parse each tag
				tmpLen = strlen(name);
				for(j = 0; j < tmpLen; j++)
				{
					// Find argument ID
					argId = args_find_id(list, NULL, name[j]);
					if(argId < 0)
					{
						ret = ARGS_PARSE_FAILED;
						printf("Invalid argument \'-%c\'\n", name[j]);
						goto RET;
					}

					// Checking leading argument
					if(list[argId].allowLeading != argCount)
					{
						if(list[argId].allowLeading > argCount)
						{
							printf("Too few arguments for \'-%c\'\n", name[j]);
						}
						else
						{
							printf("Too many arguments for \'-%c\'\n", name[j]);
						}

						ret = ARGS_PARSE_FAILED;
						goto RET;
					}
					else
					{
						// Set enable
						list[argId].enable = 1;

						// Set leading argument
						list[argId].leading = leadPtr;
					}
				}

				// Reset leading
				argCount = 0;
				leadPtr = NULL;

				break;

			case ARGS_TYPE_ARG:
				argCount++;
				leadPtr = &argv[i];
				break;
		}
	}

RET:
	LOG("exit");
	return ret;
}

int args_find_type(const char* src, const char** strPtr)
{
	int i;
	int ret = ARGS_TYPE_ARG;
	int srcLen;
	const char* tmpPtr = &src[0];

	LOG("enter");

	// Find string length
	srcLen = strlen(src);

	// Parse string
	for(i = 0; i < srcLen - 1; i++)
	{
		if(src[i] == '-' && ret < ARGS_TYPE_NAME)
		{
			ret++;
		}
		else
		{
			break;
		}
	}
	tmpPtr = &src[i];

	// Assign value
	*strPtr = tmpPtr;

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
		if(name != NULL)
		{
			if(args_strcmp(name, list[i].name) == 0)
			{
				ret = i;
				break;
			}
		}

		// Compare tag
		if(list[i].shortTag > ' ' && shortTag == list[i].shortTag)
		{
			ret = i;
			break;
		}

		i++;
	}

	LOG("exit");
	return ret;
}
