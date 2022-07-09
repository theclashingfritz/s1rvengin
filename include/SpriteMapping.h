#ifndef _SPRITEMAPPING_H_
#define _SPRITEMAPPING_H_

#define spritepiece(x, y, width, height, tileIndex, flags) {y & 0xFF, (((width-1)<<2)+height-1) & 0xFF, (((unsigned short)tileIndex) + flags) & 0xFFFF, x & 0xFF}

struct SpriteMappingPiece {
    int8_t spriteYPos;
    byte spriteSize;
    word spriteFlags;
    int8_t spriteXPos;
};

struct SpriteMapping {
    byte spritePartCount;
    struct SpriteMappingPiece p;
};

struct SpriteMapping_4Part {
    byte spritePartCount;
    struct SpriteMappingPiece p1;
    struct SpriteMappingPiece p2;
    struct SpriteMappingPiece p3;
    struct SpriteMappingPiece p4;
};

struct SpriteMapping_5Part {
    byte spritePartCount;
    struct SpriteMappingPiece p1;
    struct SpriteMappingPiece p2;
    struct SpriteMappingPiece p3;
    struct SpriteMappingPiece p4;
    struct SpriteMappingPiece p5;
};

struct SpriteMapping_Blank {
    byte spritePartCount;
    byte padding;
};

#endif // _SPRITEMAPPING_H_