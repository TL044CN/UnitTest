#pragma once
#ifndef UT_TEST_COLLECTION_H
#define UT_TEST_COLLECTION_H

#include <list>
#include <ostream>
#include "Testable.h"

namespace Test {
	
	/// <summary>
	/// TestCollection Singleton
	/// </summary>
	class TestCollection {
	private:	// internal Defines
		typedef std::list<Testable*> testable_collection;
		typedef std::chrono::high_resolution_clock clock;
		typedef std::chrono::time_point<clock> timepoint;
		typedef std::chrono::duration<double, std::milli> duration;

	private:	//private Members
		static TestCollection* mInstance;
		testable_collection mTests;

		uint64_t mFailCount = 0;
		uint64_t mPassCount = 0;

		duration mDuration;

	public:		//Constructors and Destructors
		TestCollection() = default;

		TestCollection(const TestCollection&) = delete;

	private:	//internal Functionality
		/// <summary>
		/// Instantly reports an Error in one of the Tests caused by the Framework.
		/// This Error is Fatal and should not happen.
		/// </summary>
		/// <param name="message">the error message to display</param>
		void error(const utString& message);

	public:		//exposed Functionality
		/// <summary>
		/// Get the Instance of the TestCollection
		/// </summary>
		/// <returns>a Reference to the instance of the TestCollection</returns>
		static TestCollection& Instance();

		/// <summary>
		/// Adds a Test to the internal List of Tests to run.
		/// </summary>
		/// <param name="test">the Test to add</param>
		static void addTest(Testable* test);

		/// <summary>
		/// Runs all the Tests
		/// </summary>
		static void runTests();

		/// <summary>
		/// writes a Report to the given ostream
		/// </summary>
		/// <param name="stream">the stream to write to</param>
		static void report(std::ostream& stream, bool color=false);
	};

}

#endif