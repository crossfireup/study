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

@echo delete old driver
@devcon remove Root\HookSSDT

@echo install driver
@pushd "%driver_dest_dir%"
devcon -r install HookSSDT.inf Root\HookSSDT
@popd

@if errorlevel 0 goto ok

:err 
@echo "install failed!"
@exit /B 1

:ok
@echo "install finished!"
@exit /B 0

@endlocal