#include <string>

struct Options {
		Options();
		bool daemon() const { return daemon_; }
		const std::string& pidFile() const { return pidFile_; }
		const std::string& logFile() const { return logFile_; }

		static void init( int argc, char** argv );

		private:

				bool daemon_;
				std::string pidFile_;
				std::string logFile_;
};


extern const Options* &options;
