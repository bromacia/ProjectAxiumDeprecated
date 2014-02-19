# Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  Custom/TransmogMgr.cpp
  Custom/TransmogMgr.h
  Custom/MallMgr.cpp
  Custom/MallMgr.h
  Custom/ArenaMgr.cpp
  Custom/ArenaMgr.h
  Custom/ReadyMarker.cpp
  Custom/TeleportNPC.cpp
  Custom/PlayerHandbook.cpp
  Custom/VanityRewardsNPC.cpp
)

message("  -> Prepared: Custom")
