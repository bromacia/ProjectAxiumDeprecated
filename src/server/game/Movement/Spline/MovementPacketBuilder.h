#ifndef TRINITYSERVER_PACKET_BUILDER_H
#define TRINITYSERVER_PACKET_BUILDER_H

class ByteBuffer;
class WorldPacket;

namespace Movement
{
    class MoveSpline;
    class PacketBuilder
    {
        public:
            static void WriteCommonMonsterMovePart(const MoveSpline& mov, WorldPacket& data);
            static void WriteStopMovement(Vector3 const& loc, uint32 splineId, ByteBuffer& data);
            static void WriteMonsterMove(const MoveSpline& mov, WorldPacket& data);
            static void WriteCreate(const MoveSpline& mov, ByteBuffer& data);
    };
}
#endif // TRINITYSERVER_PACKET_BUILDER_H
