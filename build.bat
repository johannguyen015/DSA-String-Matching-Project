@echo off
cd /d "%~dp0"

echo ==========================================
echo                DSA BUILDER 
echo ==========================================

:: 1. Create bin if it does not exist
if not exist bin mkdir bin

:: 2. Biên dịch
echo Dang bien dich...
g++ -std=c++17 -I include source/*.cpp source/Algo/*.cpp -o bin/main.exe

:: 3. Kiểm tra lỗi
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Bien dich THAT BAI!
    echo Vui long cuon chuot len tren de xem loi chi tiet cua g++.
    echo ------------------------------------------
    pause
    exit /b 1
)

echo.
echo [OK] Bien dich THANH CONG!
echo ------------------------------------------

:: 4. Chạy thử
if "%~1"=="" (
    bin\main.exe -i data/puzzle.txt -a ac -o data/solution.txt
) else (
    bin\main.exe %*
)
echo.
pause