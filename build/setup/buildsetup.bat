@echo off
pushd %~dp0

set QT5DEST=%~dp0\packages\org.kingnak.dayplanner.qt5\data

IF "%QtIFW%" == "" (
	set IFW=D:\Qt\QtIFW2.0.5
) ELSE (
	set IFW=%QtIFW%
)

IF NOT EXIST "%IFW%\bin\binarycreator.exe" (
	echo QtIFW is not set correctly
	GOTO :Exit
)

IF EXIST "DayPlanner Setup.exe" del /F /Q "DayPlanner Setup.exe"
"%IFW%\bin\binarycreator.exe" -f -c config\config.xml -p packages "DayPlanner Setup.exe"

:Exit
popd
