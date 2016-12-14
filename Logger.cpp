#include "Logger.h"
#include <ctime>
#include <sstream>

///<summary> the static instance of Logger </summary>
Logger *Logger::m_instance = nullptr;

Logger::Logger()
 :m_isLogging(false),
  m_timer(0),
  m_data(vector<DataHolder>()),
  m_events(vector<string>())
{

}

///<summary> opens the file we will use to log to. </summary>
void Logger::openFile()
{
	if (m_loggerFile.is_open() == false)
	{
		time_t t = time(0);
		struct tm currentDateTime;
		
		localtime_s(&currentDateTime, &t);

		string mins;

		if (currentDateTime.tm_min < 10)
		{
			mins = "0" + std::to_string(currentDateTime.tm_min); //so it's 15:01 instead of 15:1
		}
		else
		{
			mins = std::to_string(currentDateTime.tm_min);
		}

		string fileName = "Logs/log-" + std::to_string(currentDateTime.tm_mday);
		fileName += "_" + std::to_string(currentDateTime.tm_mon + 1);
		fileName += "_" + std::to_string((currentDateTime.tm_year + 1900));
		fileName += "-" + std::to_string(currentDateTime.tm_hour);
		fileName += "_" + mins;
		fileName += ".csv";

		m_loggerFile.open(fileName);
	}



	m_loggerFile << "NEW INSTANCE" << endl; //start of each log will have this at the top, if logged multiple times per run this is the seperator line.
}


Logger::~Logger()
{
}

///<summary> returns the static instance of Logger </summary>
Logger *Logger::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Logger();
	}

	return m_instance;
}

///<summary> if we're currently logging, adds a data entry to the list of data which will be logged. </summary>
void Logger::log(int deltaTime,
	float x,
	float y)
{
	if (m_isLogging == true)
	{
		m_timer += deltaTime;

		DataHolder data;
		data.m_time = std::to_string(m_timer);
		data.m_x = std::to_string(x);
		data.m_y = std::to_string(y);
		data.m_events = m_events;
		m_data.push_back(data);

		m_events.clear();
	}
}

///<summary> will start logging data to the list if not already doing so. If it is, it will stop logging data and write what it has stored to the file. </summary>
void Logger::startStopLogging()
{
	m_isLogging = !m_isLogging;

	if (m_isLogging == true)
	{
		cout << "Started Logging!" << endl;
	}
	else
	{
		cout << "Logged to File!" << endl;
	}

	if (m_isLogging == false)
	{
		openFile();

		for (int i = 0; i < m_data.size(); i++)
		{
			DataHolder data = m_data[i];

			m_loggerFile << data.m_time << "," << data.m_x << "," << data.m_y;

			for (int j = 0; j < data.m_events.size(); j++)
			{
				m_loggerFile << "," << data.m_events[j];
			}

			m_loggerFile << endl;
		}

		m_data.clear();
		m_events.clear();
		m_timer = 0;
	}
}

///<summary> adds an event eg. key pressed to the list of data to write to the file. </summary>
void Logger::addEvent(string eventName)
{
	if (m_isLogging)
	{
		m_events.push_back(eventName);
	}
}