// THIS FILE IS DEPRECATED

#ifndef TRINITY_SYSTEMCONFIG_H
#define TRINITY_SYSTEMCONFIG_H

#include "Define.h"
#include "revision.h"

#define _PACKAGENAME "TrinityCore"

#if TRINITY_ENDIAN == TRINITY_BIGENDIAN
# define _ENDIAN_STRING "big-endian"
#else
# define _ENDIAN_STRING "little-endian"
#endif

#endif