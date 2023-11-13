#include <iostream>
#include <cmath> // For calculating distance in case of nuclear warhead
#include <ctime>   // For seeding the random number generator


using namespace std;

typedef struct Position
{
    int x;
    int y;
    void print()
    {
        cout << "[ x: " << x << " ]" << "[ y: " << y << " ]" << endl;
		cout<<::endl;
    }
} Coordinates;

enum WarHead
{
    EXPLOSIVE,
    NUCLEAR
};

typedef struct Enemy
{
    Coordinates coordinates;
} Target;

struct Missile
{
    WarHead payload;
    Coordinates coordinates;
    Target target;

    bool armed;

    void arm()
    {
        if (armed)
            armed = false;
        else
            armed = true;
    }

    void update()
    {
        coordinates.x += 1;
        coordinates.y += 2;
    }
    
// Function to check if the missile hits the target
bool checkHit()
{
    if (payload == WarHead::NUCLEAR)
    {
        // Check if the missile coordinates are within a radius of 2 tiles of the target coordinates
        int distance = sqrt(pow(coordinates.x - target.coordinates.x, 2) + pow(coordinates.y - target.coordinates.y, 2));
        return (distance <= 2); 
    }
    else if (payload == WarHead::EXPLOSIVE)
    {
        // Check if the missile coordinates are within a radius of 1 tile of the target coordinates
        int distance = sqrt(pow(coordinates.x - target.coordinates.x, 2) + pow(coordinates.y - target.coordinates.y, 2));
        return (distance <= 1); // You can adjust the radius as needed
    }

    return false; // Default
}

};

int main()
{
    // Seed the random generator with  current time
    srand(static_cast<unsigned>(time(0)));

    // Create a new Enemy
    Enemy *e = new Enemy();

    // Set Enemy Position / Target
        e->coordinates.x = rand() % 10; 
        e->coordinates.y = rand() % 10; 

    // Print Enemy Position
    cout << "Print Enemy Position" << endl;
    e->coordinates.print();

    // Create a new Missile
    Missile *m = new Missile();

    // Set Missile Payload
    cout << "Select Warhead (0 for EXPLOSIVE, 1 for NUCLEAR): ";
    int warheadChoice;
    cin >> warheadChoice;

	if( warheadChoice == 1)
	{
		m->payload = WarHead::NUCLEAR;
		cout << "You have chosen the nuclear option, I hope it was worth it." << endl;
		cout<<endl;
	}
	else if(warheadChoice == 0)
	{
		m->payload = WarHead::EXPLOSIVE;
		cout << "You have chosen the basic explosive option" <<endl;
		cout<<endl;
	}
	else
	{
		cout << "Invalid Input code, please try again:	" <<endl;
		cin >> warheadChoice;
		cout<<endl;
	}
		
    // Set Missile Target by dereferencing Enemy pointer
    m->target = *e;

    // Game loop
    while (!m->checkHit())
    {
        // Set Initial Position
        cout << "Enter Missile Coordinates (x y): ";
        cin >> m->coordinates.x >> m->coordinates.y;

        // Print Position
        cout << "Print Missile Position" << endl;
        m->coordinates.print();

        // Update Position
        m->update();

        // Print Missile Position after an Update
        cout << "Print Missile Position after an Update" << endl;
        m->coordinates.print();

        // Print Missile target
        cout << "Print Missile Target Position" << endl;
        m->target.coordinates.print();
    }

    // Inform the player whether the missile hit the enemy or not
    if (m->checkHit() == true)
    {
        cout << "Missile hit the enemy! Enemy Destroyed!" << endl;
    }
    else
    {
        cout << "Missile missed the enemy. Try again!" << endl;
    }

    // Deallocate memory
    delete e;
    delete m;

    cin.get();
    return 0;
}
