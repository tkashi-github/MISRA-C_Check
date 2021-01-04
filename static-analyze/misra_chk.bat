@echo on

%1\CppCheck\cppcheck.exe --dump %2


python %1\CppCheck\addons\misra.py --rule-texts=%1\misra2012-rule.txt %2.dump

del %2.dump


