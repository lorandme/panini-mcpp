module logging;

import <format>;


std::string_view LogLevelToString(Logger::Level level)
{
	switch (level)
	{
		using enum Logger::Level;
	case Info:
		return "Info";
	case Warning:
		return "Warning";
	case Error:
		return "Error";
	default:
		return "";
	}
}

Logger::Logger(std::ostream& os, Logger::Level minimumLevel) :
	m_os{ os },
	m_minimumLevel{ minimumLevel }
{
	// Empty
}

void Logger::SetMinimumLogLevel(Level level)
{
	m_minimumLevel = level;
}

void Logger::Log(const std::string& msg, Level level)
{
	m_os << msg << "\n";
}