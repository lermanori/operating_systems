 #include <stdio.h>
 #include <stdlib.h>
 #include "polygon.c"

typedef struct node {
 struct polygon* poly;
 struct node* next;
}Node;

typedef struct POLYGONLIST
{
    Node* head;
    Node* tail;
}PolygonList;

PolygonList* makeEmptyList(){
    PolygonList* list =(PolygonList*)malloc(sizeof(PolygonList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int isEmpty(PolygonList ls){
    if (ls.head != NULL || ls.tail != NULL)
    {
        return 0;
    }
    return 1;
}

void addNodeToTail(PolygonList* ls,Node* newNode)
{
    if(isEmpty(*ls) == 1)
    {
        ls->head = newNode;
        ls->tail = newNode;
        newNode->next = NULL;
    }
    else
    {
       ls->tail->next = newNode;
       ls->tail = newNode;
       ls->tail->next = NULL;
    }
}

Node* createNewNode(Polygon* p, Node* next)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->poly = p;
    n->next = next;
    return n;
}

void calculateAndPrint(OUTPUT_TYPE* outputTypeArr,OUTPUT_SUBJECT outputSubject,PolygonList* ls)
{
    if(outputSubject == currentOnly)
    {

            Polygon* current = ls->tail->poly;
            applyFunctions(current,outputTypeArr);
    }
    else if (outputSubject == quadLiteral) {
            Node* current = ls->head;
            while(current!=NULL)
            {
                Polygon* poly = current->poly;
                POLYGON type = poly->type;
                if (type == QUADRILATERAL )
                {
                    applyFunctions(poly,outputTypeArr);
                }
                current = current->next;
            }
    }
    else if (outputSubject == pentagon)
    {
            Node* current = ls->head;
            while(current!=NULL)
            {
                Polygon* poly = current->poly;
                POLYGON type = poly->type;
                if (type == PENTAGON )
                {
                    applyFunctions(poly,outputTypeArr);
                }
                current = current->next;
            }
    }
    else // all
    {
            Node* current = ls->head;
            while(current!=NULL)
            {
                Polygon* poly = current->poly;
                POLYGON type = poly->type;
                applyFunctions(poly,outputTypeArr);
                current = current->next;
            }
    }
}
    


/*
int main(int argc, char const *argv[])
{
    PolygonList* ls = makeEmptyList();
    Polygon pol;
    pol.type = QUADRILATERAL;
    Polygon* polPtr = &pol;
    Node* n1 = createNewNode(polPtr,NULL);
    Node* n2 = createNewNode(polPtr,NULL);
    addNodeToTail(ls,n1);
    addNodeToTail(ls,n2);
    return 0;
}*/





