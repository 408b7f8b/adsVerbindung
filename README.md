# adsVerbindung
erste bastelei für eine beckhoff-ads-anbindung in c++14. nutzt funktionen der beckhoff-ads-lib.
siehe https://github.com/Beckhoff/ADS

gebaut und getestet auf 64bit-linux ubunutu 18.04 lts und win10 64bit

## Funktion
es können variablen eines ads-systems auf eine watchlist gesetzt und überwacht (bspw. im 100 msec-abfrage) werden
es kann eine rückruffunktion eingehängt werden, die änderung des variablenwerts aufgerufen wird
variablen können geschrieben werden
beim zielsystem muss eine passende ads-route erstellt worden sein

## Anpassen der Beckhoff-ADS-Bibliothek
die beckhoff-lib muss zur nutzung mit -fpic gebaut werden (makefile ändern!)

um die beckhoff-lib auf windows bauen zu können, müssen folgende workarounds in der Sockets.cpp vorgenommen werden:

size_t Socket::read(uint8_t* buffer, size_t maxBytes, timeval* timeout) const
[...]
    if ((0 == bytesRead) || (lastError == CONNECTION_CLOSED) || (lastError == CONNECTION_ABORTED)) {
        throw std::runtime_error("connection closed by remote");
    } else {
		char errmsg[256];
        //LOG_ERROR("read frame failed with error: " << std::dec << strerr(lastError));
		LOG_ERROR("read frame failed with error: " << std::dec << strerror_s(errmsg, sizeof(errmsg), lastError));
    }
[...]

bool Socket::Select(timeval* timeout) const
[...]
	    /* and check if socket was correct */
    if ((1 != state) || (!FD_ISSET(m_Socket, &readSockets))) {
        //LOG_ERROR("something strange happen while waiting for socket in state: " <<
        //          state << " with error: " << strerror(lastError));

		char errmsg[256];
		LOG_ERROR("something strange happen while waiting for socket in state: " <<
			state << " with error: " << strerror_s(errmsg, sizeof(errmsg), lastError));

        return false;
    }
[...]