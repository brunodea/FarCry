#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "util/unit_loader_functions.h"

model::GameObject* util::loadUnitFromFile(std::string filename)
{
    std::ifstream unitFile;
    unitFile.open(filename.c_str());

    if(!unitFile.is_open())
    {
        std::cout << "Erro ao abrir arquivo " << filename << ".\n";

        return NULL;
    }

    std::string line;

    if(!unitFile.good())
    {
        std::cout << "Erro ao ler arquivo " << filename << ".\n";

        return NULL;
    }

    std::getline(unitFile, line);
    char* cline = (char*)line.c_str();
    char* attrName = strtok(cline, "=");
    char* attrVal  = strtok(NULL, "\0");

    char* baseClass = attrVal;

    free(cline);
    free(attrName);
    free(attrVal);

    std::vector<UnitAttribute> attributes;

    while(unitFile.good())
    {
        std::getline(unitFile, line);
        cline = (char*)line.c_str();
        attrName = strtok(cline, "=");
        attrVal = strtok(NULL, "\0");

        util::UnitAttribute attr;
        attr.m_attribute = attrName;
        attr.m_value = attrVal;

        attributes.push_back(attr);
    }

    unitFile.close();

    if(strcmp(baseClass, "Vehicle"))
    {
        free(baseClass);

        return (model::GameObject*)getVehicleFromAttributes(attributes);
    }
    else
    {
        return NULL;
    }
}

vehicle::Vehicle* util::getVehicleFromAttributes(std::vector<util::UnitAttribute> attrs)
{
    vehicle::Vehicle* vehicle = new vehicle::Vehicle(NULL, false);
    unsigned int vsize = attrs.size();

    for(unsigned int i = 0; i < vsize; i++)
    {
        UnitAttribute tmpAttr = (UnitAttribute)attrs.at(i);
        const char* attrName = tmpAttr.m_attribute.c_str();
        const char* attrVal = tmpAttr.m_value.c_str();

        if(strcmp(attrName, "currentFuel"))
        {
            vehicle->setCurrentFuel(atoi(attrVal));
        }
        else if(strcmp(attrName, "maxFuel"))
        {
            vehicle->setMaxFuel(atoi(attrVal));
        }
        else if(strcmp(attrName, "armor"))
        {
            vehicle->setArmor(atoi(attrVal));
        }
        else if(strcmp(attrName, "name"))
        {
            std::string s = std::string(attrName);
            vehicle->setName(s);
        }
        else if(strcmp(attrName, "passOverTerrain"))
        {
        }
    }

    return vehicle;
}