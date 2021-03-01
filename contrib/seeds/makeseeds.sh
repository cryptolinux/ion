#!/bin/bash
# Copyright (c) 2018-2020 The Ion developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

# replace Ion chainparamsseeds.h
# Requirements:
#  - 1. RUN THIS SCRIPT FROM ION (Coins) ROOT FOLDER
#  - 2. File contrib/seeds/generate-seeds.py MUST BE PRESENT
#       Check requirements for usage of generate-seeds.py
#       for your operating system.
#
#  - 3. sudo apt-get install python3-dnspython

# How to use:
# Run from ion root folder:
#   ./contrib/seeds/makeseeds.sh
#
#   Note: if seeds are not update, unmark cleanup on bottom of this script
#         and check if every IP address has a port in nodes_main.txt and nodes_test.txt
#   thats it.

MAINSEEDS="37.120.155.2:12700
88.202.231.139:12700"

MAINONIONSEEDS="xp57z6folwlbjltj.onion:12700
zj6p2uhmjvlyqkkm.onion:12700
ajjhrmc7ungkr4l2.onion:12700
sgt4peuocandnm3d.onion:12700
ffvhe3jqgzlgcz3i.onion:12700
rlohaqpm42nh7z53.onion:12700
fgdp4io6eapqkpe2.onion:12700
5jnxtpa2pnkgbnme.onion:12700"

TESTNETSEEDS="37.120.155.2:27170
88.202.231.139:27170"

TESTNETONIONSEEDS="3szeblrpwucr6eze.onion:27170
xp57z6folwlbjltj.onion:27170
bglmeozjd2av473l.onion:27170
sgt4peuocandnm3d.onion:27170
yhenkcie237wy2hd.onion:27170
443nzgqiitpyibs4.onion:27170
o5a24enfkxpcguxt.onion:27170
fgdp4io6eapqkpe2.onion:27170
iqix73pdf3gyj3yb.onion:27170
ajjhrmc7ungkr4l2.onion:27170"

setcustomseeds () {
cat <<EOF | tee -a $1
$2
EOF
}

getmainchainzmainseeds () {
    wget -O contrib/seeds/nodes_main.json https://chainz.cryptoid.info/ion/api.dws?q=nodes
    awk -F ':[ \t]*' '/^.*"nodes"/ {print $5 $9 $13 $17 $21 $25 $29 $33 $37 $41}' contrib/seeds/nodes_main.json >> contrib/seeds/nodes_main.txt
    rm -f contrib/seeds/nodes_main.json
    sed -i 's/,{\"subver\"/\\\n/g' contrib/seeds/nodes_main.txt
    sed -i 's/\[\"//g' contrib/seeds/nodes_main.txt
    sed -i 's/\",\"/:12700\\\n/g' contrib/seeds/nodes_main.txt
    sed -i 's/\"]}]//g' contrib/seeds/nodes_main.txt
    sed -i 's/\"]}/:12700/g' contrib/seeds/nodes_main.txt
    sed -i 's/\\//g' contrib/seeds/nodes_main.txt
    # delete last 2 line s
    sed -i '$d' contrib/seeds/nodes_main.txt
    sed -i '$d' contrib/seeds/nodes_main.txt
}

updateseeds () {
    cd contrib/seeds
    python3 generate-seeds.py . > ../../src/chainparamsseeds.h
    rm -f ./nodes_main.txt
    rm -f ./nodes_test.txt
    cd ../..
    cat < ./src/chainparamsseeds.h
}

cleanup () {
    rm -f contrib/seeds/nodes_main.json
    rm -f contrib/seeds/nodes_main.txt
    rm -f contrib/seeds/nodes_test.txt
}

cleanup
setcustomseeds "./contrib/seeds/nodes_main.txt" "$MAINSEEDS"
setcustomseeds "./contrib/seeds/nodes_main.txt" "$MAINONIONSEEDS"
setcustomseeds "./contrib/seeds/nodes_test.txt" "$TESTNETSEEDS"
setcustomseeds "./contrib/seeds/nodes_test.txt" "$TESTNETONIONSEEDS"
getmainchainzmainseeds
updateseeds
sleep 2
cleanup
