cmake_minimum_required(VERSION 3.10)

# Set toolchain only if it's not already provided (e.g., by CI/CD)
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(EXISTS "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    elseif(EXISTS "$ENV{HOME}/Berita/cpp_env/vcpkg/scripts/buildsystems/vcpkg.cmake")
        set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/Berita/cpp_env/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    elseif(EXISTS "$ENV{HOME}/code/cpp_env/vcpkg/scripts/buildsystems/vcpkg.cmake")
        set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/code/cpp_env/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    endif()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(demon_host VERSION 1.0)

set(SOURCES 
    main.cpp

    src/utility/src/env.cpp

)

add_executable(main ${SOURCES})

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/utility/include)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/core/include)

set(ENV "./../.env")

target_compile_definitions(main PUBLIC ENV_PATH="${ENV}")

find_package(boost_asio REQUIRED CONFIG)
target_include_directories(main PUBLIC ${boost_asio_INCLUDE_DIR})
target_link_libraries(main PUBLIC ${boost_asio_LIBRARIES} ${boost_asio_DEPENDENCIES})

find_package(boost_beast REQUIRED CONFIG)
target_include_directories(main PUBLIC ${boost_beast_INCLUDE_DIR})
target_link_libraries(main PUBLIC ${boost_beast_LIBRARIES} ${boost_beast_DEPENDENCIES})

find_package(boost_coroutine REQUIRED CONFIG)
target_link_libraries(main PUBLIC Boost::coroutine)

find_package(Boost_url REQUIRED CONFIG)
target_link_libraries(main PUBLIC Boost::url)

find_package(nlohmann_json REQUIRED)
target_include_directories(main PUBLIC ${nlohmann_json_INCLUDE_DIR})
target_link_libraries(main PUBLIC ${nlohmann_json_LIBRARIES} ${nlohmann_json_DEPENDENCIES})

find_package(OpenSSL REQUIRED)
target_include_directories(main PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(main PRIVATE ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY})

find_package(CURL REQUIRED)
target_link_libraries(main PRIVATE CURL::libcurl)

if(DEFINED ENV{VCPKG_ROOT})
    # Use the triplet CMake is building with
    set(_triplet ${VCPKG_TARGET_TRIPLET})
    if(NOT _triplet)
        set(_triplet "x64-linux") # fallback for GitHub Actions
    endif()

    target_include_directories(main PUBLIC
        $ENV{VCPKG_ROOT}/installed/${_triplet}/include
    )
endif()


# as part of packages to installed, install 

# install "pkg-config" with the system package manager

# install "autoconf"