include_guard(GLOBAL)

function(setup_project_directories)
    # 确定平台 (x64/x86)
    if(CMAKE_GENERATOR_PLATFORM)
        set(PLATFORM_NAME ${CMAKE_GENERATOR_PLATFORM})
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(PLATFORM_NAME "x64")
    else()
        set(PLATFORM_NAME "x86")
    endif()

    set(OUTPUT_SUBDIR "${PLATFORM_NAME}")
    message(STATUS "Output subdirectory configured as: ${OUTPUT_SUBDIR}")

    set(FINAL_OUTPUT_PATH "${CMAKE_BINARY_DIR}/${OUTPUT_SUBDIR}")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FINAL_OUTPUT_PATH}" CACHE PATH "Runtime output directory")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FINAL_OUTPUT_PATH}" CACHE PATH "Library output directory")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FINAL_OUTPUT_PATH}" CACHE PATH "Archive output directory")


    set(INTERMEDIATE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/mid/${OUTPUT_SUBDIR}")
    
    set(CMAKE_CXX_OBJECT_OUT_DIR "${INTERMEDIATE_OUTPUT_PATH}" CACHE PATH "Intermediate C++ object file directory")
    # if need
    set(CMAKE_C_OBJECT_OUT_DIR "${INTERMEDIATE_OUTPUT_PATH}" CACHE PATH "Intermediate C object file directory")

    message(STATUS "Final products will be placed in: ${CMAKE_BINARY_DIR}/${OUTPUT_SUBDIR}/")
    message(STATUS "Intermediate files will be placed in: ${CMAKE_BINARY_DIR}/mid/${OUTPUT_SUBDIR}/")
endfunction()

function(copy_resources_to_target TARGET_NAME)
    set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
    if(EXISTS ${RESOURCE_DIR})
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${RESOURCE_DIR}"
            "$<TARGET_FILE_DIR:${TARGET_NAME}>/res"
            COMMENT "Copying resources to output directory..."
        )
    endif()
endfunction()