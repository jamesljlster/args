#include <stdio.h>

#include <args.h>
#include <args_private.h>

int main(int argc, char* argv[])
{
	const args_t argList[] = {
		{0, "host-ip", 'I', 1, NULL, NULL, "Host IP Address"},
		{0, "host-port", 'P', 1, NULL, NULL, "Host Port"},
		{0, "max-client", 'M', 1, NULL, NULL, "Maximum Client Connection"},
		ARGS_TERMINATE
	};

	printf("ID of %s: %d\n", "host-ip", args_find_id(argList, "host-ip", 0));
	printf("ID of %c: %d\n", 'I', args_find_id(argList, NULL, 'I'));
	printf("\n");
	printf("ID of %s: %d\n", "host-port", args_find_id(argList, "host-port", 0));
	printf("ID of %c: %d\n", 'P', args_find_id(argList, NULL, 'P'));
	printf("\n");
	printf("ID of %s: %d\n", "max-client", args_find_id(argList, "max-client", 'M'));
	printf("ID of %c: %d\n", 'M', args_find_id(argList, NULL, 'M'));
	printf("\n");

	return 0;
}
