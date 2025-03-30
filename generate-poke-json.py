#!/usr/bin/python3

import glob
import json
from copy import deepcopy

def getLearnset(pokemon, gen):
    pokemon = pokemon.title().replace("_", " ")
    pokemon = pokemon.title().replace(" ", "")
    learnset = list()
    with open("src/data/pokemon/level_up_learnsets/gen_%d.h" % gen) as f:
        lines = f.readlines()
    
    found = False
    search_string = "s%sLevelUpLearnset" % pokemon
    for l in lines:
        l = l.strip()
        if not found and search_string in l:
            found = True
            continue

        if found:
            if "LEVEL_UP_END" in l:
                break
            level, move, junk = l.split(",", 3)
            learned_move = dict()
            level = int(level.split(",")[0][14:].strip())
            move = move[6:-1].title().replace("_", " ")
            learned_move["level"] = level
            learned_move["move"] = move

            learnset.append(learned_move)

    return learnset



gens = glob.glob("src/data/pokemon/species_info/gen_*_families.h")

mons = dict()

mon_struct = dict({
    "name": "",
    "gen": 0,
    "type": False,
    "type2": False,
    "baseHP": 0,
    "baseAtk": 0,
    "baseDef": 0,
    "baseSpA": 0,
    "baseSpD": 0,
    "baseSpe": 0,
    "evolves": False,
    "evolve_level": 0,
    "learnsets": { 
        "gen1": list(),
        "gen2": list(),
        "gen3": list(),
        "gen4": list(),
        "gen5": list(),
        "gen6": list(),
        "gen7": list(),
        "gen8": list(),
        "gen9": list()
                  }
    })

species = False
for gen in gens:
    gen_num = int(gen.split("_")[-2])
    with open(gen) as f:
        lines = f.readlines()

    for l in lines:
        l = l.strip()
        if l.startswith("[SPECIES_") and l[-1] == '=':
            species = l[9:-3]
            species_key = species.lower()
            print(gen, species_key)
            species_clean = species.replace("_", " ").title()
            mons[species_key] = deepcopy(mon_struct)
            mons[species_key]['name'] = species_clean
            mons[species_key]['gen'] = gen_num
            for g in range(1, 10):
                learnset = getLearnset(species_key, g)
                if len(learnset) > 0:
                    mons[species_key]["learnsets"]["gen%d" % g] = learnset
        if l.startswith(".types"):
            types = l[19:-2]
            if "," in types:
                types = types.split(",")
                mons[species_key]['type'] = types[0].strip("( )")[5:]
                mons[species_key]['type2'] = types[1].strip("( )")[5:]
            else:
                mons[species_key]['type'] = types[5:].strip()

        if l.startswith(".baseHP"):
            mons[species_key]['baseHP'] = l.split("=")[-1].strip("\\ ,")
        if l.startswith(".baseAttack"):
            mons[species_key]['baseAtk'] = l.split("=")[-1].strip("\\ ,")
        if l.startswith(".baseDefense"):
            mons[species_key]['baseDef'] = l.split("=")[-1].strip("\\ ,")
        if l.startswith(".baseSpAttack"):
            mons[species_key]['baseSpA'] = l.split("=")[-1].strip("\\ ,")
        if l.startswith(".baseSpDefense"):
            mons[species_key]['baseSpD'] = l.split("=")[-1].strip("\\ ,")
        if l.startswith(".baseSpeed"):
            mons[species_key]['baseSpe'] = l.split("=")[-1].strip("\\ ,")

        if l.startswith(".evolutions"):
            mons[species_key]['evolves'] = True
        if "EVO_LEVEL" in l:
            mons[species_key]['evolve_level'] = l.split(',')[1].strip()



with open("poke.json", "w") as f:
    f.write(json.dumps(mons, indent=4))

"""
        .baseHP        = 75,
        .baseAttack    = 123,
        .baseDefense   = 67,
        .baseSpeed     = 95,
        .baseSpAttack  = 95,
        .baseSpDefense = 85,
        .types = MON_TYPES(TYPE_ELECTRIC),
        .catchRate = 30,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 270,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 243,
    #else
        .expYield = 199,
    #endif
        .evYield_Attack = 3,
"""

