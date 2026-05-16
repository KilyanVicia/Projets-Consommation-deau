cmake_minimum_required(VERSION 3.16)

project(Consdeau VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(Qt6 REQUIRED COMPONENTS Charts)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appConsdeau
    main.cpp   labdd.h labdd.cpp

)

qt_add_qml_module(appConsdeau
    URI Consdeau
    VERSION 1.0
    QML_FILES
        Main.qml img/Deconnexion.png img/PersoAlrianne.png img/PersoAnjana.png img/PersoBernard.png img/PersoCatarina.png
        img/PersoCynthia.png img/PersoKilyan.png img/PersoRania.png img/PersoRayan.png img/PersoRoua.png img/PersoSofian.png
        img/alarme.png
        SOURCES serveur.h serveur.cpp

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appConsdeau PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appConsdeau
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appConsdeau
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Sql
    PRIVATE Qt6::Charts
    PRIVATE Qt6::WebSockets
)

include(GNUInstallDirs)
install(TARGETS appConsdeau
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
