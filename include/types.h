#include <assert.h>

#define STATIC_ASSERT(test_for_true) static_assert((test_for_true), "(" #test_for_true ") failed")

#define afEnd 0xFF // Return to beginning of animation
#define afBack 0xFE // Go back (specified number) bytes
#define afChange 0xFD // Run specified animation
#define afRoutine 0xFC // Increment routine counter
#define afReset 0xFB // Reset animation and 2nd object routine counter
#define af2ndRoutine 0xFA // Increment 2nd routine counter
#define afxflip 0x20
#define afyflip 0x40

typedef char             sbyte;
typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned short   ushort;
typedef unsigned short   word;
typedef unsigned int     dword;
typedef unsigned int     uint;
typedef unsigned long    ulong;

typedef unsigned char    undefined;
typedef unsigned char    undefined1;
typedef unsigned short   undefined2;
typedef unsigned int     undefined4;

typedef enum RenderFlags {
    Abs=0 /* Absolute screen position - Coordinates are based on the screen (e.g. the HUD) */,
    XFlip=1 /* X-Flip */,
    YFlip=2 /* Y-Flip */,
    Rel=4 /* Relative screen position - Coordinates are based on the level */,
    Bg=8 /* Align to background */,
    UseHeight=16 /* Use object height to decide if object is on screen, otherwise height is assumed to be $20 (used for large objects) */,
    RawMap=32 /* Sprites use raw mappings - i.e. Object consists of a single sprite instead of multipart sprite mappings (e.g. broken block fragments) */,
    Behind=64 /* Object is behind a loop (Sonic only) */,
    Onscreen=128 /* Object is on screen */
} RenderFlags;

typedef enum TileFlags {
    Pal1=0,
    XFlip=0x800,
    YFlip=0x1000,
    Pal2=0x2000,
    Pal3=0x4000,
    Pal4=0x6000,
    Hi=0x8000
} TileFlags;

typedef enum StatusFlags {
    0=0,
    XFlip=1 /* X-Flip */,
    Air=2 /* Sonic is in the air (Sonic Only) */,
    YFlip=2 /* Y-Flip (Objects Only) */,
    Jump=4 /* Jumping or Rolling (Sonic Only) */,
    Platform=8 /* Sonic is standing on this (objects) / Sonic is standing on object (Sonic) */,
    RollJump=16 /* Sonic is jumping after rolling (Sonic only) */,
    Pushing=32 /* Sonic is pushing this (objects) / Sonic is pushing an object (Sonic) */,
    Underwater=64 /* Sonic is underwater (Sonic only) */,
    Broken=128 /* Object has been broken (Enemies/Bosses) */
} StatusFlags;

typedef enum Zones {
    GHZ=0,
    LZ=1,
    MZ=2,
    SLZ=3,
    SYZ=4,
    SBZ=5,
    EndZ=6,
    SS=7
} Zones;

typedef enum Acts {
    Act1=0,
    Act2=1,
    Act3=2
} Acts;

