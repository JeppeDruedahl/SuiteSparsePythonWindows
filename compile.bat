cd "C:\SuiteSparsePythonWindows\build"
cd C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/
call vcvarsall.bat x64
cd "C:\SuiteSparsePythonWindows\build\"
call msbuild Example.sln /p:Configuration=Release