//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
//›                                                                         ﬁ
//› Module: Internals Example Source File                                   ﬁ
//›                                                                         ﬁ
//› Description: Declarations for the Internals Example Plugin              ﬁ
//›                                                                         ﬁ
//›                                                                         ﬁ
//› This source code module, and all information, data, and algorithms      ﬁ
//› associated with it, are part of CUBE technology (tm).                   ﬁ
//›                 PROPRIETARY AND CONFIDENTIAL                            ﬁ
//› Copyright (c) 1996-2014 Image Space Incorporated.  All rights reserved. ﬁ
//›                                                                         ﬁ
//›                                                                         ﬁ
//› Change history:                                                         ﬁ
//›   tag.2005.11.30: created                                               ﬁ
//›                                                                         ﬁ
//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ

#include "RainMakerPlugin.hpp"          // corresponding header file
#include <time.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>


// plugin information

extern "C" __declspec(dllexport)
const char* __cdecl GetPluginName() { return("Rain Maker - 2019.04.24"); }

extern "C" __declspec(dllexport)
PluginObjectType __cdecl GetPluginType() { return(PO_INTERNALS); }

extern "C" __declspec(dllexport)
int __cdecl GetPluginVersion() { return(7); }  // InternalsPluginV07 functionality (if you change this return value, you must derive from the appropriate class!)

extern "C" __declspec(dllexport)
PluginObject* __cdecl CreatePluginObject() { return(static_cast<PluginObject*>(new RainMakerPlugin)); }

extern "C" __declspec(dllexport)
void __cdecl DestroyPluginObject(PluginObject* obj) { delete(static_cast<RainMakerPlugin*>(obj)); }

RainMakerPlugin::RainMakerPlugin() 
{
}

RainMakerPlugin::~RainMakerPlugin()
{
}

void RainMakerPlugin::SetEnvironment(const EnvironmentInfoV01 &info)
{
	if (mEnvironmentSet) return;
	mEnvironmentSet = true;

	char buftime[128], bufdate[128];
	_strtime_s(buftime, 128);
	_strdate_s(bufdate, 128);

	std::string ProfilePath;
	std::string UserdataPath;
	UserdataPath = info.mPath[0];
	ProfilePath = info.mPath[1];
	size_t posa = ProfilePath.find_last_of("/\\");
	ProfilePath = ProfilePath.substr(0, posa);
	size_t posb = UserdataPath.find_last_of("/\\");
	UserdataPath = UserdataPath.substr(0, posb);
	mRainMakerDataFile = ProfilePath;
	mRainMakerDataFile.append("\\RainMakerPlugin.json");
	mRainMakerLogFile = UserdataPath;
	mRainMakerLogFile.append("\\Log\\RainMakerPluginLog.txt");
}

void RainMakerPlugin::WriteToLogFile( const char * const openStr, const char* const type, const char * const msg )
{
  FILE *fo;
  char buftime[128], bufdate[128];

  _strtime_s(buftime, 128);
  _strdate_s(bufdate, 128);

  fo = fopen(mRainMakerLogFile.c_str(), openStr );
  if( fo != NULL )
  {
    fprintf( fo, "%s %s - %s : %s\n", bufdate, buftime, type, msg );
    fclose( fo );
  }

}


void RainMakerPlugin::Startup( long version )
{
  char temp[80];
  sprintf( temp, "-STARTUP- (version %.3f)", (float) version / 1000.0f );

  WriteToLogFile( "a", "INFO", temp );
}


void RainMakerPlugin::Shutdown()
{
  WriteToLogFile( "a", "INFO", "-SHUTDOWN-" );
}


void RainMakerPlugin::StartSession()
{
  WriteToLogFile( "a", "INFO", "--STARTSESSION--" );
}


void RainMakerPlugin::EndSession()
{
  WriteToLogFile( "a", "INFO", "--ENDSESSION--" );
}


void RainMakerPlugin::EnterRealtime()
{
  // start up timer every time we enter realtime
  WriteToLogFile( "a", "INFO", "---ENTERREALTIME---" );
}


