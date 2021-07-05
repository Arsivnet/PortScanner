# PortScanner
Port Scanner in C with different variations.

-Scanner.c -> works
The most reliable one. Which is also the slowest.

-FasterScanner.c -> works
Uses non-blocking sockets for much faster connection. Doesn't work on sites that delibrately slows port response times like www.Google.com

-ScannerWithSelect.c -> Doesn't work. check issues.

-withmultithreading.c -> Doesn't work. Check issues.
