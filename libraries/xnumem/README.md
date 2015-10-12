# xnumem

## Introduction

**I do not maintain this project anymore, feel free to fork.**
Xnumem is an inter-process memory manipulation library for mac os x, written in C++ using the Mach kernel APIs.

Sudo is required for task_for_pid().

*Disclaimer: Use this software at your own risk. I'm not responsible for any damage that could occur.*

## Features

- x86 and x64 support.

- **Process Memory**
 - Allocate and free virtual memory.
 - Change memory protection.
 - Read/Write/Copy virtual memory .
 - Enumerate & dump all available segments.

- **Process Modules**
 - Enumerate all loaded modules.

## System Requirements

OS X 10.8 or higher.

## Support & Feedback

Report bugs or request features on the [bug tracker](https://github.com/jona-t4/xnumem/issues)

## Usage

See the included example usage code, headers contain documentation.

## License
Xnumem is licensed under the GPLv3 License. See GPLv3.txt for details. Dependencies are under their respective licenses.
