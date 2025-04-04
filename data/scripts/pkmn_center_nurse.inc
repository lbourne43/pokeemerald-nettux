Common_EventScript_PkmnCenterNurse::
	lock
	faceplayer
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, CountPlayerTrainerStars
	goto_if_eq VAR_RESULT, 4, EventScript_PkmnCenterNurse_GoldCard
	msgbox gText_WouldYouLikeToRestYourPkmn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, EventScript_PkmnCenterNurse_HealPkmn
	goto_if_eq VAR_RESULT, NO, EventScript_PkmnCenterNurse_Goodbye
	end

EventScript_PkmnCenterNurse_Goodbye::
	message gText_WeHopeToSeeYouAgain
	return

@ VAR_0x8004 is 1 when player has Gold Card; jumps are identical
EventScript_PkmnCenterNurse_HealPkmn::
	incrementgamestat GAME_STAT_USED_POKECENTER
	call_if_eq VAR_0x8004, 0, EventScript_PkmnCenterNurse_IllTakeYourPkmn
	call_if_eq VAR_0x8004, 1, EventScript_PkmnCenterNurse_IllTakeYourPkmn2
	waitmessage
	call EventScript_PkmnCenterNurse_TakeAndHealPkmn
	goto_if_unset FLAG_POKERUS_EXPLAINED, EventScript_PkmnCenterNurse_CheckPokerus
	goto EventScript_PkmnCenterNurse_CheckTrainerHillAndUnionRoom
	end

EventScript_PkmnCenterNurse_IllTakeYourPkmn::
	message gText_IllTakeYourPkmn
	return

EventScript_PkmnCenterNurse_IllTakeYourPkmn2::
	message gText_IllTakeYourPkmn2
	return

EventScript_PkmnCenterNurse_TakeAndHealPkmn::
	hidefollower 0
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Turn
	waitmovement 0
	dofieldeffect FLDEFF_POKECENTER_HEAL
.if OW_UNION_DISABLE_CHECK == FALSE && OW_FLAG_MOVE_UNION_ROOM_CHECK != 0
	setflag OW_FLAG_MOVE_UNION_ROOM_CHECK
	call CableClub_OnResume
	clearflag OW_FLAG_MOVE_UNION_ROOM_CHECK
.endif
	waitfieldeffect FLDEFF_POKECENTER_HEAL
	applymovement VAR_0x800B, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	return

EventScript_PkmnCenterNurse_CheckTrainerHillAndUnionRoom::
	specialvar VAR_RESULT, PlayerNotAtTrainerHillEntrance
	goto_if_eq VAR_RESULT, 0, EventScript_PkmnCenterNurse_ReturnPkmn
	specialvar VAR_RESULT, BufferUnionRoomPlayerName
	copyvar VAR_0x8008, VAR_RESULT
	goto_if_eq VAR_0x8008, 0, EventScript_PkmnCenterNurse_ReturnPkmn
	goto_if_eq VAR_0x8008, 1, EventScript_PkmnCenterNurse_PlayerWaitingInUnionRoom
	end

@ VAR_0x8004 is 1 when player has Gold Card
EventScript_PkmnCenterNurse_ReturnPkmn::
	goto_if_eq VAR_0x8004, 1, EventScript_PkmnCenterNurse_ReturnPkmn2
	message gText_RestoredPkmnToFullHealth
	waitmessage
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message gText_WeHopeToSeeYouAgain
	return

EventScript_PkmnCenterNurse_ReturnPkmn2::
	message gText_ThankYouForWaiting
	waitmessage
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message gText_WeHopeToSeeYouAgain2
	return

EventScript_PkmnCenterNurse_PlayerWaitingInUnionRoom::
	goto_if_set FLAG_NURSE_UNION_ROOM_REMINDER, EventScript_PkmnCenterNurse_ReturnPkmn
	msgbox gText_RestoredPkmnToFullHealth, MSGBOX_DEFAULT
	setflag FLAG_NURSE_UNION_ROOM_REMINDER
	message CableClub_Text_PlayerIsWaiting
	waitmessage
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message gText_WeHopeToSeeYouAgain
	return

EventScript_PkmnCenterNurse_CheckPokerus::
	specialvar VAR_RESULT, IsPokerusInParty
	goto_if_eq VAR_RESULT, TRUE, EventScript_PkmnCenterNurse_ExplainPokerus
	goto_if_eq VAR_RESULT, FALSE, EventScript_PkmnCenterNurse_CheckTrainerHillAndUnionRoom
	end

EventScript_PkmnCenterNurse_ExplainPokerus::
	message gText_PokerusExplanation
	setflag FLAG_POKERUS_EXPLAINED
	return

