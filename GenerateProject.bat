copy "premake5\GLAD\premake5.lua" "Vantus_Engine\vendor\Glad"
copy "premake5\GLFW\premake5.lua" "Vantus_Engine\vendor\GLFW"
copy "premake5\ImGui\premake5.lua" "Vantus_Engine\vendor\imgui"
call vendor\bin\premake\premake5.exe vs2019
PAUSE