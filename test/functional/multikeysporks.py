#!/usr/bin/env python3
# Copyright (c) 2018-2020 The Dash Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
import time

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import connect_nodes, wait_until

'''
multikeysporks.py

Test logic for several signer keys usage for spork broadcast.

We set 5 possible keys for sporks signing and set minimum 
required signers to 3. We check 1 and 2 signers can't set the spork 
value, any 3 signers can change spork value and other 3 signers
can change it again.
'''


class MultiKeySporkTest(BitcoinTestFramework):
    def set_test_params(self):
        self.num_nodes = 5
        self.setup_clean_chain = True
        self.is_network_split = False

    def setup_network(self):
        # secret(base58): cP8mJpvxNby6osj9XvXvquX9nscH3sDGYmRdbk2ZcqRDLW4vNCSM
        # keyid(hex): 60f0f57f71f0081f1aacdd8432340a33a526f91b
        # address(base58): g5JGcBbnLPk6tnaK7gdej1xiCr2LCRUEzd

        # secret(base58): cNqkzsc3Y3E4xrFDMxJiTmNtJL6dqa1rDbG15SF14Dnj4hvEqDY4
        # keyid(hex): 43dff2b09de2f904f688ec14ee6899087b889ad0
        # address(base58): gGxFxGW183Lvp4p5SbcRosXQsvia6grLdV

        # secret(base58): cQiCodRbSwhVCyVeCk7bc1ijbKcDVQvHJt6K5KF7kzPE3wTjrtHZ
        # keyid(hex): d9aa5fa00cce99101a4044e65dc544d1579890de
        # address(base58): g4CetDqweFKTAFsdu1rhitCybmHkJ5ApFg

        # secret(base58): cVawTMUeLN42sLCZo9WX2KXoCJTVzeL7d1Zh4FF5Z7cSURjSj1QY
        # keyid(hex): 0b23935ce0bea3b997a334f6fa276c9fa17687b2
        # address(base58): g3FRPg8CBKGbLMbHAWwpCopAoGm71kTj4X

        # secret(base58): cRrQMgBEp3RntRGjn3gJgWpaegKBDjttuWLNebdJpdDumoqVvfs5
        # keyid(hex): 1d1098b2b1f759b678a0a7a098637a9b898adcac
        # address(base58): gD5vQNB8VtHAqnMoGa3qTdvFForNspYkUB

        self.add_nodes(5)
        self.start_nodes()
        self.nodes[0].importprivkey("cP8mJpvxNby6osj9XvXvquX9nscH3sDGYmRdbk2ZcqRDLW4vNCSM", "spork1")
        spork1=self.nodes[0].getaccountaddress("spork1")
        self.stop_nodes()
        self.start_node(0, ["-sporkkey=cP8mJpvxNby6osj9XvXvquX9nscH3sDGYmRdbk2ZcqRDLW4vNCSM",
                            "-sporkaddr=g4CetDqweFKTAFsdu1rhitCybmHkJ5ApFg",
                            "-sporkaddr=gGxFxGW183Lvp4p5SbcRosXQsvia6grLdV",
                            "-sporkaddr=g5JGcBbnLPk6tnaK7gdej1xiCr2LCRUEzd",
                            "-sporkaddr=g3FRPg8CBKGbLMbHAWwpCopAoGm71kTj4X",
                            "-sporkaddr=gD5vQNB8VtHAqnMoGa3qTdvFForNspYkUB",
                            "-minsporkkeys=3"])
        self.start_node(1, ["-sporkkey=cNqkzsc3Y3E4xrFDMxJiTmNtJL6dqa1rDbG15SF14Dnj4hvEqDY4",
                            "-sporkaddr=g4CetDqweFKTAFsdu1rhitCybmHkJ5ApFg",
                            "-sporkaddr=gGxFxGW183Lvp4p5SbcRosXQsvia6grLdV",
                            "-sporkaddr=g5JGcBbnLPk6tnaK7gdej1xiCr2LCRUEzd",
                            "-sporkaddr=g3FRPg8CBKGbLMbHAWwpCopAoGm71kTj4X",
                            "-sporkaddr=gD5vQNB8VtHAqnMoGa3qTdvFForNspYkUB",
                            "-minsporkkeys=3"])
        self.start_node(2, ["-sporkkey=cQiCodRbSwhVCyVeCk7bc1ijbKcDVQvHJt6K5KF7kzPE3wTjrtHZ",
                            "-sporkaddr=g4CetDqweFKTAFsdu1rhitCybmHkJ5ApFg",
                            "-sporkaddr=gGxFxGW183Lvp4p5SbcRosXQsvia6grLdV",
                            "-sporkaddr=g5JGcBbnLPk6tnaK7gdej1xiCr2LCRUEzd",
                            "-sporkaddr=g3FRPg8CBKGbLMbHAWwpCopAoGm71kTj4X",
                            "-sporkaddr=gD5vQNB8VtHAqnMoGa3qTdvFForNspYkUB",
                            "-minsporkkeys=3"])
        self.start_node(3, ["-sporkkey=cVawTMUeLN42sLCZo9WX2KXoCJTVzeL7d1Zh4FF5Z7cSURjSj1QY",
                            "-sporkaddr=g4CetDqweFKTAFsdu1rhitCybmHkJ5ApFg",
                            "-sporkaddr=gGxFxGW183Lvp4p5SbcRosXQsvia6grLdV",
                            "-sporkaddr=g5JGcBbnLPk6tnaK7gdej1xiCr2LCRUEzd",
                            "-sporkaddr=g3FRPg8CBKGbLMbHAWwpCopAoGm71kTj4X",
                            "-sporkaddr=gD5vQNB8VtHAqnMoGa3qTdvFForNspYkUB",
                            "-minsporkkeys=3"])
        self.start_node(4, ["-sporkkey=cRrQMgBEp3RntRGjn3gJgWpaegKBDjttuWLNebdJpdDumoqVvfs5",
                            "-sporkaddr=g4CetDqweFKTAFsdu1rhitCybmHkJ5ApFg",
                            "-sporkaddr=gGxFxGW183Lvp4p5SbcRosXQsvia6grLdV",
                            "-sporkaddr=g5JGcBbnLPk6tnaK7gdej1xiCr2LCRUEzd",
                            "-sporkaddr=g3FRPg8CBKGbLMbHAWwpCopAoGm71kTj4X",
                            "-sporkaddr=gD5vQNB8VtHAqnMoGa3qTdvFForNspYkUB",
                            "-minsporkkeys=3"])
        # connect nodes at start
        for i in range(0, 5):
            for j in range(i, 5):
                connect_nodes(self.nodes[i], j)

    def get_test_spork_value(self, node):
        info = node.spork('show')
        # use InstantSend spork for tests
        return info['SPORK_12_INSTANTSEND_ENABLED']

    def set_test_spork_value(self, node, value):
        # use InstantSend spork for tests
        node.spork('SPORK_12_INSTANTSEND_ENABLED', value)

    def run_test(self):
        # check test spork default state
        for node in self.nodes:
            assert(self.get_test_spork_value(node) == 4070908800)

        self.bump_mocktime(1)
        # first and second signers set spork value
        self.set_test_spork_value(self.nodes[0], 1)
        self.set_test_spork_value(self.nodes[1], 1)
        # spork change requires at least 3 signers
        time.sleep(10)
        for node in self.nodes:
            assert(self.get_test_spork_value(node) != 1)

        # third signer set spork value
        self.set_test_spork_value(self.nodes[2], 1)
        # now spork state is changed
        for node in self.nodes:
            wait_until(lambda: self.get_test_spork_value(node) == 1, sleep=0.1, timeout=10)

        self.bump_mocktime(1)
        # now set the spork again with other signers to test
        # old and new spork messages interaction
        self.set_test_spork_value(self.nodes[2], 2)
        self.set_test_spork_value(self.nodes[3], 2)
        self.set_test_spork_value(self.nodes[4], 2)
        for node in self.nodes:
            wait_until(lambda: self.get_test_spork_value(node) == 2, sleep=0.1, timeout=10)


if __name__ == '__main__':
    MultiKeySporkTest().main()
