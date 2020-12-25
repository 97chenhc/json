//
// Created by 陈弘超 on 2020/12/24.
//
#include "json.h"

#define EXCEPT(p, ch) do { assert(*p == (ch)); p++; } while(0)

using namespace json;

void Value::parse_whitespace() {
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') p++;
}

Error Value::parse_literal(Type literal_type, const string &literal) {
    EXCEPT(p, literal[0]);
    for (int i = 1; i < literal.size(); i++) {
        if (p[i-1] != literal[i]) {
            return PARSE_INVALID_VALUE;
        }
    }
    p += literal.size() - 1;
    type = literal_type;
    return PARSE_OK;
}

Error Value::parse_number() {

}

Error Value::parse_value() {
    switch (*p) {
        case 'n':  return parse_literal(NUL, "null");
        case 'f':  return parse_literal(FALSE, "false");
        case 't':  return parse_literal(TRUE, "true");
        default :  return parse_number();
        case'\0':  return PARSE_EXPECT_VALUE;
    }
}

Error Value::parse(const char* json) {
    p = json;
    this->type = NUL;
    parse_whitespace();
    Error err;
    if ((err = parse_value()) == PARSE_OK) {
        parse_whitespace();
        if (*p != '\0') err = PARSE_ROOT_NOT_SINGULAR;
    }
    return err;
}

Type Value::get_type() {
    return type;
}

double Value::get_number() {
    return n;
}
