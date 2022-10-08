#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wordexp.h>
#include "wildcard.h"


char *fixWildcard(char *str){
  char **w;
  wordexp_t p;
  if( strchr (str, '*') != NULL || strchr (str, '?') != NULL){
    if(wordexp(str, &p, 0) == 0 ){
        w = p.we_wordv;
         return w[0];
    }
  }
  else{
    return str;
  }
  wordfree(&p);
}


char **fixSingleWildcardArg(char *str){
  wordexp_t p;

  if(wordexp(str, &p, 0) == 0 ){
    return p.we_wordv;
  }
}
