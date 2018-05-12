@echo off
:: Load compilation environment
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
e:
cd \GitHub\WordCountAutoTest\downloads\15061183\WordCount
echo 23333
:: Invoke compiler with any options passed to this batch file
::"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.11.25503\bin\HostX86\x86\cl.exe" /EHsc %*
::cl.exe /EHsc %* /Fewc.exe
::cl.exe /EHsc 1.cpp /Fewc.exe
"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.11.25503\bin\HostX86\x86\cl.exe" /EHsc %* /Fewc.exe
echo END
