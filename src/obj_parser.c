#include <stdio.h>

enum token_kind {
    TOKEN_EOF,
    TOKEN_EOL,
    TOKEN_NUM,
    TOKEN_VERTEX,
    TOKEN_TEXTURE_COORD,
    TOKEN_NORMAL,
    TOKEN_FACE,
    TOKEN_COMMENT,
};

struct token {
    enum token_kind kind;
    
};

struct stream {
    char *chars;
    struct token token;
};

void next_token(struct stream *stream)
{
    while (*stream->chars == ' ') {
        stream->chars++;
    }
    switch (*stream->chars) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            //NUM
            stream->token.kind = TOKEN_NUM;
            stream->chars++;
            break;
        case 'f':
            stream->token.kind = TOKEN_FACE;
            stream->chars++;
            break;
        case 'v':
            stream->token.kind = TOKEN_VERTEX;
            stream->chars++;
            break;
        case '#':
            stream->token.kind = TOKEN_COMMENT;
            while (*stream->chars++ != '\n');
            break;
        case '\n':
            stream->token.kind = TOKEN_EOL;
            *stream->chars++;
            break;
        default:
            stream->token.kind = 0;
            stream->chars++;
            //UNKNOWN
            break;
    }
}

struct obj_parser {
    struct stream stream;
};

void init_obj_parser(struct obj_parser *parser, const char *obj_source)
{
    parser->stream.chars = obj_source;
}

enum obj_element_type {
    OBJ_PARSE_UNKNOWN,
    OBJ_PARSE_VERTEX,
    OBJ_PARSE_END,
};

struct obj_element {
    enum obj_element_type type;
};

struct obj_element next_element(struct obj_parser *parser)
{
    struct obj_element e = {};
    next_token(&parser->stream);
    switch (parser->stream.token.kind) {
    case TOKEN_EOF:
        e.type = OBJ_PARSE_END;
        break;
    default:
        e.type = OBJ_PARSE_UNKNOWN;
        break;
    }
    return e;
}

int main(int argc, char **argv)
{
    FILE *f = fopen("/home/trent/code/3d-sandbox/assets/bunny.obj", "r");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);
    string[fsize] = 0;

    struct obj_parser parser = {};
    init_obj_parser(&parser, string);
    struct obj_element e = {};
    do {
        e = next_element(&parser);
        switch (e.type) {
        default:
            printf("UNKNOWN OBJ ELEMENT\n");
            break;
        }
    } while (e.type != OBJ_PARSE_END);

    return 0;
}

