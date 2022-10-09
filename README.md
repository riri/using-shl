# Using Single Header Libraries

This document and the associated demo project explains (and reminds to myself) how to use single header libraries (abbreviated **SHL** from now) properly.

> TODO explain SHL and most common examples of them

## Create a shl directory in the source tree

First I prefer to keep all my SHL in one place, outside of my source tree, but to reference them from inside my sources directory.

* **`external/`** (or anywhere else)
  * `one-awesome-shl`
    * `one-awesome-shl.h`
  * `another-awesome-shl`
    * `one-weird-header-name-choice.h`
* `src/`
  * **`shl/`**
    * `one-awesome-shl.h`
    * `another-awesome-shl.h`
    * **`shl.c`**
  * `myproject.h`
  * `myproject.c`
  * `main.c`
  * ...

There are several benefits in using that scheme:
1. I know I will include all headers from the only `shl/` directory, making it easy for code completion and for myself
2. If I want to use git submodules to import SHL, all of them  don't use the same structure. I usually refer to a SHL through its common name, so I include that project name instead of the real header name
3. Most SHL use macros to alter their behavior, and the same defines must be used in both the header inclusion and the implementation, so creating a header that defines macros and then includes the SHL header makes it easier for consistency
4. I create a single **`shl.c`** file in this directory to implement all the SHL at once, but keeping the compilation separated from my project

So each SHL gets its own local header file in the project

**one-awesome-shl**
```c
#ifndef SHL_ONE_AWESOME_SHL_H
#define SHL_ONE_AWESOME_SHL_H

/* configure the SHL with macros before header inclusion */
#define OAS_CONFIG_MACRO
#include <one-awesome-shl.h>

#endif /* SHL_ONE_AWESOME_SHL_H */
```

**another-awesome-shl.h**
```c
#ifndef SHL_ANOTHER_AWESOME_SHL_H
#define SHL_ANOTHER_AWESOME_SHL_H

/* configure the SHL with macros before header inclusion */
#define ANOTHER_AWESOME_SHL_WITH_SOME_PRETTY_LONG_MACRO
#include <one-weird-header-name-choice.h>

#endif /* SHL_ANOTHER_AWESOME_SHL_H */
```

**shl.c**
```c
/* one-awesome-shl */
#define OAS_IMPLEMENTATION
#include "one-awesome-shl.h"

/* another-awesome-shl */
#define ANOTHER_AWESOME_SHL_IMPLEMENTATION
#include "another-awesome-shl.h"
```

## An example with 2 SHL and a build system

The project holding this README file uses 
[Nuklear](https://github.com/Immediate-Mode-UI/Nuklear) and
[STB](https://github.com/nothings/stb).

To make it funky, I use [CMake](https://cmake.org/) to import them and build my demo project.
I use CMake's [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) module to automatically download needed libraries, and so they are kept in the build directory, hidden from the project, and only available through imported targets of cmake.

An additional feature of using local header files is to add some stuff after the inclusion of the SHL header, to augment it for personal use (see how I have added two functions for `stb_ds.h`).
