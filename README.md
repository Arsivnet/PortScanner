# PortScanner
A Port Scanner that scans the ports in a given range of a given host with different variations. It's written in C for Linux.

Since this is the GUI version, you'll need QT for compilation.

# Compilation
In the project directory, run;
```
qmake -project

qmake
```
Then, add this line to the end of the .pro file;
```
QT += widgets
```
Finally
```
make
```
Currently, the GUI uses the default "Scanner" code imported to C++. This means it's slower than the version that uses non-blocking sockets. A GUI version that uses the non-blocking sockets will be made in the near future.

-Scanner.c -> works
The most reliable one. Which is also the slowest.

-FasterScanner.c -> works
Uses non-blocking sockets for much faster connection. Doesn't work on sites that delibrately slows port response times like www.Google.com

-ScannerWithSelect.c -> Doesn't work. check issues.

-withmultithreading.c -> Doesn't work. Check issues.
