Сборка калькулятора:
********************

-перейти в диркторию calculator_src
-создать директорию build, перейти в нее
-выполнить команды:
 cmake ..
 make


Запуск калькулятора: 
********************
./calculator


Сборка тестов:
**************

-перейти в директорию test_src
-выполнить команды:
 
 cxxtestgen --error-print -o runner.cpp calculator_test.h
 g++ -o runner -I<путь к директории с cxxtest> -I../calculator_src/include/ runner.cpp ../calculator_src/sources/calculator.cpp

Запуск тестов:
**************
./runner



P.S.
для тестов использовал CxxTest, не успел оформить сборку и запуск тестов через
CMake, сейчас тесты собираются вручную.

