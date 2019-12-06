#!/usr/bin/env python3
# Copyright (c) 2015-2016 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Test the ZMQ notification interface."""
import configparser
import os
import struct

from codecs import encode

from test_framework.mininode import ionhash
from test_framework.test_framework import BitcoinTestFramework, SkipTest
from test_framework.util import (assert_equal,
                                 bytes_to_hex_str,
                                 hash256,
                                )

def ionhash_helper(b):
    return encode(ionhash(b)[::-1], 'hex_codec').decode('ascii')

class ZMQSubscriber:
    def __init__(self, socket, topic):
        self.sequence = 0
        self.socket = socket
        self.topic = topic

        import zmq
        self.socket.setsockopt(zmq.SUBSCRIBE, self.topic)

    def receive(self):
        topic, body, seq = self.socket.recv_multipart()
        # Topic should match the subscriber topic.
        assert_equal(topic, self.topic)
        # Sequence should be incremental.
        assert_equal(struct.unpack('<I', seq)[-1], self.sequence)
        self.sequence += 1
        return body


class ZMQTest (BitcoinTestFramework):
    def set_test_params(self):
        self.num_nodes = 2

    def setup_nodes(self):
        # Try to import python3-zmq. Skip this test if the import fails.
        try:
            import zmq
        except ImportError:
            raise SkipTest("python3-zmq module not available.")

        # Check that ion has been built with ZMQ enabled
        config = configparser.ConfigParser()
        if not self.options.configfile:
            self.options.configfile = os.path.abspath(os.path.join(os.path.dirname(__file__), "../config.ini"))
        config.read_file(open(self.options.configfile))

        if not config["components"].getboolean("ENABLE_ZMQ"):
            raise SkipTest("iond has not been built with zmq enabled.")

        # Initialize ZMQ context and socket.
        # All messages are received in the same socket which means
        # that this test fails if the publishing order changes.
        # Note that the publishing order is not defined in the documentation and
        # is subject to change.
        address = "tcp://127.0.0.1:28332"
        self.zmq_context = zmq.Context()
        socket = self.zmq_context.socket(zmq.SUB)
        socket.set(zmq.RCVTIMEO, 60000)
        socket.connect(address)

        # Subscribe to all available topics.
        self.hashblock = ZMQSubscriber(socket, b"hashblock")
        self.hashtx = ZMQSubscriber(socket, b"hashtx")
        self.rawblock = ZMQSubscriber(socket, b"rawblock")
        self.rawtx = ZMQSubscriber(socket, b"rawtx")

        self.extra_args = [["-zmqpub%s=%s" % (sub.topic.decode(), address) for sub in [self.hashblock, self.hashtx, self.rawblock, self.rawtx]], []]
        self.add_nodes(self.num_nodes, self.extra_args)
        self.start_nodes()

    def run_test(self):
        try:
            self._zmq_test()
        finally:
            # Destroy the ZMQ context.
            self.log.debug("Destroying ZMQ context")
            self.zmq_context.destroy(linger=None)

    def _zmq_test(self):
        num_blocks = 5
        self.log.info("Generate %(n)d blocks (and %(n)d coinbase txes)" % {"n": num_blocks})
        genhashes = self.nodes[0].generate(num_blocks)
        self.sync_all()

        self.log.info("Wait for tx")
        msg = self.zmqSubSocket.recv_multipart()
        topic = msg[0]
        assert_equal(topic, b"hashtx")
        txhash = msg[1]
        msgSequence = struct.unpack('<I', msg[-1])[-1]
        assert_equal(msgSequence, 0)  # must be sequence 0 on hashtx

        # rawtx
        msg = self.zmqSubSocket.recv_multipart()
        topic = msg[0]
        assert_equal(topic, b"rawtx")
        body = msg[1]
        msgSequence = struct.unpack('<I', msg[-1])[-1]
        assert_equal(msgSequence, 0) # must be sequence 0 on rawtx

        # Check that the rawtx hashes to the hashtx
        assert_equal(hash256(body), txhash)

        self.log.info("Wait for block")
        msg = self.zmqSubSocket.recv_multipart()
        topic = msg[0]
        assert_equal(topic, b"hashblock")
        body = msg[1]
        msgSequence = struct.unpack('<I', msg[-1])[-1]
        assert_equal(msgSequence, 0)  # must be sequence 0 on hashblock
        blkhash = bytes_to_hex_str(body)
        assert_equal(genhashes[0], blkhash)  # blockhash from generate must be equal to the hash received over zmq

        # rawblock
        msg = self.zmqSubSocket.recv_multipart()
        topic = msg[0]
        assert_equal(topic, b"rawblock")
        body = msg[1]
        msgSequence = struct.unpack('<I', msg[-1])[-1]
        assert_equal(msgSequence, 0) #must be sequence 0 on rawblock

        # Check the hash of the rawblock's header matches generate
        assert_equal(genhashes[0], ionhash_helper(body[:80]))

        self.log.info("Generate 10 blocks (and 10 coinbase txes)")
        n = 10
        genhashes = self.nodes[1].generate(n)
        self.sync_all()

        zmqHashes = []
        zmqRawHashed = []
        blockcount = 0
        for x in range(n * 4):
            msg = self.zmqSubSocket.recv_multipart()
            topic = msg[0]
            body = msg[1]
            if topic == b"hashblock":
                zmqHashes.append(bytes_to_hex_str(body))
                msgSequence = struct.unpack('<I', msg[-1])[-1]
                assert_equal(msgSequence, blockcount + 1)
                blockcount += 1
            if topic == b"rawblock":
                zmqRawHashed.append(ionhash_helper(body[:80]))
                msgSequence = struct.unpack('<I', msg[-1])[-1]
                assert_equal(msgSequence, blockcount)

        for x in range(n):
            assert_equal(genhashes[x], zmqHashes[x])  # blockhash from generate must be equal to the hash received over zmq
            assert_equal(genhashes[x], zmqRawHashed[x])

        self.log.info("Wait for tx from second node")
        payment_txid = self.nodes[1].sendtoaddress(self.nodes[0].getnewaddress(), 1.0)
        self.sync_all()

        # Should receive the broadcasted txid.
        txid = self.hashtx.receive()
        assert_equal(payment_txid, bytes_to_hex_str(txid))

        # Should receive the broadcasted raw transaction.
        hex = self.rawtx.receive()
        assert_equal(payment_txid, bytes_to_hex_str(hash256(hex)))

if __name__ == '__main__':
    ZMQTest().main()
