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

        if(line.size() <= 0)
        {
            continue;
        }

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

        if(strcmp(attrName, "currentFuel") == 0)
        {
            vehicle->setCurrentFuel(atoi(attrVal));
        }
        else if(strcmp(attrName, "maxFuel") == 0)
        {
            vehicle->setMaxFuel(atoi(attrVal));
        }
        else if(strcmp(attrName, "armor") == 0)
        {
            vehicle->setArmor(atoi(attrVal));
        }
        else if(strcmp(attrName, "name") == 0)
        {
            std::string s = std::string(attrName);
            vehicle->setName(s);
        }
        else if(strcmp(attrName, "passOverTerrain") == 0)
        {
            /*char s = '|';
            std::vector<std::string> v = splitString(attrVal, &s);

            for(unsigned int t = 0; t < v.size(); t++)
            {
                std::cout << v.at(i) << std::endl;
            }*/
        }
    }

    return vehicle;
}

std::vector<std::string> util::splitString(const char* str, const char* separator)
{
    std::string terrains = std::string(str);
    std::vector<std::string> vterrain;
    std::string *tmpStr = new std::string();
    unsigned int tmpI = 0;

    for(unsigned int i = 0; i < terrains.length(); i++)
    {
        if(terrains[i] != separator[0])
        {
            tmpStr[tmpI++] = terrains[i];

            std::cout << "tmpStr " << tmpStr[tmpI-1] << std::endl;
        }
        else
        {
            std::cout << "else " << tmpStr << std::endl;
            char* tmpchar;
            std::string tmp = std::string(strcpy(tmpchar, tmpStr->c_str()));
            vterrain.push_back(tmp);

            delete tmpStr;
            tmpI = 0;
            tmpStr = new std::string();
        }
    }

    std::cout << "res " << tmpStr << std::endl;

    if(tmpStr->length() > 0)
    {
        vterrain.push_back(*tmpStr);
    }

    delete tmpStr;

    return vterrain;
}
