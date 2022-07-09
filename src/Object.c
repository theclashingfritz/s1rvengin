#include "globals.h"

#include "Object.h"

#include "Motobug.h"

#include <string.h>

// This should be a reference to DeleteObject instead. But it's not in the original.
#define NullObject ObjectFall

typedef void (*objectMainPtr)(struct Object *);

void DeleteObject(struct Object *obj) {
    // The original code doesn't NULL check.
    // But we should.
    if (obj == NULL) { return; }
    // Clear the memory of the object,
    // No deallocation is done since all objects
    // are part of a array.
    memset((void *)obj, 0, sizeof(struct Object));
}

void DespawnObject(struct Object *obj) {
    // Display sprite if object moves off screen
    if (((obj->xPos & 0xff80) - (v_camera_x_pos - 128 & 0xff80)) < 0x281) {
        // Display instead of despawn
        DisplaySprite(obj);
        return;
    }
    // Get respawn id
    byte respawn = obj->respawn;
    // Only set respawn data if the object has an respawn id
    if (respawn != 0) {
        // Clear high bit of respawn entry (i.e. Object was despawned not broken)
        v_respawn_list.respawnData[respawn] = v_respawn_list.respawnData[respawn] & 0x7f;
    }
    // Delete the object
    DeleteObject(obj);
}

void DisplaySprite(struct Object *obj) {
    unsigned short count = v_sprite_queue.priorityChunks[obj->priority].count;
    // Is this section full? (0x3F)
    // If yes, return.
    if (count >= 63) { return; }
    // Increment sprite count
    count++;
    // Insert object address into queue.
    v_sprite_queue.priorityChunks[obj->priority].objs[count] = obj;
    // Set the new count for the chunk.
    v_sprite_queue.priorityChunks[obj->priority].count = count;
    
}

void *Obj_Index[] {
    NULL,                 // This should never not be a NULL. No Object has an ID of 0. If one is set to it. It's not initalized and we should crash using a NULL to prevent possible issues.
                          // In the original code, An object index of 0 would instead use instructions as an address. Causing potentional undefined behavior.
                          // Normally an object id of 0 won't execute anyways, But better safe then sorry.
    //&SonicPlayer,       // 0x01
    &NullObject,
    &NullObject,
    &NullObject,        // 0x04
    &NullObject,
    &NullObject,
    &NullObject,
    //&Splash,            // 0x08
    //&SonicSpecial,
    //&DrownCount,
    //&Pole,
    //&FlapDoor,          // 0x0C
    //&Signpost,
    //&TitleSonic,
    //&PSBTM,
    //&Obj10,             // 0x10
    //&Bridge,
    //&SpinningLight,
    //&FireMaker,
    //&FireBall,          // 0x14
    //&SwingingPlatform,
    //&Harpoon,
    //&Helix,
    //&BasicPlatform,     // 0x18
    //&Obj19,
    //&CollapseLedge,
    //&WaterSurface,
    //&Scenery,           // 0x1C
    //&MagicSwitch,
    //&BallHog,
    //&Crabmeat,
    //&Cannonball,        // 0x20
    //&HUD,
    //&BuzzBomber,
    //&Missile,
    //&MissileDissolve,   // 0x24
    //&Rings,
    //&Monitor,
    //&ExplosionItem,
    //&Animals,           // 0x28
    //&Points,
    //&AutoDoor,
    //&Chopper,
    //&Jaws,              // 0x2C
    //&Burrobot,
    //&PowerUp,
    //&LargeGrass,
    //&GlassBlock,        // 0x30
    //&ChainStomp,
    //&Button,
    //&PushBlock,
    //&TitleCard,         // 0x34
    //&GrassFire,
    //&Spikes,
    //&RingLoss,
    //&ShieldItem,        // 0x38
    //&GameOverCard,
    //&HasPassedCard,
    //&PurpleRock,
    //&SmashWall,         // 0x3C
    //&BossGreenHill,
    //&Prison,
    //&ExplosionBomb,
    &MotoBug,             // 0x40
    //&Springs,
    //&Newtron,
    //&Roller,
    //&EdgeWalls,         // 0x44
    //&SideStomp,
    //&MarbleBrick,
    //&Bumper,
    //&BossBall,          // 0x48
    //&WaterSound,
    //&VanishSonic,
    //&GiantRing,
    //&GeyserMaker,       // 0x4C
    //&LavaGeyser,
    //&LavaWall,
    //&Obj4F,
    //&Yadrin,            // 0x50
    //&SmashBlock,
    //&MovingBlock,
    //&CollapseFloor,
    //&LavaTag,           // 0x54
    //&Batbrain,
    //&FloatingBlock,
    //&SpikeBall,
    //&BigSpikeBall,      // 0x58
    //&Elevator,
    //&CirclingPlatform,
    //&Staircase,
    //&Pylon,             // 0x5C
    //&Fan,
    //&Seesaw,
    //&Bomb,
    //&Orbinaut,          // 0x60
    //&LabyrinthBlock,
    //&Gargoyle,
    //&LabyrinthConvey,
    //&Bubble,            // 0x64
    //&Waterfall,
    //&Junction,
    //&RunningDisc,
    //&Conveyor,          // 0x68
    //&SpinPlatform,
    //&Saws,
    //&ScrapStomp,
    //&VanishPlatform,    // 0x6C
    //&Flamethrower,
    //&Electro,
    //&SpinConvey,
    //&Girder,            // 0x70
    //&Invisibarrier,
    //&Teleport,
    //&BossMarble,
    //&BossFire,          // 0x74
    //&BossSpringYard,
    //&BossBlock,
    //&BossLabyrinth,
    //&Caterkiller,       // 0x78
    //&Lamppost,
    //&BossStarLight,
    //&BossSpikeball,
    //&RingFlash,         // 0x7C
    //&HiddenBonus,
    //&SSResult,
    //&SSRChaos,
    //&ContScrItem,       // 0x80
    //&ContSonic,
    //&ScrapEggman,
    //&FalseFloor,
    //&EggmanCylinder,    // 0x84
    //&BossFinal,
    //&BossPlasma,
    //&EndSonic,
    //&EndChaos,          // 0x88
    //&EndSTH,
    //&CreditsText,
    //&EndEggman,
    //&TryChaos,          // 0x8C
    NULL
};

