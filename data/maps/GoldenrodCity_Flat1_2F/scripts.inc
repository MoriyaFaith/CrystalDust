GoldenrodCity_BikeShop_MapScripts:: @ 8215139
	.byte 0

GoldenrodCity_BikeShop_EventScript_WaldasDad:: @ 821513A
	lock
	faceplayer
	specialvar VAR_RESULT, TryBufferWaldaPhrase
	compare VAR_RESULT, FALSE
	goto_if_eq GoldenrodCity_BikeShop_EventScript_WaldasDadFirstPhrase
	compare VAR_RESULT, TRUE
	goto_if_eq GoldenrodCity_BikeShop_EventScript_WaldasDadNewPhrase

GoldenrodCity_BikeShop_EventScript_GivePhrase:: @ 8215157
	special DoWaldaNamingScreen
	waitstate
	compare VAR_0x8004, 1
	goto_if_eq GoldenrodCity_BikeShop_EventScript_CancelGivePhrase
	compare VAR_0x8004, 2
	goto_if_eq GoldenrodCity_BikeShop_EventScript_CancelGiveFirstPhrase
	specialvar VAR_RESULT, TryGetWallpaperWithWaldaPhrase
	compare VAR_RESULT, TRUE
	goto_if_eq GoldenrodCity_BikeShop_EventScript_WaldaLikesPhrase
	compare VAR_RESULT, FALSE
	goto_if_eq GoldenrodCity_BikeShop_EventScript_WaldaDoesntLikePhrase
	end

GoldenrodCity_BikeShop_EventScript_WaldasDadFirstPhrase:: @ 821518D
	msgbox GoldenrodCity_BikeShop_Text_HelloDoYouKnowFunnyPhrase, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq GoldenrodCity_BikeShop_EventScript_DeclineGivePhrase
	msgbox GoldenrodCity_BikeShop_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto GoldenrodCity_BikeShop_EventScript_GivePhrase

GoldenrodCity_BikeShop_EventScript_WaldasDadNewPhrase:: @ 82151AD
	msgbox GoldenrodCity_BikeShop_Text_BeenSayingXDoYouKnowBetterPhrase, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq GoldenrodCity_BikeShop_EventScript_DeclineGivePhrase
	msgbox GoldenrodCity_BikeShop_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto GoldenrodCity_BikeShop_EventScript_GivePhrase

GoldenrodCity_BikeShop_EventScript_DeclineGivePhrase:: @ 82151CD
	msgbox GoldenrodCity_BikeShop_Text_OhIsThatRight, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_BikeShop_EventScript_CancelGivePhrase:: @ 82151D7
	msgbox GoldenrodCity_BikeShop_Text_OhYouDontKnowAny, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_BikeShop_EventScript_CancelGiveFirstPhrase:: @ 82151E1
	msgbox GoldenrodCity_BikeShop_Text_ThinkOfMyOwnPhrase, MSGBOX_DEFAULT
	call GoldenrodCity_BikeShop_EventScript_WaldasDadFaceWalda
	msgbox GoldenrodCity_BikeShop_Text_ShesNotSmilingAtAll2, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_BikeShop_EventScript_WaldaLikesPhrase:: @ 82151F8
	msgbox GoldenrodCity_BikeShop_Text_LetsGiveItATry2, MSGBOX_DEFAULT
	call GoldenrodCity_BikeShop_EventScript_WaldasDadFaceWalda
	msgbox GoldenrodCity_BikeShop_Text_OhShesLaughing, MSGBOX_DEFAULT
	applymovement 6, Common_Movement_FacePlayer
	waitmovement 0
	msgbox GoldenrodCity_BikeShop_Text_ThankYouIllGiveYouWallpaper, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_BikeShop_EventScript_WaldaDoesntLikePhrase:: @ 8215221
	msgbox GoldenrodCity_BikeShop_Text_LetsGiveItATry, MSGBOX_DEFAULT
	call GoldenrodCity_BikeShop_EventScript_WaldasDadFaceWalda
	msgbox GoldenrodCity_BikeShop_Text_ShesNotSmilingAtAll, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_BikeShop_EventScript_WaldasDadFaceWalda:: @ 8215238
	turnobject 6, DIR_EAST
	return

GoldenrodCity_BikeShop_EventScript_WaldasMom:: @ 821523D
	msgbox GoldenrodCity_BikeShop_Text_ComingUpWithMealsIsHard, MSGBOX_NPC
	end

