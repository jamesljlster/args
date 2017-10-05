#ifndef __ARGS_PRIVATE_H__
#define __ARGS_PRIVATE_H__

#include "args.h"

enum ARGS_TYPE
{
	ARGS_TYPE_ARG,
	ARGS_TYPE_TAG,
	ARGS_TYPE_NAME
};

#define ARGS_ENABLE_NAME	0x01
#define ARGS_ENABLE_TAG		0x02
#define ARGS_ENABLE_LEAD	0x04
#define ARGS_ENABLE_GROUP	0x08
#define ARGS_ENABLE_HELP	0x10

#ifdef __cplusplus
extern "C" {
#endif

int args_strcmp(const char* src1, const char* src2);
int args_find_id(const args_t* list, const char* name, char shortTag);
int args_find_type(const char* src, const char** strPtr);

int args_find_name_indent(const args_t* list, int full, const char* msg);
int args_find_tag_indent(const args_t* list, int full, const char* msg);
int args_find_leading_indent(const args_t* list, int full, const char* msg);

void args_print_flag(const args_t* list, int full, int flag);

#ifdef __cplusplus
}
#endif

#endif
