find_package(Qt6 REQUIRED COMPONENTS Widgets Test)

add_executable(test_addressbook test_addressbook.cpp)
target_link_libraries(test_addressbook PRIVATE Qt6::Widgets Qt6::Test)
add_test(NAME AddressBookTests COMMAND test_addressbook)
