@echo off
pushd %~dp0

set QT5DEST=%~dp0\packages\org.kingnak.dayplanner.qt5\data

IF "%Qt5Dir64%" == "" (
	set QT5SRC=D:\Qt\Qt.8.0_x64\5.7\msvc2015_64
) ELSE (
	set QT5SRC=%Qt5Dir64%
)

IF NOT EXIST "%QT5SRC%\bin\Qt5Core.dll" (
	echo Qt5Src is not set correctly
	GOTO :Exit
)

rmdir /S /Q "%QT5DEST%"

mkdir "%QT5DEST%"
copy /Y "%QT5SRC%\bin\D3Dcompiler_47.dll" "%QT5DEST%"
copy /Y "%QT5SRC%\bin\libEGL.dll" "%QT5DEST%"
copy /Y "%QT5SRC%\bin\libGLESV2.dll" "%QT5DEST%"
copy /Y "%QT5SRC%\bin\opengl32sw.dll" "%QT5DEST%"
copy /Y "%QT5SRC%\bin\Qt5Core.dll" "%QT5DEST%"
copy /Y "%QT5SRC%\bin\Qt5Gui.dll" "%QT5DEST%"
copy /Y "%QT5SRC%\bin\Qt5Network.dll" "%QT5DEST%"
copy /Y "%QT5SRC%\bin\Qt5Qml.dll" "%QT5DEST%"
copy /Y "%QT5SRC%\bin\Qt5Quick.dll" "%QT5DEST%"
copy /Y "%QT5SRC%\bin\Qt5QuickControls2.dll" "%QT5DEST%"
copy /Y "%QT5SRC%\bin\Qt5QuickTemplates2.dll" "%QT5DEST%"
copy /Y "%QT5SRC%\bin\Qt5Sql.dll" "%QT5DEST%"
copy /Y "%QT5SRC%\bin\Qt5Widgets.dll" "%QT5DEST%"

mkdir "%QT5DEST%\sqldrivers"
copy /Y "%QT5SRC%\plugins\sqldrivers\qsqlite.dll" "%QT5DEST%\sqldrivers"

mkdir "%QT5DEST%\platforms"
copy /Y "%QT5SRC%\plugins\platforms\qwindows.dll" "%QT5DEST%\platforms"

mkdir "%QT5DEST%\QtQuick"
xcopy /E /C /Y /I /Q "%QT5SRC%\qml\QtQuick\Controls" "%QT5DEST%\QtQuick\Controls"
xcopy /E /C /Y /I /Q "%QT5SRC%\qml\QtQuick\Controls.2" "%QT5DEST%\QtQuick\Controls.2"
xcopy /E /C /Y /I /Q "%QT5SRC%\qml\QtQuick\Layouts" "%QT5DEST%\QtQuick\Layouts"
xcopy /E /C /Y /I /Q "%QT5SRC%\qml\QtQuick\Templates.2" "%QT5DEST%\QtQuick\Templates.2"
xcopy /E /C /Y /I /Q "%QT5SRC%\qml\QtQuick\Window.2" "%QT5DEST%\QtQuick\Window.2"
xcopy /E /C /Y /I /Q "%QT5SRC%\qml\QtQuick\Dialogs" "%QT5DEST%\QtQuick\Dialogs"

mkdir "%QT5DEST%\QtQuick.2"
copy /Y "%QT5SRC%\qml\QtQuick.2\plugins.qmltypes" "%QT5DEST%\QtQuick.2\"
copy /Y "%QT5SRC%\qml\QtQuick.2\qmldir" "%QT5DEST%\QtQuick.2\"
copy /Y "%QT5SRC%\qml\QtQuick.2\qtquick2plugin.dll" "%QT5DEST%\QtQuick.2\"

xcopy /E /C /Y /I /Q "%QT5SRC%\qml\QtGraphicalEffects" "%QT5DEST%\QtGraphicalEffects"

:Exit
popd

