#!/usr/bin/python3

import glob
import random

def get_pool(tclass, level, name):
    lvl = int(level)
    if lvl >= 50:
        lvl = 50
    elif lvl >= 35:
        lvl = 35
    elif lvl >= 20:
        lvl = 20
    else:
        lvl = 10

    mon_list = glob.glob(f"trainer_sets/{tclass}/{lvl}-*")

    random.seed(f"{tclass} {name}")
    chosen_mons = random.sample(mon_list, 10)
    i = 1
    for mon in chosen_mons:
        i += 1
        with open(mon) as f:
            content = f.read().strip()

        content = random.choice(content.split("\n\n"))

        for l in content.split("\n"):
            if l.startswith("Level: "):
                print("Level:", level)
            else:
                print(l)
        if i <= len(chosen_mons):
            print()

with open("trainers.party.src") as f:
    lines = f.readlines()

for l in lines:
    if l.strip().startswith("{{"):
        args = l.split()[1:4]
        get_pool(args[0], args[1], args[2])
    else:
        print(l.strip())
