set(BINARY ${CMAKE_PROJECT_NAME}_tst)

add_executable(${BINARY} Puzzle-test.cpp PuzzleGenerator-test main.cpp)
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)

add_test(NAME ${BINARY} COMMAND ${BINARY})
