#include<iostream>

class Toy {
    std::string toyName;
public:
    Toy(std::string inToyName) : toyName(inToyName) {}
    Toy() : toyName("some toy") {}
    auto getToyName() {
        return toyName;
    }
    ~Toy() {
        std::cout << "\nToy " << toyName << " was droped" << std::endl;
    }
};

class Dog {
private:
    std::shared_ptr<Toy> hisToy = nullptr;
    std::string dogName;
public:
    Dog(std::string inDogName, std::shared_ptr<Toy> inToyName) : dogName(inDogName), hisToy(inToyName) {}
    Dog() : dogName("some name"), hisToy(std::make_shared<Toy>()) {}
    Dog(std::string inDogName) : dogName(inDogName), hisToy(nullptr) {}
    void getToy(std::shared_ptr<Toy> otherToy) {
        if (otherToy == hisToy) {
            std::cout << "\nI alredy have this toy" << std::endl;
            return;
        }
        if (otherToy.use_count() > 2) {
            std::cout << "\nSome one alrydy play with this toy" << std::endl;
            return;
        }
        std::cout << "\nDog " << dogName << " take the toy" << std::endl;
        hisToy = otherToy;
    }
    void dropToy() {
        if (hisToy == nullptr) {
            std::cout << "\nNothing to drop" << std::endl;
            return;
        }
        std::cout << "\nDog " << dogName << " drop toy " << std::endl;
        hisToy.reset();
    }
    auto getDogName() {
        return dogName;
    }
    auto getDogToy() {
        return hisToy;
    }
};

int main() {
    Dog* dogs[3];
    std::shared_ptr<Toy> Ball = std::make_shared<Toy>("Ball");
    dogs[0] = new Dog("Sharik");
    dogs[1] = new Dog("Boboik");
    dogs[2] = new Dog("Simon");
    std::string choice;
    while (choice != "exit") {
        std::cout << "\nDogs names : " << std::endl;
        for (auto& current : dogs) {
            std::cout << current->getDogName();
            if (current->getDogToy() != nullptr) {
                std::cout <<" hold toy : " << current->getDogToy()->getToyName();
            }
            std::cout << std::endl;
        }
        std::cout << "\nEnter dog name : ";
        std::cin >> choice;
        if (choice != "exit") {
            Dog* chosenDog = nullptr;
            for (int i = 0; i < 3; ++i) {
                if (choice == dogs[i]->getDogName()) {
                    chosenDog = dogs[i];
                    break;
                }
            }
            if (chosenDog != nullptr) {
                std::cout << "\nWhat dog need to do (get/drop) : ";
                std::cin >> choice;
                if (choice == "get") {
                    chosenDog->getToy(Ball);
                }
                else if (choice == "drop") {
                    chosenDog->dropToy();
                }
            }
        }
    }
}