Minitalk 📡
A client-server communication program using UNIX signals
42 School Project | Low-level system programming with C

# 🌐 Overview
Minitalk is a client-server program that demonstrates inter-process communication (IPC) using UNIX signals (SIGUSR1 and SIGUSR2). The project involves:

A server that waits for messages from clients.

A client that sends messages to the server via signals.

A custom binary protocol for encoding/decoding messages.

Key Concepts Demonstrated:
✔️ Signal handling (signal() or sigaction())
✔️ Bitwise operations for data encoding
✔️ Process synchronization
✔️ Error handling and robustness

# 🎯 Features
Core Functionality
Server:

Displays its PID for clients to connect.

Receives and reconstructs messages from signals without needing to restart.

Client:

Takes a server PID and a message as input (./client <PID> "message").

Sends the message bit-by-bit using SIGUSR1 (0) and SIGUSR2 (1).

Technical Highlights
No printf or external functions (only write, signal, usleep, kill).

Supports Unicode characters (bonus part).

Efficient signal handling with minimal delays.

# ⚙️ Technical Implementation

Server: Uses sigaction to listen for SIGUSR1 (0) and SIGUSR2 (1).

Client: Sends signals in sequence based on message bits using kill() function.

# ✅ Compliance
42 Norminette: Strict coding style.

No Leaks.
