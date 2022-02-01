# PortScanner
A Port Scanner that scans the ports in a given range of a given host with different variations. It's written in C for Linux.

You'll need gcc for compilation. can compile with:
```
gcc -o PortScanner Scanner.c
```
If you wish to call this program with a different, perhaps shorter, name you can change the "PortScanner" part of the command above with any custom name you wish.
This applies to the "Example usage" part below this paragraph.
You can use compilers other than gcc as well.

Example usage:
```
PortScanner www.google.com
```

-Scanner.c -> works
The most reliable one. Which is also the slowest.

-FasterScanner.c -> works
Uses non-blocking sockets for much faster connection. Doesn't work on sites that delibrately slows port response times like www.Google.com

-ScannerWithSelect.c -> Doesn't work. check issues.

-withmultithreading.c -> Doesn't work. Check issues.
