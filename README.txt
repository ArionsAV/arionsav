The ArionsAV Project
======================

...

FEATURES
----------

- Service and agent will check for watchdog integrity too.
- Show notifications on multiple different systems (Ubuntu, Debian etc...)
- Make it cross-platform for: Ubuntu, Debian, CentOS
- Agent will search regularly for updates for both DB and AV. It will check watchdog existence aswell
- Service will be analyzing events within the system...new env vars, new files, new processes, new actions, new hardware connected, new networks etc
- Watchdog will check the existence of the other processes and check files integrity (content, permissions etc)

- The quarantine files will be encrypted and stored on a specific directory

Manage features
++++++++++++++++

- Enable/disable notifications
- Enable/disable AV
- Load whitelist/blacklist rules
- Add file to quarantine
- Get file from quarantine
- Add/delete file path exception / detection
- Add/delete file content exception / detection
- Search for updates

Agent Features
++++++++++++++++

- Check for watchdog existence, else start it
- Connect each N seconds to server to check for both AV updates and DB updates (more regularly)
- AV updates will consist on a bash script that won't touch disk that will apply the needed changes and download needed files. The bash file transference will be performed encrypted and it's signature will be checked later
- DB updates will consist on an encrypted DB file which it's signatures will be checked later
- When manager orders something we will connect to service from here

Service Features
+++++++++++++++++

- communicate with kernel module to detect syscalls
- when a file is downloaded, analuze format, extract it, inteprete it and evauate malicious or not
- when a new process is started, first analyze it's format, elf, pe, bash etc, then try to analyze process memory to find malicious behaviour
- when a file is changed of location, copied or symlinked it get's analyzed.
- when a new env var is created it gets analyzed, if it contains a path analyze it contents
- use a priority order to select files, eg.: the ones who access files like /etc/passwd (file blacklist), the ones who execute certain commands (cmd blacklist), etc etc
- When user requests scan, or SCAN_DELAY time is reached depending on the configuration start looking for malicious files all along the system. FIlesystem, Processes, persistence, env vars, users etc

Watchdog features
++++++++++++++++++

- Check for service and agent processes existence
- Detect unexpected behaviour on agent, service or manager processes (like popping a root shell)

Kernel module features
++++++++++++++++++++++++

- detect malware via syscalls

SECURITY
----------

- Atomic and mutexes to avoid race conditions
- Secure memory manipulation functions to void out-of-bounds write/read
- free() wrapper to NULL pointers after being freed to avoid Use-After-Free or Double free corruptions
- Input checking to avoid multiple type of vulnerabilities
- fuzz tests included so the community can fuzz ArionsAV modules and report vulnerabilities found
- Multiple techniques to protect internal function pointers and make control-flow hijacking attacks harder
- Blacklist _malloc_hook() and _free_hook() etc addresses in memory
- Compling with all compiler protections: Full RELRO, PIE, NX, Stack Guard
- Alert user if ASLR is disabled and ask him for enable it
- Watchdog will detect unexpected behaviour on other services like agent or service. Example, if a root shell is getting popped.
- Avoid importing dangerous functions like system() or execve() and implement own wrappers via syscalls with checks and blacklisted/whitelisted programs
- Implementing SECCOMP
- Implementing a shadow stack for all the functions used to make buffer overflow exploitation attempts harder.
- Blacklist input characters like 0x7f, 0x55 in string-only inputs to make harder getting valid memory addresses
- Implement heap cookies to make heap-based buffer overflow exploitation harder
- Add a memset() in the free() wrapper to make Use-After-Free exploitation harder
- Use signal handlers to remove impact on crash/DoS vulnerabilities
- When loading libraries eg.: with dlopen, check library hash first (be aware to avoid race condition) to avoid library hijacking
- When returning back data to the user blacklist non-ASCII characters to minimize memory leakage impact.
- BSS cookies to avoid BSS-based buffer overflows exploitation
- A good attack vector to bypass memory protections is reusing functions to write on arbitrary files arbitrary data. Add some machanism to minimize impact
- Limit function pointer to a segment range
- A good method to minimize Data-only attacks impact?
- A good method to minimize integer overflow impact?



SIGNATURE ELF
---------------

When an ELF file is needed to be detected, no indicious, or malicious strings can be used, so we migh use signatures.

A signature will be a sha256 hash of a portion of code of N bytes.

They will always be aligned starting from .text start and skipping common code, like libc functions, PLT, compiler related functions etc

extracting
+++++++++++++

To extract a signature we will use a tool inside tools directory to extract a bunch of hashes from .text code

then with another tool we will be able to add it to the database.

checking
++++++++++

Go to .text and using block to block start doing hashing and if any block identified, or similar (somehow?) flag it as malicious and search on the database a name for it eg.: Meterpreter




