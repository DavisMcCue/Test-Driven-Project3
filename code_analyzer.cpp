/**
 * @file code_analyzer.cpp
 *
 * Implementation of code analyzer
 */

#include "code_analyzer.hpp"
#include "get_language_from_filename.hpp"
#include "xml_wrapper.hpp"
#include <iostream>
#include <string>

/**
 * markup_source_code 
 * @param request Data that forms the request
 * @retval Source analysis request in XML format
 * @retval Empty string if invalid
 *
 * Generate source analysis XML based on the request
 * Content is wrapped with an XML element that includes the metadata
 */
std::string markup_source_code(const analysis_request& request) {

    // wrap the content with a unit element
    xml_wrapper wrap("src", "https://www.srcML.org/src");
    wrap.start_element("unit");
    wrap.attribute("language", request.option_language);
	std::string filename;
	filename = request.option_filename;
	//Rule 1
	if (!filename.empty())
	{
		wrap.attribute("filename", filename);
	}
	// Rule 2 and 3 checking below if entry = data and if not then it checks if itd empty and preforms task accordingly. 
	else if (request.entry_filename == "data")
	{
		wrap.attribute("filename", request.disk_filename);
	}
	else if (!request.entry_filename.empty())
	{
		wrap.attribute("filename", request.entry_filename);
	}
	//Rule 4 
	else if (request.disk_filename == "-")
	{
		wrap.attribute("filename", request.entry_filename);
	}
	else if (request.entry_filename == "data")
	{
		wrap.attribute("filename", filename);
	}
	else if (filename == " ")
	{
		wrap.attribute("filename", filename);
	}
	//Rule 5
	if (!request.option_url.empty())
	{
		wrap.attribute("url", request.option_url);
	}
	//Rule 6
	if (!request.option_hash.empty())
	{
		wrap.attribute("hash", request.option_hash);
	} 
	//Rule 7
	if (request.option_loc >= 0)
	{
		int Loc = (request.option_loc);
		std::string Locprint = std::to_string(Loc);
		wrap.attribute("loc", Locprint);
	}
	
	//Error throwing return/print empty string if option file/disk/or entry is empty it throws an error
	if (request.option_filename.empty() || request.option_filename == " ")
	{
		std::cerr << "Error" << "";
	}
	else if (request.disk_filename.empty() || request.disk_filename == " ")
	{
		std::cerr << "Error" << "";
	}
	else if (request.entry_filename.empty()|| request.entry_filename == " ")
	{
		std::cerr << "Error" << "";
	}
	//if lang is not present but filename is throw error saying Language for stdin not declared
	if (!request.option_filename.empty() && request.option_language.empty())
	{
		std::cerr << " Language for stdin not declared" << "";
	}
	else if (!request.disk_filename.empty() && request.option_language.empty())
	{
		std::cerr << " Language for stdin not declared" << "";
	}
	else if (!request.entry_filename.empty() && request.option_language.empty())
	{
		std::cerr << " Language for stdin not declared" << "";
	}
    wrap.content(request.source_code);
    wrap.end_element();
	std::cerr << wrap.xml();
    return wrap.xml();
}
