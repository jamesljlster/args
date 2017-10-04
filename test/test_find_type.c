#include <stdio.h>

#include <args.h>
#include <args_private.h>

int main(int argc, char* argv[])
{
	int tmpType;
	int i;
	const char* name;

	for(i = 1; i < argc; i++)
	{
		tmpType = args_find_type(argv[i], &name);
		printf("%s: type = %d, name = %s\n", argv[i], tmpType, name);
	}

	return 0;
}
