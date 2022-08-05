#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "types.h"
#include "globals.h"

/*
 * Generic structure for all objects.
*/
struct Object {
    byte id; /* Object ID */
    enum RenderFlags renderFlags; /* Bitfield for x/y flip, Display mode */
    enum TileFlags tileFlags; /* Palette line & VRAM setting */
    enum StatusFlags statusFlags; /* Orientation or mode */
    void *mappings; /* Mappings address */
    unsigned short xPos; /* X-axis position */
    unsigned short xSubPos; /* X-axis subpixel position */
    //unsigned short yScreen; /* Y-axis position for screen-fixed items */
    unsigned short yPos; /* Y-axis position */
    unsigned short ySubPos; /* Y-axis subpixel position */
    short xVel; /* X-axis velocity */
    short yVel; /* Y-axis velocity */
    short inertia; /* Potential speed */
    byte height; /* height/2 */
    byte width; /* width/2 */
    byte priority; /* Sprite stack priority - 0 is highest, 7 is lowest */
    byte displaywidth; /* Display width/2 */
    byte frame; /* Current frame displayed */
    byte anim_frame; /* Current frame in animation script */
    byte anim; /* Current animation */
    byte anim_restart; /* Restart animation flag / Next animation number (Sonic) */
    short anim_time; /* General timer (2 bytes) */
    //byte frame_time; /* Time to next frame (1 byte) */
    //byte frame_time2; /* Used by some objects as master copy of timer (1 byte) */
    byte col_type; /* Collision response type - 0 = None, 1-$3F = Enemy, $41-$7F = Items, $81-BF = Hurts, $C1-$FF = Custom */
    byte col_property; /* Collision extra property */
    byte respawn; /* Respawn list index number */
    byte routine; /* Routine number */
    byte routine2; /* Secondary routine number */
    //byte solid; /* Solid status flag */
    short angle; /* Angle of floor or rotation - 0 = Flat, $40 = Vertical left, $80 = Ceiling, $C0 = Vertical right */
    byte subtype; /* Object Subtype - Must go last because some objects use this as a start address for a list. */
    
    byte padding[21];
    short enemyCombo; /* Number of enemies broken in a row (0-$A) */
};

STATIC_ASSERT(sizeof(struct Object) == 0x40)

void DeleteObject(struct Object *obj);
void DespawnObject(struct Object *obj);
void DisplaySprite(struct Object *obj);
void ExecuteObjects(void);
void ObjectFall(struct Object *obj);
void SpeedToPos(struct Object *obj);

#define out_of_range(obj) ((128 + screen_width + 192) < ((obj->xPos & 0xff80) - (v_camera_x_pos - 128 & 0xff80)))

#endif // _OBJECT_H_