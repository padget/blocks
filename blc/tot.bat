call "%DOMAIN_HOME%\bin\setCheckoutEnv.cmd"

set CKO_LOGS_FOLDER=%DOMAIN_HOME%\logs
set CKO_DOMAIN_HOME=%CHECKOUT_PATH%\cinkeo-resources\target\externe
set CKO_PROPERTIES=%CKO_DOMAIN_HOME%\resources

set CKO_CONFIG=-DDOMAIN_HOME=%CKO_DOMAIN_HOME% -Dfile.encoding=utf8
set CKO_LOG_BACK=-Dlogback.ContextSelector=JNDI -DINSTANCE_LOG_DIR=%CKO_LOGS_FOLDER% -DLOGS_FOLDER=%CKO_LOGS_FOLDER%
set CKO_NESSIE=-DinstanceName=%SERVER_NAME% -Ddomain.home=%CKO_PROPERTIES%

if NOT "%JAVA_OPTIONS%"=="" (
    set JAVA_OPTIONS=%JAVA_OPTIONS% %CKO_CONFIG% %CKO_LOG_BACK% %CKO_NESSIE%
) else (
    set JAVA_OPTIONS=%CKO_CONFIG% %CKO_LOG_BACK% %CKO_NESSIE%
)

if NOT "%EXT_POST_CLASSPATH%"=="" (
    set EXT_POST_CLASSPATH=%EXT_POST_CLASSPATH%;%CKO_PROPERTIES%
) else (
    set EXT_POST_CLASSPATH=%CKO_PROPERTIES%
)

@REM Fin Personnalisation Cinke-O

set WL_HOME=C:\bea\wlserver_10.3
for %%i in ("%WL_HOME%") do set WL_HOME=%%~fsi

set BEA_JAVA_HOME=C:\Users\hselle\Downloads\Logiciels\java7\jre

set SUN_JAVA_HOME=

if "%JAVA_VENDOR%"=="Oracle" (
    set JAVA_HOME=C:\Users\hselle\Downloads\Logiciels\java7\jre
) else (
    if "%JAVA_VENDOR%"=="Sun" (
        set JAVA_HOME=C:\Users\hselle\Downloads\Logiciels\java7\jre
    ) else (
        set JAVA_VENDOR=Unknown
        set JAVA_HOME=C:\Users\hselle\Downloads\Logiciels\java7\jre
    )
)

@REM We need to reset the value of JAVA_HOME to get it shortened AND
@REM we can not shorten it above because immediate variable expansion will blank it

set JAVA_HOME=%JAVA_HOME%
for %%i in ("%JAVA_HOME%") do set JAVA_HOME=%%~fsi

set SAMPLES_HOME=%WL_HOME%\samples

set DOMAIN_HOME=C:\bea\WLS_CINKEO
for %%i in ("%DOMAIN_HOME%") do set DOMAIN_HOME=%%~fsi

set LONG_DOMAIN_HOME=C:\bea\WLS_CINKEO

if "%DEBUG_PORT%"=="" (
    set DEBUG_PORT=8453
)

if "%SERVER_NAME%"=="" (
    set SERVER_NAME=AdminServer
)

set DERBY_FLAG=

set enableHotswapFlag=

set PRODUCTION_MODE=

set doExitFlag=false
set verboseLoggingFlag=false
for %%p in (%*) do call :SET_PARAM %%p
GOTO :CMD_LINE_DONE
    :SET_PARAM
    for %%q in (%1) do set noQuotesParam=%%~q
    if /i "%noQuotesParam%" == "nodebug" (
        set debugFlag=false
        GOTO :EOF
    )
    if /i "%noQuotesParam%" == "production" (
        set DOMAIN_PRODUCTION_MODE=true
        GOTO :EOF
    )
    if /i "%noQuotesParam%" == "notestconsole" (
        set testConsoleFlag=false
        GOTO :EOF
    )
    if /i "%noQuotesParam%" == "noiterativedev" (
        set iterativeDevFlag=false
        GOTO :EOF
    )
    if /i "%noQuotesParam%" == "noLogErrorsToConsole" (
        set logErrorsToConsoleFlag=false
        GOTO :EOF
    )
    if /i "%noQuotesParam%" == "noderby" (
        set DERBY_FLAG=false
        GOTO :EOF
    )
    if /i "%noQuotesParam%" == "doExit" (
        set doExitFlag=true
        GOTO :EOF
    )
    if /i "%noQuotesParam%" == "noExit" (
        set doExitFlag=false
        GOTO :EOF
    )
    if /i "%noQuotesParam%" == "verbose" (
        set verboseLoggingFlag=true
        GOTO :EOF
    )
    if /i "%noQuotesParam%" == "enableHotswap" (
        set enableHotswapFlag=-javaagent:%WL_HOME%\server\lib\diagnostics-agent.jar
        GOTO :EOF
    ) else (
        set PROXY_SETTINGS=%PROXY_SETTINGS% %1
    )
    GOTO :EOF
