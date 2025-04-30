cmake_minimum_required(VERSION 3.14)
project(QuizApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

# Add source files
set(SOURCES
    User.cpp
    Admin.cpp
    Player.cpp
    Question.cpp
    Quiz.cpp
    Score.cpp
    DataManager.cpp
    MainWindow.cpp
    LoginPage.cpp
    RegistrationPage.cpp
    AdminDashboard.cpp
    PlayerDashboard.cpp
    QuizTakingPage.cpp
    main.cpp
)

# Add header files
set(HEADERS
    User.h
    Admin.h
    Player.h
    Question.h
    Quiz.h
    Score.h
    DataManager.h
    MainWindow.h
    LoginPage.h
    RegistrationPage.h
    AdminDashboard.h
    PlayerDashboard.h
    QuizTakingPage.h
)

# Add UI files
set(UI_FILES
    MainWindow.ui
    LoginPage.ui
    RegistrationPage.ui
    AdminDashboard.ui
    PlayerDashboard.ui
    QuizTakingPage.ui
)

# Add resource files
set(RESOURCES
    resources.qrc
)

# Create executable
add_executable(QuizApp ${SOURCES} ${HEADERS} ${UI_FILES} ${RESOURCES})

# Link Qt libraries
target_link_libraries(QuizApp PRIVATE
    Qt6::Core
    Qt6::Widgets
)

# Include directories
target_include_directories(QuizApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Create data directory if it doesn't exist
add_custom_command(TARGET QuizApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/data
) 