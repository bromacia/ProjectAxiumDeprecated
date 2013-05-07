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
  Custom/reset_onduelend.cpp
  Custom/npc_teleport.cpp
  Custom/npc_prof.cpp
  Custom/npc_beastmaster.cpp
  Custom/npc_arena_ranks.cpp
  Custom/npc_gossip_vendor.cpp
  Custom/npc_class_trainer.cpp
  Custom/pvp_titles.cpp
  Custom/PrematureStart.cpp
)

message("  -> Prepared: Custom")
