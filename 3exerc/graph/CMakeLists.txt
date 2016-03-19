add_library (lgraph lgraph.c)
add_library (magraph magraph.c)

target_include_directories (lgraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories (magraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

