- [ION Core version 5.0.99 is now available](#ion-core-version-5099-is-now-available)
  - [Mandatory Update](#mandatory-update)
  - [How to Upgrade](#how-to-upgrade)
  - [Compatibility](#compatibility)
    - [Mac OSX High Sierra](#mac-osx-high-sierra)
  - [Noteable Changes](#noteable-changes)
    - [Migrate Travis as pipeline](#migrate-travis-as-pipeline)
    - [Zerocoin](#zerocoin)
    - [Tokenimplementation](#tokenimplementation)
    - [Protocol change](#protocol-change)
  - [New RPC Commands](#new-rpc-commands)
    - [Tokens](#tokens)
    - [Masternodes](#masternodes)
  - [Deprecated RPC Commands](#deprecated-rpc-commands)
    - [Masternodes](#masternodes-1)
  - [5.0.99 Change log](#5099-change-log)

## ION Core version 5.0.99 is now available  

Download at: https://github.com/ioncoincore/ion/releases

This is a new major version release, including various bug fixes, performance improvements, implementation of the Atomic Token Protocol (ATP), as well as updated translations.

Please report bugs using the issue tracker at github: https://bitbucket.org/ioncoin/ion/issues?status=new&status=open

### Mandatory Update
___  

ION Core v5.0.99 is a mandatory update for all users. This release contains new consensus rules and improvements that are not backwards compatible with older versions. Users will have a grace period of up to two week to update their clients before enforcement of this update is enabled - a grace period that will end at block 1320000 the latest.

### How to Upgrade
___
If you are running an older version, shut it down. Wait until it has completely shut down (which might take a few minutes for older versions), then run the installer (on Windows) or just copy over /Applications/ION-Qt (on Mac) or iond/ion-qt (on Linux).

### Compatibility
ION Core is extensively tested on multiple operating systems using the Linux kernel, macOS 10.8+, and Windows Vista and later.

Microsoft ended support for Windows XP on April 8th, 2014, No attempt is made to prevent installing or running the software on Windows XP, you can still do so at your own risk but be aware that there are known instabilities and issues. Please do not report issues about Windows XP to the issue tracker.

ION Core should also work on most other Unix-like systems but is not frequently tested on them.
Database space usage improvements
--------------------------------
Version 0.13.0.0 introduced a new database (evodb) which is found in the datadir of Ion Core. It turned
out that this database grows quite fast when a lot of changes inside the deterministic masternode list happen,
which is for example the case when a lot PoSe punishing/banning is happening. Such a situation happened
immediately after the activation LLMQ DKGs, causing the database to grow a lot. This release introduces
a new format in which information in "evodb" is stored, which causes it grow substantially slower.  

Version 0.14.0.0 also introduced a new database (llmq) which is also found in the datadir of Ion Core.
This database stores all LLMQ signatures for 7 days. After 7 days, a cleanup task removes old signatures.
The idea was that the "llmq" database would grow in the beginning and then stay at an approximately constant
size. The recent stress test on mainnet has however shown that the database grows too much and causes a risk
of out-of-space situations. This release will from now also remove signatures when the corresponding InstantSend
lock is fully confirmed on-chain (superseded by a ChainLock). This should remove >95% of all signatures from
the database. After the upgrade, no space saving will be observed however as this logic is only applied to new
signatures, which means that it will take 7 days until the whole "llmq" database gets to its minimum size.

DKG and LLMQ signing failures fixed
-----------------------------------
Recent stress tests have shown that masternodes start to ban each other under high load and specific situations.
This release fixes this and thus makes it a highly recommended upgrade for masternodes.

MacOS: macOS: disable AppNap during sync and mixing
---------------------------------------------------
AppNap is disabled now when Ion Core is syncing/reindexing or mixing.

Signed binaries for Windows
---------------------------
This release is the first one to include signed binaries for Windows.

New RPC command: quorum memberof <proTxHash>
--------------------------------------------
This RPC allows you to verify which quorums a masternode is supposed to be a member of. It will also show
if the masternode succesfully participated in the DKG process.

More information about number of InstantSend locks
--------------------------------------------------
The debug console will now show how many InstantSend locks Ion Core knows about. Please note that this number
does not necessarily equal the number of mempool transactions.

The "getmempoolinfo" RPC also has a new field now which shows the same information.

0.14.0.3 Change log
===================

See detailed [set of changes](https://bitbucket.org/ioncoin/ion/compare/v0.14.0.2...ionpay:v0.14.0.3).

- [`f2443709b`](https://bitbucket.org/ioncoin/ion/commit/f2443709b) Update release-notes.md for 0.14.0.3 (#3054)
- [`17ba23871`](https://bitbucket.org/ioncoin/ion/commit/17ba23871) Re-verify invalid IS sigs when the active quorum set rotated (#3052)
- [`8c49d9b54`](https://bitbucket.org/ioncoin/ion/commit/8c49d9b54) Remove recovered sigs from the LLMQ db when corresponding IS locks get confirmed (#3048)
- [`2e0cf8a30`](https://bitbucket.org/ioncoin/ion/commit/2e0cf8a30) Add "instantsendlocks" to getmempoolinfo RPC (#3047)
- [`a8fb8252e`](https://bitbucket.org/ioncoin/ion/commit/a8fb8252e) Use fEnablePrivateSend instead of fPrivateSendRunning
- [`a198a04e0`](https://bitbucket.org/ioncoin/ion/commit/a198a04e0) Show number of InstantSend locks in Debug Console (#2919)
- [`013169d63`](https://bitbucket.org/ioncoin/ion/commit/013169d63) Optimize on-disk deterministic masternode storage to reduce size of evodb (#3017)
- [`9ac7a998b`](https://bitbucket.org/ioncoin/ion/commit/9ac7a998b) Add "isValidMember" and "memberIndex" to "quorum memberof" and allow to specify quorum scan count (#3009)
- [`99824a879`](https://bitbucket.org/ioncoin/ion/commit/99824a879) Implement "quorum memberof" (#3004)
- [`7ea319fd2`](https://bitbucket.org/ioncoin/ion/commit/7ea319fd2) Bail out properly on Evo DB consistency check failures in ConnectBlock/DisconnectBlock (#3044)
- [`b1ffedb2d`](https://bitbucket.org/ioncoin/ion/commit/b1ffedb2d) Do not count 0-fee txes for fee estimation (#3037)
- [`974055a9b`](https://bitbucket.org/ioncoin/ion/commit/974055a9b) Fix broken link in PrivateSend info dialog (#3031)
- [`781b16579`](https://bitbucket.org/ioncoin/ion/commit/781b16579) Merge pull request #3028 from PastaPastaPasta/backport-12588
- [`5af6ce91d`](https://bitbucket.org/ioncoin/ion/commit/5af6ce91d) Add Ion Core Group codesign certificate (#3027)
- [`873ab896c`](https://bitbucket.org/ioncoin/ion/commit/873ab896c) Fix osslsigncode compile issue in gitian-build (#3026)
- [`ea8569e97`](https://bitbucket.org/ioncoin/ion/commit/ea8569e97) Backport #12783: macOS: disable AppNap during sync (and mixing) (#3024)
- [`4286dde49`](https://bitbucket.org/ioncoin/ion/commit/4286dde49) Remove support for InstantSend locked gobject collaterals (#3019)
- [`788d42dbc`](https://bitbucket.org/ioncoin/ion/commit/788d42dbc) Bump version to 0.14.0.3 and copy release notes (#3053)

Credits
=======

Thanks to everyone who directly contributed to this release:

- UdjinM6

As well as everyone that submitted issues and reviewed pull requests.

Older releases
==============

### Mandatory Update
___  

ION Core v5.0.99 is a mandatory update for all users. This release contains new consensus rules and improvements that are not backwards compatible with older versions. Users will have a grace period of up to two week to update their clients before enforcement of this update is enabled - a grace period that will end at block 1320000 the latest.

### How to Upgrade
___
If you are running an older version, shut it down. Wait until it has completely shut down (which might take a few minutes for older versions), then run the installer (on Windows) or just copy over /Applications/ION-Qt (on Mac) or iond/ion-qt (on Linux).

### Compatibility
ION Core is extensively tested on multiple operating systems using the Linux kernel, macOS 10.8+, and Windows Vista and later.

Microsoft ended support for Windows XP on April 8th, 2014, No attempt is made to prevent installing or running the software on Windows XP, you can still do so at your own risk but be aware that there are known instabilities and issues. Please do not report issues about Windows XP to the issue tracker.

ION Core should also work on most other Unix-like systems but is not frequently tested on them.

#### Mac OSX High Sierra  
Currently there are issues with the 4.x gitian release on MacOS version 10.13 (High Sierra), no reports of issues on older versions of MacOS.

### Noteable Changes
______
- core: switch core from pivx to ion
- move to bitbucket
- token implementaion (IIP6)
- fix regtest and testnet
- new regtest genesis is inline with source
- updated dependencies
  - QT 5.9.8
  - expat 2.2.9
  - libevent 2.1.11
  - [zeromq latest master](https://github.com/zeromq/libzmq/tree/eb54966cb9393bfd990849231ea7d10e34f6319e)
  - dbus 1.13.12
  - miniupnpc 2.0.20180203
  - native_ds_storke 1.1.2
  - native_biplist 1.0.3
  - native_mac_alias 2.0.7
- Support more architectures
  - mips
  - mipsel
  - s390x
  - powerppc64
  - powerppc64le
- new gui and artworks
  - spinner
- updated and refactored build process
  - gitian build script extended
    - can be used with latest debian or ubuntu
    - added upload to a server over SSH
  - fix latest dependencies
- deployment process
  - snapcraft from bitbucket
  - snap on launchpad
  - ~~continuous build process on circleci~~
    - ~~napcraft~~
    - ~~deb packages~~
    - ~~rpm packages~~
    - ~~gitian~~
- BLS
  - [BLS Signature Scheme](https://github.com/dashpay/dips/blob/master/dip-0006/bls_signature_scheme.md)
  - [BLS M-of-N Threshold Scheme and Distributed Key Generation](https://github.com/dashpay/dips/blob/master/dip-0006/bls_m-of-n_threshold_scheme_and_dkg.md#bls-m-of-n-threshold-scheme-and-distributed-key-generation)
- ~~I2p support~~
. ~~new Hybrid-PoW~~

#### Migrate Travis as pipeline

#### Zerocoin
- Reimplement zerocoin to new source

#### Tokenimplementation
- Reimplement zerocoin to new source

#### Protocol change

- Atomic Token Protocol (ATP)

    **Introduction:**  

    As part of the integration of game development functionality and blockchain technology, the ION community chose to adopt a token system as part of its blockchain core. The community approved proposal IIP 0002 was put to vote in July 2018, after which development started. Instead of developing a solution from scratch, the team assessed a number of proposals and implementations that were currently being worked on for other Bitcoin family coins. Selection criteria were:

    * Fully open, with active development
    * Emphasis on permissionless transactions
    * Efficient in terms of resource consumption
    * Simple and elegant underlying principles 

    The ATP system implemented is based on the Group Tokenization proposal by Andrew Stone / BU.

    **References:**

    [GROUP Tokenization specification by Andrew Stone](https://docs.google.com/document/d/1X-yrqBJNj6oGPku49krZqTMGNNEWnUJBRFjX7fJXvTs/edit#heading=h.sn65kz74jmuf)  
    [GROUP Tokenization reference implementation for Bitcoin Cash](https://github.com/gandrewstone/BitcoinUnlimited/commits/tokengroups)  

    For the technical principles underlying ION Group Tokenization, the above documentation is used as our standard.

    ION developers fine tuned, extended and customized the Group Tokenization implementation. This documentation aims to support the ION community in:

    * Using the ION group token system
    * Creating additional tests as part of the development process
    * Finding new use cases that need development support


### New RPC Commands
__________

#### Tokens

`configuremanagementtoken "ticker" "name" decimalpos "description_url" description_hash ( confirm_send )  `  
`configuretoken "ticker" "name" ( decimalpos "description_url" description_hash ) ( confirm_send )  `  
`createtokenauthorities "groupid" "ionaddress" authoritylist  `  
`droptokenauthorities "groupid" "transactionid" outputnr [ authority1 ( authority2 ... ) ] `   
`getsubgroupid "groupid" "data"  `  
`gettokenbalance ( "groupid" )  `  
`listtokenauthorities "groupid"`    
`listtokenssinceblock "groupid" ( "blockhash" target-confirmations includeWatchonly ) `   
`listtokentransactions "groupid" ( count from includeWatchonly ) `   
`melttoken "groupid" quantity  `  
`minttoken "groupid" "ionaddress" quantity  `  
`sendtoken "groupid" "address" amount  `  
`tokeninfo [list, all, stats, groupid, ticker, name] ( "specifier " )  `  
`scantokens <action> ( <scanobjects> ) `

#### Masternodes
`createmasternodekey `  
`getmasternodeoutputs `  
`getmasternodecount`  
`getmasternodeoutputs`  
`getmasternodescores ( blocks )`  
`getmasternodestatus`  
`getmasternodewinners ( blocks "filter" )`  
`startmasternode "local|all|many|missing|disabled|alias" lockwallet ( "alias" )`
`listmasternodeconf ( "filter" )`  
`listmasternodes ( "filter" )`


### Deprecated RPC Commands
___
#### Masternodes
`masternode count`  
`masternode current`  
`masternode debug`  
`masternode genkey`  
`masternode outputs`  
`masternode start`  
`masternode start-alias`  
`masternode start-<mode>`  
`masternode status`  
`masternode list`  
`masternode list-conf`  
`masternode winners`  


### 5.0.99 Change log
=======
Gist gitian build scripts
----------------------------
**Note**: Please change SIGNER to your key and version to desired version, in current release it is version 3.0.2, in future releases gist will be updated.

If you use scripts, after wget has downloaded the script, run `sed -i 's/49464B32BA6683BA/YOURGPGKEY/g''  and replace `YOURGPGKEY` with your LONG Key ID. The same can be done with version.
 - Linux only: [build offline](https://gist.github.com/cevap/9d7ef39be185cc07c3d0a9b33da2fba5)
 - Windows only: [build offline](https://gist.github.com/cevap/5d6ac38f6e8530d45ab31499bc3a62ff)
 - MacOS only (without HighSierra)[build offline](https://gist.github.com/cevap/a5a90607da3a9b058b8c0aea20fdd75a)

Setup **signer** and **version**/branch
-------------------------------------------------

```
cd ./ion
export SIGNER="49464B32BA6683BA" # Replace with your Key
export VERSION=3.0.2 # github branch
git fetch
git checkout v${VERSION}
cd ..

# update signature
cd ./gitian.sigs
git pull
cd ..

# update gitian builder
cd ./gitian-builder
git pull
cd ..

# Fetch and create inputs: (first time, or when dependency versions change)
cd ./gitian-builder
mkdir -p inputs
wget -P inputs https://github.com/cevap/osslsigncode/releases/download/v1.7.1/osslsigncode-Backports-to-1.7.1.patch
wget -P inputs -O inputs/v1.7.1.tar.gz https://github.com/cevap/osslsigncode/archive/v1.7.1.tar.gz
wget -P inputs https://github.com/cevap/MacOSX-SDKs/releases/download/MacOSX10.11.sdk-trusty/MacOSX10.11.sdk.tar.gz
cd ..

# prebuild ion dependencies
cd ./gitian-builder
make -C ../ion/depends download SOURCES_PATH=`pwd`/cache/common
cd ..
```

Building offline
------------------

```
cd ./gitian-builder

# Build offline for linux
./bin/gbuild --url ion=/home/gitianuser/ion,signature=/home/gitianuser/gitian.sigs --num-make 2 --memory 3000 --commit ion=v${VERSION} ../ion/contrib/gitian-descriptors/gitian-linux.yml

# Sign for linux
./bin/gsign --signer "$SIGNER" --release ${VERSION}-linux --destination ../gitian.sigs/ ../ion/contrib/gitian-descriptors/gitian-linux.yml
mv build/out/ion-*.tar.gz build/out/src/ion-*.tar.gz ../

# Build offline for windows
./bin/gbuild --url ion=/home/gitianuser/ion,signature=/home/gitianuser/gitian.sigs --num-make 2 --memory 3000 --commit ion=v${VERSION} ../ion/contrib/gitian-descriptors/gitian-win.yml

# Sign for windows
./bin/gsign --signer "$SIGNER" --release ${VERSION}-win-unsigned --destination ../gitian.sigs/ ../ion/contrib/gitian-descriptors/gitian-win.yml
mv build/out/ion-*-win-unsigned.tar.gz inputs/ion-win-unsigned.tar.gz
mv build/out/ion-*.zip build/out/ion-*.exe ../

# Build offline for mac os
./bin/gbuild --url ion=/home/gitianuser/ion,signature=/home/gitianuser/gitian.sigs --num-make 2 --memory 3000 --commit ion=v${VERSION} ../ion/contrib/gitian-descriptors/gitian-osx.yml

# Sign for macos
./bin/gsign --signer "$SIGNER" --release ${VERSION}-osx-unsigned --destination ../gitian.sigs/ ../ion/contrib/gitian-descriptors/gitian-osx.yml
mv build/out/ion-*-osx-unsigned.tar.gz inputs/ion-osx-unsigned.tar.gz
mv build/out/ion-*.tar.gz build/out/ion-*.dmg ../
cd ..
```


Building online
---------------

```
# Build online for linux
./bin/gbuild --num-make 2 --memory 3000 --commit ion=v${VERSION} ../ion/contrib/gitian-descriptors/gitian-linux.yml

# Sign for linux
./bin/gsign --signer "$SIGNER" --release ${VERSION}-linux --destination ../gitian.sigs/ ../ion/contrib/gitian-descriptors/gitian-linux.yml
mv build/out/ion-*.tar.gz build/out/src/ion-*.tar.gz ../

# Build online for windows
./bin/gbuild --num-make 2 --memory 3000 --commit ion=v${VERSION} ../ion/contrib/gitian-descriptors/gitian-win.yml

# Sign for windows
./bin/gsign --signer "$SIGNER" --release ${VERSION}-win-unsigned --destination ../gitian.sigs/ ../ion/contrib/gitian-descriptors/gitian-win.yml
mv build/out/ion-*-win-unsigned.tar.gz inputs/ion-win-unsigned.tar.gz
mv build/out/ion-*.zip build/out/ion-*.exe ../

# Build online for mac os
./bin/gbuild --num-make 2 --memory 3000 --commit ion=v${VERSION} ../ion/contrib/gitian-descriptors/gitian-osx.yml
=======
==============


*version* Change log
==============

Detailed release notes follow. This overview includes changes that affect behavior, not code moves, refactors and string updates. For convenience in locating the code changes and accompanying discussion, both the pull request and git merge commit are mentioned.

### Core Features

### Build System
 
### P2P Protocol and Network Code

### GUI
 
### RPC/REST

### Wallet
 
### Miscellaneous
 
 
## Credits

Thanks to everyone who directly contributed to this release:


#### Linux
```
81c6c81ea4cf67f11d40b6215fdf3b7914577368b238eb4da2f7ff887f3d7b3b  ion-3.0.2-arm-linux-gnueabihf-debug.tar.gz
f3bf55bc9282a882410dabe793772501e85124322f8f30a1b0ae4f4684be0837  ion-3.0.2-arm-linux-gnueabihf.tar.gz
3b780fd5ba985847251a93a97c3aedad282e8cecb641c8873aa1591e3d84b420  ion-3.0.2-i686-pc-linux-gnu-debug.tar.gz
9483e8af1af7175efaf92c3efc99ec6ddee868e629be5269a9985abdbeade91c  ion-3.0.2-i686-pc-linux-gnu.tar.gz
a57d962fd75f97a4b73d9fb65f43611acf15c7d9139e840d455c421bf7253170  ion-3.0.2-x86_64-linux-gnu-debug.tar.gz
13ea2506bdf620d77d8316672adab68a0a5107ae9b1590a6ed5486f3b0509f63  ion-3.0.2-x86_64-linux-gnu.tar.gz
30e0390dc5d5f3bfbd91f340884ab75ca30056ff49c5831edc49fcae8c9413af  src/ion-3.0.2.tar.gz
76fa4b28ae291521be3ee12d22fa7d9b6085cafa0cc14c1c60b6b69f498d5a57  ion-linux-3.1-res.yml
```
#### windows
```
Generating report
e7e3a92a32a8dc924e64d19a276af11cfe74193cc5aad26bc7335e2e2e835a57  ion-3.0.2-win-unsigned.tar.gz
2a9b1199f03068c6ea18e5e25cd6736c15c7ddf9247ede67079bcd544c1426ad  ion-3.0.2-win32-debug.zip
624c4d36d9145efcaac2a9ed00368f2aac61631a9b75ebfc546926009e395db0  ion-3.0.2-win32-setup-unsigned.exe
49659943ab915444ab926bd392a34d9fb3397cf997f34e3deaa31f43bab185a7  ion-3.0.2-win32.zip
1a2ba3aac86fb44355b7b879f6c269d5556b1e302f3a54602c51101eedc3efe6  ion-3.0.2-win64-debug.zip
073f490607616680a5a5def73a1231885860aa047e526e7bf4694a4b88b11a56  ion-3.0.2-win64-setup-unsigned.exe
6f88c1bb4eec9b077c2e1ee60e9371b184d460a920e6170610f67dbc786e9faf  ion-3.0.2-win64.zip
679ac050e5555e097785b835f666de3d2e6b0e8af0dcefc7430ef3bfec386180  src/ion-3.0.2.tar.gz
eec21196d7d4abab4fb8c32882fed5157271161ecba4693a67d6ca407503e030  ion-win-3.1-res.yml
```
#### macos
```
7bc9149778661d03f5b26a97ff7dbbf8c9113d5198fe433e4e9b69cbb02f80f4  ion-3.0.2-osx-unsigned.dmg
2ae951d05b053790e0916db1e519fbf3f37258741ae67ffa15a8ddf455881b9b  ion-3.0.2-osx-unsigned.tar.gz
1b2f4dbcc02c423924a2dbbf2b813eca094fd796e1424a7478a14651d82524ae  ion-3.0.2-osx64.tar.gz
679ac050e5555e097785b835f666de3d2e6b0e8af0dcefc7430ef3bfec386180  src/ion-3.0.2.tar.gz
0be4184f68aaf67653b704e0bed30a83ede84fcea9c53ca39aa50c804acff614  ion-osx-3.1-res.yml
```
=======
=======
==============

Minimum Supported MacOS Version
------

The minimum supported version of MacOS (OSX) has been moved from 10.8 Mountain Lion to 10.10 Yosemite. Users still running a MacOS version prior to Yosemite will need to upgrade their OS if they wish to continue using the latest version(s) of the ION Core wallet.

Major New Features
------

### BIP65 (CHECKLOCKTIMEVERIFY) Soft-Fork

ION Core v3.2.0 introduces new consensus rules for scripting pathways to support the [BIP65](https://github.com/bitcoin/bips/blob/master/bip-0065.mediawiki) standard. This is being carried out as a soft-fork in order to provide ample time for stakers to update their wallet version.

### Automint Addresses

A new "Automint Addresses" feature has been added to the wallet that allows for the creation of new addresses who's purpose is to automatically convert any ION funds received by such addresses to xION. The feature as a whole can be enabled/disabled either at runtime using the `-enableautoconvertaddress` option, via RPC/Console with the `enableautomintaddress` command, or via the GUI's options dialog, with the default being enabled.

Creation of these automint addresses is currently only available via the RPC/Console `createautomintaddress` command, which takes no additional arguments. The command returns a new ION address each time, but addresses created by this command can be re-used if desired.

### In-wallet Proposal Voting

A new UI wallet tab has been introduced that allows users to view the current budget proposals, their vote counts, and vote on proposals if the wallet is acting as a masternode controller. The visual design is to be considered temporary, and will be undergoing further design and display improvements in the future.

### Zerocoin Lite Node Protocol

Support for the ZLN Protocol has been added, which allows for a node to opt-in to providing extended network services for the protocol. By default, this functionality is disabled, but can be enabled by using the `-peerbloomfilterszc` runtime option.

A full technical writeup of the protocol can be found [Here](https://ioncoin.xyz/wp-content/uploads/2018/11/Zerocoin_Light_Node_Protocol.pdf).

GUI Changes
------

### Console Security Warning

Due to an increase in social engineering attacks/scams that rely on users relaying information from console commands, a new warning message has been added to the Console window's initial welcome message.

### Optional Hiding of Orphan Stakes

The options dialog now contains a checkbox option to hide the display of orphan stakes from both the overview and transaction history sections. Further, a right-click context menu option has been introduced in the transaction history tab to achieve the same effect.

**Note:** This option only affects the visual display of orphan stakes, and will not prevent them nor remove them from the underlying wallet database.

### Transaction Type Recoloring

The color of various transaction types has been reworked to provide better visual feedback. Staking and masternode rewards are now purple, orphan stakes are now light gray, other rejected transactions are in red, and normal receive/send transactions are black.

### Receive Tab Changes

The address to be used when creating a new payment request is now automatically displayed in the form. This field is not user-editable, and will be updated as needed by the wallet.

A new button has been added below the payment request form, "Receiving Addresses", which allows for quicker access to all the known receiving addresses. This one-click button is the same as using the `File->Receiving Addresses...` menu command, and will open up the Receiving Addresses UI dialog.

Historical payment requests now also display the address used for the request in the history table. While this information was already available when clicking the "Show" button, it was an extra step that shouldn't have been necessary.

### Privacy Tab Changes

The entire right half of the privacy tab can now be toggled (shown/hidden) via a new UI button. This was done to reduce "clutter" for users that may not wish to see the detailed information regarding individual denomination counts.

RPC Changes
------

### Backupwallet Sanity

The `backupwallet` RPC command no longer allows for overwriting the currently in use wallet.dat file. This was done to avoid potential file corruption caused by multiple conflicting file access operations.

Build System Changes
------

### Completely Disallow Qt4

Compiling the ION Core wallet against Qt4 hasn't been supported for quite some time now, but the build system still recognized Qt4 as a valid option if Qt5 couldn't be found. This has now been remedied and Qt4 will no longer be considered valid during the `configure` pre-compilation phase.

### Further OpenSSL Deprecation

Up until now, the zerocoin library relied exclusively on OpenSSL for it's bignum implementation. This has now been changed with the introduction of GMP as an arithmetic operator and the bignum implementation has now been redesigned around GMP. Users can still opt to use OpenSSL for bignum by passing `--with-zerocoin-bignum=openssl` to the `configure` script, however such configuration is now deprecated.

**Note:** This change introduces a new dependency on GMP (libgmp) by default.

### RISC-V Support

Support for the new RISC-V 64bit processors has been added, though still experimental. Pre-compiled binaries for this CPU architecture are available for linux, and users can self-compile using gitian, depends, or an appropriate host system natively.

*version* Change log
==============

Detailed release notes follow. This overview includes changes that affect behavior, not code moves, refactors and string updates. For convenience in locating the code changes and accompanying discussion, both the pull request and git merge commit are mentioned.

### Core Features

### Build System
 
### P2P Protocol and Network Code

### GUI
 
### RPC/REST

### Wallet
 
### Miscellaneous
 
 
## Credits

Thanks to everyone who directly contributed to this release:
=======

#### Mac OSX High Sierra  
Currently there are issues with the 4.x gitian release on MacOS version 10.13 (High Sierra), no reports of issues on older versions of MacOS.
### Atomic Token Protocol (ATP)
_____

**Introduction:**  

As part of the integration of game development functionality and blockchain technology, the ION community chose to adopt a token system as part of its blockchain core. The community approved proposal IIP 0002 was put to vote in July 2018, after which development started. Instead of developing a solution from scratch, the team assessed a number of proposals and implementations that were currently being worked on for other Bitcoin family coins. Selection criteria were:

* Fully open, with active development
* Emphasis on permissionless transactions
* Efficient in terms of resource consumption
* Simple and elegant underlying principles 

The ATP system implemented is based on the Group Tokenization proposal by Andrew Stone / BU.

**References:**

[GROUP Tokenization specification by Andrew Stone](https://docs.google.com/document/d/1X-yrqBJNj6oGPku49krZqTMGNNEWnUJBRFjX7fJXvTs/edit#heading=h.sn65kz74jmuf)  
[GROUP Tokenization reference implementation for Bitcoin Cash](https://github.com/gandrewstone/BitcoinUnlimited/commits/tokengroups)  

For the technical principles underlying ION Group Tokenization, the above documentation is used as our standard.

ION developers fine tuned, extended and customized the Group Tokenization implementation. This documentation aims to support the ION community in:

* Using the ION group token system
* Creating additional tests as part of the development process
* Finding new use cases that need development support

### Noteable Changes
______
- core: switch core from pivx to ion
- updated dependencies
- QT 5.9.8
- expat 2.2.9
- libevent 2.1.11
- zeromq 4.3.2
- dbus 1.13.12
- miniupnpc 2.0.20180203
- native_ds_storke 1.1.2
- native_biplist 1.0.3
- native_mac_alias 2.0.7

##### Zerocoin
- Reimplement zerocoin to new source

##### Protocol change
- 

### New RPC Commands
__________

#### Tokens

`configuremanagementtoken "ticker" "name" decimalpos "description_url" description_hash ( confirm_send )  `  
`configuretoken "ticker" "name" ( decimalpos "description_url" description_hash ) ( confirm_send )  `  
`createtokenauthorities "groupid" "ionaddress" authoritylist  `  
`droptokenauthorities "groupid" "transactionid" outputnr [ authority1 ( authority2 ... ) ] `   
`getsubgroupid "groupid" "data"  `  
`gettokenbalance ( "groupid" )  `  
`listtokenauthorities "groupid"`    
`listtokenssinceblock "groupid" ( "blockhash" target-confirmations includeWatchonly ) `   
`listtokentransactions "groupid" ( count from includeWatchonly ) `   
`melttoken "groupid" quantity  `  
`minttoken "groupid" "ionaddress" quantity  `  
`sendtoken "groupid" "address" amount  `  
`tokeninfo [list, all, stats, groupid, ticker, name] ( "specifier " )  `  
`scantokens <action> ( <scanobjects> ) `

#### Masternodes
`createmasternodekey `  
`getmasternodeoutputs `  
`getmasternodecount`  
`getmasternodeoutputs`  
`getmasternodescores ( blocks )`  
`getmasternodestatus`  
`getmasternodewinners ( blocks "filter" )`  
`startmasternode "local|all|many|missing|disabled|alias" lockwallet ( "alias" )`
`listmasternodeconf ( "filter" )`  
`listmasternodes ( "filter" )`


### Deprecated RPC Commands
___
#### Masternodes
`masternode count`  
`masternode current`  
`masternode debug`  
`masternode genkey`  
`masternode outputs`  
`masternode start`  
`masternode start-alias`  
`masternode start-<mode>`  
`masternode status`  
`masternode list`  
`masternode list-conf`  
`masternode winners`  


### 5.0.99 Change log