cmake_minimum_required(VERSION 3.10)

project(Calculate)

set(CMAKE_CXX_STANDARD 11)

# Přidání cesty k vlastním modulům
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
message(STATUS "${CMAKE_SOURCE_DIR}")
# Najít SDL2 knihovnu
find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL2 knihovna nebyla nalezena! Ujistěte se, že je SDL2 nainstalována a že jsou nastaveny správné cesty.")
endif()

# Najít SDL2_ttf knihovnu
find_package(SDL2_ttf REQUIRED)
if(NOT SDL2_TTF_FOUND)
    message(FATAL_ERROR "SDL2_ttf knihovna nebyla nalezena! Ujistěte se, že je SDL2_ttf nainstalována a že jsou nastaveny správné cesty.")
endif()

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

# Konfigurace souboru config.h
configure_file(
    ${CMAKE_SOURCE_DIR}/config.h.in
    ${CMAKE_BINARY_DIR}/config.h
    @ONLY
)

include_directories(${CMAKE_BINARY_DIR})

# Přidání cesty k záhlaví ../api
include_directories(${CMAKE_SOURCE_DIR}/api)

# Zdrojové soubory
set(SOURCES
    src/main.cpp
    api/calculate.cpp
)

# Sestavení spustitelného souboru
add_executable(Calculate ${SOURCES})

target_link_libraries(Calculate ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# Přidání calculate.h do instalačního balíčku
install(FILES ${CMAKE_SOURCE_DIR}/api/calculate.h DESTINATION include)

install(TARGETS Calculate DESTINATION /usr/local/bin)

message(STATUS "CMake configuration complete.")

# Vytvoření .desktop souboru z šablony
configure_file(
    ${CMAKE_SOURCE_DIR}/Calculate.desktop.in
    ${CMAKE_BINARY_DIR}/Calculate.desktop
    @ONLY
)

# Instalace .desktop souboru
install(FILES ${CMAKE_BINARY_DIR}/Calculate.desktop
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications/)

# Volitelně: Instalace ikony
install(FILES ${CMAKE_SOURCE_DIR}/icon/CalculateIcon.png
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/48x48/apps/)

# Volitelně: Instalace fontu
install(FILES ${CMAKE_SOURCE_DIR}/fonts/JosefinSans-Light.ttf
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/fonts/truetype/)

