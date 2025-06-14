cmake_minimum_required(VERSION 3.14)
project(ServerApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tìm Boost (Asio + Beast nằm trong Boost >= 1.66)
find_package(Boost REQUIRED COMPONENTS system)

# Tìm thư viện nlohmann_json
find_package(nlohmann_json REQUIRED)

# Thêm đường dẫn chứa header
include_directories(include)
include_directories(${Boost_INCLUDE_DIRS})

# Gộp toàn bộ file .cpp
file(GLOB_RECURSE SOURCES
    "source/*.cpp"
)

# Tạo file thực thi
add_executable(ServerApp ${SOURCES})

# Link thư viện Boost và nlohmann_json
target_link_libraries(ServerApp
    ${Boost_LIBRARIES}
    nlohmann_json::nlohmann_json
)
