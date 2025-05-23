cmake_minimum_required(VERSION 3.16)
project(P_Alse VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Permite procesar automáticamente .ui, .qrc y .moc
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Buscar Qt6 (o Qt5 si Qt6 no está disponible)
find_package(Qt6 COMPONENTS Widgets Sql PrintSupport LinguistTools REQUIRED)
# Para Qt5 descomenta la siguiente línea en caso de usar Qt5:
# find_package(Qt5 COMPONENTS Widgets Sql PrintSupport LinguistTools REQUIRED)

set(TS_FILES P_Alse_es_CO.ts)

# Lista de fuentes y headers
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    inventorytab.cpp
    inventorytab.h
    searchtab.cpp
    searchtab.h
    alertstab.cpp
    alertstab.h
    reportstab.cpp
    reportstab.h

    inventorymanager.cpp
    inventorymanager.h
    component.cpp
    component.h
    databasemanager.cpp
    databasemanager.h
    reportgenerator.cpp
    reportgenerator.h

    ${TS_FILES}
)

# Crear ejecutable Qt6
qt_add_executable(P_Alse
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# Traducciones
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

# Enlazar librerías Qt necesarias
target_link_libraries(P_Alse PRIVATE
    Qt6::Widgets
    Qt6::Sql
    Qt6::PrintSupport
)

# Propiedades para macOS / Windows
set_target_properties(P_Alse PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Instalación
include(GNUInstallDirs)
install(TARGETS P_Alse
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalizar ejecutable (solo Qt6)
if(Qt6_FOUND)
    qt_finalize_executable(P_Alse)
endif()
