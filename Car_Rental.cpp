#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Vehicle class representing a vehicle
class Vehicle {
private:
    string make;
    string model;
    float pricePerDay;
    float pricePerHour;

public:
    Vehicle(string _make, string _model, float _pricePerDay, float _pricePerHour)
        : make(_make), model(_model), pricePerDay(_pricePerDay), pricePerHour(_pricePerHour) {}

    void displayDetails() {
        cout << "Maker: " << make << ", Model: " << model << endl;
    }

    float getPricePerDay() const { return pricePerDay; }
    float getPricePerHour() const { return pricePerHour; }

    // Getter functions to access protected members
    string getMake() const { return make; }
    string getModel() const { return model; }

    // Functions to modify price
    void setPricePerDay(float _pricePerDay) { pricePerDay = _pricePerDay; }
    void setPricePerHour(float _pricePerHour) { pricePerHour = _pricePerHour; }
};

// Booking class to store booking details
class Booking {
private:
    string name;
    int age;
    string vehicleMake;
    string vehicleModel;
    string rentType;
    float totalPrice;

public:
    Booking(string _name, int _age, string _vehicleMake, string _vehicleModel, string _rentType, float _totalPrice)
        : name(_name), age(_age), vehicleMake(_vehicleMake), vehicleModel(_vehicleModel), rentType(_rentType), totalPrice(_totalPrice) {}

    void displayBookingDetails() {
        cout << "Name: " << name << ", Age: " << age << ", Vehicle: " << vehicleMake << " " << vehicleModel
             << ", Rental Type: " << rentType << ", Total Price: $" << totalPrice << endl;
    }
};

// RentalSystem class managing vehicles and rentals
class RentalSystem {
private:
    vector<Vehicle*> vehicles; // Using vector to store vehicles
    vector<Booking*> bookings; // Using vector to store booking details

public:
    ~RentalSystem() {
        for (size_t i = 0; i < vehicles.size(); ++i) {
            delete vehicles[i];
        }
        for (size_t i = 0; i < bookings.size(); ++i) {
            delete bookings[i];
        }
    }

    void displayAvailableCars() {
        cout << "Available Cars: " << endl;
        for (size_t i = 0; i < vehicles.size(); ++i) {
            cout << i + 1 << ". ";
            vehicles[i]->displayDetails();
        }
    }

    void displayRentalPrice(int carIndex) {
        if (carIndex < 1 || carIndex > vehicles.size()) {
            cout << "Invalid car selection!" << endl;
            return;
        }

        cout << "Rental Price Details for Car " << carIndex << ": " << endl;
        cout << "Price per day: $" << vehicles[carIndex - 1]->getPricePerDay() << endl;
        cout << "Price per hour: $" << vehicles[carIndex - 1]->getPricePerHour() << endl;

        string bookChoice;
        cout << "Would you like to book this car? (Type 'yes' to confirm): ";
        cin >> bookChoice;
        if (bookChoice == "yes") {
            string name;
            int age;
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter your age: ";
            cin >> age;

            string rentType;
            cout << "Enter rental type (hour/day): ";
            cin >> rentType;

            float totalPrice = 0.0;
            if (rentType == "hour") {
                int hours;
                cout << "Enter number of hours: ";
                cin >> hours;
                totalPrice = vehicles[carIndex - 1]->getPricePerHour() * hours;
            } else if (rentType == "day") {
                int days;
                cout << "Enter number of days: ";
                cin >> days;
                totalPrice = vehicles[carIndex - 1]->getPricePerDay() * days;
            } else {
                cout << "Invalid rental type!" << endl;
                return;
            }

            cout << "Total Price: $" << totalPrice << endl;

            string confirmBooking;
            cout << "Confirm booking? (Type 'book' to confirm): ";
            cin >> confirmBooking;
            if (confirmBooking == "book") {
                bookings.push_back(new Booking(name, age, vehicles[carIndex - 1]->getMake(), vehicles[carIndex - 1]->getModel(), rentType, totalPrice));
                cout << "Booking confirmed! Thank you for choosing our service." << endl;
                return; // Exit function after booking confirmed
            }
        }
    }

    void displayBookings() {
        cout << "Booking Details: " << endl;
        for (size_t i = 0; i < bookings.size(); ++i) {
            cout << "Booking " << i + 1 << ": ";
            bookings[i]->displayBookingDetails();
        }
    }

    // Public getter function for vehicles vector
    vector<Vehicle*>& getVehicles() {
        return vehicles;
    }

    void addCar(const Vehicle& vehicle) {
        vehicles.push_back(new Vehicle(vehicle));
    }

