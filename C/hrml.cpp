#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#define TEST_DATA_FILE "./hrml.testdata2.txt"

template<typename OutIterator>
std::istream& getnlines(std::istream& is, unsigned int n, OutIterator output) {
    std::string instring;
    while (n--) {
        if (!(std::getline(is,instring))) {
            break;
        }
        *(output++) = instring;
    }
    return is;
}

class Hrml {
public:
    Hrml(const std::string& tagname=""): m_tagname(tagname) {}
    Hrml& parse_sub_hrml(const std::string& hrmlstr);
    int query(const std::string& token, std::string& value) const;
    std::string serialize(std::string indent = "") const;
private:
    Hrml& add_sub_hrml(Hrml& hrml);
    const Hrml* find_subhrml(const std::string& tagname) const;
    Hrml& parse_attributes(const std::string& attributes);
    const Hrml* query_subhrml(const std::string& token) const;
    int query_attribute(const std::string& key, std::string& value) const;

    std::string m_tagname;
    std::map<std::string, std::string> m_attributes;
    std::vector<Hrml> m_sub_hrmls;
};

int Hrml::query_attribute(const std::string& key, std::string& value) const {
    auto it = m_attributes.find(key);
    if (it == m_attributes.end()) {
        return -1;
    }
    value = it->second;
    return 0;
}

const Hrml* Hrml::find_subhrml(const std::string& tagname) const {
    for (auto& subhrml: m_sub_hrmls) {
        if (tagname == subhrml.m_tagname) {
            return &subhrml;
        }
    }
    return NULL;
}

const Hrml* Hrml::query_subhrml(const std::string& token) const {
    const Hrml* p_hrml = this;
    std::string field;

    for (auto c: token) {
        switch (c) {
        case '.':
        case '~':
            if (!(p_hrml = p_hrml->find_subhrml(field))) {
                return NULL;
            }
            if (c == '~') {
                return p_hrml;
            }
            field.clear();
            break;
        default:
            field.push_back(c);
        }
    }

    if (!field.empty()) {
        return p_hrml->find_subhrml(field);
    }

    return NULL;
}

int Hrml::query(const std::string& token, std::string& value) const {
    auto tilde = std::find(token.begin(), token.end(), '~');
    if (tilde == token.end()) {
        return -1;
    }

    const Hrml* phrml = query_subhrml(std::string(token.begin(), tilde));
    if (!phrml) {
        return -1;
    }

    return phrml->query_attribute(std::string(tilde+1, token.end()), value);
}

Hrml& Hrml::parse_attributes(const std::string& attributes) {
    std::regex rgx{R"_((\w+)\s*=\s*"([\w\s]+?)")_"};
    std::smatch match;
    auto begin = attributes.begin(), end = attributes.end();
    while (regex_search(begin, end, match, rgx)) {
        m_attributes[match.str(1)] = match.str(2);
        begin += match.position() + match.length();
    }
    return *this;
}

std::string Hrml::serialize(std::string indent) const {
    std::ostringstream oss;

    // HRML tag openner
    oss << indent << '<' << m_tagname;
    for (auto it = m_attributes.begin(); it != m_attributes.end(); ++it) {
        oss <<" " << it->first << " = \"" << it->second << "\"";
    }
    oss << '>';

    // sub HRML items
    for (auto it = m_sub_hrmls.begin(); it != m_sub_hrmls.end(); ++it) {
        oss << std::endl << it->serialize(indent + "\t");
    }

    // HRML closer
    oss << std::endl << indent << "</" << m_tagname << '>';
    return oss.str();
}

Hrml& Hrml::parse_sub_hrml(const std::string& hrmlstr) {
    std::regex rgx(R"(<(\w+?)(.*?)>([\s\S]*?)</\1>)");
    std::smatch match;
    auto begin = hrmlstr.begin(), end = hrmlstr.end();
    while (std::regex_search(begin, end, match, rgx)) {
        Hrml sub_hrml(match.str(1));
        sub_hrml.parse_attributes(match.str(2));
        sub_hrml.parse_sub_hrml(match.str(3));
        m_sub_hrmls.push_back(sub_hrml);
        begin += match.position() + match.length();
    }
    return *this;
}

Hrml& Hrml::add_sub_hrml(Hrml& hrml) {
    m_sub_hrmls.push_back(hrml);
    return *this;
}

int main(int argc, char* argv[]) {
    std::ifstream ifs(TEST_DATA_FILE);
    std::string line;
    int n = 0, q = 0;

    std::getline(ifs, line);
    sscanf(line.c_str(), "%d %d", &n, &q);

    // read hrml code string
    std::ostringstream hrmlstr(std::ostringstream::ate);
    getnlines(ifs, n, std::ostream_iterator<std::string>(hrmlstr, "\n"));

    // read queries
    std::vector<std::string> queries;
    getnlines(ifs, q, std::back_inserter(queries));

    Hrml root("root");
    root.parse_sub_hrml(hrmlstr.str());

    for (auto& query: queries) {
        std::string value;
        if (root.query(query, value) < 0) {
            std::cout << query << ": Not Found" << std::endl;
        } else {
            std::cout << query << ": " << value << std::endl;
        }
    }
    return 0;
}