#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 20
#define COLS 40
#define MAX_OBJECTS 100

char canvas[ROWS][COLS];

typedef enum
{
    RECTANGLE,
    LINE,
    TRIANGLE,
    CIRCLE
} ShapeType;

typedef struct
{
    int id;
    ShapeType type;

    int x1, y1;
    int x2, y2;
    int x3, y3;

    int width;
    int height;

    int radius;
} Shape;

Shape objects[MAX_OBJECTS];

int objectCount = 0;
int nextID = 1;

/* ================= CANVAS ================= */

void initializeCanvas()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    printf("\n");

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");
    }
}

/* ================= DRAW RECTANGLE ================= */

void drawRectangle(int row, int col, int height, int width)
{
    for(int i = row; i < row + height && i < ROWS; i++)
    {
        for(int j = col; j < col + width && j < COLS; j++)
        {
            if(i >= 0 && j >= 0)
            {
                canvas[i][j] = '*';
            }
        }
    }
}

/* ================= DRAW LINE ================= */

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(1)
    {
        if(x1 >= 0 && x1 < ROWS &&
           y1 >= 0 && y1 < COLS)
        {
            canvas[x1][y1] = '*';
        }

        if(x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if(e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if(e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

/* ================= DRAW TRIANGLE ================= */

void drawTriangle(int x1, int y1,
                  int x2, int y2,
                  int x3, int y3)
{
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

/* ================= DRAW CIRCLE ================= */

void drawCircle(int centerRow, int centerCol, int radius)
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            int d =
                (i - centerRow) * (i - centerRow) +
                (j - centerCol) * (j - centerCol);

            int r2 = radius * radius;

            if(abs(d - r2) <= radius)
            {
                canvas[i][j] = '*';
            }
        }
    }
}

/* ================= DISPLAY OBJECTS ================= */

void displayObjects()
{
    printf("\n========== OBJECT LIST ==========\n");

    if(objectCount == 0)
    {
        printf("No objects available.\n");
        return;
    }

    for(int i = 0; i < objectCount; i++)
    {
        printf("ID: %d | ", objects[i].id);

        switch(objects[i].type)
        {
            case RECTANGLE:
                printf("Rectangle");
                break;

            case LINE:
                printf("Line");
                break;

            case TRIANGLE:
                printf("Triangle");
                break;

            case CIRCLE:
                printf("Circle");
                break;
        }

        printf("\n");
    }
}

/* ================= MAIN ================= */

int main()
{
    int choice;

    int row, col, height, width;

    int x1, y1, x2, y2;

    int tx1, ty1;
    int tx2, ty2;
    int tx3, ty3;

    int centerRow, centerCol, radius;

    initializeCanvas();

    printf("=====================================\n");
    printf("      2D GRAPHICS EDITOR IN C\n");
    printf("=====================================\n");

    while(1)
    {
        printf("\n");
        printf("1. Draw Rectangle\n");
        printf("2. Draw Line\n");
        printf("3. Draw Triangle\n");
        printf("4. Draw Circle\n");
        printf("5. Display Canvas\n");
        printf("6. Display Objects\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:

                printf("Enter starting row: ");
                scanf("%d", &row);

                printf("Enter starting column: ");
                scanf("%d", &col);

                printf("Enter height: ");
                scanf("%d", &height);

                printf("Enter width: ");
                scanf("%d", &width);

                drawRectangle(row, col, height, width);

                objects[objectCount].id = nextID++;
                objects[objectCount].type = RECTANGLE;

                objects[objectCount].x1 = row;
                objects[objectCount].y1 = col;
                objects[objectCount].height = height;
                objects[objectCount].width = width;

                objectCount++;

                printf("Rectangle ID = %d\n", nextID - 1);

                break;

            case 2:

                printf("Enter start point (row col): ");
                scanf("%d %d", &x1, &y1);

                printf("Enter end point (row col): ");
                scanf("%d %d", &x2, &y2);

                drawLine(x1, y1, x2, y2);

                objects[objectCount].id = nextID++;
                objects[objectCount].type = LINE;

                objects[objectCount].x1 = x1;
                objects[objectCount].y1 = y1;
                objects[objectCount].x2 = x2;
                objects[objectCount].y2 = y2;

                objectCount++;

                printf("Line ID = %d\n", nextID - 1);

                break;

            case 3:

                printf("Enter Vertex 1 (row col): ");
                scanf("%d %d", &tx1, &ty1);

                printf("Enter Vertex 2 (row col): ");
                scanf("%d %d", &tx2, &ty2);

                printf("Enter Vertex 3 (row col): ");
                scanf("%d %d", &tx3, &ty3);

                drawTriangle(tx1, ty1, tx2, ty2, tx3, ty3);

                objects[objectCount].id = nextID++;
                objects[objectCount].type = TRIANGLE;

                objects[objectCount].x1 = tx1;
                objects[objectCount].y1 = ty1;
                objects[objectCount].x2 = tx2;
                objects[objectCount].y2 = ty2;
                objects[objectCount].x3 = tx3;
                objects[objectCount].y3 = ty3;

                objectCount++;

                printf("Triangle ID = %d\n", nextID - 1);

                break;

            case 4:

                printf("Enter center row: ");
                scanf("%d", &centerRow);

                printf("Enter center column: ");
                scanf("%d", &centerCol);

                printf("Enter radius: ");
                scanf("%d", &radius);

                drawCircle(centerRow, centerCol, radius);

                objects[objectCount].id = nextID++;
                objects[objectCount].type = CIRCLE;

                objects[objectCount].x1 = centerRow;
                objects[objectCount].y1 = centerCol;
                objects[objectCount].radius = radius;

                objectCount++;

                printf("Circle ID = %d\n", nextID - 1);

                break;

            case 5:

                displayCanvas();

                break;

            case 6:

                displayObjects();

                break;

            case 7:

                printf("Exiting...\n");
                return 0;

            default:

                printf("Invalid Choice!\n");
        }
    }

    return 0;
}