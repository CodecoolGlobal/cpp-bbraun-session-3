#include <string>
#include <iostream>

using namespace std;

class Document {
public:
    Document(string content) : content(content) {};
    string &findAndReplace(string &find, string &replace) {
        unsigned long long pos = 0;
        while ((pos = content.find(find, pos)) != string::npos) {
            content.replace(pos, find.length(), replace);
            pos += replace.length();
        }
        return content;
    }

    string *findContext(string &word, unsigned short contextLength) {
        unsigned long long pos = content.find(word);
        if (pos != string::npos) {
            unsigned long long start = pos > contextLength ? pos - contextLength : 0;
            unsigned long long end = pos + word.length() + contextLength;
            return new string("..." + content.substr(start, end - start) + "..."); 
        }
        return nullptr;
    }

    string& getContent() {
        return content;
    }
private:
    string content;
};

int main()
{
    // Example I.
    Document doc{
        R"(
        Note also that a call of a member function is essentially **a call-by-reference on the object**,
        so we often use member functions when we want to modify the value/state of an object.
        In the this example we can directly access and modify the `content` member variable within the function 
        because member functions implicitly receive a reference to the object, enabling direct modifications.
        )"};

    cout << doc.getContent() << endl;

    string find = "reference";
    string replace = "alias";

    // string content = doc.findAndReplace(find, replace) = "...empty...";
    string content = doc.findAndReplace(find, replace);
    cout << content << endl;

    // Example II.
    string word = "alias";
    string* result = doc.findContext(word, 10);
    if (result != nullptr) {
        cout << *result << endl;
        delete result;
    }

    return 0;
}