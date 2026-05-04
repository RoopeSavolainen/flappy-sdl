# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Flappy Bird clone targeting Linux, written in C++20 with SDL2. This is a vibe-coding experiment for evaluating LLMs on software development tasks.

## Build System

CMake project. Standard workflow:

```bash
cmake -B build
cmake --build build
./build/FlappyBird
```

## Dependencies

- SDL2 (dynamically linked, must be installed on the system)
- CMake

On Debian/Ubuntu: `sudo apt install libsdl2-dev cmake build-essential`

## Constraints

- Use SDL2 software rendering only — no hardware acceleration, for maximum portability.
- Mouse clicks are the only user input mechanism.
- Assets go in `assets/images/` (BMP files). No sound support. All text is rendered via static BMP sprites and digit assets.
