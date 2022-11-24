# XMC4800_Simple_SOES_Slave - EtherCAT

![image](https://user-images.githubusercontent.com/32091677/154466757-94ec70eb-4ea5-4070-bedc-38739e0c68ee.png)

# Debugger (Visual Studio Code)

## Requirements
1. Visual Studio Code: [link](https://code.visualstudio.com/)
2. GNU ARM Embedded tool-chain: [link](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
3. J-Link: [link](https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack)
4. Visual Studio Code Plugins:
 + C/C++ for Visual Studio Code:[link](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
 + Cortex-Debug:[link](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)
 + C/C++ Intellisense: [link](https://marketplace.visualstudio.com/items?itemName=austin.code-gnu-global) optional

## Build steps
Add the following to your `~/.bashrc` so that the build process can find the necessary binaries. 
```
export PATH="PATH_TO_GCC_ARM/gcc-arm-none-eabi-10.3-2021.10/bin:$PATH"
source ~/.bashrc
```
```
sudo apt install ncurses5
mv vscode .vscode
mkdir build && cd build
cmake ..
make
```

## To run debugger - VS Code
1. In Visual Studio Code, open this project : ``File`` -> ``Open folder``
2. Plug in the XMC board with USB connection.
2. Press F5 to run debugger


## To build and run debugger - Eclipse

1. Install Eclipse Embedded CDT
https://projects.eclipse.org/projects/iot.embed-cdt

2. Install Jlink, GCC ARM, OpenOCD

2. Setup in the project options the MCU tools:
![image](https://user-images.githubusercontent.com/32091677/155189890-06e1cdce-28ce-4441-87dc-e178081a358d.png)

![image](https://user-images.githubusercontent.com/32091677/155189993-8970d03a-c1af-4a55-888b-75016ac61414.png)

![image](https://user-images.githubusercontent.com/32091677/155190050-8f32889d-f0cf-49af-93d0-6385fb0dd369.png)

3. Setup in the project options the build options:
![image](https://user-images.githubusercontent.com/32091677/155190323-6eb39fa0-5082-4808-8fc9-bac357f5d7be.png)

![image](https://user-images.githubusercontent.com/32091677/155190407-c26a882e-60c5-4bb2-acad-a88c31daa5a7.png)

4. Setup the debug configuration:
![image](https://user-images.githubusercontent.com/32091677/155190736-10b3bfe0-a981-49ec-9660-5dd344130051.png)

![image](https://user-images.githubusercontent.com/32091677/155190837-181957dd-401f-4bb9-9d04-e77b9a64a7ea.png)

![image](https://user-images.githubusercontent.com/32091677/155190922-31d1abca-399b-42bc-a744-02f223c308c6.png)

