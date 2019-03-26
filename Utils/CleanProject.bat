@ECHO OFF

CD ..
IF EXIST "Release" RD Release  /Q /S
IF EXIST "Debug" RD Debug  /Q /S
IF EXIST ipch RD ipch  /Q /S
IF EXIST *.sdf DEL *.sdf  /Q /S
IF EXIST MotionConfigurator\Release RD MotionConfigurator\Release /Q /S
IF EXIST MotionConfigurator\Debug RD MotionConfigurator\Debug /Q /S
IF EXIST MotionConfigurator\Log.log DEL MotionConfigurator\Log.log /Q /S


REM PAUSE