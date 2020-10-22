#ifndef LAB1_236_PARSER_H
#define LAB1_236_PARSER_H
#include <vector>
#include "Token.h"
#include "PlainParameter.h"
#include "Datalog.h"

using namespace std;

class Parser {
private:

    vector<Token*> parseTokens;
    unsigned int tokenIndex;
    bool passedGrammar = false;

    vector<Predicate> parseSchemeList() { // this is a non terminal
        string idString;
        vector<Predicate> predicates;
        
        if (parseTokens[tokenIndex]->getTokenType() == "ID") {
            idString = parseTokens[tokenIndex]->getTokenInput();
            incrementIndex();
            Predicate predicateObject(idString, parseScheme());
            predicates.push_back(predicateObject);

            vector<Predicate> newPredicates;
            newPredicates = parseSchemeList();
            for (unsigned int i = 0; i < newPredicates.size(); ++i) {
                predicates.push_back(newPredicates.at(i));
            }
           
        }
        
        return predicates;
        
    }

    vector<Predicate> parseFactList() {
        vector<Predicate> predicates;
        
        string idString;
        if (parseTokens[tokenIndex]->getTokenType() == "ID") {
            idString = parseTokens[tokenIndex]->getTokenInput();
            incrementIndex();
            Predicate predicateObject(idString, parseFact());
            predicates.push_back(predicateObject);
        }
        if (parseTokens[tokenIndex]->getTokenType() == "ID") {
            vector<Predicate> newPredicates;
            newPredicates = parseFactList();
            for (unsigned int i = 0; i < newPredicates.size(); ++i) {
                predicates.push_back(newPredicates.at(i));
            }
        }
        return predicates;
    }

    vector<Rules> parseRuleList() {
        vector<Rules> rules;
        if (parseTokens[tokenIndex]->getTokenType() == "ID") {
            rules.push_back(parseRule());

            if (parseTokens[tokenIndex]->getTokenType() == "ID") {
                vector<Rules> newRules;
                newRules = parseRuleList();
                for (unsigned int i = 0; i < newRules.size(); ++i) {
                    rules.push_back(newRules.at(i));
                }

            }
            
        }
        return rules;
    }

    vector<Predicate> parseQueryList() {
        string idString;
        vector<Predicate> predicates;
        if (parseTokens[tokenIndex]->getTokenType() == "ID") {
            idString = parseTokens[tokenIndex]->getTokenInput();
            incrementIndex();
            Predicate predicateObject(idString, parseQuery());
            predicates.push_back(predicateObject);
            
            if (parseTokens[tokenIndex]->getTokenType() == "ID") {
                vector<Predicate> newPredicates;
                newPredicates = parseQueryList();
                for (unsigned int i = 0; i < newPredicates.size(); ++i) {
                    predicates.push_back(newPredicates.at(i));
                }

            }
            
        }

        return predicates;
    }

    vector<Parameter> parseScheme() {
        string inputString;
        vector<Parameter> parameterObjects;

        if (parseTokens[tokenIndex]->getTokenType() != "LEFT_PAREN") {
            throw parseTokens[tokenIndex];
        }
        incrementIndex();
        if (parseTokens[tokenIndex]->getTokenType() != "ID") {
            throw parseTokens[tokenIndex];
        }
        inputString = parseTokens[tokenIndex]->getTokenInput();
        Parameter parameterObject(inputString);
        parameterObjects.push_back(parameterObject);
        incrementIndex();
        if (parseTokens[tokenIndex]->getTokenType() == "COMMA") {
            vector<Parameter> newParameters;
            newParameters = parseIdList();
            for (unsigned int i = 0; i < newParameters.size(); ++i) {
                parameterObjects.push_back(newParameters.at(i));
            }
        }
        
            
        else if (parseTokens[tokenIndex]->getTokenType() != "RIGHT_PAREN") {
            throw parseTokens[tokenIndex];
        }
        incrementIndex();
        
        return parameterObjects;
       
    }