struct Object *RunObjects(struct Object *obj, int loopCount) {
    int i = -1;
    
    for (i = loopCount; i > -1; --i) {
        // Skip executing the object if its id is 0.
        if (obj->id != 0) {
            // Run the objects code
            objectMainPtr func = Obj_Index[obj->id];
            (*func)(obj);
        }
        // Next object
        obj = obj + 1;
    }
    
    return obj;
}

struct Object *DisplayObjects(struct Object *obj, int loopCount) {
    int i = -1;
    
    for (i = loopCount; i > -1; --i) {
        if ((obj->id != 0) && (obj->renderFlags < 0)) {
            // Display only
            DisplaySprite(obj);
        }
        // Next object
        obj = obj + 1;
    }
    
    return obj;
}

void ExecuteObjects(void) {
    // Get the first object from our slots.
    struct Object *obj = (struct Object *)&objectSlots;
    
    // If Sonic (Player) isn't dead, Execute all objects.
    // Otherwise Sonic is dead and we're not in active play.
    if (v_ost_player.routine < 3) { RunObjects(obj, countof_ost - 1); return; }
    
    // Run the first 0x20 objects normally.
    obj = RunObjects(obj, countof_ost_inert - 1);
    
    // Remaining 0x60 objects are display only.
    DisplayObjects(obj, ountof_ost_ert - 1);
}

void ObjectFall(struct Object *obj) {
    // Store our current y velocity.
    short lastYVel = obj->yVel;
    // Increase our falling speed.
    obj->yVel += 56;
    // Get both the main and sub positions.
    uint32_t *xPos = (uint32_t *)&obj->xPos;
    uint32_t *yPos = (uint32_t *)&obj->yPos;
    // Set both the main and sub positions.
    *xPos += obj->xVel * 0x100;
    *yPos += lastYVel * 0x100;
}

void SpeedToPos(struct Object *obj) {
    // Get both the main and sub positions.
    uint32_t *xPos = (uint32_t *)&obj->xPos;
    uint32_t *yPos = (uint32_t *)&obj->yPos;
    // Update x position
    *xPos += obj->xVel * 0x100;
    // Update y position
    *yPos += obj->yVel * 0x100;
}