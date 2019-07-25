```
  _______  _______  _______ _________          _______  _______   
(  ____ \(  ___  )(  ____ )\__   __/|\     /|(  ____ )(  ____ \  
| (    \/| (   ) || (    )|   ) (   | )   ( || (    )|| (    \/  
| |      | (___) || (____)|   | |   | |   | || (____)|| (__      
| |      |  ___  ||  _____)   | |   | |   | ||     __)|  __)     
| |      | (   ) || (         | |   | |   | || (\ (   | (        
| (____/\| )   ( || )         | |   | (___) || ) \ \__| (____/\  
(_______/|/     \||/          )_(   (_______)|/   \__/(_______/  
                                                                 
_________          _______    _______  _        _______  _______ 
\__   __/|\     /|(  ____ \  (  ____ \( \      (  ___  )(  ____ \
   ) (   | )   ( || (    \/  | (    \/| (      | (   ) || (    \/
   | |   | (___) || (__      | (__    | |      | (___) || |      
   | |   |  ___  ||  __)     |  __)   | |      |  ___  || | ____ 
   | |   | (   ) || (        | (      | |      | (   ) || | \_  )
   | |   | )   ( || (____/\  | )      | (____/\| )   ( || (___) |
   )_(   |/     \|(_______/  |/       (_______/|/     \|(_______)
                                                                 
```
  
Capture the flag is an AI driver tank battle simulation platform.  
  
## Installation  
# Pre-requisite libraries  
  * freeglut3-dev
    * OpenGL - Development libraries
  * SOIL  
    * Image processing package  
  * make
    * Linux compiler script manager
  * g++
    * Linux C++ Compiler
  * gdb
    * Linux debugger
  
# Optional Software for Windows Users  
  * Xming  
    * X-server package for displaying platform on windows
  
# Clone the repository  
  * ```git clone git@gitlab.mcs.sdsmt.edu:7442182/projectx.git```  

## Using the platform  
# Build the platform  
  * ```make```  
  * (optionaly) ```make -j8```  

# Run the initial build  
  * ```./platform```  
  
# Commandline options  
  * -quiet  
    This mode silences most text displayed during run time.  
  * -demo  
    This mode increases the display size to 1080p (1920x1080)  
  * -coverage  
    This mode silences most text and sets speed options to their fastest value  
  
## Testing and Coverage  
# Testing  
  * Method 1:  
    make tests  
    This method will build both sets of test binaries in the main program directory  
  * Method 2:  
    ```cd tests/src``` or ```cd tests/functional_tests```  
    ```make```  
    This method will build a single binary in next to the test source files.  
  
# Coverage  
  * ```./runCoverage.sh```  
    This command does a number of things:  
      It build special versions of the platform and testing binaries with coverage markers.  
      Runs a baseline test from the current configuration file.  
      Combines all of the data to show which lines of code were executed by the testing.  
      Generates an HTML report of the coverage data.  
  * ```./runCodeCheck.sh```
    This works similarly as runCoverage.  The difference is that it runs the platform during the checks to try and determine what code is never used by the platform. 
      *** Warning:  This is not 100% accurate, because of timing and how fast functions run it is possible for a function to simply be called in between the checks.