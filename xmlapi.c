#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
void* xmlParsefunction(void *arg_p);


struct xmlparser
{
    char *attribute;
    uint8_t data;
};
struct xmlparser  mem;

void main()
{
    xmlParsefunction("i=2046");
}

void* xmlParsefunction(void *arg_p)

{

    xmlDocPtr    xmlDocument;

    xmlNodePtr   currentNode;

    xmlNodePtr   currentChildNode;

    xmlChar*     nodeId;

    xmlChar*     nodeValue;


    /* Reads the XML file*/

    xmlDocument = xmlReadFile("dummy.xml",NULL,0);


    /* Fetches the root element from the xml file return variable*/

    currentNode = xmlDocGetRootElement(xmlDocument);//UAVariables gets root node

    if (currentNode == NULL)

      printf("Given XML  file is empty \n");


    /* Pointer points to the child node */

    currentNode = currentNode->xmlChildrenNode;//UAVariables getd first child node


    while (currentNode != NULL)

    {

        if((!xmlStrcmp(currentNode->name, (const xmlChar *)"UAVariable")))// check 1st child node name is UAVariable or nots

        {

            printf("Inside UA variable \n");

            nodeId = xmlGetProp(currentNode,"NodeId");// reads attributes and its value, reads NodeID attribute's value and returns it

            mem.attribute=xmlGetProp(currentNode,"BrowseName");//


            if((!xmlStrcmp(nodeId, (const xmlChar *)arg_p)))// check node ID is matched with user input node ID

            {

                currentChildNode = currentNode->xmlChildrenNode;


                while (currentChildNode != NULL)

                {

                    if((!xmlStrcmp(currentChildNode->name, \

                                    (const xmlChar *)"Value")))

                    {

                    currentChildNode = currentChildNode->xmlChildrenNode;


                    while(currentChildNode != NULL)

                    {

                        if((xmlStrcmp(currentChildNode->name, \

                                    (const xmlChar *)"text")))

                        {

                            nodeValue = xmlNodeListGetString(xmlDocument, \

                                currentChildNode->xmlChildrenNode, \

                                            1);

                            mem.data = atoi(nodeValue);

                            printf("The Value in %s node is %d\n",

                                mem.attribute,mem.data);

                            break;

                        }

                        currentChildNode = currentChildNode->next;

                    }

                    }

                    currentChildNode = currentChildNode->next;

                }

            }

        }

        currentNode = currentNode->next;

    }


}



