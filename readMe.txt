������ ������������:
********************

-������� � ��������� calculator_src
-������� ���������� build, ������� � ���
-��������� �������:
 cmake ..
 make


������ ������������: 
********************
./calculator


������ ������:
**************

-������� � ���������� test_src
-��������� �������:
 
 cxxtestgen --error-print -o runner.cpp calculator_test.h
 g++ -o runner -I<���� � ���������� � cxxtest> -I../calculator_src/include/ runner.cpp ../calculator_src/sources/calculator.cpp

������ ������:
**************
./runner



P.S.
��� ������ ����������� CxxTest, �� ����� �������� ������ � ������ ������ �����
CMake, ������ ����� ���������� �������.

