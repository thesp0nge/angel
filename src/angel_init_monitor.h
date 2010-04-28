#ifndef _ANGEL_INIT_MONITOR_H
#define _ANGEL_INIT_MONITOR_H

#define MONITOR_SIZE	4096
#define GRANTED_SIZE	4096

#define ANGEL_GID	1001

char *default_monitored_dirs[] = {
	"/bin",
	"/sbin",
	"/var",
	"/tmp",
	"/lib",
	"/usr/bin",
	"/usr/sbin",
	"/usr/lib",
	NULL
};

char *default_monitored_files[] = {
	"/bin/su",
	"/etc/passwd",
	"/etc/group",
	"/etc/shadow",
	"/etc/securetty",
	"/etc/inittab",
	"/etc/ld.so.conf",
	NULL
};

int default_granted_uids[] = {
	0,
	-1
};

//int default_granted_gids[] = {
//	ANGEL_GID,
//	-1
//};

/* Gestirli come liste
char *user_monitored_dirs[MONITOR_SIZE];
char *user_monitored_files[MONITOR_SIZE];
int user_granted_uids[GRANTED_SIZE];
int user_granted_gids[GRANTED_SIZE];
*/
#endif
