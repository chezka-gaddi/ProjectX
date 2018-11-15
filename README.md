# Slackers_Platform
Want instant communication with the Dev team? Join our
[Discord Channel](https://discord.gg/VN7ZuWR)!
## Release 4.02
## Fixed
- Modified max radar range to be equal to map width.
- Changed undestructible object sprite so it no longer looks like destructible objects
- Added MAXTURNS option into the config file
- Fixed ramming algorithm.  If a tank has 1 health and they ram another tank they will die.  If a tank has more than 1 health and the ramming damage would kill them, there health is instead set to 1.
- Added support for maps down to 5x5.  Sizes below 15x9 will fill in missing squares with unpassible objects.

## Release 4.01
## Fixed
- Range now properly scales the distance a projectile can travel. Previously, they were stuck at 6.
- baseStats are now properly passed to tanks during setAttributes.  Previously, a freshly initalized variable was passed resulting in all 0's.
- Default values have been set:
  - Health = 3   - The amount of health a tank starts with
  - Damage = 1   - The amount of damage a tank's projectile does
  - AP = 2       - The amount of Action points a tank starts with.
  - Ammo = 6     - The amount of ammo a tank starts with before needing to reload
  - Radar = 4    - How far a tanks Radar expands to
  - Range = 4    - How many spaces a projectile travels per turn
  - Shots = 0    - This is a counter, no matter how many points you put here, it will stay 0.
- Reduced size of program. 
## Release 4.00
## What's new?
- Updated Scoreboard
  - The scoreboard now lists more interesting facts about the tanks and has support for a draw.
- Reloading
  - Tanks now have a limited number of ammunition.  After they reach the limit they will have to reload.
  - A tank can reload by sending back action number 4 or the tank will automatically reload if it has no ammo and it attempts to fire.
- Water
  - New title type added that cannot be passed by tanks.  Projectiles on the other hand of no problem flying above the water.
- Health Map
  - When a tank is sent a map object there is now an additional map called the health map.  It will list the health of all the objects the tank can see.
- Attributes
  - Tanks now recieve a copy of there base stats when asked for their choice of special point spending.
- MaxTurns
  - The number of max turns can now be set in the config file.
- New formula for calculating field size display.
- Behind the scene caps for special points when dealing with a large special amount 

## Fixed
- Damage 
  - Fixed some inconsistencies between tank and projectile damages.
- SimpleAI
  - SimpleAI will now move even when it can't see the whole map.
  - Fixed incorrect header prototype.

## Release 3.10
## What's new?
- Scoreboard
  - At the end of the game a list of the top 3 players will be displayed.
- Crate_o_Fun
  - A new crate was added that has a surprise for anyone that shoots it.
- Tanks
  - Additional tank colors have been added to the map.
- Maps
  - All maps have been updated with destructible objects so that they can now be 
- Default Map
  - The default map has been updated to support up to 10 Tanks.
- SimpleAI
  - Adjusted SimpleAI so that it will no longer refuse to play the game if it can't see.

## Release 3.01
### What's new?
- Object health
	- If you arn't a fan of the new objects, now you can do something about it.  Trees and rocks can both be destroyed with enough projectile hits.
	-Warning: You still cannot drive over rocks and will take damage if you try.  After they are destroyed you can safely move over them.
	- If you were tired of the paint on your tank fading, you can now sit under the shade of a tree.  This has the added benefit of taking a few hits from projectiles for you.
	- With the new objects means the obstacle map has been changed.  It is no longer a boolean array with simply occupied or not.  It now tells you if it's empty 0, a tree T or a rock R.  
	- Previous code will still work with empty = false and everything else = true, however your tank won't know to hide in a tree if you don't update it's routines.
	- NOTE: The map can still be setup to use old style obstacles which will appear on the GUI using the new images, but retain the original properties: Infinite health, unpassible, and damaging when trying to move.  In this mode they will appear as a 1 in the obstacle map.
- New Map System
	- Maps can now be parse from the config file as shown in the config.sample
	- Valid map symbols: R - Rock, T - Tree, B - Bush, O - Obstacle, and a space for empty
	- The width and height parameters are now mandatory so the config file parser knows how big to search
  - A smaller sample map has been included in the src folder.
- Updated loading messages so if something fails you know where. Maybe.
- Makefile update
	- The makefile was updated to allow the use of the structres found in the header files found in the src directory.  This means you can make your own mapData structure to save data instead of relying soley on the one provided each turn.
- Results.txt
	- The results.txt will now be created on a first run of the platform.  It will log all the players added to the map, and the winner of the game.  And append to the file if it exists.

### Fixes
- Fixed a bug where dead actors were causing a delay in turn processing.
- Partially, optimized turn checks for a small speed increase.  

## Release 2.04
### New Features
- The same boring objects are a thing of the past.  The game will now choose a random obstacle category when generating the map.  In addition to a random category, a random style will also be selected.

## Release 2.03
### New Features
- Added a new config.sample file that gives a template for how to setup a map file.
- If the makefile detects that no configuration file is present, it will automatically generate one from the config.sample file.
### Changes:
- The repository no longer stores a config.txt file.  This is to prevent a developers local copy from getting overwritten and to avoid merge conflicts.  This means that on a first clone the user will need to run 'make' once to generate a config.txt file if it does not exist.

## Release 2.02
### Fixes
- Problem with freshly made tanks not being able to find the constructor
- The game will display a message to console and exit when no config file is found
- Changed development pipeline to push to a pre-release branch before merging with master release

## Release 2.01
### What needs to change:
- All config.txt files will need to be updated with new image files.  The format is now:
	AI <AI Name> <x> <y> <Up Image> <Right Image> <Down Image> <Left Image> <Bullet Image>
	All images follow this format:
	images/<color>/tank<ColorLetter>_<direction>.png
	images/<color>/bullet<ColorLetter>.png
	For the blue tank:
		images/Blue/tankB_U.png 
		images/Blue/tankB_R.png 
		images/Blue/tankB_D.png 
		images/Blue/tankB_L.png 
		images/Blue/bulletB.png

### What's New?
- Radar
	- The Radar stat is what determines how far around the tank it can see.  If you 
		have a Radar stat of 2, you will only be able to see objects 2 spaces away from 
		you.
- Random Objects
	- The platform will now select from a pool of objects during object placement on
		the map.  The current two options are:  Tree, or Rock.
- Map Scaling
	- The map size can now be changed in the configuration settings between 15x9 to 
		40 x 20
- Idle Speed Adjustment
	- The idle speed can be changed within the configuration file.  Currently, this will
		only affect the time between turns.
- Restructuring of Images
	- Added two new colors for tanks and projectiles.  And restructured them based on their 
	affiliated color.
	- Restructured Objects into folders based on type

### Fixes
- Deconstructor is now called for custom tanks instead of relying on the parent.
- Changed configuration file to account for Radar instead of Range.
- Tanks are now limited to only pending the allowed number of attribute points.
- You will no longer get a message for an incorrect number of attribute points spent
	if you were within the limit.

## Release 1.04
### Whats New?
- Added checks for tanks cheating and adding too many attributes points to their
stats

## Release 1.03
### What's New?
- A new example tank has been added to show the basics of movment and shooting
- Fixed Bugs associated to parsing the config file,
    - The config file can now load up to 4 tanks
    - The config file also now error checking so invalid options are ignored and
set to defaults
- Improved the effeciency of the game manager so tank moves process faster