:CMD_LINE_DONE


set MEM_DEV_ARGS=

if "%DOMAIN_PRODUCTION_MODE%"=="true" (
    set PRODUCTION_MODE=%DOMAIN_PRODUCTION_MODE%
)

if "%PRODUCTION_MODE%"=="true" (
    set debugFlag=false
    set testConsoleFlag=false
    set iterativeDevFlag=false
    set logErrorsToConsoleFlag=false
)

@REM If you want to override the default Patch Classpath, Library Path and Path for this domain,
@REM Please uncomment the following lines and add a valid value for the environment variables
@REM set PATCH_CLASSPATH=[myPatchClasspath] (windows)
@REM set PATCH_LIBPATH=[myPatchLibpath] (windows)
@REM set PATCH_PATH=[myPatchPath] (windows)
@REM PATCH_CLASSPATH=[myPatchClasspath] (unix)
@REM PATCH_LIBPATH=[myPatchLibpath] (unix)
@REM PATCH_PATH=[myPatchPath] (unix)

call "%WL_HOME%\common\bin\commEnv.cmd"

set WLS_HOME=%WL_HOME%\server

if "%JAVA_VENDOR%"=="Oracle" (
    set WLS_MEM_ARGS_64BIT=-Xms1024m -Xmx2048m
    set WLS_MEM_ARGS_32BIT=-Xms1024m -Xmx2048m
) else (
    set WLS_MEM_ARGS_64BIT=-Xms1024m -Xmx2048m
    set WLS_MEM_ARGS_32BIT=-Xms1024m -Xmx2048m
)

set MEM_ARGS_64BIT=%WLS_MEM_ARGS_64BIT%

set MEM_ARGS_32BIT=%WLS_MEM_ARGS_32BIT%

if "%JAVA_USE_64BIT%"=="true" (
    set MEM_ARGS=%MEM_ARGS_64BIT%
) else (
    set MEM_ARGS=%MEM_ARGS_32BIT%
)

set MEM_PERM_SIZE_64BIT=-XX:PermSize=2048m

set MEM_PERM_SIZE_32BIT=-XX:PermSize=2048m

if "%JAVA_USE_64BIT%"=="true" (
    set MEM_PERM_SIZE=%MEM_PERM_SIZE_64BIT%
) else (
    set MEM_PERM_SIZE=%MEM_PERM_SIZE_32BIT%
)

set MEM_MAX_PERM_SIZE_64BIT=-XX:MaxPermSize=2048m

set MEM_MAX_PERM_SIZE_32BIT=-XX:MaxPermSize=2048m

if "%JAVA_USE_64BIT%"=="true" (
    set MEM_MAX_PERM_SIZE=%MEM_MAX_PERM_SIZE_64BIT%
) else (
    set MEM_MAX_PERM_SIZE=%MEM_MAX_PERM_SIZE_32BIT%
)

if "%JAVA_VENDOR%"=="Oracle" (
    if "%PRODUCTION_MODE%"=="" (
        set MEM_DEV_ARGS=-XX:CompileThreshold=8000 %MEM_PERM_SIZE%
    )
)

@REM Had to have a separate test here BECAUSE of immediate variable expansion on windows

if "%JAVA_VENDOR%"=="Oracle" (
    set MEM_ARGS=%MEM_ARGS% %MEM_DEV_ARGS% %MEM_MAX_PERM_SIZE%
)

if "%JAVA_VENDOR%"=="HP" (
    set MEM_ARGS=%MEM_ARGS% %MEM_MAX_PERM_SIZE%
)

if "%JAVA_VENDOR%"=="Apple" (
    set MEM_ARGS=%MEM_ARGS% %MEM_MAX_PERM_SIZE%
)

@REM IF USER_MEM_ARGS the environment variable is set, use it to override ALL MEM_ARGS values

if NOT "%USER_MEM_ARGS%"=="" (
    set MEM_ARGS=%USER_MEM_ARGS%
)

set JAVA_PROPERTIES=-Dplatform.home=%WL_HOME% -Dwls.home=%WLS_HOME% -Dweblogic.home=%WLS_HOME%