EventScript_PkmnCenterNurse_GoldCard::
	goto_if_set FLAG_NURSE_MENTIONS_GOLD_CARD, EventScript_PkmnCenterNurse_AskForUsual
	setflag FLAG_NURSE_MENTIONS_GOLD_CARD
	msgbox gText_WelcomeCutShort, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement VAR_0x800B, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x800B, Common_Movement_Delay48
	waitmovement 0
	msgbox gText_NoticesGoldCard, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, EventScript_PkmnCenterNurse_GoldCardHealPkmn
	message gText_WeHopeToSeeYouAgain2
	return

EventScript_PkmnCenterNurse_AskForUsual::
	msgbox gText_YouWantTheUsual, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, EventScript_PkmnCenterNurse_GoldCardHealPkmn
	message gText_WeHopeToSeeYouAgain2
	return

EventScript_PkmnCenterNurse_GoldCardHealPkmn::
	setvar VAR_0x8004, 1
	goto EventScript_PkmnCenterNurse_HealPkmn
	end

Movement_PkmnCenterNurse_Bow:
	nurse_joy_bow
	delay_4
	step_end

Movement_PkmnCenterNurse_Turn:
	walk_in_place_faster_left
	step_end



NettuxHelper_EventScript_MartHelper::
        lockall
        faceplayer
        message NettuxHelper_EventScript_MartHelper_Text_1
        multichoice 25, 1, MULTICHOICE_NETTUX_MART_HELPER, 0
        closemessage
        compare VAR_RESULT, 0
        goto_if_eq NettuxHelper_EventScript_MartHelper_5
        compare VAR_RESULT, 1
        goto_if_eq NettuxHelper_EventScript_MartHelper_6
        compare VAR_RESULT, 2
        goto_if_eq NettuxHelper_EventScript_MartHelper_7
        compare VAR_RESULT, 3
        goto_if_eq NettuxHelper_EventScript_MartHelper_8
        compare VAR_RESULT, 4
        goto_if_eq NettuxHelper_HyperTrain
NettuxHelper_EventScript_MartHelper_4:
        msgbox NettuxHelper_EventScript_MartHelper_Text_2
        waitmessage
        release
        return

NettuxHelper_EventScript_MartHelper_5:
        call NettuxHelper_EventScript_BattleMart
        goto NettuxHelper_EventScript_MartHelper_4

NettuxHelper_EventScript_MartHelper_6:
        call NettuxHelper_EventScript_TrainingMart
        goto NettuxHelper_EventScript_MartHelper_4

NettuxHelper_EventScript_MartHelper_7:
        call NettuxHelper_EventScript_TMMart
        goto NettuxHelper_EventScript_MartHelper_4

NettuxHelper_EventScript_MartHelper_8:
        call NettuxHelper_EventScript_EvolveMart
        goto NettuxHelper_EventScript_MartHelper_4


NettuxHelper_EventScript_BattleMart::
        lock
        message NettuxHelper_EventScript_BattleMart_Text_0
        waitmessage
        pokemart NettuxBattleMartItems
        msgbox NettuxHelper_EventScript_BattleMart_Text_1
        release
        return


NettuxHelper_EventScript_TrainingMart::
        lock
        message NettuxHelper_EventScript_TrainingMart_Text_0
        waitmessage
        pokemart NettuxTrainingMartItems
        msgbox NettuxHelper_EventScript_BattleMart_Text_1
        release
        return


NettuxHelper_EventScript_TMMart::
        lock
        message NettuxHelper_EventScript_TMMart_Text_0
        waitmessage
        pokemart NettuxTMMartItems
        msgbox NettuxHelper_EventScript_BattleMart_Text_1
        release
        return


NettuxHelper_EventScript_EvolveMart::
        lock
        message NettuxHelper_EventScript_EvolveMart_Text_0
        waitmessage
        pokemart NettuxEvolveMartItems
        msgbox NettuxHelper_EventScript_BattleMart_Text_1
        release
        return

        .align 2
NettuxBattleMartItems:
        .2byte ITEM_EXP_SHARE
        .2byte ITEM_NONE

        .align 2
NettuxTrainingMartItems:
        .2byte ITEM_EXP_CANDY_XS
        .2byte ITEM_NONE

        .align 2
NettuxTMMartItems:
        .2byte ITEM_TM_PROTECT
        .2byte ITEM_NONE

        .align 2
NettuxEvolveMartItems:
        .2byte ITEM_LINKING_CORD
        .2byte ITEM_NONE

NettuxHelper_EventScript_MartHelper_Text_1:
        .string "Do you want a pokemon?$"

NettuxHelper_EventScript_MartHelper_Text_2:
        .string "Come back anytime!$"

NettuxHelper_EventScript_BattleMart_Text_0:
        .string "Ready to Battle?$"

NettuxHelper_EventScript_BattleMart_Text_1:
        .string "Level up!$"

NettuxHelper_EventScript_TrainingMart_Text_0:
        .string "Ready to Train?$"

NettuxHelper_EventScript_TMMart_Text_0:
        .string "Ready to Learn?$"

NettuxHelper_EventScript_EvolveMart_Text_0:
        .string "Ready to Evolve?$"


