# OpenOCD配置


```json

    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug with OpenOCD",
            "device": "STM32H743VIHx", //MCU used
            "cwd": "${workspaceRoot}",
            "executable": "${command:cmake.launchTargetPath}",
            "request": "launch",
            "type": "cortex-debug",
            "servertype": "openocd",
            "configFiles": [
                "stlink-v2.cfg",
                "stm32h7x.cfg"
            ],
            "searchDir": [],
            "svdFile": "${config:STM32VSCodeExtension.cubeCLT.path}/STMicroelectronics_CMSIS_SVD/STM32H743.svd",
            "runToEntryPoint": "main",
            "showDevDebugOutput": "raw",
            "interface": "swd",
            "rttConfig": {
                "enabled": true,
                "address": "auto",
                "decoders": [
                    {
                        "label": "",
                        "port": 0,
                        "type": "console"
                    }
                ]
            },
            "liveWatch": {
                "enabled": true,
                "samplesPerSecond": 4
            }
        }
    ]
    
```