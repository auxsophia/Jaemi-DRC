# Microsoft Developer Studio Project File - Name="khr3win" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=khr3win - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "khr3win.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "khr3win.mak" CFG="khr3win - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "khr3win - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "khr3win - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "khr3win - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 rtapi_w32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "khr3win - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 rtapi_w32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "khr3win - Win32 Release"
# Name "khr3win - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Board.cpp
# End Source File
# Begin Source File

SOURCE=.\CANwin.cpp
# End Source File
# Begin Source File

SOURCE=.\CommThread.cpp
# End Source File
# Begin Source File

SOURCE=.\EncReadDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FT_ReadDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GainSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Gesture.cpp
# End Source File
# Begin Source File

SOURCE=.\khr3win.cpp
# End Source File
# Begin Source File

SOURCE=.\khr3win.rc
# End Source File
# Begin Source File

SOURCE=.\khr3winDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\KirkWalking2.cpp
# End Source File
# Begin Source File

SOURCE=.\MotorState.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenLoopTestDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ParameterSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\PositionControl.cpp
# End Source File
# Begin Source File

SOURCE=.\ProfileGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TiltReadDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UtilityWin.cpp
# End Source File
# Begin Source File

SOURCE=.\Walk00TestDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WalkingExpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Z_PhaseEncoderViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Z_PhaseSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ZMPZeroDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Board.h
# End Source File
# Begin Source File

SOURCE=.\CANwin.h
# End Source File
# Begin Source File

SOURCE=..\CommonDefinition.h
# End Source File
# Begin Source File

SOURCE=.\CommThread.h
# End Source File
# Begin Source File

SOURCE=.\Define.h
# End Source File
# Begin Source File

SOURCE=.\EncReadDlg.h
# End Source File
# Begin Source File

SOURCE=.\FT_ReadDlg.h
# End Source File
# Begin Source File

SOURCE=.\GainSet.h
# End Source File
# Begin Source File

SOURCE=.\Gesture.h
# End Source File
# Begin Source File

SOURCE=.\khr3win.h
# End Source File
# Begin Source File

SOURCE=.\khr3winDlg.h
# End Source File
# Begin Source File

SOURCE=.\KirkWalking2.h
# End Source File
# Begin Source File

SOURCE=.\MotorState.h
# End Source File
# Begin Source File

SOURCE=.\OpenLoopTestDlg.h
# End Source File
# Begin Source File

SOURCE=.\ParameterSetting.h
# End Source File
# Begin Source File

SOURCE=.\PositionControl.h
# End Source File
# Begin Source File

SOURCE=.\ProfileGraph.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\SharedMemory.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TiltReadDlg.h
# End Source File
# Begin Source File

SOURCE=.\UtilityWin.h
# End Source File
# Begin Source File

SOURCE=.\Walk00TestDlg.h
# End Source File
# Begin Source File

SOURCE=.\WalkingExpDlg.h
# End Source File
# Begin Source File

SOURCE=.\Z_PhaseEncoderViewDlg.h
# End Source File
# Begin Source File

SOURCE=.\Z_PhaseSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\ZMPZeroDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\khr3win.ico
# End Source File
# Begin Source File

SOURCE=.\res\khr3win.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
