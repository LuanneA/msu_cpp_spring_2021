#pragma once
#include <iostream>
#include <sstream>
using namespace std;

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer{
    public:
        explicit Serializer(ostream& out):out_(out) {};

        template <class T>
        Error save(T& object){
            return object.serialize(*this);
        }

        template <class ... ArgsT>
        Error operator()(ArgsT && ... args){
            return process(forward<ArgsT>(args)...);
        }
        Error process1(bool arg){
            if (arg == true){
                out_ << "true";
            }
            else{
                out_ << "false";
            }
            return Error::NoError;
        }

        Error process1(uint64_t arg){
            out_ << arg;
            return Error::NoError;
        }

        template <class T>
        Error process1(T arg){
            return Error::CorruptedArchive;
        }

        template<class T, class ... ArgsT>
        Error process(T && Arg1, ArgsT... args){
            Error err = process1(Arg1);
            if (err == Error::NoError){
                out_ << Separator;
                return process(args...);
            }
            return err;
        }

        template<class T>
        Error process(T && Arg){
            return process1(Arg);
        }


    private:
        static constexpr char Separator = ' ';
        ostream& out_;
};

class Deserializer{
    public:
        explicit Deserializer(istream& in):in_(in) {};


        template <class T>
        Error load(T& object){
            return object.deserialize(*this);
        }

        template <class ... ArgsT>
        Error operator()(ArgsT && ... args){
               return process(forward<ArgsT>(args)...);
        }

        template <class T>
        Error process2(T arg){
            return Error::CorruptedArchive;
        }

        template<class T, class ... ArgsT>
        Error process(T && Arg1, ArgsT&&... args){
            Error err = process2(Arg1);
            if (err ==  Error::NoError){
                return process(args...);
            }
            return err;
        }

        template<class T>
        Error process(T& Arg){
            return process2(Arg);
        }


        Error process2(bool &value){
            string text;
            in_ >> text;
            if (text == "true")
                value = true;
            else if (text == "false")
                value = false;
            else
                return Error::CorruptedArchive;
            return Error::NoError;
        }

        Error process2(uint64_t &value){
            string text;
            in_ >> text;
            try{
                value = stoull(text);
                return Error::NoError;
            }
            catch(Error & err){
                   return Error::CorruptedArchive;
            }
        }
    private:
        static constexpr char Separator = ' ';
        istream& in_;
};