GoldenrodCity_BikeShop_EventScript_PokeDoll:: @ 8215246
	msgbox GoldenrodCity_BikeShop_Text_ItsAPokemonPlushDoll, MSGBOX_SIGN
	end

GoldenrodCity_BikeShop_Text_ComingUpWithMealsIsHard: @ 821524F
	.string "Oh, it's so hard every day…\p"
	.string "What's hard?\n"
	.string "You need to ask?\p"
	.string "It's trying to figure out what to\n"
	.string "make for meals every day.\p"
	.string "It really isn't easy coming up with\n"
	.string "meals every day.$"

GoldenrodCity_BikeShop_Text_HelloDoYouKnowFunnyPhrase: @ 82152FA
	.string "Oh, hello!\n"
	.string "Welcome to the PEPPER household.\p"
	.string "I have a question for you.\n"
	.string "Have you ever baby-sat?\p"
	.string "You see, I'm a new father, so raising\n"
	.string "a child is all new to me.\p"
	.string "And I have a problem. My daughter\n"
	.string "WALDA doesn't laugh enough.\p"
	.string "I think she'd laugh for me if I told\n"
	.string "her something funny.\p"
	.string "Do you know of a funny word or\n"
	.string "phrase you can tell me?$"

GoldenrodCity_BikeShop_Text_BeenSayingXDoYouKnowBetterPhrase: @ 8215448
	.string "I've been saying “{STR_VAR_1}”\n"
	.string "to amuse her lately.\p"
	.string "Do you know of a better word or\n"
	.string "a phrase that might work?$"

GoldenrodCity_BikeShop_Text_WonderfulLetsHearSuggestion: @ 82154AD
	.string "Oh, that's wonderful.\n"
	.string "So, let's hear it, your suggestion.$"

GoldenrodCity_BikeShop_Text_OhIsThatRight: @ 82154E7
	.string "Oh, is that right?\p"
	.string "Well, if you come up with a good\n"
	.string "suggestion, I'm all ears.$"

GoldenrodCity_BikeShop_Text_LetsGiveItATry2: @ 8215535
	.string "Ah, I see.\n"
	.string "Well, let's give it a try, shall we?$"

GoldenrodCity_BikeShop_Text_OhShesLaughing: @ 8215565
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "Oh, yes! She's laughing!\n"
	.string "Oh, I am as delighted as she!$"

GoldenrodCity_BikeShop_Text_LetsGiveItATry: @ 82155A4
	.string "Ah, I see.\n"
	.string "Well, let's give it a try, shall we?$"

GoldenrodCity_BikeShop_Text_ShesNotSmilingAtAll: @ 82155D4
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "Hmmm… She's not smiling at all.\n"
	.string "Maybe WALDA is one serious child…$"

GoldenrodCity_BikeShop_Text_ThinkOfMyOwnPhrase: @ 821561E
	.string "Oh, so you don't know any good words.\n"
	.string "I'd better think for myself, then.\p"
	.string "Hmm…\n"
	.string "How about “{STR_VAR_1}”?\l"
	.string "Let's see if that will work.$"

GoldenrodCity_BikeShop_Text_ShesNotSmilingAtAll2: @ 8215699
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "Hmmm… She's not smiling at all.\n"
	.string "Maybe WALDA is one serious child…$"

GoldenrodCity_BikeShop_Text_OhYouDontKnowAny: @ 82156E3
	.string "Oh, so you don't know any good words.\n"
	.string "I guess I'll try to amuse her with\l"
	.string "the saying I used before.\p"
	.string "Anyways, if you have a good suggestion,\n"
	.string "don't hesitate in telling me, okay?$"

GoldenrodCity_BikeShop_Text_ThankYouIllGiveYouWallpaper: @ 8215792
	.string "Thank you!\p"
	.string "Thanks to you, my darling WALDA\n"
	.string "laughed for me!\p"
	.string "Actually, I may not look all that\n"
	.string "special, but I'm one of DEVON\l"
	.string "CORPORATION's top researchers.\p"
	.string "So, how about I do something in return\n"
	.string "for you?\p"
	.string "I know, I'll add some new wallpaper\n"
	.string "patterns for the BOXES in the PC\l"
	.string "POKéMON Storage System.\p"
	.string "In the wallpaper pattern menu,\n"
	.string "select “FRIENDS.”\p"
	.string "That will give you access to the new\n"
	.string "wallpaper patterns.$"

GoldenrodCity_BikeShop_Text_ItsAPokemonPlushDoll: @ 8215923
	.string "It's a POKéMON plush DOLL!$"