    vector<Parameter> parseFact() {
        string inputString; 
        vector<Parameter> parameterObjects;
        if (parseTokens[tokenIndex]->getTokenType() != "LEFT_PAREN") {
            throw parseTokens[tokenIndex];
        }
        incrementIndex();
        if (parseTokens[tokenIndex]->getTokenType() != "STRING") {
            throw parseTokens[tokenIndex];
        }
        inputString = parseTokens[tokenIndex]->getTokenInput();
        Parameter parameterObject(inputString);
        parameterObjects.push_back(parameterObject);
        incrementIndex();
        if (parseTokens[tokenIndex]->getTokenType() == "COMMA") {
            vector<Parameter> newParameters;
            newParameters = parseStringList();
            for (unsigned int i = 0; i < newParameters.size(); ++i) {
                parameterObjects.push_back(newParameters.at(i));
            }
        }
            
        if (parseTokens[tokenIndex]->getTokenType() != "RIGHT_PAREN") {
            throw parseTokens[tokenIndex];
        }
        incrementIndex();
        if (parseTokens[tokenIndex]->getTokenType() != "PERIOD") {
            throw parseTokens[tokenIndex];
        }
        incrementIndex();

        
        return parameterObjects;
    }

    Rules parseRule() {
        vector<Parameter> parameters;
        vector<Parameter> newParameters;
        vector<Predicate> predicates;
        string idString;
        if (parseTokens[tokenIndex]->getTokenType() != "ID") {
            throw parseTokens[tokenIndex];
        }
        idString = parseTokens[tokenIndex]->getTokenInput();
        incrementIndex();

        parameters = parseHeadPredicate();
        Predicate headPredicate(idString, parameters);
        

        
        if (parseTokens[tokenIndex]->getTokenType() != "COLON_DASH") {
            throw parseTokens[tokenIndex];
        }
        incrementIndex();

        if (parseTokens[tokenIndex]->getTokenType() == "ID") {
            idString = parseTokens[tokenIndex]->getTokenInput();
            
            incrementIndex();
            
            newParameters = parsePredicate();
            
        }
        else {
            throw parseTokens[tokenIndex];
        }
        Predicate firstPredicate(idString, newParameters);
        predicates.push_back(firstPredicate);

        if (parseTokens[tokenIndex]->getTokenType() == "COMMA") {
            vector<Predicate> newPredicates;
            newPredicates = parsePredicateList();
            for (unsigned int i = 0; i < newPredicates.size(); ++i) {
                predicates.push_back(newPredicates.at(i));
                
            }
        }
        
        
        if (parseTokens[tokenIndex]->getTokenType() != "PERIOD") {
            throw parseTokens[tokenIndex];
        }
        incrementIndex();
        Rules ruleObject(headPredicate, predicates);
        return ruleObject;
    }

    vector<Parameter> parseQuery() {
        vector<Parameter> parameterObjects;
        parameterObjects = parsePredicate();

        if (parseTokens[tokenIndex]->getTokenType() != "Q_MARK") {
            throw parseTokens[tokenIndex];
        }
        incrementIndex();

        return parameterObjects;
    }

    vector<Parameter> parseHeadPredicate() {
        string inputString;
        vector<Parameter> parameterObjects;
        if (parseTokens[tokenIndex]->getTokenType() != "LEFT_PAREN") {
            throw parseTokens[tokenIndex];
        }
        incrementIndex();
        if (parseTokens[tokenIndex]->getTokenType() != "ID") {
            throw parseTokens[tokenIndex];
        }
        inputString = parseTokens[tokenIndex]->getTokenInput();
        Parameter parameterObject(inputString);
        parameterObjects.push_back(parameterObject);
        incrementIndex();
        if (parseTokens[tokenIndex]->getTokenType() == "COMMA") {
            vector<Parameter> newParameters;
            newParameters = parseIdList();
            for (unsigned int i = 0; i < newParameters.size(); ++i) {
                parameterObjects.push_back(newParameters.at(i));
            }
        }
        if (parseTokens[tokenIndex]->getTokenType() != "RIGHT_PAREN") {
            throw parseTokens[tokenIndex];
        }
        incrementIndex();
        
        return parameterObjects;
    }

