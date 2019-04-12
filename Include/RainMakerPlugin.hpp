#ifndef _RAINMAKER_H
#define _RAINMAKER_H

#include "InternalsPlugin.hpp"
#include <set>
#include <map>
#include <vector>
#include <list>
#include <string>
#include <boost/config/compiler/visualc.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

// This is used for the app to use the plugin for its intended purpose
class RainMakerPlugin : public InternalsPluginV07  // REMINDER: exported function GetPluginVersion() should return 1 if you are deriving from this InternalsPluginV01, 2 for InternalsPluginV02, etc.
{
	protected:
		// logging
		bool mLogging;                        // whether we want logging enabled
		char* mLogPath;                       // path to write logs to
		FILE* mLogFile;                       // the file pointer

		std::string mStartMode;
		bool mApplyCloudinessInstantly;
		bool mLoopWrFileReading;
		std::string mOnceSessionWrFile;
		std::string	mOnceSessionSession;
		std::string mEverySessionPracticeWrFile;
		std::string mEverySessionQualiWrFile;
		std::string mEverySessionRaceWrFile;
		std::string mTimeSessionWrFile;
		int mTimeSessionStartTime;	

	public:
	  // Constructor/destructor
	  RainMakerPlugin();
	  ~RainMakerPlugin();

	  // These are the functions derived from base class InternalsPlugin
	  // that can be implemented.
	  void Startup( long version );  // game startup
	  void SetEnvironment(const EnvironmentInfoV01& info);
	  void Shutdown();               // game shutdown

	  void EnterRealtime();          // entering realtime
	  void ExitRealtime();           // exiting realtime

	  void StartSession();           // session has started
	  void EndSession();             // session has ended

	  // GAME OUTPUT
	  long WantsTelemetryUpdates() { return( 0 ); } // CHANGE TO 1 TO ENABLE TELEMETRY EXAMPLE!
	  bool WantsGraphicsUpdates() { return( false ); } // CHANGE TO TRUE TO ENABLE GRAPHICS EXAMPLE!

	  // SCORING OUTPUT
	  bool WantsScoringUpdates() { return( true ); } // CHANGE TO TRUE TO ENABLE SCORING EXAMPLE!
	  void UpdateScoring( const ScoringInfoV01 &info );

 private:
	 bool mEnvironmentSet;
	 std::string mRainMakerDataFile;
	 std::string mRainMakerLogFile;

	 char buftime[128], bufdate[128];

	 void WriteToLogFile(const char* const type, const char* const msg);
	 void LoadJsonConf();
};
#endif

