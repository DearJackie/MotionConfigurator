
@ECHO OFF

CD ..
IF EXIST "Release" GOTO _CREATE_RELEASE
IF EXIST "Debug" GOTO _CREATE_DEBUG
GOTO _ERROR

:_CREATE_RELEASE
COPY MotionConfigurator\Galil\dll\x86\gclib.dll Release\
COPY MotionConfigurator\Galil\dll\x86\gclibo.dll Release\
IF NOT EXIST MotionConfiguratorRelease MD MotionConfiguratorRelease
COPY MotionConfigurator\DLLs\*.dll  MotionConfiguratorRelease\
COPY Release\*.dll   MotionConfiguratorRelease\
COPY Release\*.exe   MotionConfiguratorRelease\
GOTO _SUCCESS

:_CREATE_DEBUG
COPY MotionConfigurator\Galil\dll\x86\gclib.dll Debug\
COPY MotionConfigurator\Galil\dll\x86\gclibo.dll Debug\
IF NOT EXIST MotionConfiguratorDebug MD MotionConfiguratorDebug
COPY MotionConfigurator\DLLs\*.dll  MotionConfiguratorDebug\
COPY Debug\*.dll   MotionConfiguratorDebug\
COPY Debug\*.exe   MotionConfiguratorDebug\
GOTO _SUCCESS

:_ERROR
@ECHO "No build files found!"
GOTO _END

:_SUCCESS
@ECHO Package Created Successfully
GOTO _END

:_END
REM PAUSE