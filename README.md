# Set Game Implementation in C++

This repository contains a console-based implementation of the popular board game "Set" written in C++.

## Overview

"Set" is a card game where players identify sets of three cards based on certain characteristics, such as color, shape, number, and shading. A set consists of three cards in which each feature is either all the same or all different. 

## Files

- **main.cpp**: Contains the main logic for running the game.
- **Card.h** and **Card.cpp**: Define the Card class representing each card in the game.
- **functions.h** and **functions.cpp**: Declare and implement various helper functions used in the game, such as shuffling the deck and checking for sets.
- **set.exe**: .exe file for starting the game.
- **save.txt**: Example of a saved game.

## Gameplay

The game starts with a deck of 81 unique cards, with each card having four features: color, shape, number, and shading.
At the beginning of the game, 12 cards are dealt onto the board.
Players can choose three cards from the board and determine if they form a set. If they do, those cards are replaced with new ones from the deck.
The game continues until either the player exits or there are no more sets on the board.
Players can save and load their game progress at any time.

## Features

Random shuffling of the deck ensures a different game experience each time.
ANSI escape codes are used to display colorful cards in the console.
Players can save and load their game progress using text files.

## How to Play
Start a new game or load a saved game.
Look for sets of three cards on the board.
If you find a set, select those three cards.
The game will indicate whether the selected cards form a set.
Continue playing until you finish or exit the game.
