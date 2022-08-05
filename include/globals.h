#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "types.h"

#include "Object.h"

#define screen_width  320
#define screen_height 224

struct RespawnList {
    byte respawnIndex;
    byte respawnIndex2;
    byte respawnData[254];
};

struct SpriteQueueChunk {
    ushort count;
    struct Object *objs[63];
};

struct SpriteQueue {
    struct SpriteQueueChunk priorityChunks[8];
};

extern unsigned short v_camera_x_pos;

extern RespawnList v_respawn_list;

extern SpriteQueue v_sprite_queue;

// Object Slot Stuff

#define sizeof_ost sizeof(Object)  // Size of one OST (Object) in bytes
#define countof_ost 0x80  // Number of OSTs available.
#define countof_ost_inert 0x20  // Number of OSTs that don't interact with Sonic (including Sonic himself)
#define countof_ost_ert countof_ost - countof_ost_inert  // Number of OSTs that do interact with Sonic (0x60)

// The game has 128 available object slots.
// Some slots are pre-coded to have certain things in them.
extern Object objectSlots[countof_ost];

// Hardcoded locations for certain objects.

#define v_ost_all objectSlots[0]
#define v_ost_player objectSlots[0]
// Title screen and intro
#define v_ost_titlesonic objectSlots[1] // title screen Sonic
#define v_ost_psb objectSlots[2] // title screen "Press Start Button"
#define v_ost_tm objectSlots[3] // title screen "TM"
#define v_ost_titlemask objectSlots[4] // title screen sprite mask
// Intro/credits
#define v_ost_credits objectSlots[2] // "Sonic Team Presents" and credits text
// Try again
#define v_ost_endeggman objectSlots[2] // ending/"Try Again" Eggman
#define v_ost_tryagain objectSlots[3] // "Try Again" text
#define v_ost_tryag_emeralds objectSlots[0x20] // "Try Again" chaos emeralds
// Continue
#define v_ost_cont_text objectSlots[1] // continue screen text
#define v_ost_cont_oval objectSlots[2] // continue screen oval
#define v_ost_cont_minisonic objectSlots[3] // continue screen mini Sonics
// Level - no interaction with Sonic
#define v_ost_hud objectSlots[1] // HUD
#define v_ost_titlecard1 objectSlots[2] // title card - zone name
#define v_ost_titlecard2 objectSlots[3] // title card - "zone"
#define v_ost_titlecard3 objectSlots[4] // title card - "act" 1/2/3
#define v_ost_titlecard4 objectSlots[5] // title card - oval
#define v_ost_gameover1 objectSlots[2] // game over card - "game"/"time"
#define v_ost_gameover2 objectSlots[3] // game over card - "over"
#define v_ost_shield objectSlots[6] // shield
#define v_ost_stars1 objectSlots[8] // invincibility stars
#define v_ost_stars2 objectSlots[9] // invincibility stars
#define v_ost_stars3 objectSlots[0xA] // invincibility stars
#define v_ost_stars4 objectSlots[0xB] // invincibility stars
#define v_ost_splash objectSlots[0xC] // splash
#define v_ost_bubble objectSlots[0xD] // bubble from Sonic's mouth
#define v_ost_end_emeralds objectSlots[0x10] // ending chaos emeralds
#define v_ost_haspassed1 objectSlots[0x17] // has passed act - "Sonic has"
#define v_ost_haspassed2 objectSlots[0x18] // has passed act - "passed"
#define v_ost_haspassed3 objectSlots[0x19] // has passed act - "act" 1/2/3
#define v_ost_haspassed4 objectSlots[0x1A] // has passed act - score
#define v_ost_haspassed5 objectSlots[0x1B] // has passed act - time bonus
#define v_ost_haspassed6 objectSlots[0x1C] // has passed act - ring bonus
#define v_ost_haspassed7 objectSlots[0x1D] // has passed act - oval
#define v_ost_watersurface1 objectSlots[0x1E] // LZ water surface
#define v_ost_watersurface2 objectSlots[0x1F] // LZ water surface
// Special stage results
#define v_ost_ssresult1 objectSlots[0x17] // special stage results screen
#define v_ost_ssresult2 objectSlots[0x18] // special stage results screen
#define v_ost_ssresult3 objectSlots[0x19] // special stage results screen
#define v_ost_ssresult4 objectSlots[0x1A] // special stage results screen
#define v_ost_ssresult5 objectSlots[0x1B] // special stage results screen
#define v_ost_ssres_emeralds objectSlots[0x20] // special stage results screen chaos emeralds
// Level - can interact with Sonic
#define v_ost_level_obj objectSlots[countof_ost_inert] // level object variable space (0x1800 bytes)

#endif