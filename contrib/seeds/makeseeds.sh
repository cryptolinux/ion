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
80.194.62.218:12700
88.202.231.139:12700
95.216.29.84:12700
98.203.82.233:12700
104.207.149.116:12700
142.93.233.62:12700
144.76.97.45:12700
144.202.93.126:12700
178.63.235.201:12700
[2a01:4f9:2b:60b::2]:12700
[2a02:c207:2026:3409:6763::7]:12700"

MAINONIONSEEDS="3szeblrpwucr6eze.onion:12700
ajjhrmc7ungkr4l2.onion:12700
g2x6xrzpef6fktez.onion:12700
heaoykp3ic2ykdb4.onion:12700
mdbpyigvanhrv6jg.onion:12700
ndqgxcnvvd2s6pbr.onion:12700
sp6khtufo2zc4zql.onion:12700"

TESTNETSEEDS="37.120.155.2:27170
88.202.231.139:27170"

TESTNETONIONSEEDS="3szeblrpwucr6eze.onion:27170
ajjhrmc7ungkr4l2.onion:27170
g2x6xrzpef6fktez.onion:27170
heaoykp3ic2ykdb4.onion:27170
mdbpyigvanhrv6jg.onion:27170
ndqgxcnvvd2s6pbr.onion:27170
sp6khtufo2zc4zql.onion:27170"

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
