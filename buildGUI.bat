call cd GUI

call ant clean
call ant

call cd ..

call xcopy scripts Release\scripts /Y /s /i
call xcopy scripts Debug\scripts /Y /s /i

call xcopy data Release\data /Y /s /i
call xcopy data Debug\data /Y /s /i