NettuxHelper_Text_WhichStat::
    .string "Which stat shoud I raise?$"

NettuxHelper_SetIVs::
        checkmoney 5000
        goto_if_eq VAR_RESULT, FALSE, NettuxHelper_EventScript_NotEnoughMoneyHyperTrain
        special ChoosePartyMon
        waitstate
        compare VAR_0x8004, PARTY_SIZE
        goto_if_ge NettuxHelper_ButIRefuse
        specialvar VAR_RESULT, ScriptGetPartyMonSpecies
        compare VAR_RESULT, SPECIES_EGG
        goto_if_eq NettuxHelper_Rejected
        message NettuxHelper_Text_WhichStat
        multichoice 0, 0, MULTICHOICE_NETTUX_HYPER_TRAINER, 0
        closemessage
        compare VAR_RESULT, 0
        goto_if_eq NettuxHelper_SetHpIVs_Proceed
        compare VAR_RESULT, 1
        goto_if_eq NettuxHelper_SetAtkIVs_Proceed
        compare VAR_RESULT, 2
        goto_if_eq NettuxHelper_SetDefIVs_Proceed
        compare VAR_RESULT, 3
        goto_if_eq NettuxHelper_SetSpaIVs_Proceed
        compare VAR_RESULT, 4
        goto_if_eq NettuxHelper_SetSpdIVs_Proceed
        compare VAR_RESULT, 5
        goto_if_eq NettuxHelper_SetSpeIVs_Proceed

        goto NettuxHelper_ButIRefuse


NettuxHelper_SetHpIVs_Proceed:
        lockall
        faceplayer
        removemoney 5000
        special MaxHpIvs
        msgbox NettuxHelper_IVsSetSuccessfully 4
        closemessage
        releaseall
        end

NettuxHelper_SetAtkIVs_Proceed:
        lockall
        faceplayer
        removemoney 5000
        special MaxAtkIvs
        msgbox NettuxHelper_IVsSetSuccessfully 4
        closemessage
        releaseall
        end

NettuxHelper_SetDefIVs_Proceed:
        lockall
        faceplayer
        removemoney 5000
        special MaxDefIvs
        msgbox NettuxHelper_IVsSetSuccessfully 4
        closemessage
        releaseall
        end

NettuxHelper_SetSpaIVs_Proceed:
        lockall
        faceplayer
        removemoney 5000
        special MaxSpAtkIvs
        msgbox NettuxHelper_IVsSetSuccessfully 4
        closemessage
        releaseall
        end

NettuxHelper_SetSpdIVs_Proceed:
        lockall
        faceplayer
        removemoney 5000
        special MaxSpDefIvs
        msgbox NettuxHelper_IVsSetSuccessfully 4
        closemessage
        releaseall
        end

NettuxHelper_SetSpeIVs_Proceed:
        lockall
        faceplayer
        removemoney 5000
        special MaxSpdIvs
        msgbox NettuxHelper_IVsSetSuccessfully 4
        closemessage
        releaseall
        end

NettuxHelper_ButIRefuse:
        lockall
        faceplayer
        msgbox NettuxHelper_ComeBackAnytime 6
        releaseall
        end

NettuxHelper_Rejected:
        lockall
        faceplayer
        msgbox NettuxHelper_Reject 6
        releaseall
        end

NettuxHelper_IVsSetSuccessfully:
        .string "Hyper training complete!\n"
        .string "Come back anytime.$"

NettuxHelper_Reject:
        .string "Sorry, I can't modify the stats\n"
        .string "of an EGG.$"

NettuxHelper_ComeBackAnytime:
        .string "Come back anytime.$"

NettuxHelper_HyperTrain::
        faceplayer
        showmoneybox 0, 0
        msgbox NettuxHelper_HyperTrain_Text_0, MSGBOX_YESNO
        hidemoneybox
        compare VAR_RESULT, YES
        goto_if_eq NettuxHelper_HyperTrain_1
        msgbox NettuxHelper_HyperTrain_Text_1, MSGBOX_NPC
        applymovement VAR_LAST_TALKED, Movement_PkmnCenterNurse_Turn @ Changed from Common_Movement_WalkInPlaceFasterLeft to force the follower to enter their Poké Ball
        applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
        callnative UpdateFollowingPokemon
        return

NettuxHelper_HyperTrain_1:
        goto NettuxHelper_SetIVs
        return

NettuxHelper_EventScript_NotEnoughMoneyHyperTrain::
        msgbox NettuxHelper_EventScript_NotEnoughMoneyHyperTrain_Text_0, MSGBOX_NPC
        return

NettuxHelper_HyperTrain_Text_0:
        .string "Hyper train a pokemon for ¥5000?$"

NettuxHelper_HyperTrain_Text_1:
        .string "Come back anytime.$"

NettuxHelper_EventScript_NotEnoughMoneyHyperTrain_Text_0:
        .string "Not enough money.$"
