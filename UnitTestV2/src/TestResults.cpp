#include "TestResults.h"
#include <iomanip>

namespace Test {

	/// <summary>
	/// Creates a new Test Result
	/// </summary>
	/// <param name="code">the Code Segment</param>
	/// <param name="file">the File with the Test</param>
	/// <param name="line">the Line of the Test</param>
	TestResultCollection::TestResult::TestResult(const utString& code, const char* file, size_t line)
	: mCode(code), mFile(file), mLine(line) {}


	/// <summary>
	/// Writes the Test result to the given ostream
	/// </summary>
	/// <param name="stream"></param>
	void TestResultCollection::TestResult::report(std::ostream& stream, uint32_t indent) const {
		stream
			<< std::setw(indent) << std::left
			<< "Condition: "	<< mCode << '\n'
			<< std::setw(indent) << std::left
			<< "in File: "	<< mFile << ':' << mLine << '\n';
	}



	/// <summary>
	/// Records a Fail of the Test
	/// </summary>
	/// <param name="code">the Code Segment with the Test</param>
	/// <param name="file">the File containing the Segment</param>
	/// <param name="line">the Line with the Code Segment</param>
	void TestResultCollection::fail(const utString& code, const char* file, size_t line) {
		mResults.push_back(TestResult(code, file, line));
	}

	/// <summary>
	/// Reports the Error that occured, if an error occured
	/// </summary>
	/// <param name="stream">the Stream to write to</param>
	void TestResultCollection::reportError(std::ostream& stream, uint32_t indent) const {
		if (!mError.empty()) stream << std::setw(indent) << "Error: " << mError << '\n';
	}

	/// <summary>
	/// Reports all the Fails that occured
	/// </summary>
	/// <param name="stream">the Stream to write to</param>
	void TestResultCollection::reportFails(std::ostream& stream, uint32_t indent) const {
		for (auto& result : mResults)
 			result.report(stream, indent);
	}


	/// <summary>
	/// Records an Escape from the Test Code, an Exception or a
	/// Fail while running the init or cleanup functions
	/// </summary>
	/// <param name="err">the Error Message</param>
	void TestResultCollection::error(const utString& err) {
		mError = err;
	}

	/// <summary>
	/// returns the number of failed Tests
	/// </summary>
	/// <returns>the number of failed Tests</returns>
	uint64_t TestResultCollection::failCount() const {
		return mResults.size();
	}
	
	/// <summary>
	/// returns weather an Error has occured or not
	/// </summary>
	/// <returns>true when an Error occured</returns>
	bool TestResultCollection::hasError() const {
		return !mError.empty();
	}
}