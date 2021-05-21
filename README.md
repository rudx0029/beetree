# UNDERCONSTRUCTION

Apologies, we are under construction in order to provide you a better ~~beer~~ experience.

# StudioBee

1. extensible
2. interchangeable (platform swap)
3. modular
4. flexible
5. rapid
6. low cost
7. arduino like interfaces
8. leading embedded robotics ecosystem
9. STEM friendly
10. ROS compatible
11. framework
12. Close to the metal


Who we are?/ History?

We are a group of visionaries from a leading robotics organization.....


What issues are we addressing?

- Robotic software is academic, chaotic, at a code organization level -- hardware
- Existing frameworks do not provide consistent, approachable solutions.
- Hard to work with and off the shelf solutions cannot be used for production.


- FOCUS ON YOUR APPLICATION, NOT THREADING, DEVICES, PROTOCOLS, ALL THAT STUFF
- Focus on robotic easy robotic behaviors

- Inspiration is from the successful arduino community
- Development split between application develepment (your code) and platform development (our goal is to provide you this so you don't have to)
  - platform independence via simple interface 
  - run your application with no changes from a PC to an stm32 microcontroller.
- application development emphasising single tasking and static memory usage and supporting dynamic memory/multi-tasking 
     - We take care of the concurrency for you so you do not have to!!!!!
- Unified unit system

- organize complex autonomous sequences motion,events, 
- simplify complex systems

Components:

BeeTree (bte) - an embeddable, manageable, extensible, and approachable behavior tree solution
    - BeeTree Core the application library
    - BeePlatform - blah
BeeView - an web diagnostics interface
Beehaviorlets - a library of delegated autonomous and robotic behaviors
BeeUnits - a unified units system
BeeTrace - zero-memory,string-free, low latency, flexible, logging and event system
BeeRegistry - Inter/Intra-bee networking and communications - low latency - short and to point the point - simple - provides visibility - interprocessor interface
BeeBoard

How it fits to together:

TODO: Make diagram and then describe diagram
1. Interface between processors (BeeTrace, BeeRegistry)
2. Interface between platforms and application ()
3. Applicion Develpment in TREES (NEEDS EMPHASIS) (talk about earlier)
4. Nodes, Services, Models, Blackboard, Facilities (Beetree Section)
5. Remote control of beehaviorlets (NEEDS EMPHASIS) (via registry)

Quotes: "Intelligence close to the metal" says the distinguished engineer
Quotes: "Keep 'em separated! Factors my code into reasonable chunks, indepent and maintainable."

# ![beetree logo][logo] BeeTree

*BeeTree* is a behavior tree application framework written in `C++ 11` and targeted for small to medium embedded processors, e.g. *ARM Cortex M0* and *ARM Cortex M4*. The goal of the framework is to help make programming robotic behaviors more approachable for embedded processors while providing sophisticated behavior. This is accomplished by representing robotic strategies and behaviors as interchangeable, modular behavior trees, while maintaining a small, nimble footprint.

## Getting Started

[Hello World! Tutorial](docs/tutorials/helloworld.md)

An introductory tutorial that will walk you through setting up your environment, build BeeTree for the desktop, and launch BeeView, BeeTree's real-time web visualization.

[Development Environment](docs/development-environment.md)

The document presents the necessary tools to build and run BeeTree applications.

[Build BeeTree](docs/build-beetree.md)

The document presents an in-depth guide on how to build BeeTree applications for embedded platforms to desktop platforms.

[Architecture and Design](docs/architecture.md)

## User's Reference

For roboticists, hobbyists, and developers who want to create BeeTree applications.

[User's Guide](docs/users-guide/README.md)

## Developer Reference

For developers who want to contribute to the BeeTree project.

[Developer's Guide](docs/developers-guide/README.md)

[Best Practices](docs/best-practices.md)

[Coding Standards](docs/coding-standards.md)

## Other

[Handy References](docs/references.md)

[logo]: docs/img/beetree-logo-50px.png
