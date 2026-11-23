
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Time
{
    short h, m, s;
};

class Train
{
private:
    int number;
    Time departureTime;
    string destination;

public:
    Train() : number(0), departureTime{ 0, 0, 0 }, destination("") {}

    Train(int number, Time time, string destination)
        : number(number), departureTime(time), destination(destination) {
    }

    int getNumber() const
    {
        return number;
    }

    string getDestination() const
    {
        return destination;
    }

    Time getTime() const
    {
        return departureTime;
    }

    void setTime(Time time)
    {
        departureTime = time;
    }

    void Show() const
    {
        cout << "Number: " << number << endl;
        cout << "Departure time: "
            << setfill('0') << setw(2) << departureTime.h << ":"
            << setw(2) << departureTime.m << ":"
            << setw(2) << departureTime.s << setfill(' ') << endl;
        cout << "Destination: " << destination << endl;
        cout << "------------------------" << endl;
    }

    bool operator<(const Train& other) const
    {
        if (departureTime.h != other.departureTime.h)
            return departureTime.h < other.departureTime.h;

        if (departureTime.m != other.departureTime.m)
            return departureTime.m < other.departureTime.m;

        return departureTime.s < other.departureTime.s;
    }

    friend ostream& operator<<(ostream& out, const Train& train)
    {
        out << train.number << endl;
        out << train.departureTime.h << " "
            << train.departureTime.m << " "
            << train.departureTime.s << endl;
        out << train.destination << endl;

        return out;
    }

    friend istream& operator>>(istream& in, Train& train)
    {
        in >> train.number;
        in >> train.departureTime.h
            >> train.departureTime.m
            >> train.departureTime.s;

        in.ignore();
        getline(in, train.destination);

        return in;
    }
};

class Railway
{
private:
    vector<Train> trains;

public:
    void AddTrain()
    {
        int number;
        Time time;
        string destination;

        cout << "Enter train number: ";
        cin >> number;

        cout << "Enter departure time (h m s): ";
        cin >> time.h >> time.m >> time.s;

        if (time.h < 0 || time.h > 23 ||
            time.m < 0 || time.m > 59 ||
            time.s < 0 || time.s > 59)
        {
            cout << "Invalid time!" << endl;
            return;
        }

        for (int i = 0; i < trains.size(); i++)
        {
            if (trains[i].getNumber() == number)
            {
                cout << "Train already exists!" << endl;
                return;
            }
        }

        cin.ignore();

        cout << "Enter destination: ";
        getline(cin, destination);

        trains.push_back(Train(number, time, destination));

        cout << "Train added successfully!" << endl;
    }

    void ShowAll() const
    {
        if (trains.empty())
        {
            cout << "No trains in the system!" << endl;
            return;
        }

        for (int i = 0; i < trains.size(); i++)
        {
            trains[i].Show();
        }
    }

    void FindTrain() const
    {
        int number;

        cout << "Enter train number: ";
        cin >> number;

        for (int i = 0; i < trains.size(); i++)
        {
            if (trains[i].getNumber() == number)
            {
                trains[i].Show();
                return;
            }
        }

        cout << "Train not found!" << endl;
    }

    void EditTime()
    {
        int number;
        Time time;

        cout << "Enter train number: ";
        cin >> number;

        for (int i = 0; i < trains.size(); i++)
        {
            if (trains[i].getNumber() == number)
            {
                cout << "Enter new departure time (h m s): ";
                cin >> time.h >> time.m >> time.s;

                if (time.h < 0 || time.h > 23 ||
                    time.m < 0 || time.m > 59 ||
                    time.s < 0 || time.s > 59)
                {
                    cout << "Invalid time!" << endl;
                    return;
                }

                trains[i].setTime(time);

                cout << "Time changed successfully!" << endl;
                return;
            }
        }

        cout << "Train not found!" << endl;
    }

    void SortTrains()
    {
        sort(trains.begin(), trains.end());

        cout << "Trains sorted by departure time!" << endl;
    }

    void FindByDestination() const
    {
        string destination;
        bool found = false;

        cin.ignore();

        cout << "Enter destination: ";
        getline(cin, destination);

        for (int i = 0; i < trains.size(); i++)
        {
            if (trains[i].getDestination() == destination)
            {
                trains[i].Show();
                found = true;
            }
        }

        if (!found)
            cout << "No trains to this destination!" << endl;
    }

    void SaveToFile() const
    {
        ofstream file("trains.txt");

        if (!file)
        {
            cout << "File opening error!" << endl;
            return;
        }

        file << trains.size() << endl;

        for (int i = 0; i < trains.size(); i++)
        {
            file << trains[i];
        }

        file.close();

        cout << "Data saved successfully!" << endl;
    }

    void LoadFromFile()
    {
        ifstream file("trains.txt");

        if (!file)
        {
            cout << "File opening error!" << endl;
            return;
        }

        int count;
        file >> count;

        if (!file || count < 0)
        {
            cout << "Invalid file data!" << endl;
            return;
        }

        vector<Train> newTrains;

        for (int i = 0; i < count; i++)
        {
            Train train;

            file >> train;

            if (!file)
            {
                cout << "Error reading train data!" << endl;
                return;
            }

            newTrains.push_back(train);
        }

        trains = newTrains;

        file.close();

        cout << "Data loaded successfully!" << endl;
    }
};

int main()
{
    Railway railway;
    int choice;

    do
    {
        cout << "\n===== RAILWAY STATION =====" << endl;
        cout << "1. Add train" << endl;
        cout << "2. Show all trains" << endl;
        cout << "3. Find train by number" << endl;
        cout << "4. Edit departure time" << endl;
        cout << "5. Sort trains by departure time" << endl;
        cout << "6. Show trains by destination" << endl;
        cout << "7. Save trains to file" << endl;
        cout << "8. Load trains from file" << endl;
        cout << "0. Exit" << endl;

        cout << "Your choice: ";
        cin >> choice;

        system("cls");

        switch (choice)
        {
        case 1:
            railway.AddTrain();
            break;

        case 2:
            railway.ShowAll();
            break;

        case 3:
            railway.FindTrain();
            break;

        case 4:
            railway.EditTime();
            break;

        case 5:
            railway.SortTrains();
            break;

        case 6:
            railway.FindByDestination();
            break;

        case 7:
            railway.SaveToFile();
            break;

        case 8:
            railway.LoadFromFile();
            break;

        case 0:
            cout << "Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 0);
}
