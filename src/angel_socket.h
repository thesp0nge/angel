#ifndef _ANGEL_SOCKET_H
#define _ANGEL_SOCKET_H

#include <net/sock.h>

#include "engine.h"
int angel_is_a_broadcast(struct sock *sk);
#endif
