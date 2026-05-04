# Flappy Bird clone for Linux - Local LLM vibe coding experiment

This repo is meant to be a simple Flappy Bird clone targeting Linux + SDL2.

The goal of the project is to try out local LLMs and how well they're suited for software development. The (initial) scope of the project is therefore kept very limited on purpose.

Language for the project is C++. We'll use cmake as the build system and assume SDL2 is installed on the build machine and link against it dynamically. We'll target C++20.


## Roadmap

- Window creation
- Basic gameplay + event loop
- Input system
- Game logic
- Menu system


## Restrictions

- The game should use SDL2 for rendering. Don't expect any hardware acceleration to be present so that the game is as portable as possible.
- Use SDL2 for input. Only mouse clicks should be used for user input.

