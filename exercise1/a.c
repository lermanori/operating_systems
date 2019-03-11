#include <stdio.h>
#include <stdlib.h>
#include "polygonList.c"




char* printBool(bool arg);

int main()
{
     PolygonList* ls  = makeEmptyList();

   /*  struct polygon poly;
     (*funcArr[2])(&poly);*/

    
    while(1){
        long long number;
        scanf("%llx",&number);//gets the 64-bit hexadecimal number into the var number

        bool  isItNew = checkIfNew(number);
        if (isItNew == true){
            POLYGON pType = getPolygonType(number);
            Polygon* currentPolygon = createPolygon(pType);
            Node* newNode = createNewNode(currentPolygon,NULL);
            addNodeToTail(ls,newNode);
        }   
        OUTPUT_TYPE* outType = checkOutputType(number);
        if (outType != NULL)
        {
            OUTPUT_SUBJECT outSubject = checkOutputSubject(number);
            calculateAndPrint(outType,outSubject,ls);
        }
        bool ToExit = checkContinuation(number);
        if( ToExit == true)
        {
            exit(0);
        }
    }
}


char* printBool(bool arg)
{
     char* res;

     if (arg == true)
        res="true";
     else
         res="false";
     
     return res;
}
