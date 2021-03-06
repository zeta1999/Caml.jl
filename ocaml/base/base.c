#include <caml/mlvalues.h>
#include <caml/callback.h>
#include <caml/alloc.h>
#include <caml/memory.h>

#include <stdio.h>

#define Alloc_return(res) ({\
  value *allocated = malloc(sizeof(value));\
  *allocated = (res);\
  caml_register_generational_global_root(allocated);\
  return allocated;\
})

void dummy_base() { return; }

void caml_release(value *obj) {
  caml_remove_generational_global_root(obj);
  free(obj);
}

long caml_to_long(value *v) { return Long_val(*v); }

int caml_to_bool(value *v) { return Bool_val(*v); }

const char* caml_to_string(value *v) { return String_val(*v); }

value* caml_of_long(long x) { Alloc_return(Val_long(x)); }

value* caml_of_bool(int x) { Alloc_return(Val_bool(x)); }

value* caml_of_string(char *str) { Alloc_return(caml_copy_string(str)); }

value* caml_make_unit() { Alloc_return(Val_unit); }