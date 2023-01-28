#include "TestCollection.h"
#include <iomanip>
#include <vector>
#include <thread>
#include <map>
#include <chrono>

namespace Test {
	// initialize the Instance pointer to nullptr
	TestCollection* TestCollection::mInstance = nullptr;


	/// <summary>
	/// Instantly reports an Error in one of the Tests caused by the Framework.
	/// This Error is Fatal and should not happen.
	/// </summary>
	/// <param name="message"></param>
	void TestCollection::error(const utString& message) {
		perror(message.c_str());
	}

	/// <summary>
	/// Get the Instance of the TestCollection
	/// </summary>
	/// <returns>a Reference to the instance of the TestCollection</returns>
	TestCollection& TestCollection::Instance() {
		if (mInstance == nullptr)
			mInstance = new TestCollection();
		return *mInstance;
	}

	/// <summary>
	/// Adds a Test to the internal List of Tests to run.
	/// </summary>
	/// <param name="test">the Test to add</param>
	void TestCollection::addTest(Testable* test) {
		Instance().mTests.push_back(test);
	}

	/// <summary>
	/// Runs all the Tests
	/// </summary>
	void TestCollection::runTests() {
		timepoint start = clock::now();
		std::vector<std::thread> threads;

		for (auto& test : Instance().mTests) {
			threads.push_back(std::thread([&]()->void {
				try {
					if (!test->_init()) return;
					test->_run();
					test->_cleanup();

					if (test->hasFailed()) Instance().mFailCount++;
					else Instance().mPassCount++;
				}
				catch (std::exception& e) {
					mInstance->error(e.what());
				}
				catch (...) {
					mInstance->error("unexpected error");
				}
			}));
		}

		for (auto& thread : threads)
			thread.join();

		timepoint end = clock::now();
		Instance().mDuration = end - start;
	}

	/// <summary>
	/// writes a Report to the given ostream
	/// </summary>
	/// <param name="stream">the stream to write to</param>
	void TestCollection::report(std::ostream& stream, bool color) {

		auto repeat = [](char c, uint32_t times) -> utString {
			std::string result = "";
			for (; times--;)
				result += c;
			return result;
		};

		constexpr uint32_t seperator_width = 90;
		constexpr uint32_t indent = 14;

		std::map<const char*, const char*> colorMap;
		colorMap["reset"] = "";
		colorMap["green"] = "";
		colorMap["red"] = "";
		colorMap["yellow"] = "";
		colorMap["orange"] = "";

		if (color) {
			colorMap["reset"]	= "\x1b[0m";
			colorMap["green"]	= "\x1b[38;5;40m";
			colorMap["red"]		= "\x1b[38;5;160m";
			colorMap["yellow"]	= "\x1b[38;5;226m";
			colorMap["orange"]	= "\x1b[38;5;208m";
		}

		//change Unit Test Headline Color based on tests passed or failed.
		//green: all tests passed
		//red: all tests failed
		//yellow: both failed and passed tests
		//orange: no tests being run
		switch ((Instance().mFailCount > 0 ? 1 : 0) + (Instance().mPassCount > 0 ? 2 : 0)) {
		case 1:
			stream << colorMap["red"];
			break;
		case 2:
			stream << colorMap["green"];
			break;
		case 3:
			stream << colorMap["yellow"];
			break;
		default:
			stream << colorMap["orange"];
			break;
		}

		stream << "Unit Test Report:" << colorMap["reset"] << '\n';

		for (auto& testable : Instance().mTests) {

			stream << std::setw(seperator_width) << std::left << std::setfill('=');
			stream << repeat('=', seperator_width / 2 - testable->getName().size() / 2 -2) + '[' + testable->getName() + ']' << '\n';

			stream << std::setfill(' ')
			<< std::setw(indent) << std::left << "Duration: " << testable->getTime().count() << "ms\n"
			<< std::setw(indent) << std::left << "Status: ";
			if (testable->hasFailed()) {
				stream << colorMap["red"] << "failed" << colorMap["reset"] << "\nReport:\n";
				testable->mResult.reportFails(stream, indent);
				testable->mResult.reportError(stream, indent);
			} else stream << colorMap["green"] << "passed" << colorMap["reset"] << '\n';
		}
		stream << std::setw(seperator_width) << std::setfill('=') << '=' << '\n';
		stream << std::setfill(' ')
			<< "Conclusion: \n"
			<< std::setw(indent) << "Failed Tests: " << Instance().mFailCount << '\n'
			<< std::setw(indent) << "Passed Tests: " << Instance().mPassCount << '\n'
			<< std::setw(indent) << "Duration: " << Instance().mDuration.count() << "ms\n";

	}

}