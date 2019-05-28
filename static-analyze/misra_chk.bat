@echo off

FOR /F %%i in ('wsl wslpath -u '%1'') do set WSL_PATH_CPP_CHECK=%%i
FOR /F %%i in ('wsl wslpath -u '%2'') do set WSL_PATH_SOURCE=%%i

@echo on
wsl %WSL_PATH_CPP_CHECK%/Cppcheck/cppcheck --dump %WSL_PATH_SOURCE%

python %1\Cppcheck\addons\misra.py --rule-texts=%1\misra2012-rule.txt %2.dump

del %2.dump


