Ion Core integration/staging repository
=======================================
[ ![pipelines](https://img.shields.io/bitbucket/pipelines/ioncoin/ion/master "pipelines") ](https://bitbucket.org/ioncoin/ion/addon/pipelines/home/ "pipelines") [![Snap Status](https://build.snapcraft.io/badge/ioncoincore/ion.svg)](https://build.snapcraft.io/user/ioncoincore/ion) [![CircleCI Build Status](https://img.shields.io/circleci/build/bitbucket/ioncoin/ion/master?style=plastic&token=88c8747ed5aaec6a61964b24b8bce84906fd6867)](https://circleci.com/bb/ioncoin/ion)
[![BitBucket issues](https://img.shields.io/bitbucket/issues/ioncoin/ion.svg?style=social)](https://bitbucket.org/ioncoin/ion/issues?status=new&status=open)

[![Build Status](https://travis-ci.org/cevap/ion.svg?branch=master)](https://travis-ci.org/cevap/ion) [![GitHub version](https://badge.fury.io/gh/cevap%2Fion.svg)](https://badge.fury.io/gh/cevap%2Fion) [![Snap Status](https://build.snapcraft.io/badge/cevap/ion.svg)](https://build.snapcraft.io/user/cevap/ion) [![GitHub issues](https://img.shields.io/github/issues/cevap/ion.svg)](https://github.com/cevap/ion/issues) [![GitHub forks](https://img.shields.io/github/forks/cevap/ion.svg)](https://github.com/cevap/ion/network) [![GitHub stars](https://img.shields.io/github/stars/cevap/ion.svg)](https://github.com/cevap/ion/stargazers) [![GitHub license](https://img.shields.io/github/license/cevap/ion.svg)](https://github.com/cevap/ion)

[![Twitter](https://img.shields.io/twitter/url/https/github.com/cevap/ion.svg?style=social)](https://twitter.com/intent/tweet?text=Wow:&url=https%3A%2F%2Fgithub.com%2Fcevap%2Fion) [![Chat on Discord](https://img.shields.io/discord/308323056592486420.svg?logo=discord)](https://discord.gg/vuZn7gC) [![Latest Release](https://img.shields.io/github/downloads/cevap/ion/latest/total.svg)](https://github.com/cevap/ion/releases/latest)

Table of Contents
-----------------
- [Downloads](#downloads)
- [Important information](#important-information)
  - [Client: Helium](#client-helium)
    - [Ion Core FAQ/Help](#ion-core-faqhelp)
    - [Build and install](#build-and-install)
    - [Additional external ressources](#additional-external-ressources)
- [Introduction](#introduction)
  - [Our sources:](#our-sources)
  - [Coin Specs](#coin-specs)
  - [Reward Distribution](#reward-distribution)
    - [Genesis block](#genesis-block)
  - [PoW Rewards Breakdown](#pow-rewards-breakdown)
  - [PoS/PoW Rewards Breakdown](#pospow-rewards-breakdown)
  - [PoS Rewards Breakdown](#pos-rewards-breakdown)

## Downloads
| OS | 32-Bit | 64-Bit |
 :---: | ---: | ---: |
MacOS/OSX | [![Download ion Setup for OSX 32-bit](https://img.shields.io/github/downloads/cevap/ion/3.0.5/ion-3.0.5osx-unsigned.dmg.svg)](https://github.com/cevap/ion/releases/download/v3.0.5/ion-3.0.5osx-unsigned.dmg) | [![Download ion Setup for OSX 64-bit](https://img.shields.io/github/downloads/cevap/ion/3.0.5/ion-3.0.5osx64.tar.gz.svg)](https://github.com/cevap/ion/releases/download/3.0.5/ion-3.0.5-osx64.tar.gz) |
Windows XP/Vista/7/10 |  [![Download ion Setup for Windows 32-bit](https://img.shields.io/github/downloads/cevap/ion/latest/ion-3.0.5win32-setup-unsigned.exe.svg)](https://github.com/cevap/ion/releases/download/v3.0.5/ion-3.0.5win32-setup-unsigned.exe) | [![Download ion Setup for Windows 64-bit](https://img.shields.io/github/downloads/cevap/ion/latest/ion-3.0.5win64-setup-unsigned.exe.svg)](https://github.com/cevap/ion/releases/download/v3.0.5/ion-3.0.5win64-setup-unsigned.exe) |
| | [![Download ion binaries for Windows 32-bit](https://img.shields.io/github/downloads/cevap/ion/latest/ion-3.0.5win32.zip.svg)](https://github.com/cevap/ion/releases/download/v3.0.5/ion-3.0.5win32.zip) | [![Download ion binaries for Windows 64-bit](https://img.shields.io/github/downloads/cevap/ion/latest/ion-3.0.5win64.svg)](https://github.com/cevap/ion/releases/download/v3.0.5/ion-3.0.5win64.exe) |
Linux | [![Download ion for Linux 32-bit (i686)](https://img.shields.io/github/downloads/cevap/ion/3.0.5/ion-3.0.5i686-pc-linux-gnu.tar.gz.svg)](https://github.com/cevap/ion/releases/download/v3.0.5/ion-3.0.5i686-pc-linux-gnu.tar.gz) | [![Download ion for Linux 64-bit (x86_x64)](https://img.shields.io/github/downloads/cevap/ion/3.0.5/ion-3.0.5x86_64-linux-gnu.tar.gz.svg)](https://github.com/cevap/ion/releases/download/v3.0.5/ion-3.0.5x86_64-linux-gnu.tar.gz)
|| [![Download ion for ARM Linux](https://img.shields.io/github/downloads/cevap/ion/3.0.5/ion-3.0.5arm-linux-gnueabihf.tar.gz.svg)](https://github.com/cevap/ion/releases/download/v3.0.5/ion-3.0.5arm-linux-gnueabihf.tar.gz) | [![Download ion for aarch64 Linux](https://img.shields.io/github/downloads/cevap/ion/3.0.5/ion-3.0.5aarch64-linux-gnu.tar.gz.svg)](https://github.com/cevap/ion/releases/download/v3.0.5/ion-3.0.5aarch64-linux-gnu.tar.gz)


Download checksums: [![Download SHA256SUMS.asc](https://img.shields.io/github/downloads/cevap/ion/3.0.5/SHA256SUMS.asc.svg)](https://github.com/cevap/ion/releases/download/v3.0.5/SHA256SUMS.asc)

#### Install via SNAP (_preffered method for linux users_)

_For full information about usage and possible installation methods and Branches, please check out [Ioncore Snap Builds](snap/README.md#ioncore-snap-builds)_

[CEVAP](https://github.com/cevap/) remains as ŕepository from which SNAP builds (Ubuntu Software Center) are delivered and this is the reason why CEVAP will keep contributing and updating the code. All official releases will be available on ioncoincore as binary releases and on CEVAP over SNAP builds. In future we will rename ioncoin.* to ioncoinCE and reserve ioncoin as official name for official branch https://github.com/ioncoincore/ion.git

[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-black.svg)](https://snapcraft.io/ioncore)

### Client: Helium
![](assets/images/Helium.jpg)

#### Ion Core FAQ/Help
- [Documentation](../../tree/master/doc)
  - [Setup Ion](../../tree/master/doc#setup)
  - [Running Ion Core](../../tree/master/doc#running)
    - [Windows](https://github.com/cevap/ion/tree/master/doc#windows)
    - [Unix](https://github.com/cevap/ion/tree/master/doc#unix)
    - [OSX](https://github.com/cevap/ion/tree/master/doc#osx)
- [Ion Core CE Wiki](../../wiki)
  - [Accounts-Explained](../../wiki/Accounts-Explained)
  - [API Call list](../../wiki/API-Calls-List)
  - [API-Reference-JSON-RPC](../../wiki/API-Reference-JSON-RPC)
  - [Data-Directory](../../wiki/Data-Directory)
- External ressources
  - [Ionomy.com](https://ionomy.com)
    - [Telegram](https://t.me/ionomy)
    - [Twitter](https://twitter.com/ionomics)
    - [ionomy github](https://github.com/ionomy)
    - [reddit](https://www.reddit.com/r/ionomy/)
    - [facebook](https://facebook.com/ionomy)

#### Build and install
- [Build and install ion (all OS)](../../tree/master/doc)

#### Additional external ressources


## Introduction

We released version based on [Ion core wallet v3.1.0](../../tag/v3.1.0) which is refactored old wallet based on new source with several fixes from bitcoin as well as all commits from our main source PIVX (up to commit [4b1be145](https://github.com/PIVX-Project/PIVX/commit/4b1be14505ded427378f267d9c31a3a0f72bda75)). Please check release notes for more info.


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
Algorithm | hybrid: X11 (PoW) / SHA-256 (PoS) |
Retargeting Algorithm | DGW |
Difficulty Retargeting | Every Block
Max Coin Supply | Unlimited
Premine | 16,400,000 ION*

_*16,629,951 Ion Premine was burned in block [1](https://chainz.cryptoid.info/ion/block.dws?000000ed2f68cd6c7935831cc1d473da7c6decdb87e8b5dba0afff0b00002690.htm)_

### Reward Distribution

#### Genesis block

| Block Height | Reward Amount | Notes |
 ------------: | ------------: | :---: |
1 | 16,400,000 ION | Initial Pre-mine |

### PoW Rewards Breakdown

Block Height | Masternodes | Miner | Total | Max coin supply |
 ----------: | ----------: | ----: | ----: | ----: |
2-454 | 50% (11.5 ION) | 50% (11.5 ION) | 10,419 ION | 16,410,419 ION |

### PoS/PoW Rewards Breakdown

Block Height | Masternodes | Miner/Minter | Budget | Max coin supply |
 ----------: | ----------: | ----: | -----: | ----: |
455-1000 | 50% (11.5 ION) | 50% (11.5 ION)| 12,558 ION | 16,422,977 ION |

### PoS Rewards Breakdown

Block Height | Masternodes | Minter | Budget | Max coin supply |
 ----------: | ----------: | ----: | -----: | ----: |
1001-125146 | 50% (11.5 ION) | 50% (11.5 ION) | 2,855,358 ION | 19,278,335 ION |
125147-550001 | 50% (8.5 ION) | 50% (8.5 ION) | 7,222,535 ION | 26,500,870 ION |
550002-551441 | 50% (0.01 ION) | 50% (0.01 ION) | 28.8 ION | 26,500,898.8 ION |
551442-570063 | 50% (8.5 ION) | 50% (8.5 ION) | 316,574 ION | 26,817,472.8 ION |
570064-1013539 | 50% (5.75 ION) | 50% (5.75 ION) | 5,099,974 ION | 31,917,446.8 ION |
1013540-1600000 | 50% (2.875 ION) | 50% (2.875 ION) | 3,372,150.75 ION | 35,289,597.55 ION |

### Hybrid PoS/PoW Rewards Breakdown

Block Height | Masternodes | Miner | Minter | Annual (ION) | Annual (ELEC) |
 ----------: | ----------: | ----: | -----: | ----: | ----: |
1600000 - | 70% ION (0.35 ION) | 100% ELEC (0.5 ELEC)| 30% ION (0.15 ION)| 262,800 ION | 262,800 ELEC |

## Ion Core FAQ/Help
_get support/chat with us or send your request per [Email](mail:support@ionomy.com). You can also join our discord or encrypted chat on matrix._
[![Twitter](https://img.shields.io/twitter/url/https/bitbucket.org/ioncoin/ion.svg?style=social)](https://twitter.com/intent/tweet?text=Wow:&url=https%3A%2F%2Fgithub.com%2Fioncoincore%2Fion)

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