void RainMakerPlugin::ExitRealtime()
{
  WriteToLogFile( "a", "INFO", "---EXITREALTIME---" );
}



void RainMakerPlugin::UpdateScoring( const ScoringInfoV01 &info )
{

}

bool RainMakerPlugin::GetCustomVariable(long i, CustomVariableV01 &var)
{
	WriteToLogFile("a", "INFO", "- GetCustomVariable");
	switch (i)
	{
		case 0:
		{
			// rF2 will automatically create this variable and default it to 1 (true) unless we create it first, in which case we can choose the default.
			strcpy_s(var.mCaption, " Enabled");
			var.mNumSettings = 2;
			var.mCurrentSetting = 1;
			return(true);
		}

		case 1:
		{
			strcpy_s(var.mCaption, "Logging");
			var.mNumSettings = 2;
			var.mCurrentSetting = 0;
			return(true);
		}

		case 2:
		{
			strcpy_s(var.mCaption, "StartMode");
			var.mNumSettings = 4;
			var.mCurrentSetting = 1;
			return(true);
		}
		case 3:
		{
			strcpy_s(var.mCaption, "LoopWrFileReading");
			var.mNumSettings = 2;
			var.mCurrentSetting = 0;
			return(true);
		}
		case 4:
		{
			strcpy_s(var.mCaption, "ApplyCloudinessInstantly");
			var.mNumSettings = 2;
			var.mCurrentSetting = 0;
			return(true);
		}
	
	}
	return(false);
}

void RainMakerPlugin::AccessCustomVariable(CustomVariableV01 &var)
{
	if (0 == _stricmp(var.mCaption, " Enabled"))
	{
		// Do nothing; this variable is just for rF2 to know whether to keep the plugin loaded.
	}
	else if (0 == _stricmp(var.mCaption, "Logging"))
	{
		// Set a flag whether we want logging enabled ... it may be too early to actually open the file because
		// the call SetEnvironment() may not have been called yet.
		mLogging = (var.mCurrentSetting != 0);
	}
	else if (0 == _stricmp(var.mCaption, "StartMode"))
	{
		mStartMode = var.mCurrentSetting;
	}
	else if (0 == _stricmp(var.mCaption, "LoopWrFileReading"))
	{
		mLoopWrFileReading = var.mCurrentSetting;
	}
	else if (0 == _stricmp(var.mCaption, "ApplyCloudinessInstantly"))
	{
		mLoopWrFileReading = var.mCurrentSetting;
	}
	else
	{
	}
}

void RainMakerPlugin::GetCustomVariableSetting(CustomVariableV01 &var, long i, CustomSettingV01 &setting)
{
	if (0 == _stricmp(var.mCaption, " Enabled"))
	{
		if (0 == i)
			strcpy_s(setting.mName, "False");
		else
			strcpy_s(setting.mName, "True");
	}
	else if (0 == _stricmp(var.mCaption, "Logging"))
	{
		if (0 == i)
			strcpy_s(setting.mName, "False");
		else
			strcpy_s(setting.mName, "True");
	}
	else if (0 == _stricmp(var.mCaption, "Startmode"))
	{
		switch (i)
		{
		case 0:  sprintf_s(setting.mName, "Nothing"); break; // Yes, these two are functionally equivalent, because we never
		case 1:  sprintf_s(setting.mName, "Time"); break; // even try to adjust under green.
		case 2:  sprintf_s(setting.mName, "Every Session"); break;
		case 3:  sprintf_s(setting.mName, "Once Session"); break;
		default: sprintf_s(setting.mName, "Nothing"); break; // We don't actually try to adjust during race halt currently.
		}
	}
	else if (0 == _stricmp(var.mCaption, "LoopWrFileReading"))
	{
		if (0 == i)
			strcpy_s(setting.mName, "False");
		else
			strcpy_s(setting.mName, "True");
	}
	else if (0 == _stricmp(var.mCaption, "ApplyCloudinessInstantly"))
	{
		if (0 == i)
			strcpy_s(setting.mName, "False");
		else
			strcpy_s(setting.mName, "True");
	}
}