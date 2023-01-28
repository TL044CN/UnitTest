#include "Testable.h"
#include "TestCollection.h"

namespace Test {
	/// <summary>
	/// Creates the Testable and registers it with the Framework
	/// and gives it a human readable Name
	/// </summary>
	/// <param name="name">the Name of the Test</param>
	Testable::Testable(const std::string& name): mName(name) {
		TestCollection::addTest(this);
	}


	/// <summary>
	/// init function wrapper
	/// </summary>
	/// <returns>false when initialization failed. </return>
	bool Testable::_init() {
		try {
			//backup cout and cin buffer and replace them with internal ones
			mStdCoutBackup = std::cout.rdbuf(mCout.rdbuf());
			mStdCinBackup = std::cin.rdbuf(mCin.rdbuf());

			mStartTime = clock::now();

			if (init()) return true;
			mResult.error("Failed to Initiate Test");
		} catch (std::exception& e) {
			mResult.error(e.what());
		} catch (...) {
			mResult.error("Unknown Error");
		}

		//restore original cout and cin buffer (because _init failed)
		std::cout.rdbuf(mStdCoutBackup);
		std::cin.rdbuf(mStdCinBackup);

		return false;
	}

	/// <summary>
	/// run function wrapper
	/// </summary>
	void Testable::_run() {
		try {
			run();
		} catch (std::exception& e) {
			mResult.error(e.what());
		} catch (...) {
			mResult.error("Unknown Error");
		}
	}

	/// <summary>
	/// return, weather a test has failed yet
	/// </summary>
	/// <returns>true when a test failed</returns>
	void Testable::_cleanup() {
		try {
			//restore original cout and cin buffer
			if (!cleanup()) mResult.error("Failed to Cleanup Test");
			std::cout.rdbuf(mStdCoutBackup);
			std::cin.rdbuf(mStdCinBackup);
			mEndTime = clock::now();
			mFinished = true;
		} catch (std::exception& e) {
			mResult.error(e.what());
		} catch (...) {
			mResult.error("Unknown Error");
		}

	}

	/// <summary>
	/// return, weather a test has failed yet
	/// </summary>
	/// <returns>true when a test failed</returns>
	bool Testable::hasFailed() const {
		if (mResult.hasError()) return true;
		return mResult.failCount() > 0;
	}


	/// <summary>
	/// Implements the Test Function to check for something being True
	/// </summary>
	/// <param name="value">the expression</param>
	/// <param name="code">the line of Code being checked</param>
	/// <param name="file">the file with the Line of Code</param>
	/// <param name="line">the Line Number of the Line of Code</param>
	void Testable::isTrue_impl(bool value, const char* code, const char* file, size_t line) {
		if (!value) mResult.fail(code, file, line);
	}

	/// <summary>
	/// Implements the Test Function to check for no Exception being thrown
	/// </summary>
	/// <param name="exp">the Function being tested</param>
	/// <param name="code">the Line of Code being tested</param>
	/// <param name="file">the File with the line of Code</param>
	/// <param name="line">the Number of the Line of Code</param>
	void Testable::noneThrown_impl(std::function<void()> exp, const char* code, const char* file, size_t line) {
		try {
			exp();
		}
		catch (...) {
			mResult.fail(code, file, line);
		}
	}


	/// <summary>
	/// Initializes the Test.
	/// Everything to set up the Environment for the Test
	/// should happen here.
	/// </summary>
	/// <returns>true on success</returns>
	bool Testable::init() { return true; }

	/// <summary>
	/// Cleans up after the Test.
	/// Everything to clean up the Environment after the Test
	/// should happen here
	/// </summary>
	/// <returns>true on success</returns>
	bool Testable::cleanup() { return true; }

	/// <summary>
	/// Getter for the Name of the Test
	/// </summary>
	/// <returns>the Name of the Test</returns>
	utString Testable::getName() const {
		return mName;
	}

	/// <summary>
	/// Returns the Time the test took
	/// </summary>
	Testable::duration Testable::getTime() const {
		if (!mFinished) return duration(0);
		return mEndTime - mStartTime;
	}
}
