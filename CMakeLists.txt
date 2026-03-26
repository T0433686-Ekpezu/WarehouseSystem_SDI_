cmake_minimum_required(VERSION 4.0)
project(WarehouseSystem_SDI_)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(WarehouseSystem_SDI_
        SRC/main.cpp
        SRC/Product.cpp
        SRC/OrderItem.cpp
        SRC/Order.cpp
        SRC/User.cpp
        SRC/Employee.cpp
        SRC/Manager.cpp
        SRC/Inventory.cpp
        SRC/FileHandler.cpp
)

set_target_properties(WarehouseSystem_SDI_ PROPERTIES RUNTIME_OUTPUT_DIRECTORY
${CMAKE_SOURCE_DIR}/BUILD
)