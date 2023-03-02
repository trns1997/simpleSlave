# Simple_SOES_Slave - EtherCAT

## Requirements
1. GNU ARM Embedded tool-chain: [link](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
2. J-Link: [link](https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack)

## Build Project
1. The first thing is to tell the build system which arm-gcc you want to use. To do that makefile expects the environment variable `ARM_GCC_BIN_FOLDER` to be set.
```
export ARM_GCC_BIN_FOLDER="$PATH_TO_ARM_GCC_TOOLCHAIN/gcc-arm-none-eabi-10.3-2021.10/bin"
```
Note that you can add the previous export to your `~/.bashrc` so that you don't have to repeat the export each time you open a new terminal. 

2. Clone Simple Slave Project
```
$ git clone git@github.com:trns1997/simpleSlave.git
$ cd $PATH_TO_SIMPLE_SLAVE_PROJECT
```

3. Build Binaries
```
$ ./build.sh -h
Usage: ./build.sh mcu product board
OR
Usage: ./build.sh unit
Supported mcus:
  - XMC4800_F144x2048
Supported products:
  - ankle
  - blinker
  - fallsafe
Supported boards:
  - ankle
  - relax
```
Example if you wish to build **product** `blinker` on the **board** `xmc4800 relax kit` which has **mcu** `XMC4800_F144x2048`:
```
./build.sh XMC4800_F144x2048 blinker relax
```

## Deploy Binaries


### Debugging
<details close>
<summary>Debugger using Visual Studio Code</summary>
<br>
1. Download Visual Studio Code: [link](https://code.visualstudio.com/)

<br>
2. Visual Studio Code Plugins:

 + C/C++ for Visual Studio Code:[link](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
 + Cortex-Debug:[link](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)
 + C/C++ Intellisense: [link](https://marketplace.visualstudio.com/items?itemName=austin.code-gnu-global) optional
 
 <br>
3. Running the debugger

 + In Visual Studio Code, open this project : ``File`` -> ``Open folder``
 + Plug in the XMC board with USB connection.
 + Press F5 to run debugger
</details>

<details close>
<summary>Debugger using Eclipse</summary>
<br>
1. Install Eclipse Embedded CDT
https://projects.eclipse.org/projects/iot.embed-cdt

<br>
2. Install Jlink, GCC ARM, OpenOCD

<br>
3. Setup in the project options the MCU tools:
![image](https://user-images.githubusercontent.com/32091677/155189890-06e1cdce-28ce-4441-87dc-e178081a358d.png)

![image](https://user-images.githubusercontent.com/32091677/155189993-8970d03a-c1af-4a55-888b-75016ac61414.png)

![image](https://user-images.githubusercontent.com/32091677/155190050-8f32889d-f0cf-49af-93d0-6385fb0dd369.png)

<br>
4. Setup in the project options the build options:
![image](https://user-images.githubusercontent.com/32091677/155190323-6eb39fa0-5082-4808-8fc9-bac357f5d7be.png)

![image](https://user-images.githubusercontent.com/32091677/155190407-c26a882e-60c5-4bb2-acad-a88c31daa5a7.png)

<br>
5. Setup the debug configuration:
![image](https://user-images.githubusercontent.com/32091677/155190736-10b3bfe0-a981-49ec-9660-5dd344130051.png)

![image](https://user-images.githubusercontent.com/32091677/155190837-181957dd-401f-4bb9-9d04-e77b9a64a7ea.png)

![image](https://user-images.githubusercontent.com/32091677/155190922-31d1abca-399b-42bc-a744-02f223c308c6.png)
</details>
