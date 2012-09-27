#ifndef XML_READER_H_
#define XML_READER_H_

/*
 * @brief The XMLReader class is responsible for dealing with libxml's api
 *      and constructing the XMLNode's objects representing the xml's nodes
 *
 * @author Filipe N. Felisbino
 *
 * */
#include <string>
#include <list>
#include <map>
#include <stdexcept>
#include <libxml/parser.h>
#include <libxml/tree.h>

using std::runtime_error;
using std::string;
using std::map;
using std::list;

class XMLReaderException : public runtime_error {
public:
    XMLReaderException(const string &x) :
        runtime_error(x) {};

};

class XMLNode {
public:
    static XMLNode NULL_NODE;
    static const XMLNode END_NODE;

//    typedef vector<XMLNode>::iterator iterator;
    typedef list<XMLNode> ListType;
    typedef map<string, ListType> MapType;

    string name; // tag name
    string text; // tag value ( if is a text tag )
    map<string, string> attributes;
    MapType children;

    XMLNode& operator[](const std::string &name);
    ListType::iterator FirstChild(const std::string &name);
    ListType::iterator LastChild(const std::string &name);
};

class XMLReader {
public:
    XMLReader(const string &o);
    ~XMLReader();

    void parse(list<XMLNode> &);
    bool findNode(const string&);
private:
    xmlDoc *doc_;

    void getAttributes(xmlNode *node, map<string,string>&data);
    void getChildren(xmlNode *node, XMLNode &result);
    void populateNode(xmlNode* node, XMLNode &result);
};

#endif // XML_READER_H_

