


## 0 总体结构

- **RAM(Random Access Memory, 随机存取存储器)**
  - **SRAM(Static Random Access Memory, 静态随机存取存储器)**
  - **DRAM(Dynamic Random Access Memory, 动态随机存取存储器)**

- **ROM(Read Only Memory, 只读存储器)**
  - **ROM(Read Only Memory, 只读存储器)**
  - **PROM(Programmable Read-Only Memory, 可编程只读存储器)**
  - **EEPROM(Electrically Erasable Programmable Read-Only Memory, 电可擦除可编程只读存储器)**

- **FLASH**
  - **Nandflash**: 主要用于大容量数据存储。
  - **Norflash**: 支持随机访问，适合代码存储和执行。

## 01 RAM

“随机存储器”，是与CPU直接交换数据的内部存储器，也叫主存(内存)。存储单元的内容可按需随意取出或存入，且存取的速度与存储单元的位置无关的存储器。

  
所谓“随机存取”，指的是当存储器中的数据被读取或写入时，所需要的时间与这段信息所在的位置或所写入的位置无关。相对的，读取或写入顺序访问（Sequential Access）存储设备中的信息时，其所需要的时间与位置就会有关系。

## 02 SRAM

SRAM是英文Static RAM的缩写，它是一种具有静止存取功能的内存，静态随机存取存储器采取多重晶体管设计，不需要刷新电路即能保存它内部存储的数据，特点为高性能、低集成度、速度快、体积较大。

## 03 DRAM

DRAM动态随机存取存储器中每个存储单元由配对出现的晶体管和电容器构成，每隔一段时间，固定要对DRAM刷新充电一次，否则内部的数据即会消失。

## 04 ROM

rom最初不能编程，出厂什么内容就永远什么内容，不灵活。后来出现了prom，可以自己写入一次，要是写错了，只能再换一片。后来又出现了可多次擦除写入的EPROM，每次擦除要把芯片拿到紫外线上照一下。

## 05 EEPROM

电可擦除可编程只读存储器”，即Electrically

Erasable Programmable Read-Only Memory，是相对于紫外擦除的rom来讲的。

## 06 FLASH

flash属于广义的EEPROM，因为它也是电擦除的rom。但是为了区别于一般的按字节为单位的擦写的EEPROM，我们都叫它flash。

  
flash做的改进就是擦除时不再以字节为单位，而是以块为单位。

  
flash分为nor flash和nand flash。

  
norflash数据线和地址线分开，可以实现ram一样的随机寻址功能，可以读取任何一个字节。但是擦除仍要按块来擦。

  
nandflash同样是按块擦除，但是数据线和地址线复用，不能利用地址线随机寻址。

  
读取只能按页来读取。（nandflash按块来擦除，按页来读，norflash没有页）

## 07 Nandflash

Nandflash是IO设备，数据、地址、控制线都是共用的，需要软件区控制读取时序，所以不能像nor flash、内存一样随机访问，不能EIP（片上运行），因此不能直接作为boot。

  
S3C2440把Bootloader烧到nand flash上启动，因为在S3C2440里有一个内置的SRAM，叫做stepping stone(垫脚石，很形象…)，系统启动加电后，会把nandflash上的起始4KB的内容拷贝到SRAM里执行，这样就实现了从nandflash启动。

## 08 Norflash

Norflash的有自己的地址线和数据线，可以采用类似于memory的随机访问方式，  
在norflash上可以直接运行程序，所以norflash可以直接用来做boot。

  
norflash适合做代码存储并EIP的，nandflash适合用来作大量数据存储的。

norflash的读取速度比nandflash稍快，但擦写速度比nandflash慢很多。


> 所谓“随机存取”，指的是当存储器中的数据被读取或写入时，所需要的时间与这段信息所在的位置或所写入的位置无关。相对的，读取或写入顺序访问（Sequential Access）存储设备中的信息时，其所需要的时间与位置就会有关系。

