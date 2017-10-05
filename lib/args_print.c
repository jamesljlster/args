#include <stdio.h>
#include <string.h>

#include "args_private.h"
#include "debug.h"

#define ARGS_NAME_STR	"[Argument]"
#define ARGS_TAG_STR	"[Tag]"
#define ARGS_LEAD_STR	"[Value]"
#define ARGS_HELP_STR	"[Description]"

#define ARGS_BUF_SIZE	128

void args_print_summary(const args_t* list)
{
	int flag = ARGS_ENABLE_NAME | ARGS_ENABLE_LEAD;
	args_print_flag(list, 0, flag);
}

void args_print_help(const args_t* list)
{
	int flag = ~ARGS_ENABLE_LEAD;
	args_print_flag(list, 1, flag);
}

void args_print_flag(const args_t* list, int full, int flag)
{
	int i, j;
	int ret;
	int procIndex;
	int nameIndent = 0, tagIndent = 0, leadIndent = 0;
	char leadBuf[ARGS_BUF_SIZE];

	// Find indents and print header
	if(flag & ARGS_ENABLE_NAME)
	{
		nameIndent = args_find_name_indent(list, full, ARGS_NAME_STR);
		printf("\t%-*s", nameIndent, ARGS_NAME_STR);
	}

	if(flag & ARGS_ENABLE_TAG)
	{
		tagIndent = args_find_tag_indent(list, full, ARGS_TAG_STR);
		printf("\t%-*s", tagIndent, ARGS_TAG_STR);
	}

	if(flag & ARGS_ENABLE_LEAD)
	{
		leadIndent = args_find_leading_indent(list, full, ARGS_LEAD_STR);
		printf("\t%-*s", leadIndent, ARGS_LEAD_STR);
	}

	if(flag & ARGS_ENABLE_HELP)
	{
		printf("\t%s", ARGS_HELP_STR);
	}

	printf("\n");

	// Print summary
	for(i = 0; list[i].enable >= 0; i++)
	{
		if(list[i].enable > 0 || full > 0)
		{
			// Print group
			if((flag & ARGS_ENABLE_GROUP) && list[i].groupMsg != NULL)
			{
				printf("\n%s\n", list[i].groupMsg);
			}

			// Print name
			if((flag & ARGS_ENABLE_NAME) && list[i].name != NULL)
			{
				printf("\t%-*s", nameIndent, list[i].name);
			}

			// Print tag
			if((flag & ARGS_ENABLE_TAG) && list[i].shortTag > ' ')
			{
				printf("\t%-*c", tagIndent, list[i].shortTag);
			}

			// Print leading
			if(flag & ARGS_ENABLE_LEAD)
			{
				leadBuf[0] = '\0';

				// Processing leading
				if(list[i].allowLeading > 0)
				{
					for(j = 0; j < list[i].allowLeading && list[i].leading != NULL; j++)
					{
						procIndex = strlen(leadBuf);
						ret = snprintf(&leadBuf[procIndex], ARGS_BUF_SIZE - procIndex - 1, "%s", list[i].leading[j]);
						if(ret <= 0 || ret >= ARGS_BUF_SIZE - 1)
						{
							fprintf(stderr, "Insufficient buffer size!\n");
						}

						if(j < list[i].allowLeading - 1)
						{
							procIndex = strlen(leadBuf);
							strncat(leadBuf, " ", ARGS_BUF_SIZE - procIndex - 1);
						}
					}
				}

				printf("\t%-*s", leadIndent, leadBuf);
			}

			// Print description
			if(flag & ARGS_ENABLE_HELP)
			{
				if(list[i].helpMsg != NULL)
				{
					printf("\t%s", list[i].helpMsg);
				}
			}

			printf("\n");
		}
	}
}

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
