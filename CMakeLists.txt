cmake_minimum_required(VERSION 4.1)
project(oop_26Kpi)

set(CMAKE_CXX_STANDARD 20)
if (MSVC)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()


add_executable(lab1 WIN32
        lab1/MyProg.cpp
        lab1/module1.h
        lab1/module2.h
        lab1/utils.h
   )

add_executable(lab2 WIN32
        lab2/main.cpp
        lab2/resource.h
        lab2/shapeObjEditor.cpp
        lab2/shapeObjEditor.h
        lab2/editor/editor.h
        lab2/editor/shapeEditor.cpp
        lab2/editor/shapeEditor.h
        lab2/editor/shape/shape.h
        lab2/editor/shape/pointShape.h
        lab2/editor/shape/lineShape.h
        lab2/editor/shape/rectShape.h
        lab2/editor/shape/ellipseShape.h
        lab2/editor/pointEditor.h
        lab2/editor/lineEditor.h
        lab2/editor/rectEditor.h
        lab2/editor/ellipseEditor.h
)

add_executable(lab3 WIN32
        lab3/main.cpp
        lab3/main.h
        lab3/resource.h
        lab3/toolbar.h
        lab3/shapeObjEditor.cpp
        lab3/shapeObjEditor.h
        lab3/editor/editor.h
        lab3/editor/shapeEditor.h
        lab3/editor/shape/shape.h
        lab3/editor/shape/pointShape.h
        lab3/editor/shape/lineShape.h
        lab3/editor/shape/rectShape.h
        lab3/editor/shape/ellipseShape.h
        lab3/editor/pointEditor.h
        lab3/editor/lineEditor.h
        lab3/editor/rectEditor.h
        lab3/editor/ellipseEditor.h
)
target_link_libraries(lab3 PRIVATE comctl32)

add_executable(lab4 WIN32
        lab4/main.cpp
        lab4/main.h
        lab4/resource.h
        lab4/toolbar.h
        lab4/myEditor.h
        lab4/shapeObjEditor.cpp
        lab4/shapeObjEditor.h
        lab4/editor/editor.h
        lab4/editor/shapeEditor.h
        lab4/editor/shape/shape.h
        lab4/editor/shape/pointShape.h
        lab4/editor/shape/lineShape.h
        lab4/editor/shape/rectShape.h
        lab4/editor/shape/ellipseShape.h
        lab4/editor/shape/lineWithCirclesShape.h
        lab4/editor/shape/cubeShape.h
        lab4/editor/pointEditor.h
        lab4/editor/lineEditor.h
        lab4/editor/rectEditor.h
        lab4/editor/ellipseEditor.h
        lab4/editor/lineWithCirclesEditor.h
        lab4/editor/cubeEditor.h
)
target_link_libraries(lab4 PRIVATE comctl32)