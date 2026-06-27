//
//  Workout.h
//  SmartGymTracker
//
//  Created by Sebastian Alvarez on 6/27/25.
//
#ifndef WORKOUT_H
#define WORKOUT_H
#include <string>
#include <fstream>
using namespace std;

class Workout {

    public:
        Workout(string n, string d, string t) : name(n), date(d), type(t) {}; // constructor for workout object takes in name, date, and type
        virtual void logWorkout() = 0; //abstract function must be implemented in concrete class
        virtual void displayWorkout() const = 0; //abstract function
        virtual void logWorkoutToStream(std::ostream& out) const = 0; //logworkouts again after deleting a workout without having to use logWorkout every time.
        virtual ~Workout(){} //destructor
    protected:
        string name;
        string date;
        string type;
};
#endif
