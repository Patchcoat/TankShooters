#ifndef PACKET_H
#define PACKET_H

typedef struct JoystickValue {
    unsigned short VRx = 0;
    unsigned short VRy = 0;
    bool SW = false;
} JoystickValue;
typedef struct ControllerPacket {
    JoystickValue joystick1;
    JoystickValue joystick2;
} ControllerPacket;
typedef struct TankPacket {
    bool hit;
    bool dead;
} TankPacket;

#endif