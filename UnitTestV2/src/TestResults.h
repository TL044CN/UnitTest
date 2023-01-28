#pragma once
#ifndef UT_TEST_RESULTS_H
#define UT_TEST_RESULTS_H
#include "utCommon.h"
#include <cstdint>
#include <ostream>
#include <list>

namespace Test {

	class TestResultCollection {
	private: //internal Class
		class TestResult {
		private:	//private Members
			utString mCode;
			utString mFile;
			uint64_t mLine = 0;

		public:		//Constructors and Destructors
			/// <summary>
			/// Creates a new Test Result
			/// </summary>
			/// <param name="code">the Code Segment</param>
			/// <param name="file">the File with the Test</param>
			/// <param name="line">the Line of the Test</param>
			explicit TestResult(const utString& code, const char* file, size_t line);

		public:		//Functionality
			/// <summary>
			/// Writes the Test result to the given ostream
			/// </summary>
			/// <param name="stream">the stream to write to</param>
			void report(std::ostream& stream, uint32_t indent = 12) const;
		};

	private:	//internal Defines
		typedef std::list<TestResult> result_collection;
		typedef result_collection::iterator iterator;
		typedef result_collection::const_iterator const_iterator;

	private:	//private Members
		result_collection mResults;
		utString mError;

	public:		//Constructors and Destructors
		/// <summary>
		/// Creates the TestResult Collection
		/// </summary>
		TestResultCollection() = default;

	public:		//exposed Functionality
		/// <summary>
		/// Records a Fail of the Test
		/// </summary>
		/// <param name="code">the Code Segment with the Test</param>
		/// <param name="file">the File containing the Segment</param>
		/// <param name="line">the Line with the Code Segment</param>
		void fail(const utString& code, const char* file, size_t line);

		/// <summary>
		/// Reports the Error that occured, if an error occured
		/// </summary>
		/// <param name="stream">the Stream to write to</param>
		void reportError(std::ostream& stream, uint32_t indent = 12) const;

		/// <summary>
		/// Reports all the Fails that occured
		/// </summary>
		/// <param name="stream">the Stream to write to</param>
		void reportFails(std::ostream& stream, uint32_t indent = 12) const;

	public:		//Getters and Setters
		/// <summary>
		/// Records an Escape from the Test Code, an Exception or a
		/// Fail while running the init or cleanup functions
		/// </summary>
		/// <param name="err">the Error Message</param>
		void error(const utString& err);

		/// <summary>
		/// returns the number of failed Tests
		/// </summary>
		/// <returns>the number of failed Tests</returns>
		uint64_t failCount() const;

		/// <summary>
		/// returns weather an Error has occured or not
		/// </summary>
		/// <returns>true when an Error occured</returns>
		bool hasError() const;
	};

}

#endif