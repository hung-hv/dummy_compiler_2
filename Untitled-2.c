#include "parser.h"

uint8_t parser_check_token (ParserToken* parser_token, TokenType kind) {
    if (parser_token->cur_token->kind == kind) {
        return 1;
    }
    return 0;
}

uint8_t parser_peek_token (ParserToken* parser_token, TokenType kind) {
    if (parser_token->pek_token->kind == kind) {
        return 1;
    }
    return 0;
}

uint8_t parser_match (ParserToken* parser_token, Lexer* code, TokenType kind) {
    uint8_t return_val = 0;
    if (parser_check_token(parser_token, kind) == 0) {
        printf("\n! NOT match token");
        return_val = 0;
    } else {
        return_val = 1;
    }
    parser_next_token(parser_token, code);
    return return_val;

}

void parser_next_token (ParserToken* parser_token, Lexer* code) {
    Token* lexer_token = (Token*)malloc(sizeof(Token));
    parser_token->cur_token = parser_token->pek_token;
    lexer_token = get_token(code);
    parser_token->pek_token = lexer_token->kind;
    if (0) {
        printf("\nToken Lexer: %-10s", token2string(lexer_token->kind));
        printf("\nToken Current: %-10s", token2string(parser_token->cur_token));
        printf("\nToken Peek: %-10s\n", token2string(parser_token->pek_token));
    }
    
}

void parser_program (ParserToken* parser_token, Lexer* code) {
    /*init*/
    parser_next_token(parser_token, code);
    parser_next_token(parser_token, code);

    
    printf("\nPROGRAM");
    /*parser all the statements in the programs*/
    while (!parser_check_token(parser_token, EOF_t)) {
        parser_statement(parser_token, code);
    }
    // parser_statement(parser_token, code);
    // parser_statement(parser_token, code);
    // parser_statement(parser_token, code);

}

void parser_statement (ParserToken* parser_token, Lexer* code) {
    /*check the first token: what is statement*/
    /* statement ::= "PRINT" (expression | string) nl */
    if (parser_check_token(parser_token, PRINT)) {
        printf("\nSTATEMENT - PRINT");
        parser_next_token(parser_token, code);
        if (parser_check_token(parser_token, STRING)) {
            parser_next_token(parser_token, code);
        } else {
            // parser_expression();
        }
    } 
    /*"IF" comparison "THEN" nl {statement} "ENDIF" nl*/
    else if (parser_check_token(parser_token, IF)) {
        printf("\nSTATEMENT - IF");
        parser_next_token(parser_token, code);
        //comparison()
        parser_match (parser_token, code, THEN);
        parser_nl(parser_token, code);
        /* 0 or more than 1 statement in body*/
        while (!parser_check_token(parser_token, ENDIF)) {
            parser_statement(parser_token, code);
        }
        parser_match(parser_token, code, ENDIF);
    }
    /*"WHILE" comparison "REPEAT" nl {statement nl} "ENDWHILE" nl*/
    else if (parser_check_token(parser_token, WHILE)) {
        printf("\nSTATEMENT - WHILE");
        parser_next_token(parser_token, code);
        //comparison()
        parser_match (parser_token, code, REPEAT);
        parser_nl(parser_token, code);
        /* 0 or more than 1 statement in body*/
        while (!parser_check_token(parser_token, ENDWHILE)) {
            parser_statement(parser_token, code);
        }
        parser_match(parser_token, code, ENDWHILE);
    }

    parser_nl(parser_token, code);
}

void parser_comparison (ParserToken* parser_token, Lexer* code) {
    
}

uint8_t IsComparisonOperator (ParserToken* parser_token, Lexer* code) {
    if (parser_check_token(parser_token, EQEQ)   
    ||  parser_check_token(parser_token, NOTEQ)     
    ||  parser_check_token(parser_token, LT)        
    ||  parser_check_token(parser_token, LTEQ)      
    ||  parser_check_token(parser_token, GTEQ)     
    ||  parser_check_token(parser_token, GTEQ)) {
        return 1; 
    }
    return 0;
}

void unary (ParserToken* parser_token, Lexer* code) {
    /* unary ::= ["+" | "-"] primary */
    printf("\nUNARY");

    if (parser_check_token(parser_token, PLUS) 
    || parser_check_token(parser_token, MINUS)) {
        parser_next_token(parser_token, code);
    }
    primary(parser_token, code);

}

void primary (ParserToken* parser_token, Lexer* code) {
    printf("\nPRIMARY");
    if (parser_check_token(parser_token, NUMBER)) {
        parser_next_token(parser_token, code);
    } else if (parser_check_token(parser_token, IDENT)) {
        parser_next_token(parser_token, code);
    } else {
        printf("\n>>ERROR!!!");
        return 0;
    }
    
}

void parser_nl (ParserToken* parser_token, Lexer* code) {
    printf("\nNEWLINE");
    parser_match (parser_token, code, NEWLINE);
    while (parser_check_token(parser_token, NEWLINE)) {
        parser_next_token(parser_token, code);
    }
    
}