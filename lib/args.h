#ifndef __ARGS_H__
#define __ARGS_H__

enum ARGS_RETURN_VALUE
{
	ARGS_NO_ERROR		= 0,
	ARGS_PARSE_FAILED	= -1
};

typedef struct
{
	int enable;

	const char* name;
	char shortTag;

	int allowLeading;
	const char* leading;

	const char* groupMsg;
	const char* helpMsg;
} args_t;

#define ARGS_TERMINATE	{-1, NULL, 0, 0, NULL, NULL, NULL}

#ifdef __cplusplus
extern "C" {
#endif

int args_parse(const args_t* list, int argc, const char* argv[], const char* versionMsg);
void args_print_summary(const args_t* list);
void args_print_help(const args_t* list);

#ifdef __cplusplus
}
#endif

#endif
