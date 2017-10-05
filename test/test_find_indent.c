#include <stdio.h>

#include <args.h>
#include <args_private.h>

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

	printf("Indent length of name: %d\n", args_find_name_indent(list, 1, "Argument"));
	printf("Indent length of tag: %d\n", args_find_tag_indent(list, 1, "Tag"));
	printf("Indent length of leading: %d\n", args_find_leading_indent(list, 1, "Default"));

	return 0;
}