    vector<Parameter> parsePredicate() {
        
        vector<Parameter> parameterVectors;
        string inputString;

        if (parseTokens[tokenIndex]->getTokenType() != "LEFT_PAREN") {
            throw parseTokens[tokenIndex];
        }
        incrementIndex();
        if ((parseTokens[tokenIndex]->getTokenType() == "STRING") || (parseTokens[tokenIndex]->getTokenType() == "ID")) {
            inputString = parseTokens[tokenIndex]->getTokenInput();
            Parameter parameterObject(inputString);
            parameterVectors.push_back(parameterObject);
            incrementIndex();
        }
        else if (parseTokens[tokenIndex]->getTokenType() == "LEFT_PAREN") {
            incrementIndex();
            string input;

            input = parseExpression();
            Parameter parameterObject(input);
            parameterVectors.push_back(parameterObject);
        }
        else {
            throw parseTokens[tokenIndex];
        }
            
        if (parseTokens[tokenIndex]->getTokenType() == "COMMA") {
            vector<Parameter> newParameters;
            newParameters = parseParameterList();
            for (unsigned int i = 0; i < newParameters.size(); ++i) {
                parameterVectors.push_back(newParameters.at(i));
            }
            
        }

        if (parseTokens[tokenIndex]->getTokenType() != "RIGHT_PAREN") {
            throw parseTokens[tokenIndex];
        }
        incrementIndex();
        
        return parameterVectors;
    }

    vector<Predicate> parsePredicateList() {
        vector<Predicate> predicateList;
        string idString;
        if (parseTokens[tokenIndex]->getTokenType() == "COMMA") {
            incrementIndex();
            if (parseTokens[tokenIndex]->getTokenType() == "ID") {
                idString = parseTokens[tokenIndex]->getTokenInput();
                incrementIndex();
                
                Predicate predicateObject(idString, parsePredicate());
                
                predicateList.push_back(predicateObject);
            }
            else {
                throw parseTokens[tokenIndex];
            }
            
            if (parseTokens[tokenIndex]->getTokenType() == "COMMA") {
                vector<Predicate> newPredicates;
                newPredicates = parsePredicateList();
                for (unsigned int i = 0; i < newPredicates.size(); ++i) {
                    predicateList.push_back(newPredicates.at(i));
                    
                }
            }
                
        }
        
        return predicateList;
    }

    vector<Parameter> parseParameterList() {
        vector<Parameter> parameterVectors;
        string inputString;
        if (parseTokens[tokenIndex]->getTokenType() == "COMMA") {
            incrementIndex();

            if ((parseTokens[tokenIndex]->getTokenType() == "STRING") || (parseTokens[tokenIndex]->getTokenType() == "ID")) {
                
                inputString = parseTokens[tokenIndex]->getTokenInput();
                Parameter parameterObject(inputString);
                parameterVectors.push_back(parameterObject);
                incrementIndex();
            }
            else if (parseTokens[tokenIndex]->getTokenType() == "LEFT_PAREN") {
                incrementIndex();
                inputString = parseExpression();
                Parameter parameterObject(inputString);
                parameterVectors.push_back(parameterObject);
            }
            else {
                throw parseTokens[tokenIndex];
            }
            
            if (parseTokens[tokenIndex]->getTokenType() == "COMMA") {
                vector<Parameter> newParameters;
                newParameters = parseParameterList();
                for (unsigned int i = 0; i < newParameters.size(); ++i) {
                    parameterVectors.push_back(newParameters.at(i));
                }
            }
                
        }
        return parameterVectors;
        
    }

