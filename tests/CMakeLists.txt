find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Test)

add_executable(test_addressbook
    test_addressbook.cpp
    ../mainwindow.cpp
    ../addresswidget.cpp
    ../adddialog.cpp
    ../tablemodel.cpp
    ../newaddresstab.cpp
)

target_link_libraries(test_addressbook PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Test
)

target_compile_features(test_addressbook PRIVATE cxx_std_17)

add_test(NAME AddressBookTests COMMAND test_addressbook)
