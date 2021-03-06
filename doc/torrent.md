- [Uploading and Downloading Torrents](#uploading-and-downloading-torrents)
  - [Transmission](#transmission)
    - [Uploading -- note: transmission bittorrent client is used in examples below](#uploading----note-transmission-bittorrent-client-is-used-in-examples-below)
    - [install transmission-cli](#install-transmission-cli)
    - [create torrent file](#create-torrent-file)
    - [Upload your torrent(s)](#upload-your-torrents)
  - [Downloading -- note: transmission bittorrent client is used in examples below](#downloading----note-transmission-bittorrent-client-is-used-in-examples-below)

# Uploading and Downloading Torrents

## Transmission

### Uploading -- note: transmission bittorrent client is used in examples below

### install transmission-cli

```bash
sudo apt-get install transmission-cli
```

### create torrent file

Create a .torrent file using the command "transmission-create -t <tracker\> <file\>" using one or all of the following trackers:

```list
http://tracker.tfile.me:80/announce
udp://tracker.cyberia.is:6969/announce
udp://open.demonii.si:1337
udp://denis.stalker.upeer.me:6969/announce
http://peersteers.org:80/announce
https://tracker.fastdownload.xyz:443/announce
https://t.quic.ws:443/announce
udp://tracker.moeking.me:6969/announce
https://1.tracker.animmouse.tk:443/announce
https://2.tracker.animmouse.tk:443/announce
udp://retracker.netbynet.ru:2710/announce
udp://tracker.skynetcloud.tk:6969/announce
http://tracker.gbitt.info:80/announce
udp://retracker.lanta-net.ru:2710/announce
http://torrent.nwps.ws:80/announce
http://tracker.tfile.co:80/announce
udp://exodus.desync.com:6969/announce
udp://retracker.hotplug.ru:2710/announce
udp://tracker.port443.xyz:6969/announce
https://opentracker.xyz:443/announce
http://t.acg.rip:6699/announce
udp://bittracker.ru:6969/announce
http://open.trackerlist.xyz:80/announce
http://open.trackerlist.xyz:80/announce
udp://tracker.birkenwald.de:6969/announce
udp://tracker.filemail.com:6969/announce
udp://bt.xxx-tracker.com:2710/announce
udp://tracker.torrent.eu.org:451/announce
udp://tracker.nyaa.uk:6969/announce
udp://prestige.minimafia.nl:443/announce
http://vps02.net.orel.ru:80/announce
udp://chihaya.toss.li:9696/announce
http://t.nyaatracker.com:80/announce
udp://hk1.opentracker.ga:6969/announce
udp://ipv4.tracker.harry.lu:80/announce
http://0d.kebhana.mx:443/announce
udp://tracker.opentrackr.org:1337/announce
udp://tw.opentracker.ga:36920/announce
http://tracker.openzim.org:80/announce
udp://tracker.iamhansen.xyz:2000/announce
udp://explodie.org:6969/announce
udp://thetracker.org:80/announce
udp://tracker.internetwarriors.net:1337/announce
udp://tracker.coppersurfer.tk:6969/announce
http://tracker.corpscorp.online:80/announce
http://tracker.internetwarriors.net:1337/announce
udp://9.rarbg.to:2710/announce
udp://tracker1.itzmx.com:8080/announce
udp://tracker.tiny-vps.com:6969/announce
udp://open.stealth.si:80/announce
http://open.acgnxtracker.com:80/announce
udp://tracker.vanitycore.co:6969/announce
http://retracker.telecom.by:80/announce
http://retracker.telecom.by:80/announce

### Upload your torrent(s)
- open a browser and log into the transmission server on port 9091
- click on the open file icon on the left hand side<br><br>
![torrent page](https://i.imgur.com/Yb2Vijt.png)<br>
- upload your torrent file(s) to the transmission server<br><br>
![torrent upload](https://i.imgur.com/bPLTIMj.png)<br><br>

Downloading -- note: transmission bittorrent client is used in examples below
---------
- donwload the list of torrents from https://bytebucket.org/ioncoin/ion/wiki/VM_Torrents/torrents.zip
- select the torrent for the VM you wish to download into file -> open<br><br>
![download torrent](https://i.imgur.com/jjFBaGT.png)<br>
- select open
- torrent will start downloading
