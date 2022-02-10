/**
 * @file xml_wrapper.hpp
 *
 * Class for wrapping code with an XML tag and descriptive attributes
 */

#ifndef INCLUDE_CODE_XML_WRAPPER_HPP
#define INCLUDE_CODE_XML_WRAPPER_HPP

#include <string>
#include <cstring>
#include <stdexcept>

/**
 * xml_wrapper
 *
 * Creates XML of a single element around content:
 *   * Single-include file
 *   * Processes in UTF-8, and only in UTF-8
 *   * Requires namespace prefix and uri (non-blank)
 */
class xml_wrapper {
private:
    std::string local_name;
    std::string ns_uri;
    std::string ns_prefix;
    std::string text;
    enum { ROOT, STARTTAG, CONTENT, COMPLETED } state = ROOT;
public:

    /**
     * xml_wrapper
     * @param prefix default namespace prefix
     * @param uri default namespace URI
     *
     * Construct uml_wrapper with default uri/prefix
     * Initialize start of UML document text
     */
    xml_wrapper(const std::string& prefix, const std::string& uri)
        : ns_prefix(prefix), ns_uri(uri) {

        if (uri.empty())
            throw std::invalid_argument("URI for namespace required");

        if (prefix.empty())
            throw std::invalid_argument("Non-default namespace prefix required");

        text = R"^^^(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>)^^^";
        text += "\n";
    }

    /**
     * start_element
     * @param name Name of the element to start
     *
     * Starts the element
     *   * Must not be preceded by call to attribute, content(), and end_element()
     *   * Can only be called once
     * 
     */
    void start_element(const std::string& name) {

        // verify is allowed
        switch (state) {
            case ROOT:
                break;
            case STARTTAG:
            case CONTENT:
            case COMPLETED:
                throw std::out_of_range("start_element() can only be called once");
        }

        // save the element name to write the end element
        local_name = name;

        // start of start tag
        text += "<";
        text += ns_prefix;
        text += ":";
        text += local_name;

        // namespace
        text += " ";
        text += "xmlns:";
        text += ns_prefix;
        text += "=\"";
        text += ns_uri;
        text += "\"";

        state = STARTTAG;
    }

    /**
     * attribute
     * @param name Name of the attribute to append
     * @param value Value of the attribute to append
     *
     * Appends attribute of form name="value"
     *  * Must be preceded by call to start_element(), and before calls to content() and end_element()
     *  * Can be called multiple times
     */
    void attribute(const std::string& name, const std::string& value) {

        // verify is allowed
        switch (state) {
            case ROOT:
                throw std::out_of_range("start_element() must be called before attribute()");
            case STARTTAG:
                break;
            case CONTENT:
                throw std::out_of_range("attribute() cannot be called after content()");
            case COMPLETED:
                throw std::out_of_range("attribute() cannot be called after end_element()");
        }

        // attribute of the form name="value"
        text += " ";
        text += name;
        text += "=\"";
        text += value;
        text += "\"";
    }


    /**
     * end_element
     *
     * Ends wrapping element
     *   * Must be preceded by call to start_element()
     *   * Only allowed to be called once
     *   * No calls to start_element() or content() after
     */
    void end_element() {

        // verify is allowed
        switch (state) {
            case ROOT:
                throw std::out_of_range("start_element() must be called before end_element()");
            case STARTTAG:
            case CONTENT:
                break;
            case COMPLETED:
                throw std::out_of_range("end_element() can only be called once");
        }

        // end previous start tag if not closed
        if (state == STARTTAG)
            text += ">";

        // end element tag
        text += "</";
        text += ns_prefix;
        text += ":";
        text += local_name;
        text += ">\n";

        state = COMPLETED;
    }


    /**
     * content
     * @param content Content (i.e., text) to add between tag
     *
     * Appends content escaping characters needed for XML
     *   * Must be preceded by call to start_element()
     *   * Cannot be called after end_element()
     *   * Multiple calls are allowed
     */
    void content(const std::string& content) {

        switch (state) {
            case ROOT:
                throw std::out_of_range("start_element() must be called before content()");
            case STARTTAG:
            case CONTENT:
                break;
            case COMPLETED:
                throw std::out_of_range("content() cannot be called before end_element()");
        }

        // end previous start tag if not closed
        if (state == STARTTAG)
            text += ">";

        // insert content, escaping if needed
        if (strpbrk(content.c_str(), "<>&") == nullptr) {

            text += content;

        } else {
  
            for (char c : content) {
                if (c == '<') {
                    text += "&lt;";
                } else if (c == '>') {
                    text += "&gt;";
                } else if (c == '&') {
                    text += "&amp;";
                } else {
                    text += c;
                }
            }
        }

        state = CONTENT;
    }


    /**
     * xml
     * @retval Currently stored XML
     * 
     * Get method retrieving currently stored XML
     */
    // current xml
    std::string xml() const { 

        // xml() is allowed for any state
        
        return text;
    }

};

#endif
