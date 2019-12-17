
[![Build Status](https://travis-ci.org/bitcoin-core/secp256k1.svg?branch=master)](https://travis-ci.org/bitcoin-core/secp256k1)

Optimized C library for EC operations on curve secp256k1.

This library is a work in progress and is being used to research best practices. Use at your own risk.

Features:
* secp256k1 ECDSA signing/verification and key generation.
* Adding/multiplying private/public keys.
* Serialization/parsing of private keys, public keys, signatures.
* Constant time, constant memory access signing and pubkey generation.
* Derandomized DSA (via RFC6979 or with a caller provided function.)
* Very efficient implementation.

Implementation details
----------------------

* General
  * No runtime heap allocation.
  * Extensive testing infrastructure.
  * Structured to facilitate review and analysis.
  * Intended to be portable to any system with a C89 compiler and uint64_t support.
  * No use of floating types, except in benchmarks.
  * Expose only higher level interfaces to minimize the API surface and improve application security. ("Be difficult to use insecurely.")
* Field operations
  * Optimized implementation of arithmetic modulo the curve's field size (2^256 - 0x1000003D1).
    * Using 5 52-bit limbs (including hand-optimized assembly for x86_64, by Diederik Huys).
    * Using 10 26-bit limbs.
  * Field inverses and square roots using a sliding window over blocks of 1s (by Peter Dettman).
* Scalar operations
  * Optimized implementation without data-dependent branches of arithmetic modulo the curve's order.
    * Using 4 64-bit limbs (relying on __int128 support in the compiler).
    * Using 8 32-bit limbs.
* Group operations
  * Point addition formula specifically simplified for the curve equation (y^2 = x^3 + 7).
  * Use addition between points in Jacobian and affine coordinates where possible.
  * Use a unified addition/doubling formula where necessary to avoid data-dependent branches.
  * Point/x comparison without a field inversion by comparison in the Jacobian coordinate space.
* Point multiplication for verification (a*P + b*G).
  * Use wNAF notation for point multiplicands.
  * Use a much larger window for multiples of G, using precomputed multiples.
  * Use Shamir's trick to do the multiplication with the public key and the generator simultaneously.
  * Optionally (off by default) use secp256k1's efficiently-computable endomorphism to split the P multiplicand into 2 half-sized ones.
* Point multiplication for signing
  * Use a precomputed table of multiples of powers of 16 multiplied with the generator, so general multiplication becomes a series of additions.
  * Intended to be completely free of timing sidechannels for secret-key operations (on reasonable hardware/toolchains)
    * Access the table with branch-free conditional moves so memory access is uniform.
    * No data-dependent branches
  * Optional runtime blinding which attempts to frustrate differential power analysis.
  * The precomputed tables add and eventually subtract points for which no known scalar (private key) is known, preventing even an attacker with control over the private key used to control the data internally.
=======
ctaes
=====

Simple C module for constant-time AES encryption and decryption.

Features:
* Simple, pure C code without any dependencies.
* No tables or data-dependent branches whatsoever, but using bit sliced approach from https://eprint.iacr.org/2009/129.pdf.
* Very small object code: slightly over 4k of executable code when compiled with -Os.
* Slower than implementations based on precomputed tables or specialized instructions, but can do ~15 MB/s on modern CPUs.

Performance
-----------

Compiled with GCC 5.3.1 with -O3, on an Intel(R) Core(TM) i7-4800MQ CPU, numbers in CPU cycles:

| Algorithm | Key schedule | Encryption per byte | Decryption per byte |
| --------- | ------------:| -------------------:| -------------------:|
| AES-128   |         2.8k |                 154 |                 161 |
| AES-192   |         3.1k |                 169 |                 181 |
| AES-256   |         4.0k |                 191 |                 203 |

Build steps
-----------

Object code:

    $ gcc -O3 ctaes.c -c -o ctaes.o

Tests:

    $ gcc -O3 ctaes.c test.c -o test

Benchmark:

    $ gcc -O3 ctaes.c bench.c -o bench

Review
------

Results of a formal review of the code can be found in http://bitcoin.sipa.be/ctaes/review.zip
=======
Ion Core integration/staging repository
=======================================
[ ![pipelines](https://img.shields.io/bitbucket/pipelines/ioncoin/ion/master "pipelines") ](https://bitbucket.org/ioncoin/ion/addon/pipelines/home/ "pipelines") [![Snap Status](https://build.snapcraft.io/badge/ioncoincore/ion.svg)](https://build.snapcraft.io/user/ioncoincore/ion) [![CircleCI Build Status](https://img.shields.io/circleci/build/bitbucket/ioncoin/ion/master?style=plastic&token=88c8747ed5aaec6a61964b24b8bce84906fd6867)](https://circleci.com/bb/ioncoin/ion)
[![BitBucket issues](https://img.shields.io/bitbucket/issues/ioncoin/ion.svg?style=social)](https://bitbucket.org/ioncoin/ion/issues?status=new&status=open)

**Latest release** | **Contact us/Chat with us** | **ionomy.com homepage status** |
 :-: | :-: | :-: |
[![Latest release](https://img.shields.io/github/release/ioncoincore/ion.svg)](https://bitbucket.org/ioncoin/ion/releases/latest) ![Release date](https://img.shields.io/github/release-date/ioncoincore/ion.svg) | [![Twitter](https://img.shields.io/twitter/url/https/bitbucket.org/ioncoin/ion.svg?style=social)](https://twitter.com/intent/tweet?text=Wow:&url=https%3A%2F%2Fgithub.com%2Fioncoincore%2Fion) [![Chat on Discord](https://img.shields.io/discord/308323056592486420.svg?logo=discord)](https://discord.gg/vuZn7gC) ![Official Encrypted Support (Matrix)](https://img.shields.io/matrix/ionsupportgeneral:matrix.provenstack.com.svg?server_fqdn=matrix.provenstack.com) | [![](https://img.shields.io/website/https/ionomy.com.svg?down_color=darkred&down_message=ionomy.com%20is%20offline&style=for-the-badge&up_color=green&up_message=ionomy.com%20is%20online)](https://ionomy.com)

_If you want to encrypt your email/files, please use public pgp key provided below._
![Keybase PGP](https://img.shields.io/keybase/pgp/ioncoincore.svg?style=flat)

## Installation methods

  We offer different installation and distribution methods covering most user needs.
  Below you can see

#### Install via SNAP (_preffered method for linux users_)

_For full information about usage and possible installation methods and Branches, please check out [Ioncore Snap Builds](snap/README.md#ioncore-snap-builds)_

    sudo snap install ioncore

[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-black.svg)](https://snapcraft.io/ioncore)

#### Download and install latest stable release binaries (_preffered method for windows and mac os users_)

[![Latest release](https://img.shields.io/github/release/ioncoincore/ion.svg)](https://bitbucket.org/ioncoin/ion/releases/latest) ![Latest stable Release](https://img.shields.io/github/downloads/ioncoincore/ion/latest/total.svg?style=social)

_For full information about usage and possible installation methods and Branches, please check out [Build and install ion (all OS)](../../tree/master/doc)_

#### Build, compile and install from source (_for advanced users_)

- [Build, compile and install documentation](../../tree/master/doc#building)


## Ion sources:

We forked from [PIVX](https://github.com/PIVX-Project/PIVX) and integrated ION's specific features into the PivX codebase.

By doing so, we connect to an enthusiastic and active community - leaving behind old Ion code that inherits from less actively developed and maintained code. Our main sources are now derived from:

pivx | dash | bitcoin
:-: | :--: | :-: |
[![](https://github.com/PIVX-Project/PIVX/raw/master/share/pixmaps/pivx64.png)](https://github.com/PIVX-Project/PIVX) | [![](https://github.com/dashpay/dash/raw/master/share/pixmaps/dash32.png)](https://github.com/dashpay/dash) | [![](https://github.com/bitcoin/bitcoin/raw/master/share/pixmaps/bitcoin32.png)](https://github.com/bitcoin/bitcoin)

More information at [ionomy.com](https://www.ionomy.com) Visit our ANN thread at [BitcoinTalk](https://bitcointalk.org/index.php?topic=1443633.7200)

## Coin Specs

Coin specifications ||
:------------ | :---:
Algorithm | Quark |
Retargeting Algorithm | DGW |
Difficulty Retargeting | Every Block
Max Coin Supply | 48,035,935.4 ION
Premine | 16,400,000 ION*

_*16,629,951 Ion Premine was burned in block [1](https://chainz.cryptoid.info/ion/block.dws?000000ed2f68cd6c7935831cc1d473da7c6decdb87e8b5dba0afff0b00002690.htm)_

### Reward Distribution

#### Genesis block

| Block Height | Reward Amount | Notes |
 ------------: | ------------: | :---: |
1 | 16,400,000 ION | Initial Pre-mine |

### PoW Rewards Breakdown

Block Height | Masternodes | Miner | Total |
 ----------: | ----------: | ----: | ----: |
2-454 | 50% (11.5 ION) | 50% (11.5 ION) | 10,419 ION |

### PoS/PoW Rewards Breakdown

Block Height | Masternodes | Miner | Budget |
 ----------: | ----------: | ----: | -----: |
455-1000 | 50% (11.5 ION) | 50% (11.5 ION)| 12,558 ION |

### PoS Rewards Breakdown

Block Height | Masternodes | Miner | Budget |
 ----------: | ----------: | ----: | -----: |
1001-125147 | 50% (11.5 ION) | 50% (11.5 ION) | 2,855,381 ION |
125148-550001 | 50% (8.5 ION) | 50% (8.5 ION) | 7,222,518 ION |
550002-551441 | 50% (0.01 ION) | 50% (0.01 ION) | 28.8 ION |
551442-570063 | 50% (8.5 ION) | 50% (8.5 ION) | 316,574 ION |
570064-1013539 | 50% (5.75 ION) | 50% (5.75 ION) | 5,099,974 ION |
1013540-1457015 | 50% (2.875 ION) | 50% (2.875 ION) | 2,549,987 ION |
1457016-3677391 | 50% (0.925 ION) | 50% (0.925 ION) | 4,107,695.6 ION |
3677392-50981391 | 50% (0.1 ION) | 50% (0.1 ION) | 9,460,800 ION |

## Ion Core FAQ/Help
_get support/chat with us or send your request per [Email](mail:support@ionomy.com). You can also join our discord or encrypted chat on matrix._
[![Twitter](https://img.shields.io/twitter/url/https/bitbucket.org/ioncoin/ion.svg?style=social)](https://twitter.com/intent/tweet?text=Wow:&url=https%3A%2F%2Fgithub.com%2Fioncoincore%2Fion) [![Chat on Discord](https://img.shields.io/discord/308323056592486420.svg?logo=discord)](https://discord.gg/vuZn7gC) ![Official Encrypted Support (Matrix)](https://img.shields.io/matrix/ionsupportgeneral:matrix.provenstack.com.svg?server_fqdn=matrix.provenstack.com)

- [Documentation](../../tree/master/doc)
  - [Setup Ion](../../tree/master/doc#setup)
  - [Running Ion Core](../../tree/master/doc#running)
    - [Windows](https://bitbucket.org/ioncoin/ion/tree/master/doc#windows)
    - [Unix](https://bitbucket.org/ioncoin/ion/tree/master/doc#unix)
    - [OSX](https://bitbucket.org/ioncoin/ion/tree/master/doc#osx)
- [Ion Core CE Wiki](../../wiki)
  - [Accounts-Explained](../../wiki/Accounts-Explained)
  - [API Call list](../../wiki/API-Calls-List)
  - [API-Reference-JSON-RPC](../../wiki/API-Reference-JSON-RPC)
  - [Data-Directory](../../wiki/Data-Directory)
- External resources
  - [Ionomy.com](https://ionomy.com)
    - [Telegram](https://t.me/ionomy)
    - [Twitter](https://twitter.com/ionomics)
    - [ionomy github](https://github.com/ionomy)
    - [reddit](https://www.reddit.com/r/ionomy/)
    - [facebook](https://facebook.com/ionomy)

## Documentation

- [Client Documentation](../../tree/master/doc)
- [Technical documentation (doxygen)](techdocu.ioncore.xyz)
