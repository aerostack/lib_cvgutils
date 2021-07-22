#ifndef DRONE_STATE_COMMAND_ENUM_H
#define DRONE_STATE_COMMAND_ENUM_H

// Drone State Command names declaration:
//  [*] To avoid problems make sure that the corresponding enum<->int values
//      are the same as in droneMsgsROS/msg/droneCommand.msg

namespace DroneStateCommand {
    enum StateCommand {
        IDLE     = 0,   // added, initialization value of DroneStateCommand in MAVwork... [unused in recovered code]
        TAKE_OFF = 1,
        HOVER    = 2,
        LAND     = 3,
        MOVE     = 4,
        RESET    = 5,   // same as EMERGENCY_STOP in MAVwork, thus...
        EMERGENCY_STOP = 5,
        INIT     = 6    // added, initialization value of DroneStateCommand in MAVwork...
    };
}

#endif // DRONE_STATE_COMMAND_ENUM_H
