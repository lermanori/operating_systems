typedef enum {typeAndVertices=3 ,calcAndPerimeter=4,calcAndArea=5,calcAndSumDiagonals=6,empty=7} OUTPUT_TYPE;
typedef enum {currentOnly,quadLiteral,pentagon,all} OUTPUT_SUBJECT;

typedef enum {false,true} bool;

bool checkBit(int index,long long number);


bool checkIfNew(long long number)
{
    bool res = checkBit(1,number);
    return res;
}

OUTPUT_TYPE* checkOutputType(long long number)
{
    OUTPUT_TYPE* res = (OUTPUT_TYPE*)malloc(4*sizeof(OUTPUT_TYPE));
    for(int i=0;i<4;i++)
        res[i] = empty;
    int wrintingIndex = 0;
    for(int i=typeAndVertices;i <= calcAndSumDiagonals;i++)
    {
        if(checkBit(i,number) == true )
        {
            res[wrintingIndex] = (OUTPUT_TYPE) i;
            wrintingIndex++;
        }
    }
    if(wrintingIndex == 0)
    {
        free(res);
        res = NULL;
    }
    
    return res;
}

OUTPUT_SUBJECT checkOutputSubject(long long number)
{
    bool bit7 = checkBit(7,number);
    bool bit8 = checkBit(8,number);
    OUTPUT_SUBJECT res;

    if (bit7 == true && bit8== true)//11
    {
        res = all;
    }
    else if (bit7==true && bit8 == false)//01
    {
        /* code */
        res = quadLiteral;
    }
    else if (bit7==false && bit8== true) //10
    {
        res = pentagon;
    }
    else//00
    {
        res= currentOnly;
    }
    return res;
}

bool checkContinuation(long long number)
{
    bool res = checkBit(0,number);
    return res;
}

bool checkBit(int index,long long number)
{
    bool result = false;
    long long indicator = number&(1<<index);
    if( indicator  != 0  )
        result = true;
    return result;
}
