#include <iostream>
#include <vector>

class Toy {
    std::string toyName;
public:
    Toy() : toyName("some toy") {}
    Toy(std::string inToyName) : toyName(inToyName) {}
    std::string getToyName() {
        return toyName;
    }
    ~Toy() {
        std::cout << "\nToy " << toyName << " was dropped" << std::endl;
    }
};

class Dog {
    std::string name;
    std::shared_ptr<Toy> takenToy;
public:
    Dog(std::string inName) : name(inName) {}
    Dog() : Dog("Bobik") {}

    std::string getName() {
        return name;
    }

    void takeToy(std::shared_ptr<Toy> someToy) {
        if (takenToy == someToy) {
            std::cout << "\nI already have this toy " << std::endl;
            return;
        }
        if (someToy.use_count() > 2) {
            std::cout << "\nAnother dog is playing with this toy." << std::endl;
            return;
        }
        takenToy = someToy;
        std::cout << name << " dog take " << someToy->getToyName() << std::endl;
    }
    void dropToy() {
        if (takenToy == nullptr) {
            std::cout << "\nNothing to drop" << std::endl;
            return;
        }
        std::cout << "\nDog " << name << " live " << takenToy->getToyName() << " on floor" << std::endl;
        takenToy.reset();
    }
};

std::vector<Dog>::iterator findDog(std::vector<Dog>& dogs, std::string dogName) {
    for (auto iter = dogs.begin(); iter != dogs.end(); ++iter) {
        if (iter->getName() == dogName) {
            return iter;
        }
    }
    std::cout << "\nWrong dog name " << std::endl;
    return dogs.end();
}


int main() {
    std::vector<Dog> dogs;
    dogs.emplace_back("sharick");
    dogs.emplace_back("bobik");
    dogs.emplace_back("barbos");
    std::shared_ptr<Toy> boll = std::make_shared<Toy>("boll");
    std::string choice;
    while (choice != "exit") {
        std::cout << "\nDogs name : ";
        for (int i = 0; i < dogs.size(); ++i) {
            std::cout << dogs[i].getName() << "   ";
        }
        std::cout << "\nEnter dog name or \"exit\"  : ";
        std::cin >> choice;
        if (choice != "exit") {
            auto iter = findDog(dogs, choice);
            if (iter != dogs.end()) {
                std::cout << "\nWhat dog do \"drop\" \"take\" : ";
                std::cin >> choice;
                if (choice == "take") {
                    iter->takeToy(boll);
                }
                else if (choice == "drop") {
                    iter->dropToy();
                }
                else {
                    std::cout << "\nInvalid option" << std::endl;
                }
            }
        }
    }
}