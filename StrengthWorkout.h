//
//  StrengthWorkout.h
//  SmartGymTracker
//
//  Created by Sebastian Alvarez on 6/27/25.
//
#ifndef STRENGTHWORKOUT_H// this is a header guard to make sure it doesnt get included more than once
#define STRENGTHWORKOUT_H
#include <iostream>
#include <fstream>
#include "Workout.h"
using namespace std;

class StrengthWorkout : public Workout {
public:
    StrengthWorkout(string n, string d, string t, int s, vector<int> r, vector<float> w) : Workout(n,d,t), sets(s), multReps(r), weight(w) {}
    void logWorkout() override {
        ofstream file("workout.txt", ios::app); // ios::app is a way to append or add to file if file already exists and to not overwrite it.
        if(file.is_open()) {
            cout << "Writing to workout.txt now..." << endl;
            file << date << ", Strength Work, " << type << ", " << name << ", Sets: " << multReps.size() << "\n";
            for (int i = 0; i < sets; i++) {
                file << "Set " << (i + 1) << ": " << multReps[i] << " reps of " << weight[i] << " lbs\n";
            }
            cout << "Done writing file." << endl;
            file.close();
        }
    }
    void logWorkoutToStream(std::ostream& out) const override {
        out << date << ", Strength Work, " << type << ", " << name << ", Sets: " << multReps.size() << "\n";
        for (int i = 0; i < sets; i++) {
            out << "Set " << (i + 1) << ": " << multReps[i] << " reps of " << weight[i] << " lbs\n";
        }
    }
        // other useful ios:: are out which is default, trunc deletes all existing content, in opens just for reading, binary opens in binary mode
    void displayWorkout() const override {
        cout << date << " || " << name << " || " << type << "\n";
        for (int i = 0; i < sets; i++) {
            cout << "Set " << (i + 1) << ": " << multReps[i] << " reps of " << weight[i] << " lbs\n";
        }
    }
private:
    int sets;
    vector<float> weight;// keep in mind floats are smaller and take less memory than double 4 vs 8 bytes
    vector<int> multReps;
};
#endif //ends the if not defined code
