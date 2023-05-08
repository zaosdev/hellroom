#pragma once

#include "../facade/xmlFacade.hpp"
#include "../utils/random.hpp"
#include "../utils/effectType.hpp"


#include <cassert>
#include <iostream>

namespace FV_factory {

    static constexpr const char * efListFilePath        = "../media/xml/effectList.xml";
    static constexpr const char * efNameListFilePath    = "../media/xml/effectNameList.xml";
    //XML ELEMENT NAMES 
    static constexpr const char * commonEffects             = "commonEffects";
    static constexpr const char * name        = "name";
    static constexpr const char * effect       = "effect";
    static constexpr const char * description        = "description";
    static constexpr const char * flag               = "flags";
    static constexpr const char * variable           = "variable";
    static constexpr const char * maxValue           = "maxValue";
    static constexpr const char * minValue           = "minValue";

    //XML ATTRIBUTE NAMES

    static constexpr const char * value              = "value";

    static constexpr const char * objFilePath        = "objFilePath";

    struct effectsFactory
    {
        using XMLReader = FVeng::xmlReader_facade<tinyxml2::XMLDocument,tinyxml2::XMLElement>;
        using XMLElem = FVeng::xmlElement_facade<tinyxml2::XMLElement>;

        effectsFactory()
        {

            xmlEffectsNameList_.loadFile(efNameListFilePath);
            xmlEffectsNameList_.printError();

            XMLElem comnEffctsElem = xmlEffectsNameList_.FirstChildOnDocument(commonEffects);
            XMLElem effectname = comnEffctsElem.FirstChildNamed(name);

            while(!effectname.isEmpty())
            {
                const char* tempHolder{};

                effectname.queryAttribute<const char**>(effect,&tempHolder);

                effectsNameList.push_back(std::string(tempHolder));

                effectname = effectname.NextSiblingNamed(name);
            }


            xmlEffectsList_.loadFile(efListFilePath);
            xmlEffectsNameList_.printError();
        //    effectsListIdx = static_cast<unsigned int>(jsonEng_.addJSONByFilePath(efListFilePath));

        }
        
        effectsFactory(const effectsFactory&) = delete;
        effectsFactory(effectsFactory&&) = delete;
        effectsFactory& operator=(const effectsFactory&)= delete;
        effectsFactory& operator=(effectsFactory&&)= delete;

        //LISTS ALL EFFECTS ON THE MANAGER
        void listAllEffects()
        {   
            for(auto& effect : effectsNameList)
            {
                std::cout << effect << "\n";
            }

        }

        //RETURNS EFFECT NAME PROVIDED AN INDEX POSITION
        [[nodiscard]] std::string getEffectNameByIndex(unsigned long idx) noexcept
        {
            assert(idx<effectsNameList.size());
            return effectsNameList[idx];
        }

        [[nodiscard]] effect_utils::effectType createRandomEffect() noexcept  
        {
            unsigned long idx; 

            idx = static_cast<unsigned long>(FVmath::calcualteRandom(int(effectsNameList.size()-1)));

            auto resultingEffect = createEffectNamed(getEffectNameByIndex(idx));

            return resultingEffect;
        } 


        //CREATES AN EFFECT FROM AN EFFECT NAME, 
        [[nodiscard]] effect_utils::effectType createEffectNamed(std::string effectName) noexcept   
        {
            std::cout << effectName << std::endl;

            //LOAD ONTO THE effect Manager EFFECT INFORMATION
            XMLElem  effectList = xmlEffectsList_.FirstChildOnDocument("effectList");
            XMLElem effectELEM = effectList.FirstChildNamed(effectName.c_str());

            //CREATE LOCAL EFFECT
            effect_utils::effectType tempEf{};

            //ASSIGN EFFECT NAME TO THE EFFECT
            tempEf.name = effectName;

            //ASSIGN DESCRIPTION TO THE EFFECT
            getDescription(tempEf.description, effectELEM);

            //ASSIGN MODEL FILE PATH TO THE EFFECT
            //getModelFilePath(tempEf.objFilePath);

            //CALCULATE RANDOM VALUES BASED ON DATA PROVIDED BY THE EFFEC AND ASSIGN IT
            calculateEffectValues(tempEf,effectELEM);


            //RETURN COPY OF THE EFFECT
            return tempEf;
            
        }


        //ASSIGN DESCRIPTION NAME TO THE PROVIDED STRING
        void getDescription(std::string& descp, XMLElem& elem) noexcept
        {
            XMLElem descElem = elem.FirstChildNamed(description);

            const char* tempHolder{};

            descElem.queryAttribute<const char**>(value,&tempHolder);

            descp = std::string(tempHolder);

        }

        float calculateRandomEffectValue(int flags, float maxValue, float minValue)
        {
                float finalValue{0};

                if(flags == effect_utils::effectFlags::isPercentage)
                {
                    maxValue*=10;

                    int randValue = FVmath::calcualteRandom(maxValue,minValue);

                    randValue/=10;

                    finalValue = float(randValue);
                }
                else
                {
                    int randValue = FVmath::calcualteRandom(maxValue,minValue);

                    finalValue = float(randValue);

                }

                return finalValue;
        }

        //CALCULATE RANDOM VALUES BASED ON MAX VALUE, FOR EACH VALUE PROVIDED
        void calculateEffectValues(effect_utils::effectType& ef, XMLElem& elem) noexcept
        {          
            //auto value  =  jsonEng_.getArrayFromKey<std::string>(valueKey);
            int maxValueptr{};
            int minValueptr{};
            const char* variablesptr{};

            auto maxValueElem = elem.FirstChildNamed(maxValue);
            maxValueElem.queryAttribute<int*>(value,&maxValueptr);

            auto minValueElem = elem.FirstChildNamed(minValue);
            minValueElem.queryAttribute<int*>(value,&minValueptr);

            auto variablesElem = elem.FirstChildNamed(variable);
            variablesElem.queryAttribute<const char **>(value,&variablesptr);

            auto flagElem = elem.FirstChildNamed(flag);
            flagElem.queryAttribute<int*>(value,&ef.Flags);

            ef.variable.push_back(std::string(variablesptr));

            auto val = calculateRandomEffectValue(ef.Flags, maxValueptr, minValueptr);

            ef.value.push_back(val);

        }


        private:
        std::vector<std::string> effectsNameList{};

        XMLReader xmlEffectsNameList_{};
        XMLReader xmlEffectsList_{};


    };

}