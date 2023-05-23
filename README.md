# ESP-IDF_DHT22_TX

**Table of Contents** 
1. [Project Description](#pd-id)
1. [Project Features]
1. [Installation and Setup]
1. [Usage examples]
1. [Link to ESP-idf-
1.


```c


printf("Hello World\n");

```
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<a id="pd-id"></a>

## Project Description  

**Completed Project Example**
<br>
![image](https://github.com/rudi547317/ESP-IDF_DHT22_TX/assets/133919829/0d16897e-867d-4298-a99f-3b3447507038)



**Changes should be made to the following CMakeFile** 

/WorkSpace/Project_TX/CMakeLists.txt

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
Delete existing make file and replace with code above 
