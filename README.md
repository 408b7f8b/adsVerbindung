# adsVerbindung
erste bastelei für eine beckhoff-ads-anbindung in c++14. nutzt funktionen der beckhoff-ads-lib.
siehe https://github.com/Beckhoff/ADS
die beckhoff-lib muss zur nutzung mit -fpic gebaut werden (makefile ändern!)

ist wegen pthread aktuell auf linux beschränkt (docker?)
--> deswegen auf der steuerung direkt nur mit mingw oder sowas benutzbar (nicht getestet)
alternative: linux-system & route auf der sps anlegen

es können variablen auf eine watchlist gesetzt und überwacht (bspw. im 100 msec-abfrage) werden
es kann eine rückruffunktion eingehängt werden, die änderung des variablenwerts aufgerufen wird