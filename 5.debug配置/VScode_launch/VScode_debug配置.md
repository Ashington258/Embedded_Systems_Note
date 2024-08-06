# VScode Debug配置

VScode配置DEBUG主要是需要配置launch.json文件，常见的配置方法

1. 手动配置
2. 插件配置
   1. Cortex-debug
   2. STM32 VScode Extension

## Cortex-debug

使用插件可以生成一个惯用式的模板，但是还需要自行配置一些选项


## STM32 VScode Extension

该插件可以检测系统中STM32CubeCLT环境变量，从而可以很方便的配置，但是智能配置ST-LINK，所以其实可以先使用该插件基于STM32CubeCLT配置路径后映射回Jlink或其他debuger、


## 示例

我会给出我常用的json配置示例,其中包含了J-link，STlink，以及RTT/SWO功能的使用示例

```json

{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug with JLink",
            "cwd": "${workspaceFolder}",
            "executable": "${command:cmake.launchTargetPath}",
            "request": "launch",
            "type": "cortex-debug",
            "device": "STM32H743VIHx", //MCU used
            "runToEntryPoint": "main",
            "svdFile": "${config:STM32VSCodeExtension.cubeCLT.path}/STMicroelectronics_CMSIS_SVD/STM32H743.svd",
            "showDevDebugOutput": "none",
            "servertype": "jlink",
            "configFiles": [],
            // "preLaunchTask": "build",
            "rttConfig": {
                "enabled": true,
                "address": "auto",
                "polling_interval": 20,
                // "decoders": [
                //     {
                //         "label": "",
                //         "port": 0,
                //         "type": "console"
                //     }
                // ]
                
            },
            // "swoConfig": 
            // {
            //     "enabled": true, 
            //     "decoders": [
            //         {
            //             "type": "graph",
            //             "port": 0,      
            //             "encoding": "unsigned",
            //             "graphId": "1", 
            //             "scale": 1
            //         },
            //         {
            //             "type": "graph",
            //             "port": 1,      
            //             "encoding": "unsigned",
            //             "graphId": "2", 
            //             "scale": 1
            //         },
            //     ],
            //     "cpuFrequency": 75000000,   
            //     "swoFrequency":  2000000,   
            //     "source": "probe",
            // },
            
            // "graphConfig": [
            //     {
            //         "label": "Graph 1",
            //         "timespan": 5,
            //         "type": "realtime",
            //         "annotate": false,
            //         "maximum": 256,
            //         "minimum": 0,
            //         "plots": [
            //             {
            //                 "graphId": "1", 
            //                 "label": "data 1",
            //                 "color": "#53753c"
            //             },
            //             // {
            //             //     "graphId": "2", 
            //             //     "label": "data 2",
            //             //     "color": "#955f20"
            //             // }
            //         ]
            //     },
            // ],
            "liveWatch": {
                "enabled": true,
                "samplesPerSecond": 4
            }
        },
        {
            "name": "Build & Debug Microcontroller - ST-Link",
            "cwd": "${workspaceFolder}",
            "type": "cortex-debug",
            "executable": "${command:cmake.launchTargetPath}",
            // Let CMake extension decide executable: "${command:cmake.launchTargetPath}"
            // Or fixed file path: "${workspaceFolder}/path/to/filename.elf"
            "request": "launch",
            "servertype": "stlink",
            "device": "STM32H743VIHx", //MCU used
            "interface": "swd",
            "serialNumber": "",        //Set ST-Link ID if you use multiple at the same time
            "runToEntryPoint": "main",
            "svdFile": "${config:STM32VSCodeExtension.cubeCLT.path}/STMicroelectronics_CMSIS_SVD/STM32H743.svd",
            "v1": false,               //Change it depending on ST Link version
            "serverpath": "${config:STM32VSCodeExtension.cubeCLT.path}/STLink-gdb-server/bin/ST-LINK_gdbserver",
            "stm32cubeprogrammer":"${config:STM32VSCodeExtension.cubeCLT.path}/STM32CubeProgrammer/bin",
            "stlinkPath": "${config:STM32VSCodeExtension.cubeCLT.path}/STLink-gdb-server/bin/ST-LINK_gdbserver",   
            "armToolchainPath": "${config:STM32VSCodeExtension.cubeCLT.path}/GNU-tools-for-STM32/bin",
            "gdbPath":"${config:STM32VSCodeExtension.cubeCLT.path}/GNU-tools-for-STM32/bin/arm-none-eabi-gdb",            
            "serverArgs": [
                "-m","0",
            ],
            //"preLaunchTask": "Build + Flash"
            /* If you use external loader, add additional arguments */
            //"serverArgs": ["--extload", "path/to/ext/loader.stldr"],
            "liveWatch": {
                "enabled": true,
                "samplesPerSecond": 20
            },
            "rttConfig": {
                "enabled": true,
                "address": "auto",
                "clearSearch": false,
                "polling_interval": 20,
                "decoders": [
                    {
                        "label": "",
                        "port": 0,
                        "type": "console"
                    }
                ]
            }
        },
        {
            "name": "Attach to Microcontroller - ST-Link",
            "cwd": "${workspaceFolder}",
            "type": "cortex-debug",
            "executable": "${command:cmake.launchTargetPath}",
            // Let CMake extension decide executable: "${command:cmake.launchTargetPath}"
            // Or fixed file path: "${workspaceFolder}/path/to/filename.elf"
            "request": "attach",
            "servertype": "stlink",
            "device": "STM32H743VIHx", //MCU used
            "interface": "swd",
            "serialNumber": "",        //Set ST-Link ID if you use multiple at the same time
            "runToEntryPoint": "main",
            "svdFile": "${config:STM32VSCodeExtension.cubeCLT.path}/STMicroelectronics_CMSIS_SVD/STM32H743.svd",
            "v1": false,               //Change it depending on ST Link version
            "serverpath": "${config:STM32VSCodeExtension.cubeCLT.path}/STLink-gdb-server/bin/ST-LINK_gdbserver",
            "stm32cubeprogrammer":"${config:STM32VSCodeExtension.cubeCLT.path}/STM32CubeProgrammer/bin",
            "stlinkPath": "${config:STM32VSCodeExtension.cubeCLT.path}/STLink-gdb-server/bin/ST-LINK_gdbserver",   
            "armToolchainPath": "${config:STM32VSCodeExtension.cubeCLT.path}/GNU-tools-for-STM32/bin",
            "gdbPath":"${config:STM32VSCodeExtension.cubeCLT.path}/GNU-tools-for-STM32/bin/arm-none-eabi-gdb",            
            "serverArgs": [
                "-m","0",
            ],
            /* If you use external loader, add additional arguments */
            //"serverArgs": ["--extload", "path/to/ext/loader.stldr"],
        }

            ]
}

```