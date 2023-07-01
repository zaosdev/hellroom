#pragma once

#include "../utils/types.hpp"

namespace FVeng
{
    template <typename XMLElement_type>
    struct xmlElement_facade
    {
        template<typename T,typename U>
        friend struct xmlReader_facade;

        [[nodiscard]] xmlElement_facade NextSiblingNamed(const char* elemName)
        {
            xmlElement_facade temp{};
            temp.XMLE = XMLE->NextSiblingElement(elemName);
            return temp;
        }

        [[nodiscard]] xmlElement_facade FirstChildNamed(const char* elemName)
        {
            xmlElement_facade temp{};
            temp.XMLE = XMLE->FirstChildElement(elemName);
            return temp;
        }

        [[nodiscard]] xmlElement_facade FindFirstChildwithName(const char* childName,const char* attValue )
        {
            xmlElement_facade temp{};
            temp.XMLE = XMLE->FirstChildElement(childName);

            bool found{false};

            while(!found || (!found && !temp.isEmpty()))  
            {
                const char * tempValue{};
                temp.XMLE->QueryStringAttribute("name", &tempValue);
                if(std::strcmp(tempValue,attValue)==0)
                {
                    found=true;
                }
                else
                {
                    temp = temp.NextSiblingNamed(childName);
                }
            }

            return temp;
        }

        template<typename T>
        void queryAttribute(const char* attName, T attribute) 
        {
            queryAttribute<T>(attName, attribute ,typename FV_types::queryTypes<T>::Type());
        };

        template<typename T>
        void queryAttribute(const char* attName, T attribute, FV_types::int_Type) 
        {
            XMLE->QueryIntAttribute(attName, attribute);
        };
                
        template<typename T>
        void queryAttribute(const char* attName, T attribute,  FV_types::bool_Type ) 
        {
            XMLE->QueryBoolAttribute(attName, attribute);
        };        

        template<typename T>
        void queryAttribute(const char* attName, T attribute,  FV_types::const_char_Type ) 
        {
            XMLE->QueryStringAttribute(attName, attribute);
        };

        [[nodiscard]] bool isEmpty() noexcept
        {
            if(XMLE) return false;
            else return true;
        }

        private:
         XMLElement_type* XMLE{};
    };
    
    template <typename XMLReader_type,typename XMLElement_type>
    struct xmlReader_facade
    {

        void loadFile(const char* filePath)
        {
            XMLR.LoadFile(filePath);
        }

        void printError(){ XMLR.PrintError();}

        [[nodiscard]] xmlElement_facade<XMLElement_type> FirstChildOnDocument(const char* elemName)
        {
            xmlElement_facade<XMLElement_type> temp{};
            temp.XMLE = XMLR.FirstChildElement(elemName);
            return temp;
        }

        private:
        
         XMLReader_type XMLR{};   
    };

}