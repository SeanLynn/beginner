#pragma once
//JSON data type
typedef enum{ TOUCH_NULL,
              TOUCH_FALSE,
              TOUCH_TRUE,
              TOUCH_NUMBER,
              TOUCH_STRING,
              TOUCH_ARRAY,
              TOUCH_OBJECT
            } touch_type;

//JSON value
typedef struct{
    touch_type type;
}touch_value;

//context
typedef struct{
  const char* json;
}touch_context;

//return value for touch_parse()
enum {
	TOUCH_PARSE_OK = 0,
	TOUCH_PARSE_EXPECT_VALUE,
	TOUCH_PARSE_INVALID_VALUE,
	TOUCH_PARSE_ROOT_NOT_SINGULAR
};

//use to parse JSON
int touch_parse(touch_value* v, const char* json);

//access the result of the touch_value
touch_type touch_get_type(const touch_value* v);