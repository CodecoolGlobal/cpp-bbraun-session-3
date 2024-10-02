#include <iostream>
#include <chrono>

using namespace std;

class Correctness {
    public:
        int value;
        void inspect() const {
            cout << "Inspecting..." << endl;
        }
        void mutate() {
            cout << "Mutating..." << endl;
        }
        string const& getSecret() const {
            return secret;
        }
    private:
        string secret = "very long and secret string";
};

class Person {
public:
    Person(const std::string& name, int biologicalAge) : _name(name), _biologicalAge(biologicalAge), _lastAccessed(chrono::system_clock::now()), _lastFetched(chrono::system_clock::now()) {}

    string getName() const { return _name; }
    int getBiologicalAge() const {
        _lastAccessed = std::chrono::system_clock::now();
        const_cast<chrono::time_point<chrono::system_clock>&>(_lastFetched) = chrono::system_clock::now();
        return _biologicalAge; 
    }

    void setBiologicalAge(int biologicalAge) {
        biologicalAge = biologicalAge;
    }

private:
    string _name;
    int _biologicalAge;
    mutable std::chrono::time_point<std::chrono::system_clock> _lastAccessed;
    chrono::time_point<chrono::system_clock> _lastFetched;
};

int main() {

    // Example I.
    const Correctness a = Correctness();
    Correctness b{};
    // a = b; // error
    // a.value = 10; // error
    
    // Example II.
    Correctness c;
    c.inspect();
    c.mutate();

    Correctness& cRef = c;
    cRef.inspect();
    cRef.mutate();

    const Correctness& cConstRef = c;
    cConstRef.inspect();
    // cConstRef.mutate(); // error

    // Example III.
    Correctness d;
    // d.getSecret() = "secret string";  // error
    cout << "Secret is: " << d.getSecret() << endl;

    // Example IV.
    Person p("John", 30);
    cout << p.getName() << " is " << p.getBiologicalAge() << " years old." << endl;

    return 0;
}