typedef enum ObjectIDs {
    ID_SonicPlayer=1,
    ID_NullObject1=2,
    ID_NullObject2=3,
    ID_NullObject3=4,
    ID_NullObject4=5,
    ID_NullObject5=6,
    ID_NullObject6=7,
    ID_Splash=8,
    ID_SonicSpecial=9,
    ID_DrownCount=10,
    ID_Pole=11,
    ID_FlapDoor=12,
    ID_Signpost=13,
    ID_TitleSonic=14,
    ID_PSBTM=15,
    ID_Obj10=16,
    ID_Bridge=17,
    ID_SpinningLight=18,
    ID_FireMaker=19,
    ID_FireBall=20,
    ID_SwingingPlatform=21,
    ID_Harpoon=22,
    ID_Helix=23,
    ID_BasicPlatform=24,
    ID_Obj19=25,
    ID_CollapseLedge=26,
    ID_WaterSurface=27,
    ID_Scenery=28,
    ID_MagicSwitch=29,
    ID_BallHog=30,
    ID_Crabmeat=31,
    ID_Cannonball=32,
    ID_HUD=33,
    ID_BuzzBomber=34,
    ID_Missile=35,
    ID_MissileDissolve=36,
    ID_Rings=37,
    ID_Monitor=38,
    ID_ExplosionItem=39,
    ID_Animals=40,
    ID_Points=41,
    ID_AutoDoor=42,
    ID_Chopper=43,
    ID_Jaws=44,
    ID_Burrobot=45,
    ID_PowerUp=46,
    ID_LargeGrass=47,
    ID_GlassBlock=48,
    ID_ChainStomp=49,
    ID_Button=50,
    ID_PushBlock=51,
    ID_TitleCard=52,
    ID_GrassFire=53,
    ID_Spikes=54,
    ID_RingLoss=55,
    ID_ShieldItem=56,
    ID_GameOverCard=57,
    ID_HasPassedCard=58,
    ID_PurpleRock=59,
    ID_SmashWall=60,
    ID_BossGreenHill=61,
    ID_Prison=62,
    ID_ExplosionBomb=63,
    ID_MotoBug=64,
    ID_Springs=65,
    ID_Newtron=66,
    ID_Roller=67,
    ID_EdgeWalls=68,
    ID_SideStomp=69,
    ID_MarbleBrick=70,
    ID_Bumper=71,
    ID_BossBall=72,
    ID_WaterSound=73,
    ID_VanishSonic=74,
    ID_GiantRing=75,
    ID_GeyserMaker=76,
    ID_LavaGeyser=77,
    ID_LavaWall=78,
    ID_Obj4F=79,
    ID_Yadrin=80,
    ID_SmashBlock=81,
    ID_MovingBlock=82,
    ID_CollapseFloor=83,
    ID_LavaTag=84,
    ID_Batbrain=85,
    ID_FloatingBlock=86,
    ID_SpikeBall=87,
    ID_BigSpikeBall=88,
    ID_Elevator=89,
    ID_CirclingPlatform=90,
    ID_Staircase=91,
    ID_Pylon=92,
    ID_Fan=93,
    ID_Seesaw=94,
    ID_Bomb=95,
    ID_Orbinaut=96,
    ID_LabyrinthBlock=97,
    ID_Gargoyle=98,
    ID_LabyrinthConvey=99,
    ID_Bubble=100,
    ID_Waterfall=101,
    ID_Junction=102,
    ID_RunningDisc=103,
    ID_Conveyor=104,
    ID_SpinPlatform=105,
    ID_Saws=106,
    ID_ScrapStomp=107,
    ID_VanishPlatform=108,
    ID_Flamethrower=109,
    ID_Electro=110,
    ID_SpinConvey=111,
    ID_Girder=112,
    ID_Invisibarrier=113,
    ID_Teleport=114,
    ID_BossMarble=115,
    ID_BossFire=116,
    ID_BossSpringYard=117,
    ID_BossBlock=118,
    ID_BossLabyrinth=119,
    ID_Caterkiller=120,
    ID_Lamppost=121,
    ID_BossStarLight=122,
    ID_BossSpikeball=123,
    ID_RingFlash=124,
    ID_HiddenBonus=125,
    ID_SSResult=126,
    ID_SSRChaos=127,
    ID_ContScrItem=128,
    ID_ContSonic=129,
    ID_ScrapEggman=130,
    ID_FalseFloor=131,
    ID_EggmanCylinder=132,
    ID_BossFinal=133,
    ID_BossPlasma=134,
    ID_EndSonic=135,
    ID_EndChaos=136,
    ID_EndSTH=137,
    ID_CreditsText=138,
    ID_EndEggman=139,
    ID_TryChaos=140
} ObjectIDs;

typedef enum CollisionTypes {
    // Sizes
    col_20x20=1    /* GHZ ball */,
    col_12x20=2,
    col_20x12=3,
    col_4x16=4     /* GHZ spike pole, SYZ boss spike */,
    col_12x18=5    /* Ball Hog, Burrobot */,
    col_16x16=6    /* SBZ spikeball, Crabmeat, Monitor, SYZ spikeball, Prison */,
    col_6x6=7      /* Cannonball, Crab/Buzz missile, Ring */,
    col_24x12=8    /* Buzz Bomber */,
    col_12x16=9    /* Chopper */,
    col_16x12=10   /* Jaws */,
    col_8x8=11     /* MZ fire, Fireball, Batbrain, LZ spikeball, SLZ seesaw spike, Orbinaut, Caterkiller */,
    col_20x16=12   /* Newtron, Motobug, Yadrin */,
    col_20x8=13    /* Newtron */,
    col_14x14=14   /* Roller */,
    col_24x24=15   /* Bosses */,
    col_40x16=16   /* MZ stomper */,
    col_16x24=17   /* MZ stomper */,
    col_8x16=18    /* Giant ring */,
    col_32x112=19  /* MZ geyser */,
    col_64x32=20   /* MZ lava wall, MZ lava tag */,
    col_128x32=21  /* MZ lava tag */,
    col_32x32=22   /* MZ lava tag */,
    col_8x8_2=23   /* SYZ bumper */,
    col_4x4=24     /* SYZ spike chain, Bomb shrapnel, Orbinaut spike, LZ gargoyle fire */,
    col_32x8=25    /* SLZ swing */,
    col_12x12=26   /* Bomb enemy, FZ plasma */,
    col_8x4=27     /* LZ harpoon */,
    col_24x4=28    /* LZ harpoon */,
    col_40x4=29    /* LZ harpoon */,
    col_4x8=30     /* LZ harpoon */,
    col_4x24=31    /* LZ harpoon */,
    col_4x40=32    /* LZ harpoon */,
    col_4x32=33    /* LZ pole */,
    col_24x24_2=34 /* SBZ saw */,
    col_12x24=35   /* SBZ flamethrower */,
    col_72x8=36    /* SBZ electric */,
    
    // Types
    col_enemy=0    /* enemies */,
    col_item=64    /* monitors, rings, giant rings */,
    col_hurt=128   /* hurts Sonic when touched */,
    col_custom=192 /* enemies with spikes (yadrin, caterkiller), SYZ bumper */
} CollisionTypes;