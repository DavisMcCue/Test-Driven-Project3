/**
 * @file test_code_analysis.cpp
 *
 *  Test program for analysis requests
 */

#include "code_analyzer.hpp"

#include <string>
#include <cassert>

/*
 * main
 * @retval 0 if successfully run, nonzero otherwise
 *
 * Tests markup_source_code() using TDD approach
 * Use simple testing each in a separate {} as use below or Boost.Test
 */
int main() {

    // option language
    {
        analysis_request request;
        request.source_code = R"(
if (a < b) a = b;
)";
        request.disk_filename  = "";
        request.entry_filename  = "";
        request.option_filename = "";
        request.source_url       = "";
        request.option_url      = "";
        request.option_language = "C++";
        request.default_language = "";
        request.option_loc = -1;

        assert(markup_source_code(request) ==
            R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<src:unit xmlns:src="https://www.srcML.org/src" language="C++">
if (a &lt; b) a = b;
</src:unit>
)");
    }

	// Option_FileName Rule 1
	{
		analysis_request request;
		request.source_code = R"(
if (a < b) a = b;
)";
		request.disk_filename = "";
		request.entry_filename = "";
		request.option_filename = "NewMain.cpp";
		request.source_url = "";
		request.option_url = "";
		request.option_language = "";
		request.default_language = "";
		request.option_loc = -1;

		assert(markup_source_code(request) ==
			R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<src:unit xmlns:src="https://www.srcML.org/src" language="" filename="NewMain.cpp">
if (a &lt; b) a = b;
</src:unit>
)");
	}
//-----------------------------------------------------------------------------------------------------------
	// diskfile_filename Rule 2-3
	{
		analysis_request request;
		request.source_code = R"(
if (a < b) a = b;
)";
		request.disk_filename = "CrazyDisk.cpp";
		request.entry_filename = "data";
		request.option_filename = "";
		request.source_url = "";
		request.option_url = "";
		request.option_language = "C++";
		request.default_language = "";
		request.option_loc = -1;

		assert(markup_source_code(request) ==
			R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<src:unit xmlns:src="https://www.srcML.org/src" language="C++" filename="CrazyDisk.cpp">
if (a &lt; b) a = b;
</src:unit>
)");
	}
	//Rule 2 - 3 cont
	{
		analysis_request request;
		request.source_code = R"(
if (a < b) a = b;
)";
		request.disk_filename = "CrazyDisk.cpp";
		request.entry_filename = "data";
		request.option_filename = "file.cpp";
		request.source_url = "";
		request.option_url = "";
		request.option_language = "C++";
		request.default_language = "";
		request.option_loc = -1;

		assert(markup_source_code(request) ==
			R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<src:unit xmlns:src="https://www.srcML.org/src" language="C++" filename="file.cpp">
if (a &lt; b) a = b;
</src:unit>
)");
	}
//-----------------------------------------------------------------------------------------------------------
	// Rule 4
	{
		analysis_request request;
		request.source_code = R"(
if (a < b) a = b;
)";
		request.disk_filename = "-";
		request.entry_filename = "Crazybill.cpp";
		request.option_filename = "";
		request.source_url = "";
		request.option_url = "";
		request.option_language = "C++";
		request.default_language = "";
		request.option_loc = -1;

		assert(markup_source_code(request) ==
			R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<src:unit xmlns:src="https://www.srcML.org/src" language="C++" filename="Crazybill.cpp">
if (a &lt; b) a = b;
</src:unit>
)");
	}
	// Rule 4 Cont..
	{
	analysis_request request;
	request.source_code = R"(
if (a < b) a = b;
)";
	request.disk_filename = "";
	request.entry_filename = "data";
	request.option_filename = "CrazySteve.cpp";
	request.source_url = "";
	request.option_url = "";
	request.option_language = "C++";
	request.default_language = "";
	request.option_loc = -1;

	assert(markup_source_code(request) ==
		R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<src:unit xmlns:src="https://www.srcML.org/src" language="C++" filename="CrazySteve.cpp">
if (a &lt; b) a = b;
</src:unit>
)");
	}
	// Rule 4 Cont..
	{
	analysis_request request;
	request.source_code = R"(
if (a < b) a = b;
)";
	request.disk_filename = "";
	request.entry_filename = "";
	request.option_filename = " ";
	request.source_url = "";
	request.option_url = "";
	request.option_language = "C++";
	request.default_language = "";
	request.option_loc = -1;

	assert(markup_source_code(request) ==
		R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<src:unit xmlns:src="https://www.srcML.org/src" language="C++" filename=" ">
if (a &lt; b) a = b;
</src:unit>
)");
	}
//-----------------------------------------------------------------------------------------------------------
	// Rule 5
	{
		analysis_request request;
		request.source_code = R"(
if (a < b) a = b;
)";
		request.disk_filename = "";
		request.entry_filename = "";
		request.option_filename = "NewMain.cpp";
		request.source_url = "";
		request.option_url = "https://www.cs.bgsu.edu/mdecke/NewMain.cpp";
		request.option_language = "C++";
		request.default_language = "";
		request.option_loc = -1;

		assert(markup_source_code(request) ==
			R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<src:unit xmlns:src="https://www.srcML.org/src" language="C++" filename="NewMain.cpp" url="https://www.cs.bgsu.edu/mdecke/NewMain.cpp">
if (a &lt; b) a = b;
</src:unit>
)");
	}
//-----------------------------------------------------------------------------------------------------------
	//Rule 6
	{
		analysis_request request;
		request.source_code = R"(
if (a < b) a = b;
)";
		request.disk_filename = "";
		request.entry_filename = "";
		request.option_filename = "NewMain.cpp";
		request.source_url = "";
		request.option_url = "";
		request.option_language = "C++";
		request.default_language = "";
		request.option_hash = "39dcad4f59855aa76420aa3d69af3d7ba30a91bb";
		request.option_loc = -1;

		assert(markup_source_code(request) ==
			R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<src:unit xmlns:src="https://www.srcML.org/src" language="C++" filename="NewMain.cpp" hash="39dcad4f59855aa76420aa3d69af3d7ba30a91bb">
if (a &lt; b) a = b;
</src:unit>
)");
	}
//-----------------------------------------------------------------------------------------------------------
	//Rule 7
	{
		analysis_request request;
		request.source_code = R"(
if (a < b) a = b;
)";
		request.disk_filename = "";
		request.entry_filename = "";
		request.option_filename = "NewMain.cpp";
		request.source_url = "";
		request.option_url = "";
		request.option_language = "C++";
		request.default_language = "";
		request.option_loc = 2;

		assert(markup_source_code(request) ==
			R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<src:unit xmlns:src="https://www.srcML.org/src" language="C++" filename="NewMain.cpp" loc="2">
if (a &lt; b) a = b;
</src:unit>
)");
	}
/*
//-----------------------------------------------------------------------------------------------------------
	//Error's Language not found
	//if you remove c++ from option_language it will throw an error and break.
	{
		analysis_request request;
		request.source_code = R"(
if (a < b) a = b;
)";
		request.disk_filename = "";
		request.entry_filename = "";
		request.option_filename = "";
		request.source_url = "";
		request.option_url = "";
		request.option_language = "C++";
		request.default_language = "";
		request.option_loc;

		assert(markup_source_code(request) ==
			R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<src:unit xmlns:src="https://www.srcML.org/src" language="C++">
if (a &lt; b) a = b;
</src:unit>
)");
	}
	*/
	return 0;
}
