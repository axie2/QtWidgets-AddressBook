# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(addressbook LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()

qt_add_executable(addressbook
    adddialog.cpp adddialog.h
    addresswidget.cpp addresswidget.h
    main.cpp
    mainwindow.cpp mainwindow.h
    newaddresstab.cpp newaddresstab.h
    tablemodel.cpp tablemodel.h
    tests/test_addressbook.cpp
    tests/CMakeLists.txt
)

set_target_properties(addressbook PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(addressbook PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

install(TARGETS addressbook
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET addressbook
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})


enable_testing() # enables CMake's CTest framework
# CTest Framework allows for commands like:
    # ctest    :runs all tests added with add_test()
    # ctest -V   :runs all tests and shows verbose output
add_subdirectory(tests)
