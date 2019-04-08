#include "RainMakerPlugin.hpp"          // corresponding header file
#include <time.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "jsonxx.h"


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

void RainMakerPlugin::LoadConf()
{
	using namespace jsonxx;

	std::ifstream iFile(mRainMakerDataFile);
	std::string strJSON((std::istreambuf_iterator<char>(iFile)), std::istreambuf_iterator<char>());
	iFile.close();
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