    vector<Parameter> parseStringList() {
        vector<Parameter> parameterObjects;
        string inputString;

        if (parseTokens[tokenIndex]->getTokenType() == "COMMA") {
            incrementIndex();
            if (parseTokens[tokenIndex]->getTokenType() != "STRING") {
                throw parseTokens[tokenIndex];
            }
            inputString = parseTokens[tokenIndex]->getTokenInput();
            Parameter parameterObject(inputString);
            parameterObjects.push_back(parameterObject);
            incrementIndex();
            if (parseTokens[tokenIndex]->getTokenType() == "COMMA") {
                vector<Parameter> newParameters;
                newParameters = parseStringList();
                for (unsigned int i = 0; i < newParameters.size(); ++i) {
                    parameterObjects.push_back(newParameters.at(i));
                }
                    
            }
                
        }
               
        return parameterObjects;
    }

    vector<Parameter> parseIdList() {
        vector<Parameter> parameterObjects;
        string inputString;

        if (parseTokens[tokenIndex]->getTokenType() != "COMMA") {
            throw parseTokens[tokenIndex];
        }
        incrementIndex();

        if (parseTokens[tokenIndex]->getTokenType() != "ID") {
            throw parseTokens[tokenIndex];
        }
        inputString = parseTokens[tokenIndex]->getTokenInput();
        Parameter parameterObject(inputString);
        parameterObjects.push_back(parameterObject);
        incrementIndex();

        if (parseTokens[tokenIndex]->getTokenType() == "COMMA") {
            vector<Parameter> newParameters;
            newParameters = parseIdList();
            for (unsigned int i = 0; i < newParameters.size(); ++i) {
                parameterObjects.push_back(newParameters.at(i));
            }
        }
            
        return parameterObjects;
    }

    string parseParameter() {
        string inputString;
        if (parseTokens[tokenIndex]->getTokenType() == "LEFT_PAREN") {
            incrementIndex();
            inputString = parseExpression();
        }
        else {
            throw parseTokens[tokenIndex];
        }
        
        return inputString;
    }

    string parseExpression() {
        string inputString = "(";
        
        if ( (parseTokens[tokenIndex]->getTokenType() == "STRING") || parseTokens[tokenIndex]->getTokenType() == "ID" ) {
            inputString = inputString + parseTokens[tokenIndex]->getTokenInput();
            incrementIndex();
        }
        else if (parseTokens[tokenIndex]->getTokenType() == "LEFT_PAREN") {
            inputString = inputString + parseParameter();
        }
        else {
            throw parseTokens[tokenIndex];
        }

        if ((parseTokens[tokenIndex]->getTokenType() == "ADD") || parseTokens[tokenIndex]->getTokenType() == "MULTIPLY") {
            inputString = inputString + parseTokens[tokenIndex]->getTokenInput();
            incrementIndex();
        }
        else {
            throw parseTokens[tokenIndex];
        }

        if ((parseTokens[tokenIndex]->getTokenType() == "STRING") || parseTokens[tokenIndex]->getTokenType() == "ID") {
            inputString = inputString + parseTokens[tokenIndex]->getTokenInput() + ")";
            incrementIndex();
        }
        else if (parseTokens[tokenIndex]->getTokenType() == "LEFT_PAREN") {
            inputString = inputString + parseParameter() + ")";
        }
        else {
            throw parseTokens[tokenIndex];
        }

        if (parseTokens[tokenIndex]->getTokenType() != "RIGHT_PAREN") {
            throw parseTokens[tokenIndex];
        }
        incrementIndex();
        
        return inputString;
    }

    

