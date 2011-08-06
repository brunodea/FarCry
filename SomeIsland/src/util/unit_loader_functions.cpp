#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>
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

 //   free(cline);
 //   free(attrName);
 //   free(attrVal);

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
//        free(baseClass);

        return (model::GameObject*)getVehicleFromAttributes(attributes);
    }
    else
    {
        return NULL;
    }
}

vehicle::Vehicle* util::getVehicleFromAttributes(std::vector<util::UnitAttribute> attrs)
{
    return NULL;
    /*
    vehicle::Vehicle* vehicle = new vehicle::Vehicle(*(new std::vector<model::Shape*>), false);
    unsigned int vsize = attrs.size();
    model::PolygonShape* polygon = NULL;

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
            char s = '|';
            std::string aux = attrVal;
            std::vector<std::string> v = split(aux, s);

            for(unsigned int t = 0; t < v.size(); t++)
            {
                vehicle->addPassOverTerrain(getTerrainFromString(v.at(t)));
            }
        }
        else if(strcmp(attrName, "line") == 0)
        {
            if(polygon == NULL)
            {
                polygon = new model::PolygonShape();
            }

            char s = ',';
            std::string aux = attrVal;
            std::vector<std::string> v = split(aux, s);
            std::vector<int> coords;

            for(unsigned int t = 0; t < v.size(); t++)
            {
                coords.push_back(atoi(v.at(t).c_str()));
            }
        }
    }

    return vehicle;
    */
}

std::vector<std::string> &util::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}


std::vector<std::string> util::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

TerrainType util::getTerrainFromString(std::string str)
{
    if(strcmp(str.c_str(), "LAND") == 0) return LAND;
    else if(strcmp(str.c_str(), "SHALLOW_WATER") == 0) return SHALLOW_WATER;
    else if(strcmp(str.c_str(), "DEEP_WATER") == 0) return DEEP_WATER;
    else if(strcmp(str.c_str(), "MUD") == 0) return MUD;
    else if(strcmp(str.c_str(), "SAND") == 0) return SAND;
    else if(strcmp(str.c_str(), "ROCK") == 0) return ROCK;

    return LAND;
}
