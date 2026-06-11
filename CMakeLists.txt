cmake_minimum_required(VERSION 3.12)
project(MyProjectName)
set(CMAKE_CXX_STANDARD 20)  # Устанавливаем C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Заставляем CMake выдать ошибку, если компилятор не поддерживает выбранный стандарт
set(CMAKE_CXX_EXTENSIONS OFF)  # Отключаем расширения компилятора для повышения переносимости


# Добавьте источник в исполняемый файл этого проекта.

set(PostgreSQL_ADDITIONAL_VERSIONS "17")

add_subdirectory(D:/libpq/libpqxx-8.0.1 build-pqxx)

add_executable(MyProjectName main.cpp Clients.h Clients.cpp)

# Линкуемся к только что собранной цели 'pqxx'
target_link_libraries(MyProjectName PRIVATE pqxx)
