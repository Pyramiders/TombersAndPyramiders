## Project Overview

### Game

Pyramid Panic is a 2.5D top down 16 person online ‘battle arena’ like game. Every player begins the game as an undead character with no weapons at the bottom of a pyramid. At the top of the pyramid is a treasure that brings your character back to life, but there is only one of these treasures and sixteen players. Players race to the top of the pyramid, solving puzzles, avoiding booby-traps and fighting other players along the way.

The combat system allows for five types of equippable items. Weapons, Shields, Greaves, Helmets and Chestplates. Weapons, Shields and Greaves are activables, each with unique affects. The items equipped determines your characters fighting abilities. The pyramid is filled with other undead aggressive enemies that can kill players, as well as puzzle rooms which may require multiple characters to partake together. 

### Engine

The game engine is a custom built C++ engine created for both Windows and Mac. The engine uses SDL for the cross-platform audio, input, networking and window creation support, while using OpenGL to handle all rendering to the Window. The engine contains multiple features, such as sprite rendering, post-processing effects, culling, physics and collision detection, networking, messaging systems, and audio.

### Current State

The game is currently at our planned Alpha stage, which was intended to be our minimum viable product for user testing the controls and combat system over the network. Currently, the engine is built, however will require optimizations before beta. The game itself allows for two users to create a game online and fight each other. There are not currently any puzzles or randomly generated rooms, as those were planned for our beta version. Users can run around online, attacking each other with the bow they get on spawn. The players can switch to the sword that is on the ground to fight with the sword. There are random walking and shooting AI’s that are placed around the scene which can kill players or be killed.

The game, however, is not complete. Not everything is sync’d over the network yet, meaning certain things get out of sync in the games. The game crashes on player death due to a bug with the networking logic, however that bug was deemed acceptable for the initial launch for testing due to player death already being the end game state for alpha. Optimizations are required to allow for mass scaling, currently the team is debating implementing quad tree’s to better handle the culling and physics collision. 

User testing will be done to determine changes required for the core mechanics in the game before finalizing them for Beta.

## Technology Stack

The game and engine are both written in C++ 11. It is intended to be compilable on both the Microsoft VC++ compiler as well as with g++, therefore strictly C++ 11 compliant code is only allowed. On Windows, SDK version 10> is used with ToolKit version 141. The only external dependency used is SDL in order to give us convenient access to cross-platform networking, audio and input, as well as OpenGL 3.3 being used for rendering.

### How To Compile - Windows
- git clone
- Open project in Visual Studio
- Use ToolKit version 141 and SDK version 10
- Build in x86
- If errors occur regarding missing DLL's, copy the DLLs from the "RequiredRuntimeWindowsDLLs" folder into the built .exe's directory
- If errors occur regarding failing to load assets, or if the screen is rendered in a pure colour such as red, create a "Game" folder in the directory that the .exe sits in, then copy the "Assets" folder into the new "Game" folder from the source code folder

### How  To Run - Windows

Once built, go to the directory the .exe sits in and run the executible by double clicking it.

### Mac

Alpha does not include Mac support. The engine does support Mac, however currently the game logic utilizes a very small amount of Microsoft specific code that is to be replaced before Beta. Mac support will be included in the future. 

## Roadmap

### Beta

Our next milestone, our beta, will be created over the next month. The beta includes many upgrades, turning our concept into the intended game. The networking component will be upgraded to support sixteen players in a server based LAN environment where one player acts as the server. Audio assets will be added (created or royalty free) for varying types of scene music, as well as sound effects for every intractable noisy action. The combat system will be extended in breadth, creating various weapons in order to expand the possibilities for combat. This includes creating multiple weapons, shields, greaves, helmets and chestplates, many of which will require unique activatable abilities. The first four floors will be created for the pyramid, randomly generating rooms, with sand slowly filling up the pyramid, acting as a pseudo-timer to escape each room. All visual assets will have their initial pass created, however not necessarily finalized, for characters, weapons, armour, rooms and UI. Simple bloom post-processing effects will be added, as well as potential other shaders. The clearly defined win state of reaching the top of the pyramid first will be added in order to complete the desired game loop. The game will also be runnable on both Windows and Mac (and theoretically Linux, however we do not promise such compatibility).

### Final

The final milestone will be for April. This final release will include completing all the flours of the pyramid, randomly generating the floors, creating both puzzle rooms and combat rooms. The combat system will showcase various items with various effects. A full polished UI will be available for the game lobby and HUD. Post processing effects will be in full force with finalized visual art assets and sound, creating a polished feel. Most of the work going into final will be determine by user-testing from beta on how to improve the raw gameplay itself.

## Team

The team consists of seven members. The project manager, Dustin Limington, as well as eight other members, Carson Roscoe, Chen Li, Erick Fernandez de Arteaga, Evgeni Maiseyeu, Jaegar Sarauer, Kevin Han, Michael Nation, and Tanja Tong. We are all senior students completing our Bachelor of Technology in Computer Systems who came together to create an awesome game together.
