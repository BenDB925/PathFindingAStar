#pragma once

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

///<summary> Will log data to a csv file</summary>
class Logger
{
public:
	~Logger();

	///<summary> returns the static instance of Logger </summary>
	static Logger *getInstance();


	///<summary> adds an event eg. key pressed to the list of data to write to the file. </summary>
	void addEvent(string eventName);

	///<summary> if we're currently logging, adds a data entry to the list of data which will be logged. </summary>
	void log(int deltaTime,
		float x,
		float y);


	///<summary> will start logging data to the list if not already doing so. If it is, it will stop logging data and write what it has stored to the file. </summary>
	void startStopLogging();

private:

	///<summary> Contains everything that will be written each frame while logging. </summary>
	struct DataHolder
	{
		string m_time; // the time spent logging so far in ms
		string m_x; // the x position of the player
		string m_y; // the y position of the player
		vector<string> m_events; // any stored events that happened since last frame logged
	};

	Logger();


	///<summary> opens the file we will use to log to. </summary>
	void openFile();


	///<summary> the list of all data that will be written to the file. </summary>
	vector<DataHolder> m_data;


	///<summary> the temporary holder of any events triggered until we next log to the file. </summary>
	vector<string> m_events;


	///<summary> the total time since we started logging</summary>
	float m_timer;


	///<summary> are we currently logging to a file </summary>
	bool m_isLogging;


	///<summary> the static instance of Logger </summary>
	static Logger *m_instance;

	///<summary> the file we're logging to. </summary>
	ofstream m_loggerFile;
};

