#include <linux/sysctl.h>

struct ctl_table_header *angel_sysctl_hdr;

#ifdef CONFIG_SECURITY_ANGEL_SYSCTL
#include "angel_version.h"

#define CTL_ANGEL  255

enum {
   ANGEL_VERSION_INFO = 1,
   ANGEL_BUILD_INFO = 2,
   ANGEL_CODENAME_INFO = 3
};

char angel_version[] = ANGEL_VERSION;
char angel_build[] = ANGEL_BUILD;
char angel_codename[] = ANGEL_CODENAME;

ctl_table angel_sysctl_entry[] = {
   { ANGEL_VERSION_INFO, "version", angel_version, 20*sizeof(char), 0444, NULL, &proc_dostring},
   { ANGEL_BUILD_INFO, "build", angel_build, 20*sizeof(char), 0444, NULL, &proc_dostring},
   { ANGEL_CODENAME_INFO, "codename", angel_codename, 20*sizeof(char), 0444, NULL, &proc_dostring},
   {0}
};

ctl_table angel_sysctl_dir[] = {
   { CTL_ANGEL, "angel", NULL, 0, 0555, angel_sysctl_entry, NULL },
   { 0 },
};

int angel_sysctl_create(void)
{
	angel_sysctl_hdr = register_sysctl_table(angel_sysctl_dir, 0);
	if (!angel_sysctl_hdr)
		return -1;
	return 0;
}
int angel_sysctl_destroy(void)
{
	unregister_sysctl_table(angel_sysctl_hdr);
	return 1;
}
#else
int angel_sysctl_create(void)
{
	return 0;
}
int angel_sysctl_destroy(void)
{
	return 0;
}
#endif
