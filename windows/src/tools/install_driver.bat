@rem insall driver 

@setlocal

@set "driver_dest_dir=C:\Users\WDKRemoteUser\Desktop\test\driverfiles"
@set "driver_src_dir=\\vmware-host\Shared Folders\Projects\HookSSDT\Win7Debug\HookSSDT Package"

@echo clean old files
@if exist "%driver_dest_dir%" (
@del /Q /S /F "%driver_dest_dir%\*.*"
) else (
@echo make directory
md "%driver_dest_dir%"
@if not errorlevel 0 goto err
)

@echo copy new files "%driver_src_dir%" -- "%driver_dest_dir%"
@if exist "%driver_src_dir%" (
@robocopy /E /IS "%driver_src_dir%" "%driver_dest_dir%"
) else (
@echo copy files error
goto err
)

@echo check driver status
@devcon hwids Root\HookSSDT | findstr "Root"
@set ret=%errorlevel%

@pushd "%driver_dest_dir%"
@if %ret% equ 0 (
@echo update driver
devcon -r update HookSSDT.inf Root\HookSSDT
) else (
@echo install driver
devcon -r install HookSSDT.inf Root\HookSSDT
)
@set ret=%errorlevel%
@popd

@endlocal

if "%ret%" gtr 1 goto ok

:err 
@echo "install failed!"
@exit /B 1

:ok
@echo "install finished!"
@exit /B 0