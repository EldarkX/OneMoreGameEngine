#pragma once

#include "Modules/CoreModule/GameEngine.h"

using std::string;

class AssetsManagerUtils
{

public:

	string GetProjectDir()
	{
		if (mProjectDir.empty())
		{
			char result[MAX_PATH];
			 (NULL, result, MAX_PATH);

			string ProjectPath(result);

			ProjectPath.erase(ProjectPath.find("\\x64\\Debug"));

			mProjectDir = ProjectPath;
		}
		return mProjectDir;
	}

private:

	string mProjectDir = "";
};