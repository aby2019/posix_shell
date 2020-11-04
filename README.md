# posix_shell

POSIX compatible shell with a subset of feature support of default linux shell.

Implemented Features:

1. Builtin shell commands supported. eg: cat, pwd, ls, echo , clear..
2. Pipe , Forward redirection, Backward redirection. eg: | , > , >> , <
3. Auto Completion of input command (Trie Data Structure) eg: press tab after writing initials of any supported command.
4. Command History Maintained eg: Storing previous 5000 commands as a history
5. Support of Environment Variable ( PS1, HOME, PATH) eg: $PS1=&& , $HOME=/home/usr_name
6. Mulitple Alarm handling eg: Alaram 50 "Message"
7. Aliasing of command eg: alias ls=ls -l
8. Support of bachrc file to store global variables, PS1, Environment Path, Global Alias
9. Default Application launch handling eg: open /home/xyz.mp3 (will be launched via default application)
11. Recording as script command, where a user can initiate recording
of all input and output to a file, this happens in the
background. It will be invoked as record start and record stop.
12. History as buffer - searchable via TRIE. This is a list of all
commands executed ever. This can have a cap limit which can be
configured via “.myrc” file in HISTSIZE variable. It will be
invoked as history.
13. TRIE data structure for tab completion suppor. List of
directories to be traversed on startup which are mentioned in
PATH variable for populating all command names into the
structure.
14. Set default applications via .myrc file. This requires extension
matching/mapping to your preferred application.
