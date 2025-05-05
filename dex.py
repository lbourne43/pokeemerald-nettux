#!/usr/bin/python3
import json

with open("poke.json") as f:
    data = json.load(f)

with open("dex") as f:
    lines = f.readlines()

for l in lines:
    poke = l.strip()
    if poke.lower() in data:
        num = int(list(data.keys()).index(poke.lower().replace(" ", "_"))) + 1
        print(f"{num}\t{poke}")
    else:
        print(f"\t{poke}")
