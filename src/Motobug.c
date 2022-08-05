#include "globals.h"

#include "SpriteMapping.h

#include "Motobug.h"

// ---------------------------------------------------------------------------
// Mappings
// ---------------------------------------------------------------------------

struct SpriteMapping_4Part frame_moto_0 {
    4,
    spritepiece(-0x14, -0x10, 4, 2,   0, 0),
    spritepiece(-0x14,     0, 4, 1,   8, 0),
    spritepiece(0xC,      -8, 1, 2, 0xC, 0),
    spritepiece(-0xC,      8, 3, 1, 0xE, 0)
}

struct SpriteMapping_4Part frame_moto_1 {
    4,
    spritepiece(-0x14,  -0xF, 4, 2,    0, 0),
    spritepiece(-0x14,     1, 4, 1,    8, 0),
    spritepiece(0xC,      -7, 1, 2,  0xC, 0),
    spritepiece(-0xC,      9, 3, 1, 0x11, 0)
}

struct SpriteMapping_5Part frame_moto_2 {
    5,
    spritepiece(-0x14, -0x10, 4, 2,    0, 0),
    spritepiece(-0x14,     0, 4, 1, 0x14, 0),
    spritepiece(0xC,      -8, 1, 2,  0xC, 0),
    spritepiece(-0x14,     8, 2, 1, 0x18, 0),
    spritepiece(-4,        8, 2, 1, 0x12, 0),
}

struct SpriteMapping frame_moto_smoke1 {
    1,
    spritepiece(0x10, -6, 1, 1, 0x1A, 0),
}

struct SpriteMapping frame_moto_smoke2 {
    1,
    spritepiece(0x10, -6, 1, 1, 0x1B, 0),
}

struct SpriteMapping frame_moto_smoke3 {
    1,
    spritepiece(0x10, -6, 1, 1, 0x1C, 0),
}

struct SpriteMapping_Blank frame_moto_blank { 0, 0 }

#define id_frame_moto_0 0
#define id_frame_moto_1 1
#define id_frame_moto_2 2
#define id_frame_moto_smoke1 3
#define id_frame_moto_smoke2 4
#define id_frame_moto_smoke3 5
#define id_frame_moto_blank 6

void *Map_Moto[8] {
    &frame_moto_0,
    &frame_moto_1,
    &frame_moto_2,
    &frame_moto_smoke1,
    &frame_moto_smoke2,
    &frame_moto_smoke3,
    &frame_moto_blank,
    NULL
};

// ---------------------------------------------------------------------------
// Animation script
// ---------------------------------------------------------------------------

byte ani_moto_stand[] { // Animation Script
    0xF,
    id_frame_moto_2,
    afEnd
};

byte ani_moto_walk[] { // Animation Script
    7,
    id_frame_moto_0,
    id_frame_moto_1,
    id_frame_moto_0,
    id_frame_moto_2,
    afEnd
};

byte ani_moto_smoke[] { // Animation Script
    1,
    id_frame_moto_smoke1,
    id_frame_moto_blank,
    id_frame_moto_smoke1,
    id_frame_moto_blank,
    id_frame_moto_smoke2,
    id_frame_moto_blank,
    id_frame_moto_smoke2,
    id_frame_moto_blank,
    id_frame_moto_smoke2,
    id_frame_moto_blank,
    id_frame_moto_smoke3,
    afRoutine
};

byte *Ani_Moto[4] { // Animation Script Table
    &ani_moto_stand,
    &ani_moto_walk,
    &ani_moto_smoke,
    NULL
};

// ---------------------------------------------------------------------------
// Functions
// ---------------------------------------------------------------------------

#define id_Moto_Main 0
#define id_Moto_Action 1
#define id_Moto_Animate 2
#define id_Moto_Delete 3

#define id_Moto_Move 0
#define id_Moto_FindFloor 1

void MotoBug(struct Motobug *this) {
    switch(this->routine) {
        case id_Moto_Main:
            Moto_Main(this);
            break;
        case id_Moto_Action:
            Moto_Action(this);
            break;
        case id_Moto_Animate:
            Moto_Animate(this);
            break;
        case id_Moto_Delete:
        default: // If the routine isn't valid, Just delete the object.
            Moto_Delete(this);
            break;
    }
}

void Moto_Main(struct Motobug *this) {
    this->mappings = &Map_Moto;
    this->tileFlags = 0x4f0;
    this->renderFlags = Rel;
    this->priority = 4;
    this->displaywidth = 20;
    
    // Is the object a smoke trail?
    // If so just animate it.
    if (this->anim != 0) {
        // Goto Moto_Animate next.
        this->routine = id_Moto_Animate;
        Moto_Animate(this);
        return;
    }
      
    this->height = 14;
    this->width = 8;
    this->col_type = col_20x16;
    
    // Apply gravity and update position.
    ObjectFall((struct Object *)this);
    
    short distance = FindFloorObj((struct Object *)this);
    // Has motobug hit the floor?
    // If so realign with it.
    if (distance < 0) {
        this->yPos += distance;
        // Stop falling
        this->yVel = 0;
        // Goto Moto_Action next
        this->routine = id_Moto_Action;
        this->statusFlags ^= XFlip;
    }
}

void Moto_Action(struct Motobug *this) {
    switch(this->routine2) {
        case id_Moto_Move:
            Moto_Move(this);
            break;
        case id_Moto_FindFloor:
            Moto_FindFloor(this);
            break;
    }
    AnimateSprite((struct Object *)this, &Ani_Moto);
}

void Moto_Animate(struct Motobug *this) {
    AnimateSprite((struct Object *)this, &Ani_Moto);
    DisplaySprite((struct Object *)this);
}

void Moto_Delete(struct Motobug *this) {
    DeleteObject((struct Object *)this);
}

void Moto_Move(struct Motobug *this) {
    // Decrement wait timer
    this->waitTime -= 1;
    // If time remains, return and wait more
    if (this->waitTime >= 0) { return; }
    // Goto Moto_FindFloor next
    this->routine2 = id_Moto_FindFloor;
    // Move object to the left
    this->xVel = -0x100;
    this->anim = 1;
    
    this->statusFlags ^= XFlip;
    if ((this->statusFlags & XFlip) == 0) {
        // Change direction
        this->xVel = -this->xVel;
    }
}

void Moto_FindFloor(struct Motobug *this) {
    // Update position
    SpeedToPos((struct Object *)this);
    // d1 (distance) = distance to floor
    short distance = FindFloorObj((struct Object *)this);
    // If object is more than 11px above or 8px below floor,
    // Pause as we've reached a ledge.
    if ((-9 >= distance) || (distance >= 12)) {
        // Goto Moto_Move next
        this->routine2 = id_Moto_Move;
        // Set pause time to 1 second
        this->waitTime = 59;
        // Stop the object moving
        this->xVel = 0;
        this->anim = 0;
        return;
    }
    // Align to floor
    this->yPos += distance;
    // Decrement time between smoke puffs
    this->smokeTime -= 1;
    // If no time remains, Spawn a smoke object.
    if (this->smokeTime >= 0) { return; }
    // Reset timer
    this->smokeTime = 15;
    // Find a free object slot
    struct Object *smoke = NULL;
    bool success = FindFreeObj(&smoke);
    // Initalize the object if we found a slot.
    if (!success) { return; }
    // load exhaust smoke object
    smoke->id = ID_MotoBug;
    smoke->xPos = this->xPos;
    smoke->yPos = this->yPos;
    smoke->statusFlags = this->statusFlags;
    smoke->anim = 2;
}