set(SRC_LIB_NAME src)
set(SOURCES CharacterFinder.cpp Character.cpp CharacterParser.cpp)

include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.11.2
        )
FetchContent_MakeAvailable(json)

add_library(${SRC_LIB_NAME} ${SOURCES})
target_sources(${SRC_LIB_NAME} PRIVATE ${SOURCES})
target_include_directories(${SRC_LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${SRC_LIB_NAME} nlohmann_json::nlohmann_json)
