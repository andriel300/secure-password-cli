cmake_minimum_required(VERSION 3.15)

project(SecurePasswordCLI VERSION 0.1.1)

# ✅ Version suffix (change this to "", "-beta", "-rc1" or whatever you want)
set(VERSION_SUFFIX "-beta")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 🔍 OS Detection
if (WIN32)
    message(STATUS "🪟 Building for Windows")
elseif (APPLE)
    message(STATUS "🍎 Building for macOS")
elseif (UNIX)
    message(STATUS "🐧 Building for Linux")
else()
    message(STATUS "❓ Unknown system")
endif()

# 📁 Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/cJSON
)

# 📦 Source files
set(SOURCES
    src/main.c
    src/gui_globals.c
    src/gui_home.c
    src/gui_login.c
    src/gui_create_account.c
    src/gui_main_window.c
    src/gui_utils.c
    src/gui_page_vault.c
    src/gui_page_vault_events.c
    src/gui_page_generator.c
    src/gui_page_settings.c
    src/gui_footer.c
    src/generator.c
    src/crypto.c
    src/vault.c
    src/json_parser.c
    cJSON/cJSON.c
)

# 🎨 Windows Icon Resource
if (WIN32)
    set(SOURCES ${SOURCES} assets/icon-transparent-bg.rc)
endif()

# 🔧 Dependencies (GTK)
if (UNIX OR APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    include_directories(${GTK3_INCLUDE_DIRS})
    link_directories(${GTK3_LIBRARY_DIRS})
    add_definitions(${GTK3_CFLAGS_OTHER})
endif()

# 🔨 Executable
add_executable(SecurePasswordCLI ${SOURCES})

# 🔗 Linking
if (WIN32)
    target_link_libraries(SecurePasswordCLI -lgtk-3 -lssl -lcrypto m)
elseif (APPLE OR UNIX)
    target_link_libraries(SecurePasswordCLI ${GTK3_LIBRARIES} ssl crypto m)
endif()

# 📂 Installation
install(TARGETS SecurePasswordCLI DESTINATION bin)
install(DIRECTORY assets DESTINATION share/secure-password-cli)
install(FILES README.md DESTINATION share/secure-password-cli)
install(FILES LICENSE DESTINATION share/secure-password-cli)

# 🎁 Packaging with CPack
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "SecurePasswordCLI")
set(CPACK_PACKAGE_VENDOR "Andriel")
set(CPACK_PACKAGE_CONTACT "andrieldata@proton.me")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Secure Password CLI - Open-source, encrypted password manager with GTK GUI.")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}${VERSION_SUFFIX}")

# 🗂️ File Naming with suffix
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}")

# 🐧 Debian/Ubuntu
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Andriel")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgtk-3-0, libssl3")

# 🐧 RPM
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "Utility")

# Linux default
if (UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "DEB;RPM;TGZ;ZIP")
endif()

include(CPack)

