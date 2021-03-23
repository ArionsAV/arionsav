The ArionsAV Project
=========================

...

BEHAVIOUR
==========

- All the processes must always be running, except from manager which just runs when user executes it.

- agent: Just performs updates, and act's as intermediate between manager and service. If malware found pops up a notification and adds detected malware to data file. Add it to quarantine aswell.
- service: Just detect malware, if a malware is found, it sends to agent MALWARE FOUND + INFO so agent can pop up a notification for it, and add it to detected malware data file.
- watchdog: just checks if services are up, and working fine.

NOTES
=========

- Add a checking system to verify files signatures and avoid AV manipulation
- Sign files?
- Signed update mechanism to update signatures after update / config change

