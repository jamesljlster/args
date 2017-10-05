#include <stdio.h>
#include <string.h>

#include "args_private.h"
#include "debug.h"

#define ARGS_NAME_STR	"Argument"
#define ARGS_TAG_STR	"Short Tag"
#define ARGS_LEAD_STR	"Value"

int args_find_name_indent(const args_t* list, int full, const char* msg)
{
	int i;
	int ret;
	int tmpLen;

	// Set default value
	if(msg != NULL)
	{
		ret = strlen(msg);
	}
	else
	{
		ret = 0;
	}

	// Find max length of name row
	for(i = 0; list[i].enable >= 0; i++)
	{
		if((list[i].enable > 0 || full > 0) && list[i].name != NULL)
		{
			tmpLen = strlen(list[i].name);
			if(tmpLen > ret)
			{
				ret = tmpLen;
			}
		}
	}

	return ret;
}

int args_find_tag_indent(const args_t* list, int full, const char* msg)
{
	int i;
	int ret;

	// Set default value
	if(msg != NULL)
	{
		ret = strlen(msg);
	}
	else
	{
		ret = 0;
	}

	// Find max length of tag row
	for(i = 0; list[i].enable >= 0; i++)
	{
		if((list[i].enable > 0 || full > 0) && list[i].shortTag > ' ')
		{
			if(ret < 1)
			{
				// Length of tag is always 1
				ret = 1;
			}
		}
	}

	return ret;
}

int args_find_leading_indent(const args_t* list, int full, const char* msg)
{
	int i, j;
	int ret;
	int tmpLen;

	// Set default value
	if(msg != NULL)
	{
		ret = strlen(msg);
	}
	else
	{
		ret = 0;
	}

	// Find max length of leading row
	for(i = 0; list[i].enable >= 0; i++)
	{
		if(list[i].enable > 0 || full > 0)
		{
			// Find max length of leading string
			if(list[i].leading != NULL)
			{
				tmpLen = 0;
				for(j = 0; j < list[i].allowLeading; j++)
				{
					tmpLen += strlen(list[i].leading[j]);
					if(j < list[i].allowLeading - 1)
					{
						tmpLen++;
					}
				}

				if(tmpLen > ret)
				{
					ret = tmpLen;
				}
			}
		}
	}

	return ret;
}
