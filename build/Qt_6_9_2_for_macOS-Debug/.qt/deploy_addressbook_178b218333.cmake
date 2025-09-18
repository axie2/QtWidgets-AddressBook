include("/Applications/Qt/Examples/Qt-6.9.2/widgets/itemviews/addressbook/build/Qt_6_9_2_for_macOS-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/addressbook-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "addressbook.app"
)
