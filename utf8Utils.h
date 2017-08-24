#ifndef utf8Utils
#define utf8Utils
int utf8len(std::string str);
std::string utf8substr(std::string str, int start, int desiredLength);
int charPoint(std::string u);
void appendUnicode(std::string &str, int c);
#endif
