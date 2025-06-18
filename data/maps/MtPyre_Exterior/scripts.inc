MtPyre_Exterior_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MtPyre_Exterior_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, MtPyre_Exterior_OnTransition
	.byte 0

MtPyre_Exterior_OnLoad:
        special nettuxSetPermanentRain
        end

MtPyre_Exterior_OnTransition:
	call MtPyre_Exterior_EventScript_CheckEnterFromSummit
	end

MtPyre_Exterior_EventScript_CheckEnterFromSummit::
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	goto_if_lt VAR_TEMP_1, 12, MtPyre_Exterior_EventScript_EnterFromSummit
	return

MtPyre_Exterior_EventScript_EnterFromSummit::
        special nettuxSetPermanentRain
	return

MtPyre_Exterior_EventScript_FogTrigger::
        special nettuxSetPermanentRain
	end

MtPyre_Exterior_EventScript_SunTrigger::
        special nettuxSetPermanentRain
	end

