//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
//›                                                                         ﬁ
//› Module: Internals Example Header File                                   ﬁ
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

#ifndef _RAINMAKER_H
#define _RAINMAKER_H

#include "InternalsPlugin.hpp"
#include <set>
#include <map>
#include <vector>
#include <list>
#include<string>


// This is used for the app to use the plugin for its intended purpose
class RainMakerPlugin : public InternalsPluginV07  // REMINDER: exported function GetPluginVersion() should return 1 if you are deriving from this InternalsPluginV01, 2 for InternalsPluginV02, etc.
{
	protected:

		// logging
		bool mLogging;                        // whether we want logging enabled
		char* mLogPath;                       // path to write logs to
		FILE* mLogFile;                       // the file pointer

		long mStartMode;
		long mLoopWrFileReading;

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

  bool GetCustomVariable(long i, CustomVariableV01 &var);
  void AccessCustomVariable(CustomVariableV01 &var);
  void GetCustomVariableSetting(CustomVariableV01 &var, long i, CustomSettingV01 &setting);

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
	 void RainMakerPlugin::WriteToLogFile(const char* const openStr, const char* const type, const char* const msg);
};


#endif // _INTERNALS_EXAMPLE_H

