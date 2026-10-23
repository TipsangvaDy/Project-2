/*
   STUDENT NAME: ___Tipsangva Dy_________
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

// Initializes an empty radio lane with no nodes and a size of zero.
RadioLane::RadioLane() {
	_head = nullptr;
    _last = nullptr;
    _count = 0;
}

// Deletes all nodes remaining in the radio lane to free memory.
RadioLane::~RadioLane() {
	Burst* current = _head;

    while (current != nullptr) {
		Burst* nextNode = current->next;
		delete current;
		current = nextNode;
	}
}

// Returns the number of bursts currently in the radio lane.
int RadioLane::size() const {
	return _count;
}

// Reads n bursts from input and appends them to the radio lane.
void RadioLane::loadLane(int n) {
    for (int i = 0; i < n; i++) {
        int id, src, len;
        cin >> id >> src >> len;

        Burst* newNode = new Burst(id, src, len);

        if (_head == nullptr) {
            _head = newNode;
            _last = newNode;
        } else {
            _last->next = newNode;
            _last = newNode;
        }

        _count++;
    }
}

// Alternates bursts from two lanes, reuses existing nodes, and empties the other lane.
void RadioLane::stitch(RadioLane& other) {
    if (other._head == nullptr) {
        return;
    }

    if (_head == nullptr) {
        _head = other._head;
        _last = other._last;
        _count = other._count;

        other._head = nullptr;
        other._last = nullptr;
        other._count = 0;
        return;
    }

    Burst* currentA = _head;
    Burst* currentB = other._head;
	Burst* originalLastA = _last;
	
    Burst* lastLinked = nullptr;

    while (currentA != nullptr && currentB != nullptr) {
        Burst* nextA = currentA->next;
        Burst* nextB = currentB->next;

        currentA->next = currentB;
        currentB->next = nextA;

        lastLinked = currentB;
        currentA = nextA;
        currentB = nextB;
    }

        if (currentB != nullptr) {
        lastLinked->next = currentB;
        _last = other._last;
    } else if (currentA != nullptr) {
        _last = originalLastA;
    } else {
        _last = other._last;
    }

    _count += other._count;

    other._head = nullptr;
    other._last = nullptr;
    other._count = 0;
}

// Combines adjacent bursts with the same source by adding their lengths and deleting extra nodes.
void RadioLane::collapse() {
    Burst* current = _head;

    while (current != nullptr && current->next != nullptr) {
        if (current->src == current->next->src) {
            Burst* swallowed = current->next;

            current->len += swallowed->len;
            current->next = swallowed->next;

            if (swallowed == _last) {
                _last = current;
            }

            delete swallowed;
            _count--;
        } else {
            current = current->next;
        }
    }
}

// Prints all bursts in id:src:len format separated by single spaces.
void RadioLane::displayLane() const {
    if (_head == nullptr) {
        cout << "(empty)" << endl;
        return;
    }

    Burst* current = _head;
    bool first = true;

    while (current != nullptr) {
        if (!first) {
            cout << " ";
        }

        cout << current->id << ":" << current->src << ":" << current->len;

        first = false;
        current = current->next;
    }

    cout << endl;
}

// Prints and deletes every burst matching srcId, then prints the remaining lane.
void RadioLane::extract(int srcId) {
    cout << "Extracted bursts:" << endl;

    Burst* current = _head;
    Burst* previous = nullptr;
    bool found = false;
	bool first = true;

    while (current != nullptr) {
        if (current->src == srcId) {
            found = true;
            Burst* removed = current;
            current = current->next;

            if (previous == nullptr) {
                _head = current;
            } else {
                previous->next = current;
            }

            if (removed == _last) {
                _last = previous;
            }

            if (!first) {
                cout << " ";
            }

            cout << removed->id << ":" << removed->src
                 << ":" << removed->len;

            first = false;

            delete removed;
            _count--;
        } else {
            previous = current;
            current = current->next;
        }
    }

    cout << endl;

    if (!found) {
        cout << "(empty)" << endl;
    
    }

    if (_head == nullptr) {
        _last = nullptr;
    }

    cout << "Remaining lane:" << endl;
    displayLane();
}

// Reverses the radio lane in place using an iterative linked-list traversal.
void RadioLane::rewind() {
    Burst* previous = nullptr;
    Burst* current = _head;

    _last = _head;

    while (current != nullptr) {
        Burst* nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }

    _head = previous;
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
