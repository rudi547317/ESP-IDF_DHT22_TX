# ESP-IDF_DHT22_TX

**Table of Contents** 
1. [Project Description](#pd-id)
1. [Project Features](#pf-id)
1. [Installation and Setup](#ps-id)
1. [Important repos/links](#pm-id)
1. [Availible Parameter Modifications](#il-id)


```c

printf("Hello World\n")

```

<br>
<br>
<br>
<br>
<br>
<br>
<br>

<a id="pd-id"></a>

## Project Description  

![image](https://github.com/rudi547317/ESP-IDF_DHT22_TX/assets/133919829/0d16897e-867d-4298-a99f-3b3447507038)


### Supported versions of frameworks and devices

| Chip           | Framework          | Eclipse Versions                        |
|----------------|--------------------|-----------------------------------------|
| ESP32          | ESP-IDF v4.3.1     | Eclipse Version: 4.20.0.v202110611-1600 |

<br>
<br>
<br>
<br>
<br>
<br>
<br>

<a id="pf-id"></a>

## Project Features  

<br>
<br>
<br>
<br>
<br>
<br>
<br>

<a id="ps-id"></a>

## Installation and Setup

### CMakeLists.txt Files
Delete default CmakeLists.txt file and replace with code below 

**Directory:**_/WorkSpace/Project_TX/CMakeLists.txt_

```Makefile
# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)
set(EXTRA_COMPONENT_DIRS "esp-idf-lib/components")
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})
```

<br>
<br> 

**Directory:**_/WorkSpace/Project_TX/main/CMakeLists.txt_

```Makefile
# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.


idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS ".")
```

<br>
<br>
<br>
<br>
<br>
<br>
<br>

<a id="il-id"></a>

## Important repos/links  


<br>
<br>
<br>
<br>
<br>
<br>
<br>

<a id="pm-id"></a>

## Availible Parameter Modifications  

<br>
<br>
<br>
<br>
<br>
<br>
<br>

