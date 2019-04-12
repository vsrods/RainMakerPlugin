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
	mEnvironmentSet = false;
}

RainMakerPlugin::~RainMakerPlugin()
{
}

void RainMakerPlugin::SetEnvironment(const EnvironmentInfoV01 &info)
{
	WriteToLogFile( "INFO", "-SET ENVIRONMENT-");
	if (mEnvironmentSet) return;
	mEnvironmentSet = true;

	//char buftime[128], bufdate[128];
	//_strtime_s(buftime, 128);
	//_strdate_s(bufdate, 128);

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

void RainMakerPlugin::WriteToLogFile( const char* const type, const char * const msg )
{
  _strtime_s(buftime, 128);
  _strdate_s(bufdate, 128);

  FILE* fo = fopen(mRainMakerLogFile.c_str(), "a" );
  if( fo )
  {
	//fprintf(fo, "%s : %s\n", type, msg);
    fprintf( fo, "%s %s - %s : %s\n", bufdate, buftime, type, msg );
    fclose( fo );
  }

}

void RainMakerPlugin::LoadJsonConf()
{
	//WriteToLogFile("INFO", mRainMakerDataFile.c_str());
	std::istringstream ss(mRainMakerDataFile.c_str());
	//std::ifstream ss(mRainMakerDataFile, ifstream::in);
	//ss << mRainMakerDataFile;
	/**/
	WriteToLogFile( "INFO", "loading JSON file...");
	boost::property_tree::ptree pt;
	try {
		boost::property_tree::read_json(ss, pt);
	}
	catch (std::exception &e)
	{
		WriteToLogFile( "ERROR", "Error loading JSON file");
	}
	
	mStartMode = pt.get<std::string>("StartMode");
	mApplyCloudinessInstantly = pt.get<bool>("ApplyCloudinessInstantly");
	mLoopWrFileReading = pt.get<bool>("LoopWrFileReading");
	mOnceSessionWrFile = pt.get<std::string>("OnceSessionWrFile");
	mOnceSessionSession = pt.get<std::string>("OnceSessionSession");
	mEverySessionPracticeWrFile = pt.get<std::string>("EverySessionPracticeWrFile");
	mEverySessionQualiWrFile = pt.get<std::string>("EverySessionQualiWrFile");
	mEverySessionRaceWrFile = pt.get<std::string>("EverySessionRaceWrFile");
	mTimeSessionWrFile = pt.get<std::string>("TimeSessionWrFile");
	mTimeSessionStartTime = pt.get<int>("TimeSessionStartTime");

	if (mApplyCloudinessInstantly )
	{
		WriteToLogFile("INFO", "mApplyCloudinessInstantly is ON");
	}
	if (mLoopWrFileReading)
	{
		WriteToLogFile("INFO", "mLoopWrFileReading is ON");
	}
}

void RainMakerPlugin::Startup( long version )
{
  WriteToLogFile( "INFO", "-STARTUP-" );

}


void RainMakerPlugin::Shutdown()
{
  WriteToLogFile( "INFO", "-SHUTDOWN-" );
}


void RainMakerPlugin::StartSession()
{
  WriteToLogFile( "INFO", "--STARTSESSION--" );
  LoadJsonConf();
}


void RainMakerPlugin::EndSession()
{
  WriteToLogFile( "INFO", "--ENDSESSION--" );
}


void RainMakerPlugin::EnterRealtime()
{
  // start up timer every time we enter realtime
  WriteToLogFile( "INFO", "---ENTERREALTIME---" );
}


void RainMakerPlugin::ExitRealtime()
{
  WriteToLogFile( "INFO", "---EXITREALTIME---" );
}



void RainMakerPlugin::UpdateScoring( const ScoringInfoV01 &info )
{
	//WriteToLogFile( "INFO", mRainMakerData.StartMode.c_str());
	//WriteToLogFile("INFO", "---UPDATESCORING---");
}