    Datalog parseDatalogProgram() {
        vector<Predicate> schemePredicates;
        vector<Predicate> factPredicates;
        vector<Predicate> queryPredicates;
        vector<Rules> rules;
        
        
        try {

            if (parseTokens[tokenIndex]->getTokenType() != "SCHEMES") {       // checking SCHEME
                throw parseTokens[tokenIndex];
            }
            incrementIndex();
            if (parseTokens[tokenIndex]->getTokenType() != "COLON") {
                throw parseTokens[tokenIndex];
            }
            incrementIndex();
            if (parseTokens[tokenIndex]->getTokenType() != "ID") {
                throw parseTokens[tokenIndex];
            }
            string idString;
            idString = parseTokens[tokenIndex]->getTokenInput();
            incrementIndex();

            Predicate predicateObject(idString, parseScheme());                                                      // parse Scheme
            schemePredicates.push_back(predicateObject);
            if (parseTokens[tokenIndex]->getTokenType() == "ID") {              // parse scheme list
                vector<Predicate> newPredicates;
                newPredicates = parseSchemeList();
                for (unsigned int i = 0; i < newPredicates.size(); ++i) {
                    schemePredicates.push_back(newPredicates.at(i));
                }
            }


            
            if (parseTokens[tokenIndex]->getTokenType() == "FACTS") {           // Checking for facts
                incrementIndex();
                if (parseTokens[tokenIndex]->getTokenType() == "COLON") {
                    incrementIndex();
                    factPredicates = parseFactList();                                                // parse FactList
                }
                else {
                    throw parseTokens[tokenIndex];
                }

                
            }
            else {
                throw parseTokens[tokenIndex];
            }
            
            if (parseTokens[tokenIndex]->getTokenType() == "RULES") {           
                incrementIndex();
                if (parseTokens[tokenIndex]->getTokenType() == "COLON") {
                    incrementIndex();
                    rules = parseRuleList();                                                // parse Rule
                }
                else {
                    
                    throw parseTokens[tokenIndex];
                }
            }
            else {
                throw parseTokens[tokenIndex];
            }
            
            if (parseTokens[tokenIndex]->getTokenType() == "QUERIES") {         // parse Query
                incrementIndex();
                if (parseTokens[tokenIndex]->getTokenType() != "COLON") {
                    throw parseTokens[tokenIndex];
                }
                incrementIndex();
                if (parseTokens[tokenIndex]->getTokenType() == "ID") {
                    string idString;
                    
                    idString = parseTokens[tokenIndex]->getTokenInput();
                    incrementIndex();
                    Predicate queryPredicateObject(idString, parseQuery()); 
                    queryPredicates.push_back(queryPredicateObject);
                }
                
            }
            else {
                throw parseTokens[tokenIndex];
            }

            if (parseTokens[tokenIndex]->getTokenType() == "ID") {
                vector<Predicate> newQueryPredicates;
                newQueryPredicates = parseQueryList();
                for (unsigned int i = 0; i < newQueryPredicates.size(); ++i) {
                    queryPredicates.push_back(newQueryPredicates.at(i));
                }
            }
            
            if (parseTokens[tokenIndex]->getTokenType() != "EOF") {
                throw parseTokens[tokenIndex];
            }
            passedGrammar = true;
            //cout << "Success!" << endl;
            

            
        }
        
        catch (Token* token) {
            cout << "Failure!" << endl;
            cout << "  " << token->toString() << endl;
            
            
        }
        Datalog datalogObject(schemePredicates, factPredicates, queryPredicates, rules);
        
        return datalogObject;

        
    }
    
    void incrementIndex() {
        if (tokenIndex < parseTokens.size()) {
            ++tokenIndex;
        }
    }
    
public:
    Parser() {}

    Datalog parse(vector <Token*> tokens) {
        Datalog datalogObject;
        for (unsigned int i = 0; i < tokens.size(); ++i) {
            parseTokens.push_back(tokens[i]);
        }
        
        tokenIndex = 0;
        datalogObject = parseDatalogProgram();
        /*if (passedGrammar == true) {
            cout << datalogObject.toString();
        }*/
        
        return datalogObject;
    }

};






#endif //LAB1_236_PARSER_H
