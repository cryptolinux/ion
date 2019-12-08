## ION Core version 5.0.99 is now available  


How to Upgrade
--------------

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), then run the
installer (on Windows) or just copy over /Applications/Ion-Qt (on Mac) or
iond/ion-qt (on Linux). If you upgrade after DIP0003 activation and you were
using version < 0.13 you will have to reindex (start with -reindex-chainstate
or -reindex) to make sure your wallet has all the new data synced. Upgrading
from version 0.13 should not require any additional actions.

Due to the changes in the "evodb" database format introduced in this release, the
first startup of Ion Core will run a migration process which can take a few minutes
to finish. After the migration, a downgrade to an older version is only possible with
a reindex (or reindex-chainstate).
=======
Download at: https://github.com/ioncoincore/ion/releases

This is a new major version release, including various bug fixes, performance improvements, implementation of the Atomic Token Protocol (ATP), as well as updated translations.

Please report bugs using the issue tracker at github: https://github.com/ioncoincore/ion/issues

<<<<<<< HEAD
Downgrading to a version older than 0.14.0.3 is no longer supported due to
changes in the "evodb" database format. If you need to use an older version,
you must either reindex or re-sync the whole chain.

### Downgrade of masternodes to < 0.16

Starting with this release, masternodes will verify the protocol version of other
masternodes. This will result in PoSe punishment/banning for outdated masternodes,
so downgrading is not recommended.

Notable changes
===============


See detailed [set of changes](https://github.com/dashpay/dash/compare/v0.16.1.0...dashpay:v0.16.1.1).

- [`ccef3b4836`](https://github.com/dashpay/dash/commit/ccef3b48363d8bff4b919d9119355182e3902ef3) qt: Fix wallet encryption dialog (#3816)
=======
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

Ion was previously known as Darkcoin.

Darkcoin tree 0.8.x was a fork of Litecoin tree 0.8, original name was XCoin
which was first released on Jan/18/2014.

Darkcoin tree 0.9.x was the open source implementation of masternodes based on
the 0.8.x tree and was first released on Mar/13/2014.

Darkcoin tree 0.10.x used to be the closed source implementation of Darksend
which was released open source on Sep/25/2014.

Ion Core tree 0.11.x was a fork of Bitcoin Core tree 0.9,
Darkcoin was rebranded to Ion.

Ion Core tree 0.12.0.x was a fork of Bitcoin Core tree 0.10.

Ion Core tree 0.12.1.x was a fork of Bitcoin Core tree 0.12.

These release are considered obsolete. Old release notes can be found here:

- [v0.14.0.2](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.14.0.2.md) released July/4/2019
- [v0.14.0.1](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.14.0.1.md) released May/31/2019
- [v0.14.0](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.14.0.md) released May/22/2019
- [v0.13.3](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.13.3.md) released Apr/04/2019
- [v0.13.2](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.13.2.md) released Mar/15/2019
- [v0.13.1](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.13.1.md) released Feb/9/2019
- [v0.13.0](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.13.0.md) released Jan/14/2019
- [v0.12.3.4](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.12.3.4.md) released Dec/14/2018
- [v0.12.3.3](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.12.3.3.md) released Sep/19/2018
- [v0.12.3.2](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.12.3.2.md) released Jul/09/2018
- [v0.12.3.1](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.12.3.1.md) released Jul/03/2018
- [v0.12.2.3](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.12.2.3.md) released Jan/12/2018
- [v0.12.2.2](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.12.2.2.md) released Dec/17/2017
- [v0.12.2](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.12.2.md) released Nov/08/2017
- [v0.12.1](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.12.1.md) released Feb/06/2017
- [v0.12.0](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.12.0.md) released Aug/15/2015
- [v0.11.2](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.11.2.md) released Mar/04/2015
- [v0.11.1](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.11.1.md) released Feb/10/2015
- [v0.11.0](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.11.0.md) released Jan/15/2015
- [v0.10.x](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.10.0.md) released Sep/25/2014
- [v0.9.x](https://bitbucket.org/ioncoin/ion/blob/master/doc/release-notes/ion/release-notes-0.9.0.md) released Mar/13/2014
=======
### Mandatory Update
___  

ION Core v5.0.99 is a mandatory update for all users. This release contains new consensus rules and improvements that are not backwards compatible with older versions. Users will have a grace period of up to two week to update their clients before enforcement of this update is enabled - a grace period that will end at block 1320000 the latest.
>>>>>>> docs - update release notes and cleanup folder

### How to Upgrade
___
If you are running an older version, shut it down. Wait until it has completely shut down (which might take a few minutes for older versions), then run the installer (on Windows) or just copy over /Applications/ION-Qt (on Mac) or iond/ion-qt (on Linux).

### Compatibility
ION Core is extensively tested on multiple operating systems using the Linux kernel, macOS 10.8+, and Windows Vista and later.

Microsoft ended support for Windows XP on April 8th, 2014, No attempt is made to prevent installing or running the software on Windows XP, you can still do so at your own risk but be aware that there are known instabilities and issues. Please do not report issues about Windows XP to the issue tracker.

ION Core should also work on most other Unix-like systems but is not frequently tested on them.

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