    void removeCar(int carIndex) {
        if (carIndex < 1 || carIndex > vehicles.size()) {
            cout << "Invalid car index!" << endl;
            return;
        }
        delete vehicles[carIndex - 1];
        vehicles.erase(vehicles.begin() + carIndex - 1);
        cout << "Car removed successfully!" << endl;
    }

    void modifyCarPrice(int carIndex, float newPricePerDay, float newPricePerHour) {
        if (carIndex < 1 || carIndex > vehicles.size()) {
            cout << "Invalid car index!" << endl;
            return;
        }
        vehicles[carIndex - 1]->setPricePerDay(newPricePerDay);
        vehicles[carIndex - 1]->setPricePerHour(newPricePerHour);
        cout << "Car price modified successfully!" << endl;
    }
};

int main() {
    RentalSystem rentalSystem;

    // Adding 10 cars
    rentalSystem.addCar(Vehicle("Toyota", "Corolla", 50.0, 5.0));
    rentalSystem.addCar(Vehicle("Honda", "Civic", 60.0, 6.0));
    rentalSystem.addCar(Vehicle("Ford", "Fusion", 70.0, 7.0));
    rentalSystem.addCar(Vehicle("Chevrolet", "Malibu", 65.0, 6.5));
    rentalSystem.addCar(Vehicle("BMW", "X3", 100.0, 10.0));
    rentalSystem.addCar(Vehicle("Tesla", "Model 3", 120.0, 12.0));
    rentalSystem.addCar(Vehicle("Mercedes-Benz", "C-Class", 90.0, 9.0));
    rentalSystem.addCar(Vehicle("Audi", "A4", 95.0, 9.5));
    rentalSystem.addCar(Vehicle("Lexus", "RX", 110.0, 11.0));
    rentalSystem.addCar(Vehicle("Subaru", "Outback", 80.0, 8.0));

    int userChoice;
    cout << "Rental System Menu" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Customer" << endl;
    cout << "3. Quit" << endl;

    do {
        cout << "Enter your choice: ";
        cin >> userChoice;

        switch (userChoice) {
            case 1:
                // Admin menu
                cout << endl; // Add space before printing admin options
                cout << "Admin Menu" << endl;
                cout << "1. Access Rental Records" << endl;
                cout << "2. Check Car Details" << endl;
                cout << "3. Add Car" << endl;
                cout << "4. Remove Car" << endl;
                cout << "5. Modify Car Price" << endl;
                cout << "6. Exit" << endl;

                int adminChoice;
                cout << "Enter your choice: ";
                cin >> adminChoice;
                switch (adminChoice) {
                    case 1:
                        rentalSystem.displayBookings();
                        break;
                    case 2:
                        rentalSystem.displayAvailableCars();
                        break;
                    case 3:
                        {
                            string make, model;
                            float pricePerDay, pricePerHour;
                            cout << "Enter car make: ";
                            cin >> make;
                            cout << "Enter car model: ";
                            cin.ignore();
                            getline(cin, model);
                            cout << "Enter price per day: ";
                            cin >> pricePerDay;
                            cout << "Enter price per hour: ";
                            cin >> pricePerHour;
                            rentalSystem.addCar(Vehicle(make, model, pricePerDay, pricePerHour));
                            cout << "Car added successfully!" << endl;
                        }
                        break;
                    case 4:
                        int removeIndex;
                        cout << "Enter index of car to remove: ";
                        cin >> removeIndex;
                        rentalSystem.removeCar(removeIndex);
                        break;
                    case 5:
                        int modifyIndex;
                        float newPricePerDay, newPricePerHour;
                        cout << "Enter index of car to modify: ";
                        cin >> modifyIndex;
                        cout << "Enter new price per day: ";
                        cin >> newPricePerDay;
                        cout << "Enter new price per hour: ";
                        cin >> newPricePerHour;
                        rentalSystem.modifyCarPrice(modifyIndex, newPricePerDay, newPricePerHour);
                        break;
                    case 6:
                        cout << "Exiting admin menu..." << endl;
                        break;
                    default:
                        cout << "Invalid choice! Please try again." << endl;
                }
                break;
            case 2:
                int carIndex;
                do {
                    rentalSystem.displayAvailableCars();
                    cout << "Select a car to check rental price details (enter car number), or enter 0 to go back to the main menu: ";
                    cin >> carIndex;

                    if (carIndex == 0) {
                        break;
                    } else if (carIndex >= 1 && carIndex <= rentalSystem.getVehicles().size()) {
                        rentalSystem.displayRentalPrice(carIndex);
                    } else {
                        cout << "Invalid car selection!" << endl;
                    }
                } while (true);
                break;
            case 3:
                cout << "Exiting rental system..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (userChoice != 3);

    rentalSystem.displayBookings();
    return 0;
}