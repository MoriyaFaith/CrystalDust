#include "global.h"
#include "bg.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "m4a.h"
#include "palette.h"
#include "region_map.h"
#include "strings.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "constants/rgb.h"
#include "constants/songs.h"

/*
 *  This is the type of map shown when interacting with the metatiles for
 *  a wall-mounted Region Map (on the wall of the Pokemon Centers near the PC)
 *  It does not zoom, and pressing A or B closes the map
 *
 *  For the region map in the pokenav, see pokenav_region_map.c
 *  For the region map in the pokedex, see pokdex_area_screen.c/pokedex_area_region_map.c
 *  For the fly map, and utility functions all of the maps use, see region_map.c
 */

// Static type declarations

// Static RAM declarations

static EWRAM_DATA struct {
    MainCallback callback;
    u32 unused;
    struct RegionMap regionMap;
    u16 state;
} *sFieldRegionMapHandler = NULL;

// Static ROM declarations

static void MCB2_InitRegionMapRegisters(void);
static void VBCB_FieldUpdateRegionMap(void);
static void MCB2_FieldUpdateRegionMap(void);
static void FieldUpdateRegionMap(void);
static void ShowHelpBar(void);

extern const u16 gRegionMapFramePal[];
extern const u32 gRegionMapFrameGfxLZ[];
extern const u32 gRegionMapFrameTilemapLZ[];

// .rodata

static const struct BgTemplate sFieldRegionMapBgTemplates[] = {
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 2,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
    {
        .bg = 3,
        .charBaseIndex = 3,
        .mapBaseIndex = 28,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    }
};

static const struct WindowTemplate sFieldRegionMapWindowTemplates[] =
{
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 14,
        .baseBlock = 61
    },
    DUMMY_WIN_TEMPLATE
};

// .text

void FieldInitRegionMap(MainCallback callback)
{
    SetVBlankCallback(NULL);
    sFieldRegionMapHandler = malloc(sizeof(*sFieldRegionMapHandler));
    sFieldRegionMapHandler->state = 0;
    sFieldRegionMapHandler->callback = callback;
    SetMainCallback2(MCB2_InitRegionMapRegisters);
}

static void MCB2_InitRegionMapRegisters(void)
{
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BG2HOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    SetGpuReg(REG_OFFSET_BG3HOFS, 0);
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sFieldRegionMapBgTemplates, ARRAY_COUNT(sFieldRegionMapBgTemplates));
    InitWindows(sFieldRegionMapWindowTemplates);
    DeactivateAllTextPrinters();
    clear_scheduled_bg_copies_to_vram();
    SetMainCallback2(MCB2_FieldUpdateRegionMap);
    SetVBlankCallback(VBCB_FieldUpdateRegionMap);
}

static void VBCB_FieldUpdateRegionMap(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void MCB2_FieldUpdateRegionMap(void)
{
    FieldUpdateRegionMap();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
    do_scheduled_bg_tilemap_copies_to_vram();
}

static void FieldUpdateRegionMap(void)
{
    switch (sFieldRegionMapHandler->state)
    {
        case 0:
            InitRegionMap(&sFieldRegionMapHandler->regionMap, MAPMODE_FIELD, 0);
            CreateRegionMapPlayerIcon(0, 0);
            CreateRegionMapCursor(1, 1, TRUE);
            CreateSecondaryLayerDots(2, 2);
            CreateRegionMapName(3, 4);
            ShowHelpBar();
            sFieldRegionMapHandler->state++;
            break;
        case 1:
            LZ77UnCompVram(gRegionMapFrameGfxLZ, (u16 *)BG_CHAR_ADDR(3));
            sFieldRegionMapHandler->state++;
            break;
        case 2:
            LZ77UnCompVram(gRegionMapFrameTilemapLZ, (u16 *)BG_SCREEN_ADDR(28));
            sFieldRegionMapHandler->state++;
            break;
        case 3:
            LoadPalette(gRegionMapFramePal, 0x10, 0x20);
            sFieldRegionMapHandler->state++;
            break;
        case 4:
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0);
            sFieldRegionMapHandler->state++;
            break;
        case 5:
            SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
            ShowBg(0);
            ShowBg(2);
            ShowBg(3);
            sFieldRegionMapHandler->state++;
            break;
        case 6:
            if (!gPaletteFade.active)
            {
                sFieldRegionMapHandler->state++;
            }
            break;
        case 7:
            switch (DoRegionMapInputCallback())
            {
                case MAP_INPUT_LANDMARK_ENTER:
                    m4aSongNumStart(SE_Z_SCROLL);
                    // fallthrough
                case MAP_INPUT_LANDMARK:
                case MAP_INPUT_MOVE_END:
                    sFieldRegionMapHandler->regionMap.onButton = FALSE;
                    ShowHelpBar();
                    break;
                case MAP_INPUT_ON_BUTTON:
                    sFieldRegionMapHandler->regionMap.onButton = TRUE;
                    m4aSongNumStart(SE_W255);
                    ShowHelpBar();
                    break;
                case MAP_INPUT_A_BUTTON:
                    if (!sFieldRegionMapHandler->regionMap.onButton)
                    {
                        break;
                    }
                    m4aSongNumStart(SE_W063B);
                case MAP_INPUT_B_BUTTON:
                    sFieldRegionMapHandler->state++;
                    break;
            }
            break;
        case 8:
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
            sFieldRegionMapHandler->state++;
            break;
        case 9:
            if (!gPaletteFade.active)
            {
                FreeRegionMapResources();
                SetMainCallback2(sFieldRegionMapHandler->callback);
                if (sFieldRegionMapHandler != NULL)
                {
                    FREE_AND_SET_NULL(sFieldRegionMapHandler);
                }
                FreeAllWindowBuffers();
            }
            break;
    }
}

static void ShowHelpBar(void)
{
    const u8 color[3] = { 15, 1, 2 };

    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    AddTextPrinterParameterized3(0, 0, 144, 0, color, 0, gText_DpadMove);

    if (sFieldRegionMapHandler->regionMap.onButton)
    {
        AddTextPrinterParameterized3(0, 0, 192, 0, color, 0, gText_ACancel);
    }

    PutWindowTilemap(0);
    CopyWindowToVram(0, 3);
}
