#pragma once

namespace FVeng
{
    
    template <typename XMLReader, typename XMLElement>
    struct xmlFacade
    {
        xmlFacade() = default;

        xmlFacade (const xmlFacade&) = delete;
        xmlFacade (xmlFacade&&) = delete;
        xmlFacade& operator=(const xmlFacade&)= delete;
        xmlFacade& operator=(xmlFacade&&)= delete;     
    
        void loadFile(const char* filePath)
        {
            doc_.LoadFile(filePath);
        }

        void printError(){ doc_.PrintError();}

        [[nodiscard]] XMLElement* FirstChildElement(const char* elemName)
        {
            return doc_.FirstChildElement(elemName);
        }

        template<typename T>
        void queryAttribute(XMLElement* elem, const char* attName,  T attribute) 
        {
            // elem->QueryIntAttribute(attName, attribute);
        };

        template<>
        void queryAttribute<int*>(XMLElement* elem, const char* attName,  int* attribute) 
        {
            elem->QueryIntAttribute(attName, attribute);
        };
                
        template<>
        void queryAttribute<bool*>(XMLElement* elem, const char* attName,  bool* attribute) 
        {
            elem->QueryBoolAttribute(attName, attribute);
        };        

        template<>
        void queryAttribute<const char**>(XMLElement* elem, const char* attName,  const char** attribute) 
        {
            elem->QueryStringAttribute(attName, attribute);
        };        

        private:
            XMLReader doc_{};

    };
}