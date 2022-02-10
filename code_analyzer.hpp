/**
 * @file code_analyzer.hpp
 *
 * Header for code analyzer
 */

#ifndef INCLUDE_CODE_ANALYZER_HPP
#define INCLUDE_CODE_ANALYZER_HPP

#include "analysis_request.hpp"

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
std::string markup_source_code(const analysis_request& request);

#endif
