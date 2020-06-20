# Platforms

`Platforms` is an independent subdirectory of the beetree framework where the interface to the hardware is defined and implemented. There is a Many-to-1 relationship between *Applications* to *Platforms*. For example, many applications may re-use the same platform. However, an application should never try to use multiple platforms.

> The ultimate goal of platforms is to create a common, lightweight interface to the hardware while maintaining code re-use across processors and *operating systems*.

## Directory Structure

```bash
                                        # [lib] designates that contents of the
                                        #     directory results in a [binary] library
                                        # [~lib] means the library built for the
                                        #     common case.
platforms/
├── cmake                               # platform's pre-config settings for cmake,
│   ├── my--embedded-platform.cmake     #     e.g. linker files, global compiler definitions
│   └── ...
├── include                             # public headers and interfaces
│   ├── my-embedded-platform            # platform specific public headers and interfaces
│   ├── my-multi-processor-platform
│   │   ├── my-first-processor-platform
│   │   └── my-second-processor-platform
│   │   └── ...
│   ├── platform-interface              # the interface used by the application
│   │   ├── analog-input.hpp
│   │   ├── system-clock.hpp
│   │   ├── discrete-output.hpp
│   │   └── ...
│   ├── platform-library                # platform library which can be used by the application
│   │   └── public.hpp
│   └── unit-test-platform              # unit test platform containing mocks of
│                                       #     platforms/include/platform-interface
├── modules                             # implementation and not public
│   ├── my-embedded-platform [lib]      # platform specific implementation
│   │   └── bsp                         # bsp lives with the platform if not supported
│   │                                   #     in platform-library
│   ├── my-multi-processor-platform
│   │   ├── my-first-processor-platform [lib]
│   │   │   └── bsp
│   │   ├── my-second-processor-platform [lib]
│   │   │   └── bsp
│   │   └── ...
│   ├── generic-platform                # support running on common os's
│   │   ├── linux [lib]
│   │   ├── osx [lib]
│   │   └── windows [lib]
│   ├── platform-library  [~lib]            # common implementation for platforms including
│   │   ├── stm32-processor-family  [lib]   #     processory families e.g. stm32 common implementations
│   │   │   ├── vendor-source
│   │   │   │   └──  ...
│   │   │   ├── analog-input.xpp
│   │   │   ├── system-clock.xpp
│   │   │   ├── discrete-output.xpp
│   │   │   └── ...
│   │   ├── atmel-processor-family [lib]
│   │   │   ├── vendor-source
│   │   │   │   └──  ...
│   │   │   ├── analog-input.xpp
│   │   │   ├── system-clock.xpp
│   │   │   ├── discrete-output.xpp
│   │   │   └── ...
│   │   ├── common.xpp                  # libraries non-processor specific implementation, e.g ringq
│   │   └── ...
│   └── unit-test-platform              # implementation for unit-test test fixture, etc.
│       └── ...
└── toolchains
```