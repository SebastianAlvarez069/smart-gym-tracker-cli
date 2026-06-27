//
//  main.cpp
//  SmartGymTracker
//
//  Created by Sebastian Alvarez on 6/27/25.
//

#include <iostream>
#include <ctime>
#include <string>
#include "StrengthWorkout.h"
#include "GymTracker.h"

using namespace std;

string getTodaysDate() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char time[11];
    strftime(time, sizeof(time), "%Y-%m-%d", now);
    return string(time);
}

int main() {
    GymTracker tracker;
    
    tracker.loadFromFile();
    
    cout << "Welcome to Smart Gym Tracker CLI!\n";
    while (true) {
        cout << "1. Log a Strength Workout\n2. View History\n3. Delete Workout\n4. Exit\nChoose option: ";
        
        int choice;
        cin >> choice;
        
        if(choice == 1) {
            string n, t;
            int s, r;
            float w;
            cout << "Enter workout name (e.g. Bench Press): ";
            cin.ignore();
            getline(cin, n);
            cout << "Enter workout type (e.g. Push, Pull, Legs): ";
            getline(cin, t);
            cout << "Enter # of Sets: ";
            cin >> s;
            
            vector<int> multReps;
            vector<float> weight;
            for(int i = 0; i < s; i++) {
                cout << "Enter # of Reps for Set " << (i+1) << ": ";
                cin >> r;
                multReps.push_back(r);
                cout << "Enter weight used: ";
                cin >> w;
                weight.push_back(w);
            }
            auto work = make_unique<StrengthWorkout>(n, getTodaysDate(), t, s, multReps, weight);
            tracker.addWorkout(std::move(work));
        } else if (choice == 2) {
            cout << "\nDisplaying all workouts...\n\n";
            tracker.displayAllWorkouts();
        } else if (choice == 3) {
            int idToDelete;
            cout << "\nWorkout ID to delete: \n";
            cin >> idToDelete;
            tracker.deleteWorkout(idToDelete);
        } else if (choice == 4) {
            cout << "\nThanks for using Smart Gym Tracker CLI. See you next session!\n";
            break;
        } else {
            cout << "Invalid Option.\n";
        }
    }
    return 0;
}
