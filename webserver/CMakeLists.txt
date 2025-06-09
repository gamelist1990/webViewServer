# CMakeList.txt : webserver の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_executable (webserver "webserver.cpp" "webserver.h" "lib/console.h" )


file(GLOB_RECURSE PAGES_RESOURCES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "pages/*")




CMRC_ADD_RESOURCE_LIBRARY(
    mypages
    WHENCE "pages"
    ${PAGES_RESOURCES}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET webserver PROPERTY CXX_STANDARD 20)
endif()



include(FetchContent)

FetchContent_Declare(
    webview
    GIT_REPOSITORY https://github.com/webview/webview
    GIT_TAG 0.12.0
)
FetchContent_MakeAvailable(webview)

target_link_libraries(webserver PRIVATE webview::core mypages)
target_include_directories(webserver PRIVATE ${CMAKE_SOURCE_DIR}/external/cmrc/include)


# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。
