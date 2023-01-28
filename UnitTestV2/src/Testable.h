#pragma once
#ifndef UT_TESTABLE_H
#define UT_TESTABLE_H

#include <functional>
#include <iostream>
#include <sstream>
#include <chrono>
#include "utCommon.h"
#include "TestResults.h"

#define EXPECT_VALID(exp) isTrue_impl(exp, "EXPECT_VALID: "#exp, __FILENAME__, __LINE__)

#define EXPECT_EQ(a,b) isTrue_impl((a==b), "EXPECT_EQ: "#a " == " #b, __FILENAME__, __LINE__)

#define EXPECT_EXCEPTION(exp, exc) wasThrown_impl<exc>(\
			std::function<void()>([]()->void{exp;}),\
			"EXPECT_EXCEPTION: "#exc" in "#exp, __FILENAME__,	__LINE__)

#define EXPECT_NO_EXCEPTION(exp) noneThrown_impl(\
			std::function<void()>([]()->void{exp;}),\
			"EXPECT_NO_EXCEPTION: "#exp, __FILENAME__, __LINE__)

namespace Test {

	class TestCollection;

	class Testable {
		friend TestCollection;
	private:	//definitions
		typedef std::chrono::high_resolution_clock clock;
		typedef std::chrono::time_point<clock> timepoint;
		typedef std::chrono::duration<double, std::milli> duration;

	private:	//private Members
		utString mName;
		TestResultCollection mResult;

		timepoint mStartTime;
		timepoint mEndTime;

		std::basic_streambuf<char>* mStdCoutBackup = nullptr;
		std::basic_streambuf<char>* mStdCinBackup = nullptr;

		bool mFinished = false;

	protected:	//protected members
		std::stringstream mCout;
		std::stringstream mCin;

	public:		//Constructors and Destructors
		/// <summary>
		/// Creates the Testable and registers it with the Framework
		/// and gives it a human readable Name
		/// </summary>
		/// <param name="name">the Name of the Test</param>
		Testable(const std::string& name);

	private:	//internal functionality
		/// <summary>
		/// init function wrapper
		/// </summary>
		/// <returns>false when initialization failed</return>
		bool _init();

		/// <summary>
		/// run function wrapper
		/// </summary>
		void _run();

		/// <summary>
		/// cleanup function wrapper
		/// </summary>
		void _cleanup();

		/// <summary>
		/// return, weather a test has failed yet
		/// </summary>
		/// <returns>true when a test failed</returns>
		bool hasFailed() const;

	protected:	//Testing Functions
		/// <summary>
		/// Implements the Test Function to check for something being True
		/// </summary>
		/// <param name="value">the expression</param>
		/// <param name="code">the line of Code being checked</param>
		/// <param name="file">the file with the Line of Code</param>
		/// <param name="line">the Line Number of the Line of Code</param>
		void isTrue_impl(bool value, const char* code, const char* file, size_t line);

		/// <summary>
		/// Implements the Test Function to check if the correct Exception was thrown
		/// </summary>
		/// <typeparam name="E">the Exceptions Type</typeparam>
		/// <param name="exp">the Function being tested</param>
		/// <param name="code">the Line of Code being tested</param>
		/// <param name="file">the File with the line of Code</param>
		/// <param name="line">the Number of the Line of Code</param>
		template<typename E>
		void wasThrown_impl(std::function<void()> exp, const char* code, const char* file, size_t line) {
			try {
				exp();
				mResult.fail(code, file, line);
			}
			catch (E& e) { }
			catch (...) {
				mResult.fail(code, file, line);
			}
		}

		/// <summary>
		/// Implements the Test Function to check for no Exception being thrown
		/// </summary>
		/// <param name="exp">the Function being tested</param>
		/// <param name="code">the Line of Code being tested</param>
		/// <param name="file">the File with the line of Code</param>
		/// <param name="line">the Number of the Line of Code</param>
		void noneThrown_impl(std::function<void()> exp, const char* code, const char* file, size_t line);

	protected:		//protected functionality (to get overrides from childclasses)
		
		/// <summary>
		/// Initializes the Test.
		/// Everything to set up the Environment for the Test
		/// should happen here.
		/// </summary>
		/// <returns>true on success</returns>
		virtual bool init();

		/// <summary>
		/// Cleans up after the Test.
		/// Everything to clean up the Environment after the Test
		/// should happen here
		/// </summary>
		/// <returns>true on success</returns>
		virtual bool cleanup();

		/// <summary>
		/// Runs the Test.
		/// This has to be implemented, to make the Test a real Test
		/// </summary>
		virtual void run() = 0;

	public:	//getters and setters
		/// <summary>
		/// Getter for the Name of the Test
		/// </summary>
		/// <returns>the Name of the Test</returns>
		utString getName() const;

		/// <summary>
		/// Returns the Time the test took
		/// </summary>
		duration getTime() const;
	};

}

#endif