

#include <QtGlobal>

// Automatically generated by extract_strings_qt.py
#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif
static const char UNUSED *ion_strings[] = {
QT_TRANSLATE_NOOP("ion-core", "Ion Core"),
QT_TRANSLATE_NOOP("ion-core", "The %s developers"),
QT_TRANSLATE_NOOP("ion-core", ""
"%s file contains all private keys from this wallet. Do not share it with "
"anyone!"),
QT_TRANSLATE_NOOP("ion-core", ""
"(1 = keep tx meta data e.g. account owner and payment request information, 2 "
"= drop tx meta data)"),
QT_TRANSLATE_NOOP("ion-core", ""
"-maxtxfee is set very high! Fees this large could be paid on a single "
"transaction."),
QT_TRANSLATE_NOOP("ion-core", ""
"A fee rate (in %s/kB) that will be used when fee estimation has insufficient "
"data (default: %s)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Accept connections from outside (default: 1 if no -proxy or -connect/-"
"noconnect)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Accept relayed transactions received from whitelisted peers even when not "
"relaying transactions (default: %d)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Allow JSON-RPC connections from specified source. Valid for <ip> are a "
"single IP (e.g. 1.2.3.4), a network/netmask (e.g. 1.2.3.4/255.255.255.0) or "
"a network/CIDR (e.g. 1.2.3.4/24). This option can be specified multiple times"),
QT_TRANSLATE_NOOP("ion-core", ""
"Bind to given address and always listen on it. Use [host]:port notation for "
"IPv6"),
QT_TRANSLATE_NOOP("ion-core", ""
"Bind to given address and whitelist peers connecting to it. Use [host]:port "
"notation for IPv6"),
QT_TRANSLATE_NOOP("ion-core", ""
"Bind to given address to listen for JSON-RPC connections. Use [host]:port "
"notation for IPv6. This option can be specified multiple times (default: "
"bind to all interfaces)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Calculated accumulator checkpoint is not what is recorded by block index"),
QT_TRANSLATE_NOOP("ion-core", ""
"Cannot obtain a lock on data directory %s. ION Core is probably already "
"running."),
QT_TRANSLATE_NOOP("ion-core", ""
"Cannot obtain a lock on data directory %s. %s is probably already running."),
QT_TRANSLATE_NOOP("ion-core", ""
"Connect only to the specified node(s); -noconnect or -connect=0 alone to "
"disable automatic connections"),
QT_TRANSLATE_NOOP("ion-core", ""
"Create new files with system default permissions, instead of umask 077 (only "
"effective with disabled wallet functionality)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Delete all wallet transactions and only recover those parts of the "
"blockchain through -rescan on startup"),
QT_TRANSLATE_NOOP("ion-core", ""
"Delete all zerocoin spends and mints that have been recorded to the "
"blockchain database and reindex them (0-1, default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Disable all ION specific functionality (Masternodes, Zerocoin, SwiftX, "
"Budgeting) (0-1, default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Distributed under the MIT software license, see the accompanying file %s or "
"%s"),
QT_TRANSLATE_NOOP("ion-core", ""
"Do not keep transactions in the mempool longer than <n> hours (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Enable automatic Zerocoin minting from specific addresses (0-1, default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Enable automatic wallet backups triggered after each xION minting (0-1, "
"default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Enable or disable staking functionality for ION inputs (0-1, default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Enable or disable staking functionality for xION inputs (0-1, default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Enable spork administration functionality with the appropriate private key."),
QT_TRANSLATE_NOOP("ion-core", ""
"Enable publish raw transactions of attempted InstantSend double spend in "
"<address>"),
QT_TRANSLATE_NOOP("ion-core", ""
"Enable publish transaction hashes of attempted InstantSend double spend in "
"<address>"),
QT_TRANSLATE_NOOP("ion-core", ""
"Error: The transaction is larger than the maximum allowed transaction size!"),
QT_TRANSLATE_NOOP("ion-core", ""
"Error: The transaction is larger than the maximum allowed transaction size!"),
QT_TRANSLATE_NOOP("ion-core", ""
"Error: The transaction was rejected! This might happen if some of the coins "
"in your wallet were already spent, such as if you used a copy of wallet.dat "
"and coins were spent in the copy but not marked as spent here."),
QT_TRANSLATE_NOOP("ion-core", ""
"Error loading %s: You can't enable HD on a already existing non-HD wallet"),
QT_TRANSLATE_NOOP("ion-core", ""
"Error reading %s! All keys read correctly, but transaction data or address "
"book entries might be missing or incorrect."),
QT_TRANSLATE_NOOP("ion-core", ""
"Error: Listening for incoming connections failed (listen returned error %s)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Execute command when a relevant alert is received or we see a really long "
"fork (%s in cmd is replaced by message)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Execute command when a wallet InstantSend transaction is successfully locked "
"(%s in cmd is replaced by TxID)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Execute command when a wallet transaction changes (%s in cmd is replaced by "
"TxID)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Execute command when the best block changes (%s in cmd is replaced by block "
"hash)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Execute command when the best block changes and its size is over (%s in cmd "
"is replaced by block hash, %d with the block size)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Failed to find coin set amongst held coins with less than maxNumber of Spends"),
QT_TRANSLATE_NOOP("ion-core", ""
"Fees (in ION/Kb) smaller than this are considered zero fee for relaying "
"(default: %s)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Fees (in %s/kB) smaller than this are considered zero fee for relaying, "
"mining and transaction creation (default: %s)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Fees (in %s/kB) smaller than this are considered zero fee for transaction "
"creation (default: %s)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Force relay of transactions from whitelisted peers even if they violate "
"local relay policy (default: %d)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Found unconfirmed denominated outputs, will wait till they confirm to "
"continue."),
QT_TRANSLATE_NOOP("ion-core", ""
"How thorough the block verification of -checkblocks is (0-4, default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"If <category> is not supplied or if <category> = 1, output all debugging "
"information."),
QT_TRANSLATE_NOOP("ion-core", ""
"If paytxfee is not set, include enough fee so transactions begin "
"confirmation on average within n blocks (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"In rare cases, a spend with 7 coins exceeds our maximum allowable "
"transaction size, please retry spend using 6 or less coins"),
QT_TRANSLATE_NOOP("ion-core", ""
"In this mode -genproclimit controls how many blocks are generated "
"immediately."),
QT_TRANSLATE_NOOP("ion-core", ""
"InstantSend doesn't support sending values that high yet. Transactions are "
"currently limited to %1 ION."),
QT_TRANSLATE_NOOP("ion-core", ""
"InstantSend requires inputs with at least %d confirmations, you might need "
"to wait a few minutes and try again."),
QT_TRANSLATE_NOOP("ion-core", ""
"Invalid amount for -maxtxfee=<amount>: '%s' (must be at least the minrelay "
"fee of %s to prevent stuck transactions)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Maintain a full address index, used to query for the balance, txids and "
"unspent outputs for addresses (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Maintain a full spent index, used to query the spending txid and input index "
"for an outpoint (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Maintain a full transaction index, used by the getrawtransaction rpc call "
"(default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Maximum average size of an index occurrence in the block spam filter "
"(default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Maximum size of data in data carrier transactions we relay and mine "
"(default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Maximum size of the list of indexes in the block spam filter (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Maximum total fees to use in a single wallet transaction, setting too low "
"may abort large transactions (default: %s)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Number of seconds to keep misbehaving peers from reconnecting (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Output debugging information (default: %u, supplying <category> is optional)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Override spork address. Only useful for regtest and devnet. Using this on "
"mainnet or testnet will ban you."),
QT_TRANSLATE_NOOP("ion-core", ""
"Overrides minimum spork signers to change spork value. Only useful for "
"regtest and devnet. Using this on mainnet or testnet will ban you."),
QT_TRANSLATE_NOOP("ion-core", ""
"Please check that your computer's date and time are correct! If your clock "
"is wrong, %s will not work properly."),
QT_TRANSLATE_NOOP("ion-core", ""
"Please contribute if you find %s useful. Visit %s for further information "
"about the software."),
QT_TRANSLATE_NOOP("ion-core", ""
"PrivateSend uses exact denominated amounts to send funds, you might simply "
"need to anonymize some more coins."),
QT_TRANSLATE_NOOP("ion-core", ""
"Prune configured below the minimum of %d MiB.  Please use a higher number."),
QT_TRANSLATE_NOOP("ion-core", ""
"Prune: last wallet synchronisation goes beyond pruned data. You need to -"
"reindex (download the whole blockchain again in case of pruned node)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Query for peer addresses via DNS lookup, if low on addresses (default: 1 "
"unless -connect/-noconnect)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Randomize credentials for every proxy connection. This enables Tor stream "
"isolation (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Reduce storage requirements by enabling pruning (deleting) of old blocks. "
"This allows the pruneblockchain RPC to be called to delete specific blocks, "
"and enables automatic pruning of old blocks if a target size in MiB is "
"provided. This mode is incompatible with -txindex and -rescan. Warning: "
"Reverting this setting requires re-downloading the entire blockchain. "
"(default: 0 = disable pruning blocks, 1 = allow manual pruning via RPC, >%u "
"= automatically prune block files to stay under the specified target size in "
"MiB)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Rescans are not possible in pruned mode. You will need to use -reindex which "
"will download the whole blockchain again."),
QT_TRANSLATE_NOOP("ion-core", ""
"Set lowest fee rate (in %s/kB) for transactions to be included in block "
"creation. (default: %s)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Set maximum size of high-priority/low-fee transactions in bytes (default: %d)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Set the number of included blocks to precompute per cycle. (minimum: %d) "
"(maximum: %d) (default: %d)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Set the number of script verification threads (%u to %d, 0 = auto, <0 = "
"leave that many cores free, default: %d)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Specify full path to directory for automatic wallet backups (must exist)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Specify custom backup path to add a copy of any automatic xION backup. If "
"set as dir, every backup generates a timestamped file. If set as file, will "
"rewrite to that file every backup. If backuppath is set as well, 4 backups "
"will happen"),
QT_TRANSLATE_NOOP("ion-core", ""
"Specify custom backup path to add a copy of any wallet backup. If set as "
"dir, every backup generates a timestamped file. If set as file, will rewrite "
"to that file every backup."),
QT_TRANSLATE_NOOP("ion-core", ""
"Specify custom backup path to add a copy of any automatic xION backup. If "
"set as dir, every backup generates a timestamped file. If set as file, will "
"rewrite to that file every backup. If backuppath is set as well, 4 backups "
"will happen"),
QT_TRANSLATE_NOOP("ion-core", ""
"Specify custom backup path to add a copy of any wallet backup. If set as "
"dir, every backup generates a timestamped file. If set as file, will rewrite "
"to that file every backup."),
QT_TRANSLATE_NOOP("ion-core", ""
"Support filtering of blocks and transaction with bloom filters (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", ""
"The block database contains a block which appears to be from the future. "
"This may be due to your computer's date and time being set incorrectly. Only "
"rebuild the block database if you are sure that your computer's date and "
"time are correct"),
QT_TRANSLATE_NOOP("ion-core", ""
"The transaction amount is too small to send after the fee has been deducted"),
QT_TRANSLATE_NOOP("ion-core", ""
"The block database contains a block which appears to be from the future. "
"This may be due to your computer's date and time being set incorrectly. Only "
"rebuild the block database if you are sure that your computer's date and "
"time are correct"),
QT_TRANSLATE_NOOP("ion-core", ""
"This is a pre-release test build - use at your own risk - do not use for "
"mining or merchant applications"),
QT_TRANSLATE_NOOP("ion-core", ""
"This is the transaction fee you may pay when fee estimates are not available."),
QT_TRANSLATE_NOOP("ion-core", ""
"This product includes software developed by the OpenSSL Project for use in "
"the OpenSSL Toolkit <https://www.openssl.org/> and cryptographic software "
"written by Eric Young and UPnP software written by Thomas Bernard."),
QT_TRANSLATE_NOOP("ion-core", ""
"Total length of network version string (%i) exceeds maximum length (%i). "
"Reduce the number or size of uacomments."),
QT_TRANSLATE_NOOP("ion-core", ""
"Unable to bind to %s on this computer. ION Core is probably already running."),
QT_TRANSLATE_NOOP("ion-core", ""
"Unable to locate enough Obfuscation denominated funds for this transaction."),
QT_TRANSLATE_NOOP("ion-core", ""
"Unable to locate enough Obfuscation non-denominated funds for this "
"transaction that are not equal 20000 ION."),
QT_TRANSLATE_NOOP("ion-core", ""
"Unable to locate enough funds for this transaction that are not equal 10000 "
"ION."),
QT_TRANSLATE_NOOP("ion-core", ""
"Use separate SOCKS5 proxy to reach peers via Tor hidden services (default: "
"%s)"),
QT_TRANSLATE_NOOP("ion-core", ""
"User defined mnemonic for HD wallet (bip39). Only has effect during wallet "
"creation/first start (default: randomly generated)"),
QT_TRANSLATE_NOOP("ion-core", ""
"User defined mnemonic passphrase for HD wallet (BIP39). Only has effect "
"during wallet creation/first start (default: empty string)"),
QT_TRANSLATE_NOOP("ion-core", ""
"User defined seed for HD wallet (should be in hex). Only has effect during "
"wallet creation/first start (default: randomly generated)"),
QT_TRANSLATE_NOOP("ion-core", ""
"Username and hashed password for JSON-RPC connections. The field <userpw> "
"comes in the format: <USERNAME>:<SALT>$<HASH>. A canonical python script is "
"included in share/rpcuser. The client then connects normally using the "
"rpcuser=<USERNAME>/rpcpassword=<PASSWORD> pair of arguments. This option can "
"be specified multiple times"),
QT_TRANSLATE_NOOP("ion-core", ""
"WARNING! Failed to replenish keypool, please unlock your wallet to do so."),
QT_TRANSLATE_NOOP("ion-core", ""
"Warning: Please check that your computer's date and time are correct! If "
"your clock is wrong ION Core will not work properly."),
QT_TRANSLATE_NOOP("ion-core", ""
"Warning: The network does not appear to fully agree! Some miners appear to "
"be experiencing issues."),
QT_TRANSLATE_NOOP("ion-core", ""
"Warning: Unknown block versions being mined! It's possible unknown rules are "
"in effect"),
QT_TRANSLATE_NOOP("ion-core", ""
"Warning: Wallet file corrupt, data salvaged! Original %s saved as %s in %s; "
"if your balance or transactions are incorrect you should restore from a "
"backup."),
QT_TRANSLATE_NOOP("ion-core", ""
"Warning: We do not appear to fully agree with our peers! You may need to "
"upgrade, or other nodes may need to upgrade."),
QT_TRANSLATE_NOOP("ion-core", ""
"Whitelist peers connecting from the given IP address (e.g. 1.2.3.4) or CIDR "
"notated network (e.g. 1.2.3.0/24). Can be specified multiple times."),
QT_TRANSLATE_NOOP("ion-core", ""
"Whitelisted peers cannot be DoS banned and their transactions are always "
"relayed, even if they are already in the mempool, useful e.g. for a gateway"),
QT_TRANSLATE_NOOP("ion-core", ""
"You are starting in lite mode, all Ion-specific functionality is disabled."),
QT_TRANSLATE_NOOP("ion-core", ""
"You need to rebuild the database using -reindex to go back to unpruned "
"mode.  This will redownload the entire blockchain"),
QT_TRANSLATE_NOOP("ion-core", ""
"You need to rebuild the database using -reindex-chainstate to change -txindex"),
QT_TRANSLATE_NOOP("ion-core", ""
"You should specify a masternodeblsprivkey in the configuration. Please see "
"documentation for help."),
QT_TRANSLATE_NOOP("ion-core", "%s corrupt, salvage failed"),
QT_TRANSLATE_NOOP("ion-core", "%s is not a valid backup folder!"),
QT_TRANSLATE_NOOP("ion-core", "%s is set very high!"),
QT_TRANSLATE_NOOP("ion-core", "(default: %s)"),
QT_TRANSLATE_NOOP("ion-core", "(default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "(press q to shutdown and continue later)"),
QT_TRANSLATE_NOOP("ion-core", "-devnet can only be specified once"),
QT_TRANSLATE_NOOP("ion-core", "-maxmempool must be at least %d MB"),
QT_TRANSLATE_NOOP("ion-core", "-port must be specified when -devnet and -listen are specified"),
QT_TRANSLATE_NOOP("ion-core", "-rpcport must be specified when -devnet and -server are specified"),
QT_TRANSLATE_NOOP("ion-core", "-wallet parameter must only specify a filename (not a path)"),
QT_TRANSLATE_NOOP("ion-core", "<category> can be:"),
QT_TRANSLATE_NOOP("ion-core", "Accept command line and JSON-RPC commands"),
QT_TRANSLATE_NOOP("ion-core", "Accept public REST requests (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Add a node to connect to and attempt to keep the connection open"),
QT_TRANSLATE_NOOP("ion-core", "Adding Wrapped Serials supply..."),
QT_TRANSLATE_NOOP("ion-core", "Allow DNS lookups for -addnode, -seednode and -connect"),
QT_TRANSLATE_NOOP("ion-core", "Allow RFC1918 addresses to be relayed and connected to (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Already have that input."),
QT_TRANSLATE_NOOP("ion-core", "Always query for peer addresses via DNS lookup (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Append comment to the user agent string"),
QT_TRANSLATE_NOOP("ion-core", "Attempt to force blockchain corruption recovery"),
QT_TRANSLATE_NOOP("ion-core", "Attempt to recover private keys from a corrupt wallet.dat"),
QT_TRANSLATE_NOOP("ion-core", "Automatically create Tor hidden service (default: %d)"),
QT_TRANSLATE_NOOP("ion-core", "Block creation options:"),
QT_TRANSLATE_NOOP("ion-core", "Can't find random Masternode."),
QT_TRANSLATE_NOOP("ion-core", "Can't mix while sync in progress."),
QT_TRANSLATE_NOOP("ion-core", "Can't mix: no compatible inputs found!"),
QT_TRANSLATE_NOOP("ion-core", "Cannot downgrade wallet"),
QT_TRANSLATE_NOOP("ion-core", "Cannot resolve -%s address: '%s'"),
QT_TRANSLATE_NOOP("ion-core", "Cannot write default address"),
QT_TRANSLATE_NOOP("ion-core", "CoinSpend: Accumulator witness does not verify"),
QT_TRANSLATE_NOOP("ion-core", "CoinSpend: failed check"),
QT_TRANSLATE_NOOP("ion-core", "Collateral not valid."),
QT_TRANSLATE_NOOP("ion-core", "Connect through SOCKS5 proxy"),
QT_TRANSLATE_NOOP("ion-core", "Connect to KeePassHttp on port <port> (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Connect to a node to retrieve peer addresses, and disconnect"),
QT_TRANSLATE_NOOP("ion-core", "Connection options:"),
QT_TRANSLATE_NOOP("ion-core", "Copyright (C) 2009-%i The Bitcoin Core Developers"),
QT_TRANSLATE_NOOP("ion-core", "Copyright (C) 2014-%i The Dash Core Developers"),
QT_TRANSLATE_NOOP("ion-core", "Copyright (C) 2015-%i The PIVX Core Developers"),
QT_TRANSLATE_NOOP("ion-core", "Copyright (C) 2018-%i The ION Core Developers"),
QT_TRANSLATE_NOOP("ion-core", "Corrupted block database detected"),
QT_TRANSLATE_NOOP("ion-core", "Could not parse masternode.conf"),
QT_TRANSLATE_NOOP("ion-core", "Couldn't generate the accumulator witness"),
QT_TRANSLATE_NOOP("ion-core", "Debugging/Testing options:"),
QT_TRANSLATE_NOOP("ion-core", "Do not load the wallet and disable wallet RPC calls"),
QT_TRANSLATE_NOOP("ion-core", "Do you want to rebuild the block database now?"),
QT_TRANSLATE_NOOP("ion-core", "Done loading"),
QT_TRANSLATE_NOOP("ion-core", "Enable automatic Zerocoin minting (0-1, default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Enable precomputation of xION spends and stakes (0-1, default %u)"),
QT_TRANSLATE_NOOP("ion-core", "Enable publish hash block in <address>"),
QT_TRANSLATE_NOOP("ion-core", "Enable publish hash of governance objects (like proposals) in <address>"),
QT_TRANSLATE_NOOP("ion-core", "Enable publish hash of governance votes in <address>"),
QT_TRANSLATE_NOOP("ion-core", "Enable publish hash transaction (locked via InstantSend) in <address>"),
QT_TRANSLATE_NOOP("ion-core", "Enable publish hash transaction in <address>"),
QT_TRANSLATE_NOOP("ion-core", "Enable publish raw block in <address>"),
QT_TRANSLATE_NOOP("ion-core", "Enable publish raw transaction (locked via InstantSend) in <address>"),
QT_TRANSLATE_NOOP("ion-core", "Enable publish raw transaction in <address>"),
QT_TRANSLATE_NOOP("ion-core", "Enable the client to act as a masternode (0-1, default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Entries are full."),
QT_TRANSLATE_NOOP("ion-core", "Entry exceeds maximum size."),
QT_TRANSLATE_NOOP("ion-core", "Error initializing block database"),
QT_TRANSLATE_NOOP("ion-core", "Error initializing wallet database environment %s!"),
QT_TRANSLATE_NOOP("ion-core", "Error loading %s"),
QT_TRANSLATE_NOOP("ion-core", "Error loading %s: Wallet corrupted"),
QT_TRANSLATE_NOOP("ion-core", "Error loading %s: Wallet requires newer version of %s"),
QT_TRANSLATE_NOOP("ion-core", "Error loading %s: You can't disable HD on a already existing HD wallet"),
QT_TRANSLATE_NOOP("ion-core", "Error loading block database"),
QT_TRANSLATE_NOOP("ion-core", "Error loading wallet.dat"),
QT_TRANSLATE_NOOP("ion-core", "Error loading wallet.dat: Wallet corrupted"),
QT_TRANSLATE_NOOP("ion-core", "Error loading wallet.dat: Wallet requires newer version of ION Core"),
QT_TRANSLATE_NOOP("ion-core", "Error opening block database"),
QT_TRANSLATE_NOOP("ion-core", "Error reading from database, shutting down."),
QT_TRANSLATE_NOOP("ion-core", "Error recovering public key."),
QT_TRANSLATE_NOOP("ion-core", "Error writing zerocoinDB to disk"),
QT_TRANSLATE_NOOP("ion-core", "Error"),
QT_TRANSLATE_NOOP("ion-core", "Error: A fatal internal error occured, see debug.log for details"),
QT_TRANSLATE_NOOP("ion-core", "Error: A fatal internal error occurred, see debug.log for details"),
QT_TRANSLATE_NOOP("ion-core", "Error: Can't select current denominated inputs"),
QT_TRANSLATE_NOOP("ion-core", "Error: Disk space is low!"),
QT_TRANSLATE_NOOP("ion-core", "Error: No valid utxo!"),
QT_TRANSLATE_NOOP("ion-core", "Error: Unsupported argument -tor found, use -onion."),
QT_TRANSLATE_NOOP("ion-core", "Error: Wallet locked, unable to create transaction!"),
QT_TRANSLATE_NOOP("ion-core", "Error: You already have pending entries in the Obfuscation pool"),
QT_TRANSLATE_NOOP("ion-core", "Failed to calculate accumulator checkpoint"),
QT_TRANSLATE_NOOP("ion-core", "Failed to create mint"),
QT_TRANSLATE_NOOP("ion-core", "Failed to find Zerocoins in wallet.dat"),
QT_TRANSLATE_NOOP("ion-core", "Failed to listen on any port. Use -listen=0 if you want this."),
QT_TRANSLATE_NOOP("ion-core", "Failed to parse host:port string"),
QT_TRANSLATE_NOOP("ion-core", "Failed to read block"),
QT_TRANSLATE_NOOP("ion-core", "Failed to select a zerocoin"),
QT_TRANSLATE_NOOP("ion-core", "Failed to wipe zerocoinDB"),
QT_TRANSLATE_NOOP("ion-core", "Failed to write coin serial number into wallet"),
QT_TRANSLATE_NOOP("ion-core", "Fee (in ION/kB) to add to transactions you send (default: %s)"),
QT_TRANSLATE_NOOP("ion-core", "Finalizing transaction."),
QT_TRANSLATE_NOOP("ion-core", "Force safe mode (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Found enough users, signing ( waiting %s )"),
QT_TRANSLATE_NOOP("ion-core", "Found enough users, signing ..."),
QT_TRANSLATE_NOOP("ion-core", "How many blocks to check at startup (default: %u, 0 = all)"),
QT_TRANSLATE_NOOP("ion-core", "Importing..."),
QT_TRANSLATE_NOOP("ion-core", "Imports blocks from external blk000??.dat file on startup"),
QT_TRANSLATE_NOOP("ion-core", "Include IP addresses in debug output (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Incompatible mode."),
QT_TRANSLATE_NOOP("ion-core", "Incompatible version."),
QT_TRANSLATE_NOOP("ion-core", "Incorrect or no genesis block found. Wrong datadir for network?"),
QT_TRANSLATE_NOOP("ion-core", "Information"),
QT_TRANSLATE_NOOP("ion-core", "Initialization sanity check failed. ION Core is shutting down."),
QT_TRANSLATE_NOOP("ion-core", "Input is not valid."),
QT_TRANSLATE_NOOP("ion-core", "InstantSend options:"),
QT_TRANSLATE_NOOP("ion-core", "Insufficient funds."),
QT_TRANSLATE_NOOP("ion-core", "Invalid -onion address or hostname: '%s'"),
QT_TRANSLATE_NOOP("ion-core", "Invalid amount for -maxtxfee=<amount>: '%s'"),
QT_TRANSLATE_NOOP("ion-core", "Invalid amount for -minrelaytxfee=<amount>: '%s'"),
QT_TRANSLATE_NOOP("ion-core", "Invalid amount for -mintxfee=<amount>: '%s'"),
QT_TRANSLATE_NOOP("ion-core", "Invalid amount for -paytxfee=<amount>: '%s' (must be at least %s)"),
QT_TRANSLATE_NOOP("ion-core", "Invalid characters in -wallet filename"),
QT_TRANSLATE_NOOP("ion-core", "Invalid masternodeblsprivkey. Please see documenation."),
QT_TRANSLATE_NOOP("ion-core", "Invalid minimum number of spork signers specified with -minsporkkeys"),
QT_TRANSLATE_NOOP("ion-core", "Invalid netmask specified in -whitelist: '%s'"),
QT_TRANSLATE_NOOP("ion-core", "Invalid script detected."),
QT_TRANSLATE_NOOP("ion-core", "Invalid spork address specified with -sporkaddr"),
QT_TRANSLATE_NOOP("ion-core", "KeePassHttp id for the established association"),
QT_TRANSLATE_NOOP("ion-core", "KeePassHttp key for AES encrypted communication with KeePass"),
QT_TRANSLATE_NOOP("ion-core", "Keep N ION anonymized (%u-%u, default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Keep at most <n> unconnectable transactions in memory (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Keep the transaction memory pool below <n> megabytes (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Keypool ran out, please call keypoolrefill first"),
QT_TRANSLATE_NOOP("ion-core", "Last PrivateSend was too recent."),
QT_TRANSLATE_NOOP("ion-core", "Last successful PrivateSend action was too recent."),
QT_TRANSLATE_NOOP("ion-core", "Listen for JSON-RPC connections on <port> (default: %u or testnet: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Listen for connections on <port> (default: %u or testnet: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Loading InstantSend data cache..."),
QT_TRANSLATE_NOOP("ion-core", "Loading P2P addresses..."),
QT_TRANSLATE_NOOP("ion-core", "Loading banlist..."),
QT_TRANSLATE_NOOP("ion-core", "Loading block index..."),
QT_TRANSLATE_NOOP("ion-core", "Loading fulfilled requests cache..."),
QT_TRANSLATE_NOOP("ion-core", "Loading governance cache..."),
QT_TRANSLATE_NOOP("ion-core", "Loading masternode cache..."),
QT_TRANSLATE_NOOP("ion-core", "Loading masternode payment cache..."),
QT_TRANSLATE_NOOP("ion-core", "Loading sporks..."),
QT_TRANSLATE_NOOP("ion-core", "Loading wallet... (%3.2f %%)"),
QT_TRANSLATE_NOOP("ion-core", "Loading wallet..."),
QT_TRANSLATE_NOOP("ion-core", "Location of the auth cookie (default: data dir)"),
QT_TRANSLATE_NOOP("ion-core", "Lock is already in place."),
QT_TRANSLATE_NOOP("ion-core", "Lock masternodes from masternode configuration file (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Lookup(): Invalid -proxy address or hostname: '%s'"),
QT_TRANSLATE_NOOP("ion-core", "Maintain at most <n> connections to peers (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Masternode options:"),
QT_TRANSLATE_NOOP("ion-core", "Masternode queue is full."),
QT_TRANSLATE_NOOP("ion-core", "Masternode:"),
QT_TRANSLATE_NOOP("ion-core", "Maximum per-connection receive buffer, <n>*1000 bytes (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Maximum per-connection send buffer, <n>*1000 bytes (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Mint did not make it into blockchain"),
QT_TRANSLATE_NOOP("ion-core", "Missing input transaction information."),
QT_TRANSLATE_NOOP("ion-core", "Mixing in progress..."),
QT_TRANSLATE_NOOP("ion-core", "Need address because change is not exact"),
QT_TRANSLATE_NOOP("ion-core", "Need to specify a port with -whitebind: '%s'"),
QT_TRANSLATE_NOOP("ion-core", "No Masternodes detected."),
QT_TRANSLATE_NOOP("ion-core", "No compatible Masternode found."),
QT_TRANSLATE_NOOP("ion-core", "No errors detected."),
QT_TRANSLATE_NOOP("ion-core", "No matching denominations found for mixing."),
QT_TRANSLATE_NOOP("ion-core", "Node relay options:"),
QT_TRANSLATE_NOOP("ion-core", "Non-standard public key detected."),
QT_TRANSLATE_NOOP("ion-core", "Not compatible with existing transactions."),
QT_TRANSLATE_NOOP("ion-core", "Not enough file descriptors available."),
QT_TRANSLATE_NOOP("ion-core", "Not enough funds to anonymize."),
QT_TRANSLATE_NOOP("ion-core", "Not in the Masternode list."),
QT_TRANSLATE_NOOP("ion-core", "Number of automatic wallet backups (default: 10)"),
QT_TRANSLATE_NOOP("ion-core", "Number of custom location backups to retain (default: %d)"),
QT_TRANSLATE_NOOP("ion-core", "Obfuscation is idle."),
QT_TRANSLATE_NOOP("ion-core", "Obfuscation request complete:"),
QT_TRANSLATE_NOOP("ion-core", "Obfuscation request incomplete:"),
QT_TRANSLATE_NOOP("ion-core", "Only accept block chain matching built-in checkpoints (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Only connect to nodes in network <net> (ipv4, ipv6 or onion)"),
QT_TRANSLATE_NOOP("ion-core", "Options:"),
QT_TRANSLATE_NOOP("ion-core", "Password for JSON-RPC connections"),
QT_TRANSLATE_NOOP("ion-core", "Percentage of automatically minted Zerocoin  (1-100, default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Preparing for resync..."),
QT_TRANSLATE_NOOP("ion-core", "Prepend debug output with timestamp (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Print this help message and exit"),
QT_TRANSLATE_NOOP("ion-core", "Print version and exit"),
QT_TRANSLATE_NOOP("ion-core", "RPC server options:"),
QT_TRANSLATE_NOOP("ion-core", "Randomly drop 1 of every <n> network messages"),
QT_TRANSLATE_NOOP("ion-core", "Randomly fuzz 1 of every <n> network messages"),
QT_TRANSLATE_NOOP("ion-core", "Rebuild block chain index from current blk000??.dat files"),
QT_TRANSLATE_NOOP("ion-core", "Recalculating ION supply..."),
QT_TRANSLATE_NOOP("ion-core", "Recalculating minted XION..."),
QT_TRANSLATE_NOOP("ion-core", "Recalculating spent XION..."),
QT_TRANSLATE_NOOP("ion-core", "Receive and display P2P network alerts (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Reindex the ION and xION money supply statistics"),
QT_TRANSLATE_NOOP("ion-core", "Reindex the accumulator database"),
QT_TRANSLATE_NOOP("ion-core", "Reindexing zerocoin database..."),
QT_TRANSLATE_NOOP("ion-core", "Reindexing zerocoin failed"),
QT_TRANSLATE_NOOP("ion-core", "Relay and mine data carrier transactions (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Relay non-P2SH multisig (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Rescan the block chain for missing wallet transactions on startup"),
QT_TRANSLATE_NOOP("ion-core", "Rescanning..."),
QT_TRANSLATE_NOOP("ion-core", "Run in the background as a daemon and accept commands"),
QT_TRANSLATE_NOOP("ion-core", "Selected coins value is less than payment target"),
QT_TRANSLATE_NOOP("ion-core", "Send transactions as zero-fee transactions if possible (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Session not complete!"),
QT_TRANSLATE_NOOP("ion-core", "Session timed out."),
QT_TRANSLATE_NOOP("ion-core", "Set database cache size in megabytes (%d to %d, default: %d)"),
QT_TRANSLATE_NOOP("ion-core", "Set key pool size to <n> (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Set maximum block size in bytes (default: %d)"),
QT_TRANSLATE_NOOP("ion-core", "Set the masternode BLS private key"),
QT_TRANSLATE_NOOP("ion-core", "Set the number of threads to service RPC calls (default: %d)"),
QT_TRANSLATE_NOOP("ion-core", "Show all debugging options (usage: --help -help-debug)"),
QT_TRANSLATE_NOOP("ion-core", "Shrink debug.log file on client startup (default: 1 when no -debug)"),
QT_TRANSLATE_NOOP("ion-core", "Signing transaction failed"),
QT_TRANSLATE_NOOP("ion-core", "Specify configuration file (default: %s)"),
QT_TRANSLATE_NOOP("ion-core", "Specify connection timeout in milliseconds (minimum: 1, default: %d)"),
QT_TRANSLATE_NOOP("ion-core", "Specify data directory"),
QT_TRANSLATE_NOOP("ion-core", "Specify pid file (default: %s)"),
QT_TRANSLATE_NOOP("ion-core", "Specify wallet file (within data directory)"),
QT_TRANSLATE_NOOP("ion-core", "Specify your own public address"),
QT_TRANSLATE_NOOP("ion-core", "Spend Valid"),
QT_TRANSLATE_NOOP("ion-core", "Spend unconfirmed change when sending transactions (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Starting network threads..."),
QT_TRANSLATE_NOOP("ion-core", "Submitted following entries to masternode: %u"),
QT_TRANSLATE_NOOP("ion-core", "Submitted to masternode, waiting for more entries ( %u ) %s"),
QT_TRANSLATE_NOOP("ion-core", "Submitted to masternode, waiting in queue %s"),
QT_TRANSLATE_NOOP("ion-core", "Support the zerocoin light node protocol (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "SwiftX options:"),
QT_TRANSLATE_NOOP("ion-core", "Synchronization failed"),
QT_TRANSLATE_NOOP("ion-core", "Synchronization finished"),
QT_TRANSLATE_NOOP("ion-core", "Synchronization pending..."),
QT_TRANSLATE_NOOP("ion-core", "Synchronizing budgets..."),
QT_TRANSLATE_NOOP("ion-core", "Synchronizing masternode winners..."),
QT_TRANSLATE_NOOP("ion-core", "Synchronizing masternodes..."),
QT_TRANSLATE_NOOP("ion-core", "Synchronizing sporks..."),
QT_TRANSLATE_NOOP("ion-core", "Syncing xION wallet..."),
QT_TRANSLATE_NOOP("ion-core", "The coin spend has been used"),
QT_TRANSLATE_NOOP("ion-core", "The transaction did not verify"),
QT_TRANSLATE_NOOP("ion-core", "This help message"),
QT_TRANSLATE_NOOP("ion-core", "This is experimental software."),
QT_TRANSLATE_NOOP("ion-core", "This is not a Masternode."),
QT_TRANSLATE_NOOP("ion-core", "This is the minimum transaction fee you pay on every transaction."),
QT_TRANSLATE_NOOP("ion-core", "This is the transaction fee you will pay if you send a transaction."),
QT_TRANSLATE_NOOP("ion-core", "Threshold for disconnecting misbehaving peers (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Too many spends needed"),
QT_TRANSLATE_NOOP("ion-core", "Tor control port password (default: empty)"),
QT_TRANSLATE_NOOP("ion-core", "Tor control port to use if onion listening enabled (default: %s)"),
QT_TRANSLATE_NOOP("ion-core", "Transaction Created"),
QT_TRANSLATE_NOOP("ion-core", "Transaction Mint Started"),
QT_TRANSLATE_NOOP("ion-core", "Transaction amount too small"),
QT_TRANSLATE_NOOP("ion-core", "Transaction amounts must not be negative"),
QT_TRANSLATE_NOOP("ion-core", "Transaction created successfully."),
QT_TRANSLATE_NOOP("ion-core", "Transaction fees are too high."),
QT_TRANSLATE_NOOP("ion-core", "Transaction has too long of a mempool chain"),
QT_TRANSLATE_NOOP("ion-core", "Transaction must have at least one recipient"),
QT_TRANSLATE_NOOP("ion-core", "Transaction not valid."),
QT_TRANSLATE_NOOP("ion-core", "Transaction too large for fee policy"),
QT_TRANSLATE_NOOP("ion-core", "Transaction too large"),
QT_TRANSLATE_NOOP("ion-core", "Transmitting final transaction."),
QT_TRANSLATE_NOOP("ion-core", "Trying to spend an already spent serial #, try again."),
QT_TRANSLATE_NOOP("ion-core", "Unable to bind to %s on this computer (bind returned error %s)"),
QT_TRANSLATE_NOOP("ion-core", "Unable to find transaction containing mint"),
QT_TRANSLATE_NOOP("ion-core", "Unable to sign spork message, wrong key?"),
QT_TRANSLATE_NOOP("ion-core", "Unable to start HTTP server. See debug log for details."),
QT_TRANSLATE_NOOP("ion-core", "Unknown network specified in -onlynet: '%s'"),
QT_TRANSLATE_NOOP("ion-core", "Unknown response."),
QT_TRANSLATE_NOOP("ion-core", "Unknown state: id = %u"),
QT_TRANSLATE_NOOP("ion-core", "Upgrade wallet to latest format"),
QT_TRANSLATE_NOOP("ion-core", "Use UPnP to map the listening port (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Use UPnP to map the listening port (default: 1 when listening)"),
QT_TRANSLATE_NOOP("ion-core", "Use a custom max chain reorganization depth (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Use block spam filter (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Use the test network"),
QT_TRANSLATE_NOOP("ion-core", "User Agent comment (%s) contains unsafe characters."),
QT_TRANSLATE_NOOP("ion-core", "Username for JSON-RPC connections"),
QT_TRANSLATE_NOOP("ion-core", "Value is below the smallest available denomination (= 1) of xION"),
QT_TRANSLATE_NOOP("ion-core", "Value more than Obfuscation pool maximum allows."),
QT_TRANSLATE_NOOP("ion-core", "Verifying blocks..."),
QT_TRANSLATE_NOOP("ion-core", "Verifying wallet..."),
QT_TRANSLATE_NOOP("ion-core", "Wallet %s resides outside data directory %s"),
QT_TRANSLATE_NOOP("ion-core", "Wallet debugging/testing options:"),
QT_TRANSLATE_NOOP("ion-core", "Wallet is locked."),
QT_TRANSLATE_NOOP("ion-core", "Wallet needed to be rewritten: restart ION Core to complete"),
QT_TRANSLATE_NOOP("ion-core", "Wallet options:"),
QT_TRANSLATE_NOOP("ion-core", "Wallet window title"),
QT_TRANSLATE_NOOP("ion-core", "Warning"),
QT_TRANSLATE_NOOP("ion-core", "Warning: unknown new rules activated (versionbit %i)"),
QT_TRANSLATE_NOOP("ion-core", "Wasn't able to create wallet backup folder %s!"),
QT_TRANSLATE_NOOP("ion-core", "Whether to operate in a blocks only mode (default: %u)"),
QT_TRANSLATE_NOOP("ion-core", "Will retry..."),
QT_TRANSLATE_NOOP("ion-core", "You don't have enough Zerocoins in your wallet"),
QT_TRANSLATE_NOOP("ion-core", "You need to rebuild the database using -reindex to change -txindex"),
QT_TRANSLATE_NOOP("ion-core", "Your entries added successfully."),
QT_TRANSLATE_NOOP("ion-core", "Your transaction was accepted into the pool!"),
QT_TRANSLATE_NOOP("ion-core", "Zapping all transactions from wallet..."),
QT_TRANSLATE_NOOP("ion-core", "ZeroMQ notification options:"),
QT_TRANSLATE_NOOP("ion-core", "Zerocoin options:"),
QT_TRANSLATE_NOOP("ion-core", "could not get lock on cs_spendcache"),
QT_TRANSLATE_NOOP("ion-core", "isValid(): Invalid -proxy address or hostname: '%s'"),
QT_TRANSLATE_NOOP("ion-core", "on startup"),
QT_TRANSLATE_NOOP("ion-core", "wallet.dat corrupt, salvage failed"),
};
