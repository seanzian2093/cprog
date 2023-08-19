// Make a point from x and y components
#include <stdio.h>
#define XMAX 200
#define YMAX 200

// Define a struct with tag point
struct point {
    int x;
    int y;
};

// Define a struct with tag rect
struct rect {
    struct point pt1;
    struct point pt2;
};

// Define a function returns a struct of point
// Can be used to initialize any struct dynamically or to provide struct arg to functions.
struct point makepoint(int x, int y);

// Add two points return a point
struct point addpoint(struct point p1, struct point p2);

// Test whether a point is inside a rectangle, return 1 if yes, 0 if not
int ptinrect (struct point p, struct rect r);

int main(void)
{
    struct rect screen;
    struct point middle;

    screen.pt1 = makepoint(0, 0);
    screen.pt2 = makepoint(XMAX, YMAX);
    middle = makepoint(
        (screen.pt1.x + screen.pt2.x)/2,
        (screen.pt1.y + screen.pt2.y)/2);
    
    printf("Middle point is(%d, %d)\n", middle.x, middle.y);

    struct point *pp = &middle;
    struct rect *rp = &screen;
    // pp is a pointer which points at a struct
    // so *pp is a struct and can be used as a struct.
    printf("origin is (%d, %d)\n", (*pp).x, (*pp).y);
    // shorthand 
    printf("origin is (%d, %d)\n", pp->x, pp->y);

    // for nested struct
    printf("x coordinates of rect is (%d, %d)\n", screen.pt1.x, rp->pt2.x);
    printf("y coordinates of rect is (%d, %d)\n", (screen.pt1).y, (rp->pt2).y);

}

struct point makepoint(int x, int y)
{
    struct point temp;

    temp.x = x;
    temp.y = y;
    return temp;
}

struct point addpoint (struct point p1, struct point p2)
{
    p1.x += p2.x;
    p1.y += p2.y;
    // struct parameters are passed by value so no need to use a temp variable
    return p1;
}

int ptinrect (struct point p, struct rect r)
{
    return p.x >= r.pt1.x &&  p.x < r.pt2.x
        && p.y >= r.pt1.y &&  p.y < r.pt2.y;
}