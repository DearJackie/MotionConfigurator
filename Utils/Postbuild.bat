
@ECHO OFF

CD ..
IF EXIST "Release" GOTO _CREATE_RELEASE
IF EXIST "Debug" GOTO _CREATE_DEBUG
GOTO _ERROR

:_CREATE_RELEASE
COPY MotionConfigurator\Galil\dll\x86\gclib.dll Release\
COPY MotionConfigurator\Galil\dll\x86\gclibo.dll Release\
GOTO _SUCCESS

:_CREATE_DEBUG
COPY MotionConfigurator\Galil\dll\x86\gclib.dll Debug\
COPY MotionConfigurator\Galil\dll\x86\gclibo.dll Debug\
GOTO _SUCCESS

:_ERROR
@ECHO post build failed!
GOTO _END

:_SUCCESS
@ECHO post build success!
GOTO _END

:_END
REM PAUSE