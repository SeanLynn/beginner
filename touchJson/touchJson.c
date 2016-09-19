#include "touchJson.h"
#include <assert.h>
#include <stdlib.h> //NULL

#define EXPECT(c, ch) do { assert(*c->json == (ch)); c->json++; } while(0)

touch_type touch_get_type(const touch_value* v)
{
    assert(v != NULL);
    return v->type;
}

/* ws = *(%x20 / %x09 / %x0A / %x0D) */
static void touch_parse_whitespace(touch_context* c) {
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

/* null  = "null" */
static int touch_parse_null(touch_context* c, touch_value* v) {
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return TOUCH_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = TOUCH_NULL;
    return TOUCH_PARSE_OK;
}

static int touch_parse_ture(touch_context* c,touch_value* v){
    EXPECT(c, 't');
    if(c->json[0] != 'r' || c->json[1]!='u' || c->json[2] != 'e')
        return TOUCH_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = TOUCH_TRUE;
    return TOUCH_PARSE_OK;
}

static int touch_parse_false(touch_context* c, touch_value* v){
    EXPECT(c, 'f');
    if(c->json[0]!='a' || c->json[1]!='l' || c->json[2]!='s' || c->json[3]!='e')
        return TOUCH_PARSE_INVALID_VALUE;
    c->json += 4;
    v->type = TOUCH_FALSE;
    return TOUCH_PARSE_OK;
}

/* value = null / false / true */
static int touch_parse_value(touch_context* c, touch_value* v) {
    switch (*c->json) {
        case 't': return touch_parse_ture(c, v);
        case 'f': return touch_parse_false(c, v);
        case 'n':  return touch_parse_null(c, v);
        case '\0': return TOUCH_PARSE_EXPECT_VALUE;
        default:   return TOUCH_PARSE_INVALID_VALUE;
    }
}
int touch_parse(touch_value* v, const char* json)
{
    touch_context c;
    int ret;
    assert(v!=NULL);
    c.json = json;
    v->type = TOUCH_NULL;
    touch_parse_whitespace(&c);
    if((ret = touch_parse_value(&c, v)) == TOUCH_PARSE_OK){
        touch_parse_whitespace(&c);
        if(*c.json != '\0'){
            v->type = TOUCH_NULL;
            ret = TOUCH_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    return ret;
}