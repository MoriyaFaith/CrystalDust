#ifndef GUARD_item_menu_H
#define GUARD_item_menu_H

#include "item.h"
#include "menu_helpers.h"

#define RETURN_LOCATION_FIELD 0
#define RETURN_LOCATION_BATTLE 1
#define RETURN_LOCATION_POKEMON_LIST 2
#define RETURN_LOCATION_SHOP 3
#define RETURN_LOCATION_FIELD_2 4
#define RETURN_LOCATION_FIELD_3 5
#define RETURN_LOCATION_PC 6
#define RETURN_LOCATION_FIELD_4 7
#define RETURN_LOCATION_FIELD_5 8
#define RETURN_LOCATION_FIELD_6 9
#define RETURN_LOCATION_BATTLE_2 10
#define RETURN_LOCATION_PC_2 11
#define RETURN_LOCATION_UNCHANGED 12

// Exported type declarations
struct BagStruct
{
    void (*bagCallback)(void);
    u8 location;
    u8 pocket;
    bool8 bagOpen;
    u16 cursorPosition[POCKETS_COUNT];
    u16 scrollPosition[POCKETS_COUNT];
};

extern struct BagStruct gBagPositionStruct;

struct BagMenuStruct
{
    void (*mainCallback2)(void);
    u8 tilemapBuffer[0x800];
    u8 spriteId[12];
    u8 windowPointers[10];
    u8 itemOriginalLocation;
    u8 pocketSwitchMode:4;
    u8 itemMenuIcon:2;
    u8 inhibitItemDescriptionPrint:1;
    u8 hideCloseBagText:1;
    u16 contextMenuSelectedItem;
    u8 pocketScrollArrowsTask;
    u8 pocketSwitchArrowsTask;
    const u8* contextMenuItemsPtr;
    u8 unk824[4];
    u8 contextMenuNumItems;
    u8 totalItems[POCKETS_COUNT];
    u8 maxShowed[6];
    s16 unk834;
    u8 filler4[0xE];
    u8 filler2[4];
};

extern struct BagMenuStruct *gBagMenu;

// Exported RAM declarations

extern u16 gSpecialVar_ItemId;

// Exported ROM declarations
void sub_81AAC14(void);
void FavorLadyOpenBagMenu(void);
void QuizLadyOpenBagMenu(void);
void ApprenticeOpenBagMenu(void);
void sub_81AABB0(void);
void SetInitialScrollAndCursorPositions(u8 pocketId);
void CB2_ReturnToBagMenuPocket(void);
void CB2_BagMenuFromStartMenu(void);
u8 GetItemListPosition(u8 pocketId);
bool8 UseRegisteredKeyItemOnField(void);
void CB2_GoToSellMenu(void);
void GoToBagMenu(u8 bagMenuType, u8 pocketId, void ( *postExitMenuMainCallback2)());
void DoWallyTutorialBagMenu(void);
void ResetBagScrollPositions(void);
void ChooseBerrySetCallback(void (*callback)(void));
void CB2_ChooseBerry(void);
void Task_FadeAndCloseBagMenu(u8 taskId);
void BagCreateYesNoMenuBottomRight(u8, const struct YesNoFuncTable*);
void BagMenu_InitListsMenu(u8 taskId);
void UpdatePocketItemList(u8 pocketId);
void DisplayItemMessage(u8 taskId, u8 fontId, const u8 *str, void ( *callback)(u8 taskId));
void DisplayItemMessageOnField(u8 taskId, const u8 *src, TaskFunc callback);



#endif //GUARD_item_menu_H
