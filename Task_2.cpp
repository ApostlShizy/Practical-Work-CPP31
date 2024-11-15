#include <iostream>

class Toy {
    std::string name;
public:    
    Toy(std::string inName) : name(inName) {}
    Toy() : name("some name") {}
    std::string getName() {
        return name;
    }
    ~Toy() {
        std::cout << "\nToy " << name << " been droped" << std::endl;
    }
};

class shared_ptr_toy {
    int * count = nullptr;
    Toy* newToy = nullptr;
public:
    shared_ptr_toy(std::string toyName) {
        newToy = new Toy(toyName);
        count = new int (1);        
    }
    shared_ptr_toy(const shared_ptr_toy & someToy) {        
        newToy = someToy.newToy;
        count = someToy.count;
        ++*count;
    }
    shared_ptr_toy & operator = (const shared_ptr_toy & someToy) {
        if (newToy == someToy.newToy) return *this;
        if (newToy != nullptr && *count == 1)  delete newToy;
        --*count;
        newToy = someToy.newToy;
        count = someToy.count;
        ++*count;
        return *this;
    }
    void reset() {
        if (*count == 1) delete newToy;
        --*count;
        count = nullptr;
        newToy = nullptr;
    }
    Toy* get() const {
        return newToy;
    }
    int use_count() {
        if (count == nullptr) return 0;
        return *count;
    }
    std::string getToyName() {
        if (newToy == nullptr) return "nothing";
        return newToy->getName();
    }
    ~shared_ptr_toy() {        
        if (count != nullptr) --*count;
        if (count != nullptr && *count == 0) {
            delete count;
            delete newToy;                
        }
    }
};

shared_ptr_toy make_shared_toy(std::string toyName) {
    shared_ptr_toy tempToy (toyName);       
    return tempToy;
}

int main() {
    shared_ptr_toy toy_01 = make_shared_toy ("ball");
    shared_ptr_toy toy_02 (toy_01);
    shared_ptr_toy toy_03 ("duck");     

    std::cout << "=================================================" << std::endl;

    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "<< toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
        << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;

    std::cout << "=================================================" << std::endl;

    toy_02 = toy_03;

    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  " << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
        << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;

    std::cout << "=================================================" << std::endl;

    toy_01.reset();

    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "<< toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
        << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;

    std::cout << "=================================================" << std::endl;

    return 0;
}