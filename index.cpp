#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Reservation {
public:
    int roomNumber;
    string guestName;
    int numDays;
    string checkInDate;

    void input() {
        cout << "\nEnter Room Number: ";
        cin >> roomNumber;
        cin.ignore();
        cout << "Enter Guest Name: ";
        getline(cin, guestName);
        cout << "Enter Check-in Date (dd-mm-yyyy): ";
        getline(cin, checkInDate);
        cout << "Enter Number of Days: ";
        cin >> numDays;
    }

    void display() {
        cout << "\nRoom Number: " << roomNumber
             << "\nGuest Name: " << guestName
             << "\nCheck-in Date: " << checkInDate
             << "\nNumber of Days: " << numDays << "\n";
    }
};

// Add reservation
void addReservation() {
    Reservation r;
    ofstream file("reservations.txt", ios::app | ios::binary);
    r.input();
    file.write((char*)&r, sizeof(r));
    file.close();
    cout << "Reservation added successfully!\n";
}

// View all reservations
void viewReservations() {
    Reservation r;
    ifstream file("reservations.txt", ios::binary);
    bool found = false;
    while (file.read((char*)&r, sizeof(r))) {
        r.display();
        found = true;
    }
    file.close();
    if (!found)
        cout << "No reservations found.\n";
}

// Search reservation
void searchReservation(int roomNo) {
    Reservation r;
    ifstream file("reservations.txt", ios::binary);
    bool found = false;
    while (file.read((char*)&r, sizeof(r))) {
        if (r.roomNumber == roomNo) {
            cout << "Reservation Found:\n";
            r.display();
            found = true;
            break;
        }
    }
    file.close();
    if (!found)
        cout << "No reservation found for Room Number " << roomNo << ".\n";
}

// Delete reservation
void deleteReservation(int roomNo) {
    Reservation r;
    ifstream file("reservations.txt", ios::binary);
    ofstream temp("temp.txt", ios::binary);
    bool found = false;

    while (file.read((char*)&r, sizeof(r))) {
        if (r.roomNumber == roomNo) {
            found = true;
            continue; // Skip this one
        }
        temp.write((char*)&r, sizeof(r));
    }

    file.close();
    temp.close();
    remove("reservations.txt");
    rename("temp.txt", "reservations.txt");

    if (found)
        cout << "Reservation deleted successfully.\n";
    else
        cout << "Room number not found.\n";
}

int main() {
    int choice, roomNo;

    do {
        cout << "\n======= Hotel Reservation System =======";
        cout << "\n1. Add Reservation";
        cout << "\n2. View All Reservations";
        cout << "\n3. Search Reservation";
        cout << "\n4. Delete Reservation";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addReservation();
                break;
            case 2:
                viewReservations();
                break;
            case 3:
                cout << "Enter Room Number to search: ";
                cin >> roomNo;
                searchReservation(roomNo);
                break;
            case 4:
                cout << "Enter Room Number to delete: ";
                cin >> roomNo;
                deleteReservation(roomNo);
                break;
            case 5:
                cout << "Thank you for using Hotel Reservation System!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
