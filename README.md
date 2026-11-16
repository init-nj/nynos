# nyn0S

**A lightweight, from-scratch operating system for resource-constrained legacy hardware.**

> nyn0S is an experimental operating-system project focused on understanding and implementing the fundamental layers of an x86 system while exploring how a purpose-built OS can make older, low-resource computers useful again.

[![Status](https://img.shields.io/badge/status-early%20development-orange)](#project-status)

## Overview

nyn0S is an operating system being developed from the lowest practical software level rather than being built on top of an existing operating-system kernel. The project uses **C and x86 Assembly** and is being developed incrementally, starting with the boot path and kernel bring-up.

The main design constraint is resource efficiency. Instead of adapting a general-purpose operating system to older hardware, nyn0S explores an environment in which memory use, CPU overhead, storage footprint, and system complexity are considered throughout the design process.

The long-term goal is to provide a practical, lightweight computing environment for tasks such as:

- Basic office and document work
- File and directory management
- Programming and coding
- Command-line computing
- Lightweight graphical desktop interaction
- Basic networking and web access, subject to hardware and implementation limits

This is a long-term systems-development project. It is **not yet a daily-use operating system** and should be treated as experimental software.

## Motivation

The project is motivated by a legacy Acer Aspire One-class computer from approximately 2010. The intended target machine is described as having:

| Component | Target specification |
|---|---|
| Processor | Single-core Intel Atom |
| Memory | 1 GB DDR3 RAM |
| Storage | Approximately 100 GB |
| Device class | Legacy netbook / low-resource x86 computer |

These specifications are approximate and will be confirmed against the exact hardware model before physical-hardware compatibility is claimed.

The project asks:

> Can an operating system designed specifically around severe hardware constraints provide useful everyday functionality while keeping its own resource overhead small and measurable?

Machine-learning model training, modern gaming, professional video editing, and other compute-intensive workloads are outside the intended scope.

## Project goals

The project aims to develop the following components over time:

- [ ] Custom bootloader and boot process
- [ ] Kernel initialization and core runtime
- [ ] CPU setup, interrupts, and exception handling
- [ ] Physical and virtual memory management, as supported by the target architecture
- [ ] Process and task management
- [ ] Basic storage drivers and filesystem
- [ ] Keyboard and mouse support
- [ ] Command-line shell and basic utilities
- [ ] Lightweight graphical user interface
- [ ] File manager
- [ ] Networking support
- [ ] Investigation of lightweight web access / browser support
- [ ] Performance measurement and optimization

The checklist reflects the intended direction of the project, not a claim that these features are already implemented.

## Technology and development approach

| Area | Planned approach |
|---|---|
| Main languages | C and x86 Assembly |
| Initial architecture | x86_64 development target |
| Kernel | Custom kernel developed for nyn0S |
| Boot process | Custom boot components; implementation is ongoing |
| Testing | QEMU emulation first, followed by compatible physical hardware |
| Firmware testing | UEFI testing with OVMF where applicable |
| Development style | Incremental implementation, testing, and documentation |

The initial development target is x86_64. Compatibility with the physical Acer Aspire One target must be verified against its exact processor model and supported instruction set before that machine is treated as a confirmed target.

### Development principles

1. **Build incrementally:** establish a small working foundation before adding more subsystems.
2. **Keep the system measurable:** record memory use, CPU use, boot behavior, storage footprint, and responsiveness as these become measurable.
3. **Treat constraints as design requirements:** avoid unnecessary services and abstractions where they do not provide enough value.
4. **Test before integrating:** validate individual components in emulation before relying on physical hardware.
5. **Document decisions:** record architecture choices, assumptions, limitations, and test results.

## Project status

**Current phase: early kernel development.**

The project has reached an initial milestone in which the kernel boot stage was reached in QEMU. The repository and implementation are still evolving; this milestone does not mean that the planned operating-system subsystems are complete.

| Area | Current status |
|---|---|
| QEMU-based boot testing | Initial kernel boot milestone reached |
| Custom boot path | In progress |
| Kernel foundations | In progress |
| Memory management | Planned / under development |
| Process and task management | Planned |
| Filesystem | Planned |
| Input drivers | Planned |
| Shell | Planned |
| GUI and file manager | Planned |
| Networking and web support | Future / experimental |
| Physical target compatibility | Not yet confirmed |

Update this table whenever a milestone is completed, changed, or deferred. Only mark a component complete after it has been implemented and tested.

## Repository structure

The repository is organized by subsystem. The layout may change as the architecture develops.

```text
nyn0S/
├── arch/
│   └── x86_64/
│       ├── boot/
│       ├── cpu/
│       ├── interrupts/
│       └── memory/
├── boot/
├── docs/
├── drivers/
├── fs/
├── include/
├── kernel/
├── lib/
├── mm/
├── scripts/
├── user/
└── README.md
```

High-level directory intent:

| Directory | Intended responsibility |
|---|---|
| `arch/` | Architecture-specific code |
| `boot/` | Boot-related implementation |
| `docs/` | Design notes, development records, and technical documentation |
| `drivers/` | Device drivers |
| `fs/` | Filesystem implementation |
| `include/` | Shared header files |
| `kernel/` | Kernel core |
| `lib/` | Shared low-level routines and support code |
| `mm/` | Memory-management implementation |
| `scripts/` | Build, run, and development scripts |
| `user/` | User-space components and utilities |

## Building and running

Build and run instructions are **not yet documented as a stable interface**. The build process and scripts are still under development, so commands should not be guessed or copied from older notes without checking the current repository.

For the current working procedure, consult the scripts and development notes in `scripts/` and `docs/`. Once the build and QEMU launch commands are stable, add the verified commands here, including required tool versions and firmware configuration.

### Planned documentation for this section

- Required compiler, assembler, linker, and build tools
- QEMU version and machine configuration
- OVMF firmware selection, when using UEFI
- Exact build command
- Exact QEMU launch command
- Expected boot output
- Troubleshooting notes

## Roadmap

The roadmap is intentionally milestone-based rather than tied to fixed delivery dates.

### Phase 1 — Boot and kernel foundation

- [x] Reach the initial kernel boot stage in QEMU
- [ ] Stabilize the boot-to-kernel handoff
- [ ] Establish kernel entry and initialization routines
- [ ] Add reliable diagnostic output

### Phase 2 — CPU and memory foundations

- [ ] Set up descriptor tables and exception handling
- [ ] Configure interrupt handling
- [ ] Add a physical memory manager
- [ ] Add the required virtual-memory mechanisms

### Phase 3 — Core operating-system services

- [ ] Introduce a basic task/process model
- [ ] Add timer and scheduling foundations
- [ ] Add storage-device access
- [ ] Implement an initial filesystem

### Phase 4 — User interaction

- [ ] Add keyboard input
- [ ] Implement a basic shell
- [ ] Add essential system utilities
- [ ] Add mouse support where appropriate

### Phase 5 — Graphical environment

- [ ] Establish a minimal graphics/display layer
- [ ] Develop a lightweight GUI
- [ ] Develop a basic file manager

### Phase 6 — Networking and optimization

- [ ] Investigate network-device support
- [ ] Evaluate practical web-access options
- [ ] Profile resource usage on emulated and physical hardware
- [ ] Optimize based on measured results

## Testing and evaluation

Performance and compatibility will be evaluated incrementally. Relevant measurements may include:

- Kernel and system memory consumption
- Idle and workload CPU utilization
- Boot time
- Storage footprint
- Input and interface responsiveness
- Stability under repeated boot and operation
- Compatibility with the intended physical hardware

Comparisons with existing lightweight operating systems should use the same hardware, comparable workloads, and clearly recorded measurement conditions. The project will not claim lower overhead or better performance without supporting test results.

## Innovation and intellectual-property research

An exploratory objective is to identify whether implementation work produces a distinct technical mechanism or design that may justify further intellectual-property research. Potential investigation areas include resource-aware memory and process management, reducing operating-system overhead, and adapting system functionality to available hardware resources.

Patentability is **not assumed or guaranteed**. Any potential invention would require separate novelty, prior-art, and legal assessment. Design notes and test results should be recorded as the project develops.

## Current limitations

- nyn0S is experimental and is not intended for production use.
- The physical target machine's exact model and CPU capabilities still need confirmation.
- Hardware-driver coverage will initially be limited.
- GUI, networking, and browser-related functionality are later-stage goals.
- Modern web compatibility is not guaranteed and may not be practical on the target hardware.
- No stable release, installer, or supported upgrade path is available yet.

## Keeping this README updated

Update this file whenever the project reaches a meaningful milestone. In particular:

1. Change the **Project status** table when a subsystem moves from planned to in progress or tested.
2. Update the **Roadmap** checkboxes only after the corresponding work is complete.
3. Add verified build/run commands when the scripts are stable.
4. Record measurable performance results with the hardware, configuration, and test conditions used.
5. Add important architecture decisions and links to detailed notes in `docs/`.
6. Add a dated entry to the changelog below.

### Development changelog

| Date | Update |
|---|---|
| 2026-11-16 | Created the initial project README; recorded the QEMU kernel-boot milestone and current development roadmap. |

## License

**License not yet selected.** Until a `LICENSE` file is added to the repository, do not assume that the source code is available for unrestricted reuse, modification, or redistribution.

## Project information

- **Project name:** nyn0S
- **Project type:** Individual operating-system development project
- **Primary languages:** C and x86 Assembly
- **Initial architecture target:** x86_64
- **Primary objective:** A resource-conscious operating system for legacy hardware
