//polygon.c - all data, methods and declerations of polygon.
// the ctor function returns an array of function that preform actions on polygons 
#include "checks.c"
#include <math.h>

typedef enum {QUADRILATERAL=4, PENTAGON=5} POLYGON ;
typedef struct point
{
    char x;
    char y;
}Point;


typedef struct polygon {
 POLYGON type;
 Point* points;
}Polygon;

typedef void(*p)(struct polygon*);

void print_polygon(struct polygon* poly)
{
    POLYGON type = poly->type;
    if(type == QUADRILATERAL)
    {
        printf("quadrilateral {%d, %d} {%d, %d} {%d, %d} {%d, %d}\n",poly->points[0].x,poly->points[0].y
                                                                  ,poly->points[1].x,poly->points[1].y
                                                                  ,poly->points[2].x,poly->points[2].y
                                                                  ,poly->points[3].x,poly->points[3].y);
    }
    else
    {
        printf("pentagon {%d, %d} {%d, %d} {%d, %d} {%d, %d} {%d, %d}\n",poly->points[0].x,poly->points[0].y
                                                                  ,poly->points[1].x,poly->points[1].y
                                                                  ,poly->points[2].x,poly->points[2].y
                                                                  ,poly->points[3].x,poly->points[3].y
                                                                  ,poly->points[4].x,poly->points[4].y);
    }
}
float distanceBetweenPoints(Point p1, Point p2)
{
   float res = sqrt( pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2) );
   return res;
}

 float calculatePerimeter(Polygon* poly)
{  
     float perimeter = 0;
    for(int i=0;i<(int)poly->type;i++)
    {
        int i2 = (i+1)%((int)poly->type);//makes i2 a cyclic pointer so the last point well be the first;
        perimeter += distanceBetweenPoints(poly->points[i],poly->points[i2]);
    }
}

 float calculateDiagonals(Polygon* poly)
{
    float allDiagonals = 0;
    int numberOfEdges = (int)poly->type;
    for(int i=0; i< numberOfEdges;i++)
    {
        for(int j = i ; j<numberOfEdges ; j++) 
        {
            if(i != j && i+1 != j && (i-1)%numberOfEdges != j && (j+1)%numberOfEdges != i )
            {
                 allDiagonals += distanceBetweenPoints(poly->points[i],poly->points[j]);
            }
        }
    }
    return allDiagonals;
}

float calculateArea(Polygon* poly)
{
    float sumA = 0;
    float sumB = 0;
    float squareDiff = 0;
    float area = 0;
    int numberOfEdges = (int)poly->type;
    int j;
    for(int i = 0; i < numberOfEdges; i++)
    {   
        j=i+1;
        if( j==numberOfEdges )
            j=0;

            sumA += (poly->points[i].x)*(poly->points[j].y);
            sumB += (poly->points[i].y)*(poly->points[j].x);
    }
        squareDiff = fabs(sumA - sumB);
        area = squareDiff/2;
        return area;
}

void print_perimeter(struct polygon* poly)
{
    float perimeter = calculatePerimeter(poly);
    printf("perimeter = %.1f\n",perimeter);
}

void print_diagonals(struct polygon* poly)
{
    float diagonals = calculateDiagonals(poly);
    printf("diagonals = %.1f\n",diagonals);
}

void print_area(struct polygon* poly)
{
    float area = calculateArea(poly);
    printf("area = %.1f\n",area);
}



 p* ctor(){
     p* pArr = (p*)malloc(4*sizeof(p));  ; 
     pArr[0] = print_polygon;
     pArr[1] = print_perimeter;
     pArr[2] = print_diagonals;
     pArr[3] = print_area;
     return pArr;
 } 

 POLYGON getPolygonType(long long number)
 {
     POLYGON res;
     bool bit = checkBit(2,number);
     if (bit == true)
     {
         res = PENTAGON;
     }
     else
     {
         res = QUADRILATERAL;
     }
     return res;
     
 }

 Point extractPoint(int index,long long number)
 {
     Point p;
     number = number >> (16*index);
     p.x = (char)0xff & number;
     number = number >> 8;
     p.y =  (char)0xff & number;
     return p;
 }

 void extractQuadToPolygon(Point* quadArr, long long number)
 {
     for(int i=0; i<QUADRILATERAL;i++)
     {
         quadArr[i] = extractPoint(i,number);
     }
 }

void extractPentaToPolygon(Point* PentaArr, long long number,long long number2)
 {
      extractQuadToPolygon(PentaArr,number);
      PentaArr[4] = extractPoint(0,number2);
 }

 Polygon* createPolygon(POLYGON polygonType)
 {
    long long number;
    scanf("%llx",&number);//gets the 64-bit hexadecimal number into the var number
    Polygon* result = (Polygon*)malloc(sizeof(Polygon));

    if(polygonType == QUADRILATERAL)
    {
        Point* quadPointsArray = (Point*)malloc(QUADRILATERAL*sizeof(Point));
        extractQuadToPolygon(quadPointsArray,number);
        result->points = quadPointsArray;
        result->type = QUADRILATERAL;
    }
    else if(polygonType == PENTAGON )
    {
        Point* PentaPointsArray = (Point*)malloc(PENTAGON*sizeof(Point));
        long long number2;
        scanf("%llx",&number2);//gets the 64-bit hexadecimal number into the var number
        extractPentaToPolygon(PentaPointsArray,number,number2);
        result->points = PentaPointsArray;
        result->type = PENTAGON;

    }
    return result;     
 } 
 void applyFunctions(Polygon* poly,OUTPUT_TYPE* outputTypeArr)
 {
     if (outputTypeArr!= NULL)
     {
         p* funcArr = ctor();// p is a type and ctor is a function(returns function array) both declared in polygon.c.

         for(int i=0;i<4;i++)
         {
             switch (outputTypeArr[i])
             {
                 case typeAndVertices:
                     (*funcArr[0])(poly);
                     break;
                 case calcAndPerimeter:
                     (*funcArr[1])(poly);
                     break;
                 case calcAndArea:
                     (*funcArr[3])(poly);
                     break;
                 case calcAndSumDiagonals:
                     (*funcArr[2])(poly);
                     break;
                 case empty:
                     break;
                 default:
                    break;
             }

         }
     }
 }


