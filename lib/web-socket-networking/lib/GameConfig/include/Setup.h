#pragma once

#include "../../VarPool/include/VarPool.h"
#include <iostream>

class Setup:public VarPool{
    public:
    //name this the variable name to save
    //multiple choice takes in a vector 
    //the first value of the vector is the question
    //later are the choices
    using question_answer = std::pair<std::string,std::string>;
    using multiple_choice = std::pair<std::string,std::vector<std::string>>;

    void addQuestion(const std::string& name, const std::string& question){
        questions.push_back({name,question});
    }

    void addMultipleChoice(const std::string& name, const std::vector<std::string>& choices){
        m_choices.push_back({name,choices});
    }

    void getQuestionAnswers(){

        for(auto& q:questions){

            std::cout<<q.second<<std::endl;
            std::string inp;

            std::cin>>inp;

            addVar(q.first,inp);
        }
    }
    void getMultipleChoiceAnswer(){
        unsigned i = 0;
        for(auto& ch:m_choices){

            std::cout<<ch.second[0]<<std::endl;
            for(size_t i=1;i<ch.second.size();i++){
                std::cout<<i<<". "<<ch.second[i]<<std::endl;
            }
            int option;
            std::cin>>option;

            addVar(ch.first,ch.second[i]);
            ++i;
        }
    }

    private:
        std::vector<question_answer> questions;
        std::vector<multiple_choice> m_choices;
};