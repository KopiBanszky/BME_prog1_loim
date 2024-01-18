cmake_minimum_required(VERSION 3.26)
project(legyen_on_is_milliomos C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c
        libs/econio.c
        libs/read_data.c
        libs/utility.c
        libs/debugmalloc.h
        libs/din_list_manager.c
        pages/main_menu.c
        properties.h
        pages/settings_menu.h
        pages/settings_menu.c
        pages/name_page.c
        pages/name_page.h
        pages/pause_page.c
        pages/pause_page.h
        libs/din_list_manager.h
        pages/choose_question.c
        pages/choose_question.c
        pages/choose_question.h
        libs/read_data_from_row_file.c
        libs/read_data_from_row_file.h
        pages/row_question_page.c
        pages/row_question_page.h
        libs/manage_stat_file.c
        libs/manage_stat_file.h
        pages/stat_page.c
        pages/stat_page.h)

add_executable(legyen_on_is_milliomos ${SOURCE_FILES})
