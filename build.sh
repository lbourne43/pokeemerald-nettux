#!/bin/bash
#

./gen_trainer_pools.py > trainers.party
make clean
make -j $(nproc)
cp pokeemerald.gba "Pokemon Emerald nettux.gba"
