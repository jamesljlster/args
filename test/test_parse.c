#include <stdio.h>

#include <args.h>

int main(int argc, char* argv[])
{
	args_t list[] = {
		{0, "host-ip", 'I', 1, NULL, NULL, "Host IP Address"},
		{0, "host-port", 'P', 1, NULL, NULL, "Host Port"},
		{0, "max-client", 'M', 1, NULL, NULL, "Maximum Client Connection"},
		{0, "enable-log", 'L', 0, NULL, NULL, "Enable Log"},
		{0, "enable-ban", 'B', 0, NULL, NULL, "Enable Ban"},
		{0, "enable-whitelist", 'W', 0, NULL, NULL, "Enable Whitelist"},
		ARGS_TERMINATE
	};

	int ret;

	ret = args_parse(list, argc, argv, NULL);
	if(ret < 0)
	{
		printf("args_parse() failed!\n");
		return -1;
	}

	return 0;
}
