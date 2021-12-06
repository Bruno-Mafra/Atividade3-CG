project(greenredlight)
add_executable(${PROJECT_NAME} camera.cpp main.cpp openglwindow.cpp boneca.cpp listra.cpp
                    ground.cpp paredes.cpp soldado.cpp tronco.cpp listra.cpp bonecos.cpp folhas.cpp)
enable_abcg(${PROJECT_NAME})
