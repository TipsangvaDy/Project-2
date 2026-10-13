/*
   STUDENT NAME: ___________________
   CS 2414 Project 2 – RadioLane-Stitch
   Before submitting, add a 1-sentence description of what each method does.
*/

#include <iostream>
#include <string>
using namespace std;

class Burst {
	// DO NOT change this class
public:
    int id;
    int src;
    int len;
    Burst* next;

    Burst(int i, int s, int n) {
        id = i;
        src = s;
        len = n;
        next = nullptr;
    }
};

class RadioLane {
protected:
    Burst* _head;   // keep this pointer
    Burst* _last;   // keep this pointer which points to the last node in this lane; not a backward link
    int    _count;  // keep this variable to track the size of the radio lane
	
	// TODO: you can can more methods, do not change the exisiting method signatures
	// implement all methods outside the class definition

public:
	// implement all methods outside the class definition
    RadioLane();
    ~RadioLane();

    int size() const;
	
	// TODO Print id:src:len tokens, one space between them, no trailing space.
    // Empty lane prints (empty).
	void displayLane() const;

    // TODO: See PDF page 1 about "load" requirements
    void loadLane(int n);

	// TODO: See PDF page 1 about "stitch" requirements. 
    // Hint: reuse existing nodes; other must be empty after.
    void stitch(RadioLane& other);

    // TODO: See PDF section "PART C Collapse adjacent same-source runs"
    void collapse();

    // TODO: See PDF Illustrative Example "PART D Extract one device (X)"
    void extract(int srcId);

	// TODO: See PDF Illustrative Example "PART E Rewind (R)"
	// Must be iterative, not recursive.
    void rewind();
	
	// TODO: you can can more methods, do not change the exisiting method signatures
	// implement all methods outside the class definition
};


RadioLane::RadioLane() {
}

RadioLane::~RadioLane() {
}

int RadioLane::size() const {
}

void RadioLane::loadLane(int n) {
}

void RadioLane::stitch(RadioLane& other) {
}

void RadioLane::collapse() {
}

void RadioLane::displayLane() const {
}

void RadioLane::extract(int srcId) {
}

void RadioLane::rewind() {
}

int main() {
	// Do not modify main
    int nA, nB;
    cin >> nA >> nB;

    RadioLane radioA;
    RadioLane radioB;

    radioA.loadLane(nA);
    radioB.loadLane(nB);

    radioA.stitch(radioB);
    radioA.collapse();

    cout << "Stitched and collapsed:" << endl;
    radioA.displayLane();

    char cmd;
    int srcId;
    cin >> cmd >> srcId;   // X src
    radioA.extract(srcId);

    cin >> cmd;            // R
    radioA.rewind();
    cout << "Rewound lane:" << endl;
    radioA.displayLane();

    return 0;
}
