#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ROWS 20
#define COLS 40

char canvas[ROWS][COLS];

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
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");
    }
}
// Function to draw a rectangle on the canvas
void drawRectangle(int row, int col, int height, int width)
{
    for(int i = row; i < row + height && i < ROWS; i++)
    {
        for(int j = col; j < col + width && j < COLS; j++)
        {
            canvas[i][j] = '*';
        }
    }
}
//Function to draw a line on the canvas using Bresenham's line algorithm
void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (1)
    {
        if (x1 >= 0 && x1 < ROWS && y1 >= 0 && y1 < COLS)
        {
            canvas[x1][y1] = '*';
        }

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}
void drawTriangle(int x1, int y1,
                  int x2, int y2,
                  int x3, int y3)
{
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}
// Function to draw a circle on the canvas using the Midpoint Circle Algorithm
void drawCircle(int centerRow, int centerCol, int radius)
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            int distanceSquared =
                (i - centerRow) * (i - centerRow) +
                (j - centerCol) * (j - centerCol);

            int radiusSquared = radius * radius;

            if(abs(distanceSquared - radiusSquared) <= radius)
            {
                canvas[i][j] = '*';
            }
        }
    }
}
int main()
{
    int choice;
    int row, col, height, width;
    int x3, y3;

    initializeCanvas();

    while(1)
    {
        printf("\n===== 2D Graphics Editor =====\n");
        printf("1. Draw Rectangle\n");
        printf("2. Draw Line\n");
        printf("3. Draw Triangle\n");
        printf("4. Draw Circle\n");
        printf("5. Display Canvas\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
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
                printf("Rectangle added successfully!\n");
                break;

            case 2:
                printf("Enter starting row: ");
                scanf("%d", &row);

                printf("Enter starting column: ");
                scanf("%d", &col);

                printf("Enter ending row: ");
                scanf("%d", &height);

                printf("Enter ending column: ");
                scanf("%d", &width);

                drawLine(row, col, height, width);
                printf("Line added successfully!\n");
                break;

            case 3:
                printf("Enter coordinates for the three vertices of the triangle:\n");
                printf("Vertex 1 - Row: ");
                scanf("%d", &row);
                printf("Vertex 1 - Column: ");
                scanf("%d", &col);
                printf("Vertex 2 - Row: ");
                scanf("%d", &height);
                printf("Vertex 2 - Column: ");
                scanf("%d", &width);
                printf("Vertex 3 - Row: ");
                scanf("%d", &x3);
                printf("Vertex 3 - Column: ");
                scanf("%d", &y3);

                drawTriangle(row, col, height, width, x3, y3);
                printf("Triangle added successfully!\n");
                break;

            case 4:
                printf("Enter center row: ");
                scanf("%d", &row);
                printf("Enter center column: ");
                scanf("%d", &col);
                printf("Enter radius: ");
                scanf("%d", &height);

                drawCircle(row, col, height);
                printf("Circle added successfully!\n");
                break;

            case 5:
                displayCanvas();
                break;

            case 6:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}