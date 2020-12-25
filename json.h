//
// Created by 陈弘超 on 2020/12/24.
//
#ifndef JSON_JSON_H
#define JSON_JSON_H

#include <cassert>
#include <string>
#include <cstdlib>
#include <errno.h>   /* errno, ERANGE */
#include <math.h>    /* HUGE_VAL */

using std::string;


namespace json {

    enum Type { NUL, FALSE, TRUE, NUMBER, STRING, ARRAR, OBJECT };
    enum Error {
        PARSE_OK = 0,
        PARSE_EXPECT_VALUE,
        PARSE_INVALID_VALUE,
        PARSE_ROOT_NOT_SINGULAR,
        PARSE_NUMBER_TOO_BIG
    };

    class Value{
    public:
        void parse_whitespace();
        Error parse_value();
        Error parse_number();
        Error parse_literal(Type, const string &);
        Error parse(const char* json);
        Type get_type();
        double get_number();

        Type type;

    private:
        double n;
        const char *p;
    };

};

#endif //JSON_JSON_H
