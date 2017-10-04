#ifndef __ARGS_PRIVATE_H__
#define __ARGS_PRIVATE_H__

#include "args.h"

enum ARGS_TYPE
{
	ARGS_TYPE_ARG,
	ARGS_TYPE_TAG,
	ARGS_TYPE_NAME
};

#ifdef __cplusplus
extern "C" {
#endif

int args_strcmp(const char* src1, const char* src2);
int args_find_id(const args_t* list, const char* name, char shortTag);
int args_find_type(const char* src, const char** strPtr);

#ifdef __cplusplus
}
#endif

#endif
